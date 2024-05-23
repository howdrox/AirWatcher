#if !defined(Time_H)
#define Time_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <string>
using namespace std;

class Time
{
    //----------------------------------------------------------------- PUBLIC
    //----------------------------------------------------- Méthodes publiques

public:
    //----------------------------------------------------- Méthodes publiques
    int getYear() const;

    int getMonth() const;

    int getDay() const;

    double getTime() const;

    void setTime(const string &t);

    //------------------------------------------------- Surcharge d'opérateurs
    bool operator<(const Time &date) const;

    //-------------------------------------------- Constructeurs - destructeur
    Time(const Time &date);

    Time(int yy, int MM, int dd);

    Time();

    virtual ~Time();

protected:
    //----------------------------------------------------- Attributs protégés
    int year, month, day;
    double _time;
};

#endif // Time_H
