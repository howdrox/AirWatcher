#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <string>
#include "Time.h"

class Measurement
{
public:
    Measurement(int id, const Time &time, int sensor, const std::string &attrID, double val, bool black)
        : measurementID(id), timestamp(time), sensorID(sensor), attributeID(attrID), value(val), blacklisted(black) {}

    int getMeasurementID() const { return measurementID; }
    Time getTimestamp() const { return timestamp; }
    int getSensorID() const { return sensorID; }
    std::string getAttributeID() const { return attributeID; }
    double getValue() const { return value; }
    bool isBlacklisted() const { return blacklisted; }

    Measurement(const Measurement &m)
        : measurementID(m.measurementID), timestamp(m.timestamp), sensorID(m.sensorID), attributeID(m.attributeID), value(m.value), blacklisted(m.blacklisted) {}

    virtual ~Measurement() {}

protected:
    int measurementID;
    Time timestamp;
    int sensorID;
    std::string attributeID;
    double value;
    bool blacklisted;
};

#endif // MEASUREMENT_H
