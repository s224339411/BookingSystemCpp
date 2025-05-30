#ifndef DIALOGBOOKINGADD_H
#define DIALOGBOOKINGADD_H

#include "datasource.h"
#include <QDialog>

namespace Ui {
class DialogBookingAdd;
}

class DialogBookingAdd : public QDialog
{
    Q_OBJECT

public:
    explicit DialogBookingAdd(QWidget *parent = nullptr);
    ~DialogBookingAdd();

private slots:
    bool is_form_valid();

    bool is_valid_booking();

    vector<booking> get_room_bookings(vector<booking> booking, string room_guid);

    void on_btnCancel_clicked();

    void on_btnAccept_clicked();

    void on_btnRoomInfo_clicked();

private:
    Ui::DialogBookingAdd *ui;

};

#endif // DIALOGBOOKINGADD_H
