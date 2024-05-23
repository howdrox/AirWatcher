using namespace std;
#include <iostream>

#include "Cleaner.h"

int Cleaner::getCleanerId() const {
    return cleanerID;
}

Coord Cleaner::getCoord() const {
    return location;
}

DateTime Cleaner::getStartTime() const {
    return startTime;
}

DateTime Cleaner::getEndTime() const {
    return endTime;
}

Cleaner::Cleaner(int id, Coord coord, DateTime start, DateTime end) 
    : cleanerID(id), location(coord), startTime(start), endTime(end) {

}

Cleaner::~Cleaner() {
    
}

