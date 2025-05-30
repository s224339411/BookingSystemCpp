#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
#include <vector>
#include <string>
#include <QUuid>
#include "user.h"
#include "datasource.h"
#include "room.h"
#include "roomtype.h"
#include "globals.h"

using std::string;
using std::vector;

QJsonObject load_json_object_from_file(const QString& file_path){
    QJsonObject root;
    QFile file(file_path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file:" << file.errorString();
        return root;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);

    if (error.error != QJsonParseError::NoError) {
        qWarning() << "JSON parse error:" << error.errorString();
        return root;
    }

    if (!doc.isObject()) {
        qWarning() << "Expected a JSON object";
        return root;
    }

    root = doc.object();

    return root;
}

room find_room_by_guid(vector<room> rooms, const string guid){
    for (int i = 0; i < rooms.size(); ++i) {
        if(rooms[i].guid == guid){
            return rooms[i];
        }
    }

    return {};
}

user load_user_from_json(){
    const QString& file_path = CONFIG_FILE_PATH;
    user user;

    QJsonObject root = load_json_object_from_file(file_path);

    if (!root.isEmpty() && root.contains("datasource") && root["datasource"].isObject()) {
        QJsonObject datasource = root["datasource"].toObject();

        if (datasource.contains("login") && datasource["login"].isObject()) {
            QJsonObject login = datasource["login"].toObject();

            QString user_name = login["user"].toString();
            QString password = login["password"].toString();

            user.name = user_name.toStdString();
            user.password = password.toStdString();

        } else {
            qWarning() << "Missing 'login' object.";
        }
    } else {
        qWarning() << "Missing 'datasource' object.";
    }


    return user;
}

vector<room> load_rooms_from_json(){
    const QString& file_path = CONFIG_FILE_PATH;
    vector<room> rooms;

    QJsonObject root = load_json_object_from_file(file_path);

    if (!root.isEmpty() && root.contains("datasource") && root["datasource"].isObject()) {
        QJsonObject datasource = root["datasource"].toObject();

        QJsonArray room_array = datasource.value("rooms").toArray();

        for (const QJsonValue &val : std::as_const(room_array)) {
            QJsonObject obj = val.toObject();

            room r;
            r.guid = obj["guid"].toString().toStdString();
            r.name = obj["name"].toString().toStdString();
            r.number = obj["number"].toInt();
            r.type = static_cast<room_type>(obj["type"].toInt());
            r.private_bathroom = obj["private_bathroom"].toBool();
            r.daily_rate = obj["daily_rate"].toDouble();
            r.maximum_guests = obj["maximum_guests"].toInt();

            rooms.push_back(r);
        }

    } else {
        qWarning() << "Missing 'datasource' object.";
    }

    return rooms;
}

bool save_booking_to_json(booking booking){

    const QString& file_path = CONFIG_FILE_PATH;
    QFile file(file_path);

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Cannot open file for reading";
        return false;
    }

    QByteArray json_data = file.readAll();
    file.close();

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(json_data, &error);
    if (error.error != QJsonParseError::NoError) {
        qWarning() << "JSON parse error:" << error.errorString();
        return false;
    }

    QJsonObject root = doc.object();
    QJsonObject datasource = root["datasource"].toObject();

    QJsonArray bookings = datasource["bookings"].toArray();

    // 🔹 Create a new booking object
    QJsonObject new_booking;
    QJsonObject new_room;

    new_booking["guid"] = QUuid::createUuid().toString().replace("{","").replace("}","");
    new_booking["guest_name"] = QString::fromStdString(booking.guest_name);
    new_booking["check_in_date"] = booking.check_in_date.toString("dd/MM/yyyy");
    new_booking["check_out_date"] = booking.check_out_date.toString("dd/MM/yyyy");
    new_booking["guests_number"] = booking.guests_number;

    new_room["guid"] = QString::fromStdString(booking.room.guid);
    new_booking["room"] = new_room;

    bookings.append(new_booking);
    datasource["bookings"] = bookings;
    root["datasource"] = datasource;

    // 🔹 Write back to file
    doc.setObject(root);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Cannot open file for writing";
        return false;
    }
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();

    qDebug() << "Booking added successfully.";
    return true;
}

vector<booking> load_booking_from_json(){
    const QString& file_path = CONFIG_FILE_PATH;
    vector<booking> bookings;
    vector<room> rooms = load_rooms_from_json();

    QJsonObject root = load_json_object_from_file(file_path);

    if (!root.isEmpty() && root.contains("datasource") && root["datasource"].isObject()) {
        QJsonObject datasource = root["datasource"].toObject();

        QJsonArray bookings_array = datasource.value("bookings").toArray();

        for (const QJsonValue &val : std::as_const(bookings_array)) {
            QJsonObject obj = val.toObject();

            booking b;
            b.guid = obj["guid"].toString().toStdString();
            b.check_in_date = QDate::fromString(obj["check_in_date"].toString(), "dd/MM/yyyy");
            b.check_out_date = QDate::fromString(obj["check_out_date"].toString(), "dd/MM/yyyy");
            b.guest_name = obj["guest_name"].toString().toStdString();
            b.guests_number = obj["guests_number"].toInt();

            QJsonObject room = obj["room"].toObject();
            struct room r = find_room_by_guid(rooms,room["guid"].toString().toStdString());

            //Calculate costs related to booking
            int days_between = b.check_in_date.daysTo(b.check_out_date);
            b.daily_cost = r.daily_rate;
            b.total_cost = days_between *r.daily_rate;

            b.room = r;

            bookings.push_back(b);
        }



    } else {
        qWarning() << "Missing 'datasource' object.";
    }

    return bookings;

}

bool update_booking_by_guid_to_json(booking new_booking){
    const QString& file_path = CONFIG_FILE_PATH;

    // 1. Read the JSON file
    QFile file(file_path);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Couldn't open file for reading";
        return false;
    }

    QByteArray json_data = file.readAll();
    file.close();

    // 2. Parse the JSON
    QJsonDocument doc = QJsonDocument::fromJson(json_data);
    if (doc.isNull()) {
        qWarning() << "Failed to parse JSON";
        return false;
    }

    QJsonObject root_obj = doc.object();
    QJsonObject datasource = root_obj["datasource"].toObject();
    QJsonArray bookings = datasource["bookings"].toArray();

    // 3. Find and update the booking
    bool found = false;
    for (int i = 0; i < bookings.size(); ++i) {
        QJsonObject booking = bookings[i].toObject();

        if (booking["guid"].toString() == new_booking.guid) {
            // Update the specific fields
            booking["guest_name"] = QString::fromStdString(new_booking.guest_name);
            booking["guests_number"] = new_booking.guests_number;

            bookings[i] = booking;
            found = true;
            break;
        }
    }

    if (!found) {
        qWarning() << "Booking with GUID" << new_booking.guid << "not found";
        return false;
    }

    // 4. Save the updated JSON
    datasource["bookings"] = bookings;
    root_obj["datasource"] = datasource;
    doc.setObject(root_obj);

    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Couldn't open file for writing";
        return false;
    }

    file.write(doc.toJson(QJsonDocument::Indented)); // Keep formatted JSON
    file.close();

    return true;
}

bool delete_booking_by_guid_to_json(string guid){

    const QString& file_path = CONFIG_FILE_PATH;

    // 1. Read the JSON file
    QFile file(file_path);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Couldn't open file for reading";
        return false;
    }

    QByteArray json_data = file.readAll();
    file.close();

    // 2. Parse the JSON
    QJsonDocument doc = QJsonDocument::fromJson(json_data);
    if (doc.isNull()) {
        qWarning() << "Failed to parse JSON";
        return false;
    }

    QJsonObject root_obj = doc.object();
    QJsonObject datasource = root_obj["datasource"].toObject();
    QJsonArray bookings = datasource["bookings"].toArray();

    // 3. Find and remove the booking
    bool found = false;
    QJsonArray updated_bookings;

    for (const QJsonValue &bookingValue : bookings) {
        QJsonObject booking = bookingValue.toObject();
        if (booking["guid"].toString() != guid) {
            updated_bookings.append(booking);
        } else {
            found = true;
        }
    }

    if (!found) {
        qWarning() << "Booking with GUID" << guid << "not found";
        return false;
    }

    // 4. Save the updated JSON
    datasource["bookings"] = updated_bookings;
    root_obj["datasource"] = datasource;
    doc.setObject(root_obj);

    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Couldn't open file for writing";
        return false;
    }

    file.write(doc.toJson(QJsonDocument::Indented)); // Keep formatted JSON
    file.close();

    return true;
}
