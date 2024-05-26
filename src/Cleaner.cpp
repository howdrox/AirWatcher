using namespace std;
#include <iostream>

#include "Cleaner.h"

int Cleaner::getCleanerId() const {
    return cleanerID;
}

Coord Cleaner::getCoord() const {
    return location;
}

Time Cleaner::getStartTime() const {
    return startTime;
}

Time Cleaner::getEndTime() const {
    return endTime;
}

Cleaner::Cleaner(int id, Coord coord, Time start, Time end) 
    : cleanerID(id), location(coord), startTime(start), endTime(end) {

}

Cleaner::~Cleaner() {
    
}

