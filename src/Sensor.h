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
    Sensor(const string &sensorLine);

    int getSensorID() const { return sensorID; }
    const Coord getLocation() const { return location; }
    const vector<Measurement> &getMeasurements() const { return measurements; }
    
    void addMeasurement(const Measurement &measurement);

    friend std::ostream& operator<<(std::ostream& os, const Sensor& sensor);
    ~Sensor();

protected:
    int sensorID;
    Coord location;
    vector<Measurement> measurements;
};

#endif // SENSOR_H