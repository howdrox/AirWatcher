#include <iostream>
#include <string>
#include <cstring>
#include <sstream>

#include "Sensor.h"
#include "Coord.h"

using namespace std;

Sensor::Sensor(const int id, const Coord loc)
{
#ifdef MAP
    cout << "Appel au constructeur de <Sensor>" << endl;
#endif
    sensorID = id;
    location.latitude = loc.latitude;
    location.longitude = loc.longitude;
}

Sensor::Sensor(const string &sensorLine)
{
#ifdef MAP
    cout << "Appel au constructeur de <Sensor>" << endl;
#endif

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

Sensor::Sensor(const Sensor &sensor)
{
    sensorID = sensor.sensorID;
    location = sensor.location;
    measurements = sensor.measurements;
}

Sensor::~Sensor()
{
#ifdef MAP
    cout << "Appel au destructeur de <Sensor>" << endl;
#endif
}

void Sensor::addMeasurement(const Measurement &measurement)
{
    measurements.push_back(measurement);
}

Sensor &Sensor::operator=(const Sensor &sensor)
{
    if (this != &sensor)
    {
        sensorID = sensor.sensorID;
        location = sensor.location;
        measurements = sensor.measurements;
    }
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Sensor &sensor)
{
    os << "Sensor ID: " << sensor.sensorID << endl;
    os << "Latitude: " << sensor.location.latitude << endl;
    os << "Longitude: " << sensor.location.longitude << endl;
    ;
    os << "Measurements: " << endl;
    /*for (const auto& measurement : sensor.measurements) {
        os << measurement << " ";
    }*/
    return os;
}