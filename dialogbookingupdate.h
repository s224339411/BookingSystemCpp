#ifndef DIALOGBOOKINGUPDATE_H
#define DIALOGBOOKINGUPDATE_H

#include "datasource.h"
#include <QDialog>
#include <string>
using std::string;

namespace Ui {
class DialogBookingUpdate;
}

class DialogBookingUpdate : public QDialog
{
    Q_OBJECT

public:
    explicit DialogBookingUpdate(QWidget *parent = nullptr);
    ~DialogBookingUpdate();

private slots:
    bool is_valid_form();
    void on_btnFindGuest_clicked();
    void on_btnCancel_clicked();
    void clean_form();
    void on_btnUpdateBooking_clicked();

private:
    Ui::DialogBookingUpdate *ui;
    struct booking booking;
};

#endif // DIALOGBOOKINGUPDATE_H
