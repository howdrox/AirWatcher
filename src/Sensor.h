#ifndef SENSOR_H
#define SENSOR_H

#include "Measurement.h"
#include <vector>
#include <string>

class Sensor
{
public:
    Sensor(int sensorID, Coord location);
    Sensor(const string &sensorLine);

    const int getSensorID();
    const Coord getLocation();
    const bool getStauts();
    const vector<Measurement> &getMeasurements();

    void setSensorID(const int &id);
    void setLocation(const Coord &loc);
    void addMeasurement(const Measurement &measurement);

    ~Sensor();

protected:
    int sensorID;
    Coord location;
    vector<Measurement> measurements;
};

#endif // SENSOR_H