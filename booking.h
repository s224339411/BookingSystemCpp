#ifndef BOOKING_H
#define BOOKING_H

#include "room.h"
#include <string>
#include <QDate>
using std::string;

struct booking{

    string guid;
    room room;
    QDate check_in_date;
    QDate check_out_date;
    string guest_name;
    int guests_number;

    double daily_cost;
    double total_cost;

    booking();
};

#endif // BOOKING_H
