#include <sstream>
#include <iomanip>

#include "Time.h"

using namespace std;

// Getters
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
Time Time::zeroOutHour() 
{
    hour = 0;
    minute =0;
    second=0;
    return *this;
}
// Méthode pour vérifier si deux objets Time ont la même heure et date
bool Time::isSameHour(const Time &time) const
{
    return getYear() == time.getYear() &&
           getMonth() == time.getMonth() &&
           getDay() == time.getDay() &&
           getHour() == time.getHour();
}

// Surcharge des opérateurs de comparaison
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

// Surcharge de l'opérateur d'insertion
ostream& operator<<(ostream &out, const Time &time) {
    out << setw(4) << setfill('0') << time.year << "-"
        << setw(2) << setfill('0') << time.month << "-"
        << setw(2) << setfill('0') << time.day << " "
        << setw(2) << setfill('0') << time.hour << ":"
        << setw(2) << setfill('0') << time.minute << ":"
        << setw(2) << setfill('0') << time.second;
    return out;
}

// Constructeur avec paramètres
Time::Time(int yy, int MM, int dd, int hh, int mm, int ss)
    : year(yy), month(MM), day(dd), hour(hh), minute(mm), second(ss) {}

// Constructeur à partir d'une chaîne de caractères
Time::Time(const string &data)
{
    char delim;
    stringstream ss(data);
    ss >> year >> delim >> month >> delim >> day >> hour >> delim >> minute >> delim >> second;
}

// Constructeur de copie
Time::Time(const Time &date)
    : year(date.year), month(date.month), day(date.day), hour(date.hour), minute(date.minute), second(date.second) {}

// Destructeur
Time::~Time() {}

// Define comparison operators for the Date struct

bool operator==(const Date &lhs, const Date &rhs) {
    return lhs.year == rhs.year && lhs.month == rhs.month && lhs.day == rhs.day;
}

bool operator!=(const Date &lhs, const Date &rhs) {
    return !(lhs == rhs);
}

bool operator<(const Date &lhs, const Date &rhs) {
    if (lhs.year < rhs.year) return true;
    if (lhs.year > rhs.year) return false;
    if (lhs.month < rhs.month) return true;
    if (lhs.month > rhs.month) return false;
    return lhs.day < rhs.day;
}

bool operator<=(const Date &lhs, const Date &rhs) {
    return lhs < rhs || lhs == rhs;
}

bool operator>(const Date &lhs, const Date &rhs) {
    return !(lhs <= rhs);
}

bool operator>=(const Date &lhs, const Date &rhs) {
    return !(lhs < rhs);
}