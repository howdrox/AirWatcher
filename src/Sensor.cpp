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
    string data = sensorLine.substr(6);

    vector<string> attributes;
    string attribute;
    istringstream tokenStream(data);
    while (getline(tokenStream, attribute, ';'))
    {
        attributes.push_back(attribute);
    }

    if (attributes.size() >= 3)
    {
        sensorID = stoi(attributes[0]);
        location.latitude = stod(attributes[1]);
        location.longitude = stod(attributes[2]);
    }
}
Sensor::~Sensor()
{
#ifdef MAP
    cout << "Appel au destructeur de <Sensor>" << endl;
#endif
}




void Sensor::setSensorID(const int &id)
{
    sensorID = id;
}

void Sensor::setLocation(const Coord &loc)
{
    location = loc;
}

void Sensor::addMeasurement(const Measurement &measurement)
{
    measurements.push_back(measurement);
}

std::ostream& operator<<(std::ostream& os, const Sensor& sensor) {
        os << "Sensor ID: " << sensor.sensorID << endl;
        os << "Latitude: " << sensor.location.latitude << endl;
        os << "Longitude: " << sensor.location.longitude << endl;;
        os << "Measurements: ";
        /*for (const auto& measurement : sensor.measurements) {
            os << measurement << " ";
        }*/
        return os;
}