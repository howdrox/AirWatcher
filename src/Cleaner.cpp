using namespace std;
#include <iostream>
#include <sstream>
#include <vector>

#include "Cleaner.h"
// #include "Time.h"
// #include "Coord.h"

int Cleaner::getCleanerId() const
{
    return cleanerID;
}

Coord Cleaner::getCoord() const
{
    return location;
}

Time Cleaner::getStartTime() const
{
    return startTime;
}

Time Cleaner::getEndTime() const
{
    return endTime;
}

Cleaner::Cleaner(string data)
{
    vector<string> values;
    stringstream ss(data);
    string item;

    while (getline(ss, item, ';'))
    {
        values.push_back(item);
    }

    // Id
    string idStr = values[0].substr(7); // take only the number value in value[0], example: 'Cleaner0' --> '0'
    cleanerID = stoi(idStr);

    // Location
    double lng = stod(values[1]);
    double lat = stod(values[2]);
    location = Coord(lat, lng);

    // Start + end Time
    startTime = Time(values[3]);
    endTime = Time(values[4]);
}

Cleaner::~Cleaner()
{
}
