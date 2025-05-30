#ifndef DIALOGBOOKINGLISTTODAY_H
#define DIALOGBOOKINGLISTTODAY_H

#include <QDialog>

namespace Ui {
class DialogBookingListToday;
}

class DialogBookingListToday : public QDialog
{
    Q_OBJECT

public:
    explicit DialogBookingListToday(QWidget *parent = nullptr);
    ~DialogBookingListToday();

private:
    Ui::DialogBookingListToday *ui;
};

#endif // DIALOGBOOKINGLISTTODAY_H
