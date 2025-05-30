#ifndef DIALOGBOOKINGLISTMONTHLY_H
#define DIALOGBOOKINGLISTMONTHLY_H

#include <QDialog>
#include <QDate>
#include <QtWidgets/qtablewidget.h>
#include <vector>
using std::vector;

namespace Ui {
class DialogBookingListMonthly;
}

class DialogBookingListMonthly : public QDialog
{
    Q_OBJECT

public:
    explicit DialogBookingListMonthly(QWidget *parent = nullptr);
    ~DialogBookingListMonthly();

private:
    Ui::DialogBookingListMonthly *ui;
    int days_of_month_number;
    vector<QDate> days_of_month;
    void add_table_row(QTableWidget *table,QDate &date);
    void add_table_row(QTableWidget *table,QDate &check_in_date,QDate &check_out_date,QString guest_name, QString guest_number, QString room,QString daily_cost,QString total_cost);
};

#endif // DIALOGBOOKINGLISTMONTHLY_H
