#ifndef TIME_H
#define TIME_H

#include <string>

using namespace std;

class Time
{
public:
    // Constructors
    Time(int yy = 0, int MM = 0, int dd = 0, int hh = 0, int mm = 0, int ss = 0) : year(yy), month(MM), day(dd), hour(hh), minute(mm), second(ss){};
    Time(const Time &t) : year(t.year), month(t.month), day(t.day), hour(t.hour), minute(t.minute), second(t.second){};
    /**
     * @brief Construct from `string` in the format "yyyy-MM-dd hh:mm:ss"
     * 
     * @param str
     */
    Time(const string &str);

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

    // -------------------- Methods
    /**
     * @brief Checks if two `Time` objects have the same hour
     *
     * @param time
     * @return true
     * @return false
     */
    bool isSameHour(const Time &time) const;

    /**
     * @brief Sets the hour, minute and second to 0
     *
     * @return Time
     */
    Time zeroOutHour();

    /**
     * @brief Adds a number of days to the current date
     *
     * @param int
     * @return Time
     */
    Time addDays(int) const;

private:
    int year, month, day, hour, minute, second;
};

#endif // TIME_H
