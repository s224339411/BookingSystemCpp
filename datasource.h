#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QString>
#include <string>
#include <vector>
#include "user.h"
#include "room.h"
#include "booking.h"

using std::string;
using std::vector;

user load_user_from_json();

vector<room> load_rooms_from_json();

bool save_booking_to_json(booking booking);

vector<booking> load_booking_from_json();

bool update_booking_by_guid_to_json(booking booking);

bool delete_booking_by_guid_to_json(string guid);

#endif // DATASOURCE_H
