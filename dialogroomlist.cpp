#include "dialogroomlist.h"
#include "ui_dialogroomlist.h"
#include "room.h"//;
#include "datasource.h"
#include <QDebug>
#include <QString>
#include <vector>
#include "utilities.h"

using std::to_string;
using std::vector;

DialogRoomList::DialogRoomList(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogRoomList)

{
    ui->setupUi(this);
    this->setFixedSize(this->size());

    rooms = load_rooms_from_json();

    qDebug() << "Rooms: " << rooms.size();

    ui->tableWidget->setRowCount(rooms.size());

    for (int i = 0; i < rooms.size(); ++i) {

        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(rooms[i].name)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(to_string(rooms[i].number))));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(room_type_to_string(rooms[i].type))));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem((rooms[i].private_bathroom?"Yes":"No")));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(decimal_to_string(rooms[i].daily_rate,2))));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString::fromStdString(to_string(rooms[i].maximum_guests))));

    }

}

DialogRoomList::~DialogRoomList()
{
    delete ui;
}
