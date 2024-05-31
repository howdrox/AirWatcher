#ifndef CLEANER_H
#define CLEANER_H

#include <iostream>
#include "Timestamp.h"
#include "Coord.h"

class Cleaner {
public:
    int getCleanerId() const;
    Coord getCoord() const;
    const Timestamp& getStartTime() const; // Use const reference
    const Timestamp& getEndTime() const;   // Use const reference

    Cleaner(const std::string& data);
    virtual ~Cleaner();

protected:
    int cleanerID;
    Coord location;
    Timestamp startTime;
    Timestamp endTime;
};

#endif // CLEANER_H
