#include "dialogbookinglisttoday.h"
#include "datasource.h"
#include "ui_dialogbookinglisttoday.h"

DialogBookingListToday::DialogBookingListToday(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogBookingListToday)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());

    vector<booking> bookings =  load_booking_from_json(); //retrieve all bookings
    QDate today_date = QDate::currentDate();

    //Populate table with data
    ui->tableBooking->setRowCount(bookings.size());
    for (int i = 0; i < bookings.size(); ++i) {
        if(bookings[i].check_in_date == today_date){
            ui->tableBooking->setItem(i,0, new QTableWidgetItem(bookings[i].check_in_date.toString("dd/MM/yyyy")));
            ui->tableBooking->setItem(i,1, new QTableWidgetItem(bookings[i].check_out_date.toString("dd/MM/yyyy")));
            ui->tableBooking->setItem(i,2, new QTableWidgetItem(QString::fromStdString(bookings[i].guest_name)));
            ui->tableBooking->setItem(i,3, new QTableWidgetItem(QString::number(bookings[i].guests_number)));
            ui->tableBooking->setItem(i,4, new QTableWidgetItem(QString::fromStdString(bookings[i].room.name)));
            ui->tableBooking->setItem(i,5, new QTableWidgetItem("$" + QString::number(bookings[i].daily_cost,'f',2)));
            ui->tableBooking->setItem(i,6, new QTableWidgetItem("$" + QString::number(bookings[i].total_cost,'f',2)));
        }

    }


}

DialogBookingListToday::~DialogBookingListToday()
{
    delete ui;
}
