#if ! defined ( DATETIME_H )
#define DATETIME_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <string>
using namespace std;


class DateTime
{
//----------------------------------------------------------------- PUBLIC
//----------------------------------------------------- Méthodes publiques


    public:
    //----------------------------------------------------- Méthodes publiques
        int getYear() const;

        int getMonth() const; 

        int getDay() const;

        double getTime() const;

        void setTime(const string & t);

    //-------------------------------------------- Constructeurs - destructeur
        DateTime ( const DateTime & date );
        
        DateTime(int yy, int MM, int dd);

        DateTime();

        virtual ~DateTime ();

    protected:
    //----------------------------------------------------- Attributs protégés
        int year, month, day;
        double _time; 

};

#endif // DATETIME_H
