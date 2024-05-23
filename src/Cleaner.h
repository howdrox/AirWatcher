#if !defined(CLEANER_H)
#define CLEANER_H

#include <iostream>
#include "Time.h"
using namespace std;

typedef struct _Coord
{
    double latitude;
    double longitude;

    _Coord(double lat, double lng) : latitude(lat), longitude(lng){};

    _Coord(const Coord &coord) : latitude(coord.latitude), longitude(coord.longitude){};
} Coord;

class Cleaner
{
public:
    virtual void afficherTrajet(ostream &os) const = 0;

    int getCleanerId() const;

    Coord getCoord() const;

    Time getStartTime() const;

    Time getEndTime() const;

    Cleaner(int id, Coord coord, Time start, Time end);

    virtual ~Cleaner();

protected:
    int cleanerID;
    Coord location;
    Time startTime;
    Time endTime;
};

#endif // CLEANER_H
