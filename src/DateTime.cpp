using namespace std;
#include <iostream>
#include <sstream>
#include <string>

#include "DateTime.h"

int DateTime::getYear() const {
    return year;
}

int DateTime::getMonth() const {
    return month;
}

int DateTime::getDay() const {
    return day;
}

double DateTime::getTime() const {
    return _time;
}

void DateTime::setTime(const string & t) {
    // t in format "hh:mm:ss"
    int hours, minutes, seconds;
    char delimiter1, delimiter2;

    // Use a stringstream to parse the string
    stringstream timeStream(t);
    timeStream >> hours >> delimiter1 >> minutes >> delimiter2 >> seconds;

    // Convert to double value representing hours
    double timeInHours = hours + minutes * 1.0 / 60 + seconds * 1.0 / 3600;

    _time = timeInHours;
}

//------------------------------------------------- Surcharge d'opérateurs
bool DateTime::operator< ( const DateTime &date ) const
{
    if (year < date.year) return true;
    if (year > date.year) return false;
    if (month < date.month) return true;
    if (month > date.month) return false;
    if (day < date.day) return true;
    if (day > date.day) return false;
    return _time < date._time;
}

DateTime::DateTime ( const DateTime & date ) 
        : year(date.year), month(date.month), day(date.day), _time(date._time) {};

DateTime::DateTime(int yy, int MM, int dd) 
    : year(yy), month(MM), day(dd) {};

DateTime::DateTime() 
    : year(0), month(0), day(0), _time(0) {};

DateTime::~DateTime() {};

