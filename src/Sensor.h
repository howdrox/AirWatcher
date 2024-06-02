#ifndef SENSOR_H
#define SENSOR_H

#include <vector>
#include <string>

#include "Coord.h"
#include "Measurement.h"

class Sensor
{
public:
    Sensor(int sensorID = 0, Coord location = Coord());
    Sensor(const Sensor &sensor);
    Sensor(const string &sensorLine);
    ~Sensor();

    int getSensorID() const { return sensorID; }
    const Coord getLocation() const { return location; }
    const vector<Measurement> &getMeasurements() const { return measurements; }

    void addMeasurement(const Measurement &measurement);

    Sensor &operator=(const Sensor &sensor);
    friend std::ostream &operator<<(std::ostream &os, const Sensor &sensor);

protected:
    int sensorID;
    Coord location;
    vector<Measurement> measurements;
};

#endif // SENSOR_H