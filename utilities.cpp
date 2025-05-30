#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <sstream>

#include "utilities.h"

bool is_valid_date(string date){
    return true;
}

string trim_string(const string& str){
    auto start = std::find_if_not(str.begin(), str.end(), ::isspace);
    auto end = std::find_if_not(str.rbegin(), str.rend(), ::isspace).base();
    return (start < end) ? std::string(start, end) : "";
}


//function to check if data range intersect
bool range_overlap(const QDate &start_first_date,const QDate &end_first_date,const QDate &start_second_date,const QDate &end_second_date) {
    return (start_first_date <= end_second_date) && (end_first_date >= start_second_date);
}

bool is_date_range_intersect(const QDate &start_first_date,const QDate &end_first_date,const QDate &start_second_date,const QDate &end_second_date){

    return !range_overlap(start_first_date,end_first_date,start_second_date,end_second_date);
}

string decimal_to_string(double value, int precision_points) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision_points) << value;
    return oss.str();
}
