#include "dialogbookingupdate.h"
#include "ui_dialogbookingupdate.h"
#include "utilities.h"
#include <QIntValidator>
#include <QMessageBox>

DialogBookingUpdate::DialogBookingUpdate(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogBookingUpdate)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());

    ui->txtGuestNumber->setValidator(new QIntValidator(0, 9999, this)); //set field to accept numeric value only

}

DialogBookingUpdate::~DialogBookingUpdate()
{
    delete ui;
}

bool DialogBookingUpdate::is_valid_form(){

    string validation_message = "";

    string guest_name = ui->txtGuestName->text().toStdString();

    if(trim_string(guest_name)== ""){
        validation_message += "* Enter a valid guest name \n";
    }

    string guest_number = ui->txtGuestNumber->text().toStdString();

    if(trim_string(guest_number)== ""){
        validation_message += "* Enter a valid guest number \n";
    }

    if(validation_message != ""){
        validation_message = "The following error(s) were found: \n" + validation_message;
        QMessageBox::critical(this,"Error",QString::fromStdString(validation_message));
        return false;
    }

    return true;
}
void DialogBookingUpdate::clean_form(){
    this->booking = {};
    this->ui->txtCheckIn->setText("");
    this->ui->txtCheckOut->setText("");
    this->ui->txtRoom->setText("");
    this->ui->txtGuestName->setText("");
    this->ui->txtGuestNumber->setText("");

}

void DialogBookingUpdate::on_btnFindGuest_clicked()
{
    vector<struct booking> bookings = load_booking_from_json();
    this->clean_form();
    this->booking.guid = "";

    //Find booking by guesy name
    for (int i = 0; i < bookings.size(); ++i) {
        if(ui->txtFindGuestName->text().compare(QString::fromStdString(bookings[i].guest_name),Qt::CaseInsensitive) == 0){
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


void DialogBookingUpdate::on_btnCancel_clicked()
{
    this->close();
}


void DialogBookingUpdate::on_btnUpdateBooking_clicked()
{
    if(is_valid_form()){
        this->booking.guest_name = ui->txtGuestName->text().toStdString();
        this->booking.guests_number = ui->txtGuestNumber->text().toInt();

        if(update_booking_by_guid_to_json(this->booking)){
            this->close();
            QMessageBox::information(this,"Success","Booking updated");
        }else{
            QMessageBox::critical(this,"Error","Error updating booking");
        }

    }
}

