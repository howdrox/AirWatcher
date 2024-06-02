#ifndef TIME_H
#define TIME_H

#include <string>

using namespace std;

class Time
{
public:
    // Constructors
    Time(int yy = 0, int MM = 0, int dd = 0, int hh = 0, int mm = 0, int ss = 0) : year(yy), month(MM), day(dd), hour(hh), minute(mm), second(ss){};
    Time(const Time &t): year(t.year), month(t.month), day(t.day), hour(t.hour), minute(t.minute), second(t.second){};
    Time(const string &data);

    // Desctructor
    virtual ~Time(){};

    // Operator overload
    bool operator<(const Time &) const;
    bool operator>(const Time &) const;
    bool operator<=(const Time &) const;
    bool operator>=(const Time &) const;
    bool operator==(const Time &) const;

    Time &operator=(const Time &other);

    friend ostream &operator<<(ostream &out, const Time &time);

    // Getters
    int getYear() const { return year; };
    int getMonth() const { return month; };
    int getDay() const { return day; };
    int getHour() const { return hour; };
    int getMinute() const { return minute; };
    int getSecond() const { return second; };

    // Methods
    bool isSameHour(const Time &time) const;
    Time zeroOutHour();
    Time addDays(int) const;

private:
    int year, month, day, hour, minute, second;
};

#endif // TIME_H
