#include "dialogbookinglistmonthly.h"
#include "datasource.h"
#include "ui_dialogbookinglistmonthly.h"
#include <QDate>

DialogBookingListMonthly::DialogBookingListMonthly(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogBookingListMonthly)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());


    // Get current date
    QDate current_date = QDate::currentDate();

    // Get year and month
    int year = current_date.year();
    int month = current_date.month();

    // Get number of days in this month
    days_of_month_number = current_date.daysInMonth();

    // List all days of the month
    for (int day = 1; day <= days_of_month_number; ++day) {
        days_of_month.push_back(QDate(year, month, day));
    }

    vector<booking> bookings =  load_booking_from_json(); //retrieve all bookings

    //Populate rows for table
    for (int i = 0; i < days_of_month.size(); ++i) {
        add_table_row(ui->tableBookings,days_of_month[i]);
        for (int j = 0; j < bookings.size(); ++j) {
            if(days_of_month[i] == bookings[j].check_in_date){
                add_table_row(ui->tableBookings,
                              bookings[j].check_in_date,
                              bookings[j].check_out_date,
                              QString::fromStdString(bookings[j].guest_name),
                              QString::number(bookings[j].guests_number),
                              QString::fromStdString(bookings[j].room.name),
                              "$" + QString::number(bookings[j].daily_cost,'f',2),
                              "$" + QString::number(bookings[j].total_cost,'f',2));
            }
        }
    }
}

DialogBookingListMonthly::~DialogBookingListMonthly()
{
    delete ui;
}

void DialogBookingListMonthly::add_table_row(QTableWidget *table,QDate &date){
    int row = table->rowCount();
    table->insertRow(row);

    table->setSpan(row, 0, 1, 8); // Merge 2 rows x 3 columns starting at (1,1)
    table->setItem(row, 0, new QTableWidgetItem(date.toString("dd/MM/yyyy")));
}

void DialogBookingListMonthly::add_table_row(QTableWidget *table,QDate &check_in_date,QDate &check_out_date,QString guest_name, QString guest_number, QString room,QString daily_cost,QString total_cost){
    int row = table->rowCount();
    table->insertRow(row);

    table->setItem(row, 1, new QTableWidgetItem(check_in_date.toString("dd/MM/yyyy")));
    table->setItem(row, 2, new QTableWidgetItem(check_out_date.toString("dd/MM/yyyy")));
    table->setItem(row, 3, new QTableWidgetItem(guest_name));
    table->setItem(row, 4, new QTableWidgetItem(guest_number));
    table->setItem(row, 5, new QTableWidgetItem(room));
    table->setItem(row, 6, new QTableWidgetItem(daily_cost));
    table->setItem(row, 7, new QTableWidgetItem(total_cost));
}
