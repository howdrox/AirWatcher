#ifndef Time_H
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

    bool isSameHour(const Time &time) const;

    bool operator<(const Time &date) const;
    bool operator>(const Time &date) const;
    bool operator<=(const Time &date) const;
    bool operator>=(const Time &date) const;

    Time &operator=(const Time &other);

    Time(int yy = 0, int MM = 0, int dd = 0, int hh = 0, int mm = 0, int ss = 0);
    Time(const string &data);
    Time(const Time &date);

    virtual ~Time();

protected:
    int year, month, day, hour, minute, second;
};

#endif // Time_H
