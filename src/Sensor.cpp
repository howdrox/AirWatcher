#include <iostream>
#include <string>
#include <sstream>

#include "Sensor.h"

using namespace std;

Sensor::Sensor(const string &sensorLine)
{
    stringstream ss(sensorLine);
    string item;
    vector<string> elements;

    while (getline(ss, item, ';'))
    {
        elements.push_back(item);
    }

    sensorID = std::stoi(elements[0].substr(6));
    location.latitude = stod(elements[1]);
    location.longitude = stod(elements[2]);
}

Sensor &Sensor::operator=(const Sensor &sensor)
{
    if (this != &sensor)
    {
        sensorID = sensor.sensorID;
        location = sensor.location;
    }
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Sensor &sensor)
{
    os << "Sensor " << sensor.sensorID << " at (" << sensor.location.latitude << ", " << sensor.location.longitude << ")";
    return os;
}