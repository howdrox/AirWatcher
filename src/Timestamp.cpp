#include <sstream>
#include <iomanip>

#include "Timestamp.h"

using namespace std;

// Getters
int Timestamp::getYear() const
{
    return year;
}

int Timestamp::getMonth() const
{
    return month;
}

int Timestamp::getDay() const
{
    return day;
}

int Timestamp::getHour() const
{
    return hour;
}

int Timestamp::getMinute() const
{
    return minute;
}

int Timestamp::getSecond() const
{
    return second;
}

// Méthode pour vérifier si deux objets Time ont la même heure et date
bool Timestamp::isSameHour(const Timestamp &time) const
{
    return getYear() == time.getYear() &&
           getMonth() == time.getMonth() &&
           getDay() == time.getDay() &&
           getHour() == time.getHour();
}

// Surcharge des opérateurs de comparaison
bool Timestamp::operator<(const Timestamp &date) const
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

bool Timestamp::operator>(const Timestamp &date) const
{
    return date < *this;
}

bool Timestamp::operator<=(const Timestamp &date) const
{
    return !(*this > date);
}

bool Timestamp::operator>=(const Timestamp &date) const
{
    return !(*this < date);
}

Timestamp &Timestamp::operator=(const Timestamp &other)
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

// Timestamp::Time()
//     : year(0), month(0), day(0), hour(0), minute(0), second(0) {}

// Constructeur avec paramètres
Timestamp::Timestamp(int yy, int MM, int dd, int hh, int mm, int ss)
    : year(yy), month(MM), day(dd), hour(hh), minute(mm), second(ss) {}

// Constructeur à partir d'une chaîne de caractères
Timestamp::Timestamp(const string &data)
{
    char delim;
    stringstream ss(data);
    ss >> year >> delim >> month >> delim >> day >> hour >> delim >> minute >> delim >> second;
}

// Constructeur de copie
Timestamp::Timestamp(const Timestamp &date)
    : year(date.year), month(date.month), day(date.day), hour(date.hour), minute(date.minute), second(date.second) {}

// Destructeur
Timestamp::~Timestamp() {}
