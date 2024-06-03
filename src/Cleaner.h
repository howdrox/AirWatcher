#ifndef CLEANER_H
#define CLEANER_H

#include <iostream>
#include "Time.h"
#include "Coord.h"

class Cleaner
{
public:
    // Constructors
    /**
     * @brief Construct from `String` in the format "cleanerId;latitude;longitude;start_time;end_time"
     * 
     * @param data 
     */
    Cleaner(const std::string &data);

    // Destructor
    virtual ~Cleaner(){};

    // Getters
    int getCleanerID() const { return cleanerID; };
    Coord getCoord() const { return location; };
    const Time &getStartTime() const { return startTime; };
    const Time &getEndTime() const { return endTime; };

private:
    int cleanerID;
    Coord location;
    Time startTime;
    Time endTime;
};

#endif // CLEANER_H
