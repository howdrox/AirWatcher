#if ! defined ( CLEANER_H )
#define CLEANER_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
using namespace std;

typedef struct _Coord
{
    double latitude;
    double longitude;

    Coord( double lat, double lng ) : latitude(lat), longitude(lng) {};

    Coord ( const Coord & coord ) : latitude(coord.latitude), longitude(coord.longitude) {};
} Coord;

typedef struct _DateTime
{
    int year, month, day;
    double _time; 

    DateTime(int yy, int MM, int dd, double t) : year(yy), month(MM), day(dd), _time(t) {};

    DateTime ( const DateTime & date ) 
        : year(date.year), month(date.month), day(date.day), _time(date._time) {};
} DateTime;

class Cleaner
{
//----------------------------------------------------------------- PUBLIC
//----------------------------------------------------- Méthodes publiques


    public:
    //----------------------------------------------------- Méthodes publiques
        virtual void afficherTrajet(ostream & os) const = 0;

        int getCleanerId() const;

        Coord getCoord() const; 

        DateTime getStartTime() const;

        DateTime getEndTime() const;

    //-------------------------------------------- Constructeurs - destructeur
        Cleaner (int id, Coord coord, DateTime start, DateTime end);

        virtual ~Cleaner ();

    protected:
    //----------------------------------------------------- Attributs protégés
        int cleanerID;
        Coord location;
        DateTime startTime;
        DateTime endTime;

};

#endif // CLEANER_H
