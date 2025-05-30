#ifndef DIALOGBOOKINGCANCEL_H
#define DIALOGBOOKINGCANCEL_H

#include "datasource.h"
#include <QDialog>

namespace Ui {
class DialogBookingCancel;
}

class DialogBookingCancel : public QDialog
{
    Q_OBJECT

public:
    explicit DialogBookingCancel(QWidget *parent = nullptr);
    ~DialogBookingCancel();

private slots:
    void on_btnCancel_clicked();

    void on_btnFindGuest_clicked();

    void on_btnCancelBooking_clicked();
    void clean_form();

private:
    Ui::DialogBookingCancel *ui;
    struct booking booking;
};

#endif // DIALOGBOOKINGCANCEL_H
