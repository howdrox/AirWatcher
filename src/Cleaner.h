#ifndef CLEANER_H
#define CLEANER_H

#include <iostream>
#include "Time.h"
#include "Coord.h"

class Cleaner {
public:
    int getCleanerId() const;
    Coord getCoord() const;
    const Time& getStartTime() const; // Use const reference
    const Time& getEndTime() const;   // Use const reference

    Cleaner(const std::string& data);
    virtual ~Cleaner();

protected:
    int cleanerID;
    Coord location;
    Time startTime;
    Time endTime;
};

#endif // CLEANER_H
