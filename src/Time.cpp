using namespace std;
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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

int Time::getHour() const
{
    return hour;
}

int Time::getMinute() const
{
    return minute;
}

int Time::getSecond() const
{
    return second;
}

/**
 * @brief checks if both times are on the same date and hour
 * 
 * @param time 
 * @return true 
 * @return false 
 */
bool Time::isSameHour(const Time &time) const {
    return getYear() == time.getYear() &&
           getMonth() == time.getMonth() &&
           getDay() == time.getDay() &&
           getHour() == time.getHour();
}


//------------------------------------------------- Surcharge d'opérateurs
bool Time::operator<(const Time &date) const
{
    if (year != date.year)
        return year < date.year;
    if (month != date.month)
        return month < date.month;
    if (day != date.day)
        return day < date.day;
    if (hour != date.hour)
        return hour < date.hour;
    if (minute != date.minute)
        return minute < date.minute;
    return second < date.second;
}

bool Time::operator>(const Time &date) const
{
    return date < *this;
}

bool Time::operator<=(const Time &date) const
{
    return !(*this > date);
}

bool Time::operator>=(const Time &date) const
{
    return !(*this < date);
}

Time::Time(const Time &date)
    : year(date.year), month(date.month), day(date.day), 
    hour(date.hour), minute(date.minute), second(date.second){};

Time::Time(const string &data) {
    char delimiter1, delimiter2, delimiter3, delimiter4, delimiter5;
    stringstream timeStream(data);
    timeStream >> year >> delimiter1 >> month >> delimiter2 >> day >> hour >> delimiter3 >> minute >> delimiter4 >> second;
}

Time::Time(int yy, int MM, int dd, int hh, int mm, int ss) : 
    year(yy), month(MM), day(dd), hour(hh), minute(mm), second(ss) {};

Time::Time()
    : year(0), month(0), day(0), hour(0), minute(0), second(0) {};

Time::~Time(){};
