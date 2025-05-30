#ifndef UTILITIES_H
#define UTILITIES_H

#include <QtCore/qdatetime.h>
#include <string>
using std::string;

bool is_valid_date(string date);
string trim_string(const string& str);

bool is_date_range_intersect(const QDate &start_first_date,const QDate &end_first_date,const QDate &start_second_date,const QDate &end_second_date);

string decimal_to_string(double value, int precision_points);

#endif // UTILITIES_H
