#include "dialogbookingcancel.h"
#include "ui_dialogbookingcancel.h"
#include <QMessageBox>

DialogBookingCancel::DialogBookingCancel(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogBookingCancel)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
}

DialogBookingCancel::~DialogBookingCancel()
{
    delete ui;
}

void DialogBookingCancel::on_btnCancel_clicked()
{
    this->close();
}

void DialogBookingCancel::clean_form(){
    ui->txtCheckIn->setText("");
    ui->txtCheckOut->setText("");
    ui->txtGuestName->setText("");
    ui->txtGuestNumber->setText("");
    ui->txtRoom->setText("");
}

void DialogBookingCancel::on_btnFindGuest_clicked()
{
    vector<struct booking> bookings = load_booking_from_json();
    this->clean_form();
    this->booking.guid = "";

    //Find booking by guesy name
    for (int i = 0; i < bookings.size(); ++i) {
        if(ui->txtGuestNameFind->text().compare(QString::fromStdString(bookings[i].guest_name),Qt::CaseInsensitive) == 0 &&
            bookings[i].check_in_date>=QDate::currentDate()){
            this->booking = bookings[i];
            break;
        }
    }

    if(this->booking.guid!=""){
        this->ui->txtCheckIn->setText(this->booking.check_in_date.toString("dd/MM/yyyy"));
        this->ui->txtCheckOut->setText(this->booking.check_out_date.toString("dd/MM/yyyy"));
        this->ui->txtRoom->setText(QString::fromStdString(this->booking.room.name));
        this->ui->txtGuestName->setText(QString::fromStdString(this->booking.guest_name));
        this->ui->txtGuestNumber->setText(QString::number(this->booking.guests_number));
    }
    else{
        QMessageBox::critical(this,"Error","Booking not found");
    }
}


void DialogBookingCancel::on_btnCancelBooking_clicked()
{
    // Create confirmation dialog
    QMessageBox::StandardButton confirm_delete;
    confirm_delete = QMessageBox::question(nullptr, "Confirm Cacenlation",
                                          "Are you sure you want to cancel this booking?",
                                          QMessageBox::Yes|QMessageBox::No);

    if (confirm_delete == QMessageBox::Yes) {
        if (delete_booking_by_guid_to_json(booking.guid)) {
            this->close();
            QMessageBox::information(nullptr, "Success",
                                     "Booking cancelled successfully!");
        } else {
            QMessageBox::warning(nullptr, "Error",
                                 "Failed to delete booking!");

        }
    }
}

