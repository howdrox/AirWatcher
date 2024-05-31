#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <string>

class Time {
public:
    // Getters
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    int getHour() const;
    int getMinute() const;
    int getSecond() const;

    // Méthode pour vérifier si deux objets Time ont la même heure et date
    bool isSameHour(const Time &time) const;

    // Surcharge des opérateurs de comparaison
    bool operator<(const Time &date) const;
    bool operator>(const Time &date) const;
    bool operator<=(const Time &date) const;
    bool operator>=(const Time &date) const;

    // Surcharge de l'opérateur d'affectation
    Time &operator=(const Time &other);

    // Constructeurs
    Time(int yy = 0, int MM = 0, int dd = 0, int hh = 0, int mm = 0, int ss = 0);
    Time(const std::string &data);
    Time(const Time &date);

    // Destructeur
    virtual ~Time();

private:
    int year, month, day, hour, minute, second;
};

#endif // TIME_H
