#include "dialogbookingadd.h"
#include "dialogroomlist.h"
#include "globals.h"
#include "datasource.h"
#include "ui_dialogbookingadd.h"
#include "utilities.h"

#include <QMessageBox>

using std::vector;
using std::to_string;

DialogBookingAdd::DialogBookingAdd(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogBookingAdd)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());

    vector<room> rooms = load_rooms_from_json();

    ui->cmbRooms->insertItem(0, "",QVariant(""));
    for (int i = 0; i < rooms.size(); ++i) {
        ui->cmbRooms->addItem(QString::fromStdString(rooms[i].name),QVariant(QString::fromStdString(rooms[i].guid)));
    }

    ui->txtGuestsNumber->setValidator(new QIntValidator(0, 9999, this)); //set field to accept numeric value only

    //set checkiut and checkout default and minimum dates to select
    QDate today = QDate::currentDate();
    QDate tomorrow = QDate::currentDate().addDays(1);
    ui->txtCheckIn->setMinimumDate(today);
    ui->txtCheckIn->setDate(today);
    ui->txtCheckOut->setMinimumDate(tomorrow);
    ui->txtCheckOut->setDate(tomorrow);

}

DialogBookingAdd::~DialogBookingAdd()
{
    delete ui;
}


void DialogBookingAdd::on_btnCancel_clicked()
{
    this->close();
}
/**
 * This function check that all fields have been populated
 * also check fields values are consistent to proceed
 */
bool DialogBookingAdd::is_form_valid(){

    string validation_message = "";
    string room_guid = ui->cmbRooms->itemData(ui->cmbRooms->currentIndex()).toString().toStdString(); //Obtain from room its guid by variant value

    if(room_guid == ""){
        validation_message += "* Select a valid room \n";
    }

    string guest_name = ui->txtGuestName->text().toStdString();

    if(trim_string(guest_name)== ""){
        validation_message += "* Enter a valid guest name \n";
    }

    string guest_number = ui->txtGuestsNumber->text().toStdString();

    if(trim_string(guest_number)== ""){
        validation_message += "* Enter a valid guest number \n";
    }

    if(ui->txtCheckOut->date()<=ui->txtCheckIn->date()){
        validation_message += "*Enter a Check-out date greater than Check-in date \n";
    }

    if(validation_message != ""){
        validation_message = "The following error(s) were found: \n" + validation_message;
        QMessageBox::critical(this,"Error",QString::fromStdString(validation_message));
        return false;
    }

    return true;
}

/**
 * @brief DialogBookingAdd::get_room_bookings
 * @param booking
 * @param room_guid
 * @return selected room bookings
 */
vector<booking> DialogBookingAdd::get_room_bookings(vector<booking> booking, string room_guid){
    vector<struct booking> temp_booking = {};

    for (int i = 0; i < booking.size(); ++i) {
        if(booking[i].room.guid == room_guid){
            temp_booking.push_back(booking[i]);
        }
    }
    booking = temp_booking;

    return booking;
}

/**
 * @brief DialogBookingAdd::is_valid_booking
 * @return wether booking is valid according to current records
 */
bool DialogBookingAdd::is_valid_booking(){
    string room_guid = ui->cmbRooms->itemData(ui->cmbRooms->currentIndex()).toString().toStdString();
    vector<booking> bookings = load_booking_from_json();
    vector<booking> room_bookings = get_room_bookings(bookings,room_guid);

    if(room_bookings.size()>0){
        QDate current_check_in_date = ui->txtCheckIn->date();
        QDate current_check_out_date = ui->txtCheckOut->date().addDays(-1);

        for (int i = 0; i < room_bookings.size(); ++i) {
            QDate check_in_date = room_bookings[i].check_in_date;
            QDate check_out_date = room_bookings[i].check_out_date;
            bool is_valid_booking = is_date_range_intersect(current_check_in_date,current_check_out_date,check_in_date,check_out_date);

            if(!is_valid_booking){
                return false;
            }
        }
    }


    return true;
}

void DialogBookingAdd::on_btnAccept_clicked()
{
    if(is_form_valid() ){ //check if all fields are populated and correct
        if(is_valid_booking()){ //check if room is not taken on selected dates

            string room_guid = ui->cmbRooms->itemData(ui->cmbRooms->currentIndex()).toString().toStdString();

            booking booking = {};
            booking.room = {};

            booking.room.guid = room_guid;
            booking.check_in_date = ui->txtCheckIn->date();
            booking.check_out_date = ui->txtCheckOut->date();
            booking.guest_name = ui->txtGuestName->text().toStdString();
            booking.guests_number = std::stoi(ui->txtGuestsNumber->text().toStdString());

            if(save_booking_to_json(booking)){
                this->close();
                QMessageBox::information(this,"Success","Booking saved");

            }else{
                QMessageBox::critical(this,"Error","Error saving booking");
            }

        }else{
            QMessageBox::critical(this,"Error","This booking cannot be done \n Room is not available on selected dates");
        }


    }
}


void DialogBookingAdd::on_btnRoomInfo_clicked()
{
    string room_guid = ui->cmbRooms->itemData(ui->cmbRooms->currentIndex()).toString().toStdString();
    if(!room_guid.empty()){
        vector<room> rooms = load_rooms_from_json();

        for (int i = 0; i < rooms.size(); ++i) {

            if(rooms[i].guid == room_guid){

                string room_info = "Name: " + rooms[i].name + "\n";
                room_info += "Number: " + to_string(rooms[i].number) + "\n";
                room_info += "Type: " + room_type_to_string(rooms[i].type) + "\n";
                room_info +=  "Private bathroom: ";
                room_info += (rooms[i].private_bathroom?"Yes":"No");
                room_info += "\n";
                room_info += "Daily Rate: " + decimal_to_string(rooms[i].daily_rate,2) + "\n";
                room_info +=  "Maximum guests: " + to_string(rooms[i].maximum_guests) + "\n";

                QMessageBox::information(this,"Room Information",QString::fromStdString(room_info));
                break;
            }

        }


    }

}

