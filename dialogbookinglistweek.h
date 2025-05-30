#ifndef DIALOGBOOKINGLISTWEEK_H
#define DIALOGBOOKINGLISTWEEK_H
#include <QTableWidget>
#include <QDialog>
#include <QDate>
#include <vector>
using std::vector;

namespace Ui {
class DialogBookingListWeek;
}

class DialogBookingListWeek : public QDialog
{
    Q_OBJECT

public:
    explicit DialogBookingListWeek(QWidget *parent = nullptr);
    ~DialogBookingListWeek();

private:
    Ui::DialogBookingListWeek *ui;
    const int DAYS_OF_WEEK = 7;
    vector<QDate> days_of_week;
    void add_table_row(QTableWidget *table,QDate &date);
    void add_table_row(QTableWidget *table,QDate &check_in_date,QDate &check_out_date,QString guest_name, QString guest_number, QString room,QString daily_cost,QString total_cost);
};

#endif // DIALOGBOOKINGLISTWEEK_H
