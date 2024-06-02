#ifndef SENSOR_H
#define SENSOR_H

#include <vector>
#include <string>

#include "Coord.h"
#include "Measurement.h"

class Sensor
{
public:
    // Constructors
    Sensor(int sensorID = 0, Coord location = Coord()) : sensorID(sensorID), location(location){};
    Sensor(const Sensor &sensor) : sensorID(sensor.sensorID), location(sensor.location), measurements(sensor.measurements){};
    Sensor(const string &sensorLine);

    // Destructor
    ~Sensor(){};

    // Operators
    Sensor &operator=(const Sensor &sensor);
    friend std::ostream &operator<<(std::ostream &os, const Sensor &sensor);

    // Getters
    int getSensorID() const { return sensorID; }
    const Coord getLocation() const { return location; }
    const vector<Measurement> &getMeasurements() const { return measurements; }

    // Methods
    void addMeasurement(const Measurement &measurement);

protected:
    int sensorID;
    Coord location;
    vector<Measurement> measurements;
};

#endif // SENSOR_H