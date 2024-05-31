#ifndef TIME_H
#define TIME_H

#include <string>

using namespace std;

class Timestamp {
public:
    // Getters
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    int getHour() const;
    int getMinute() const;
    int getSecond() const;

    // Méthode pour vérifier si deux objets Time ont la même heure et date
    bool isSameHour(const Timestamp &time) const;

    // Surcharge des opérateurs de comparaison
    bool operator<(const Timestamp &date) const;
    bool operator>(const Timestamp &date) const;
    bool operator<=(const Timestamp &date) const;
    bool operator>=(const Timestamp &date) const;

    // Surcharge de l'opérateur d'affectation
    Timestamp &operator=(const Timestamp &other);

    // Constructeurs
    // Timestamp();
    Timestamp(int yy = 0, int MM = 0, int dd = 0, int hh = 0, int mm = 0, int ss = 0);
    Timestamp(const string &data);
    Timestamp(const Timestamp &date);

    // Destructeur
    virtual ~Timestamp();

private:
    int year, month, day, hour, minute, second;
};

#endif // TIME_H
