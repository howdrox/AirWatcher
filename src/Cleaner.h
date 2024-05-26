#if !defined(CLEANER_H)
#define CLEANER_H

#include <iostream>
#include "Time.h"
#include "Coord.h"
using namespace std;



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
