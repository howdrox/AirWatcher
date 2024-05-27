using namespace std;
#include <iostream>
#include <sstream>
#include <vector>

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

Cleaner::Cleaner(string data) {
    vector<string> values;
    stringstream ss(data);
    string item;
    
    while (getline(ss, item, ';')) {
        values.push_back(item);
    }

    // Id
    cleanerID = stoi(values[0]);

    // Location
    double lng = stod(values[1]);
    double lat = stod(values[2]);
    location = Coord(lat, lng);

    // Start + end Time
    startTime = Time(); startTime.setTime(values[3]);
    endTime = Time(); endTime.setTime(values[4]);
}

Cleaner::~Cleaner() {
    
}

