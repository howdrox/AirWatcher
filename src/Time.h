#if !defined(Time_H)
#define Time_H

#include <iostream>
#include <string>
using namespace std;

class Time
{
public:
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    int getHour() const;
    int getMinute() const;
    int getSecond() const;


    bool isSameHour(const Time&time) const;

    bool operator<(const Time &date) const;
    bool operator>(const Time &date) const;
    bool operator<=(const Time &date) const;
    bool operator>=(const Time &date) const;

    Time(const Time &date);
    Time(const string &data);
    Time(int yy, int MM, int dd, int hh, int mm, int ss);
    Time();

    virtual ~Time();

protected:
    int year, month, day, hour, minute, second;
};

#endif // Time_H
