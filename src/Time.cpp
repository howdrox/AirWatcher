#include <sstream>
#include <iomanip>

#include "Time.h"

using namespace std;

Time Time::zeroOutHour() const
{
    Time newTime(*this);
    newTime.hour = 0;
    newTime.minute = 0;
    newTime.second = 0;
    return newTime;
}

bool Time::isSameHour(const Time &time) const
{
    return getYear() == time.getYear() &&
           getMonth() == time.getMonth() &&
           getDay() == time.getDay() &&
           getHour() == time.getHour();
}

Time Time::addDays(int numDays) const
{
    Time newTime(*this);
    newTime.day += numDays;

    if (newTime.day == 0) {
        newTime.month -= 1;
        if (newTime.month == 0 || newTime.month == 1 || newTime.month == 3 || newTime.month == 5 || newTime.month == 7 || newTime.month == 8 || newTime.month == 10) {
            newTime.day = 31;
        } 
        else if (newTime.month == 2) newTime.day = 29;
        else newTime.day = 30;

        if (newTime.month == 0) {
            newTime.month = 12;
            newTime.year -= 1;
        }
    }

    return newTime;
}

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

bool Time::operator==(const Time &t) const
{
    return year == t.year && month == t.month && day == t.day && hour == t.hour && minute == t.minute && second == t.second;
}

Time &Time::operator=(const Time &other)
{
    if (this != &other)
    {
        year = other.year;
        month = other.month;
        day = other.day;
        hour = other.hour;
        minute = other.minute;
        second = other.second;
    }
    return *this;
}

ostream &operator<<(ostream &out, const Time &time)
{
    out << setw(4) << setfill('0') << time.year << "-"
        << setw(2) << setfill('0') << time.month << "-"
        << setw(2) << setfill('0') << time.day << " "
        << setw(2) << setfill('0') << time.hour << ":"
        << setw(2) << setfill('0') << time.minute << ":"
        << setw(2) << setfill('0') << time.second;
    return out;
}

Time::Time(const string &data)
{
    char delim;
    stringstream ss(data);
    ss >> year >> delim >> month >> delim >> day >> hour >> delim >> minute >> delim >> second;
}