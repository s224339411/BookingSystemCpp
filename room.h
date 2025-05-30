#ifndef ROOM_H
#define ROOM_H

#include <string>
#include "roomtype.h"
using std::string;

struct room{
    string guid;
    string name;
    int number;
    room_type type;
    bool private_bathroom;
    double daily_rate;
    int maximum_guests;

    room();

};

#endif // ROOM_H
