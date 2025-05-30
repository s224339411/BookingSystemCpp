#include "roomtype.h"

const string room_type_to_string(room_type room_type){
    switch(room_type){
        case SINGLE: return "Single";
        case DOUBLE: return "Double";
        case DELUXE: return "Deluxe";
        default: return "Unknown";
    }
}



