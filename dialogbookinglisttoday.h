#ifndef DIALOGBOOKINGLISTTODAY_H
#define DIALOGBOOKINGLISTTODAY_H

#include <QDialog>
#include <QtWidgets/qtablewidget.h>

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
    void add_table_row(QTableWidget *table,QDate &check_in_date,QDate &check_out_date,QString guest_name, QString guest_number, QString room,QString daily_cost,QString total_cost);
};

#endif // DIALOGBOOKINGLISTTODAY_H
