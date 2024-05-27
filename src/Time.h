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
    double getTime() const;
    void setTime(const string &t);

    bool isSameHour(const Time&time) const;

    bool operator<(const Time &date) const;
    bool operator>(const Time &date) const;
    bool operator<=(const Time &date) const;
    bool operator>=(const Time &date) const;

    Time(const Time &date);
    Time(int yy, int MM, int dd);
    Time();

    virtual ~Time();

protected:
    int year, month, day;
    double _time;
};

#endif // Time_H
