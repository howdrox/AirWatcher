using namespace std;
#include <iostream>
#include <sstream>
#include <string>

#include "Time.h"

int Time::getYear() const
{
    return year;
}

int Time::getMonth() const
{
    return month;
}

int Time::getDay() const
{
    return day;
}

double Time::getTime() const
{
    return _time;
}

void Time::setTime(const string &t)
{
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
bool Time::operator<(const Time &date) const
{
    if (year < date.year)
        return true;
    if (year > date.year)
        return false;
    if (month < date.month)
        return true;
    if (month > date.month)
        return false;
    if (day < date.day)
        return true;
    if (day > date.day)
        return false;
    return _time < date._time;
}

Time::Time(const Time &date)
    : year(date.year), month(date.month), day(date.day), _time(date._time){};

Time::Time(int yy, int MM, int dd)
    : year(yy), month(MM), day(dd), _time(0){};

Time::Time()
    : year(0), month(0), day(0), _time(0){};

Time::~Time(){};
