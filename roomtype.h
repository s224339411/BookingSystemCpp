#ifndef ROOMTYPE_H
#define ROOMTYPE_H

#include <string>
using std::string;

enum room_type{
    UNKNOWN,
    SINGLE,
    DOUBLE,
    DELUXE
};

const string room_type_to_string(room_type room_type);

#endif // ROOMTYPE_H
