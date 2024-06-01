#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <string>
#include "Time.h"

using namespace std;

enum PollutantType
{
    O3,
    NO2,
    SO2,
    PM10
};

class Measurement
{
public:
    Measurement(const string &);
    Measurement(int id, const Time &time, int sensor, const PollutantType &attrID, double val, bool black)
        : measurementID(id), timestamp(time), sensorID(sensor), attributeID(attrID), value(val), blacklisted(black) {}
    Measurement(const Measurement &m)
        : measurementID(m.measurementID), timestamp(m.timestamp), sensorID(m.sensorID), attributeID(m.attributeID), value(m.value), blacklisted(m.blacklisted) {}
    virtual ~Measurement() {}

    int getMeasurementID() const { return measurementID; }
    Time getTimestamp() const { return timestamp; }
    int getSensorID() const { return sensorID; }
    PollutantType getAttributeID() const { return attributeID; }
    double getValue() const { return value; }
    bool isBlacklisted() const { return blacklisted; }

protected:
    int measurementID;
    Time timestamp;
    int sensorID;
    PollutantType attributeID;
    double value;
    bool blacklisted;
};

#endif // MEASUREMENT_H
