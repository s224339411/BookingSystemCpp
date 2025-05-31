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
    for (int i = 0; i < bookings.size(); ++i) {
        if(bookings[i].check_in_date == today_date){

            add_table_row(ui->tableBooking,
                          bookings[i].check_in_date,
                          bookings[i].check_out_date,
                          QString::fromStdString(bookings[i].guest_name),
                          QString::number(bookings[i].guests_number),
                          QString::fromStdString(bookings[i].room.name),
                          "$" + QString::number(bookings[i].daily_cost,'f',2),
                          "$" + QString::number(bookings[i].total_cost,'f',2)
                          );
        }

    }


}

DialogBookingListToday::~DialogBookingListToday()
{
    delete ui;
}

void DialogBookingListToday::add_table_row(QTableWidget *table,QDate &check_in_date,QDate &check_out_date,QString guest_name, QString guest_number, QString room,QString daily_cost,QString total_cost){
    int row = table->rowCount();
    table->insertRow(row);

    table->setItem(row, 0, new QTableWidgetItem(check_in_date.toString("dd/MM/yyyy")));
    table->setItem(row, 1, new QTableWidgetItem(check_out_date.toString("dd/MM/yyyy")));
    table->setItem(row, 2, new QTableWidgetItem(guest_name));
    table->setItem(row, 3, new QTableWidgetItem(guest_number));
    table->setItem(row, 4, new QTableWidgetItem(room));
    table->setItem(row, 5, new QTableWidgetItem(daily_cost));
    table->setItem(row, 6, new QTableWidgetItem(total_cost));
}
