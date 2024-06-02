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
    // Constructors
    Measurement(const Time &time, int sensor, const PollutantType &attrID, double val, bool black)
        : timestamp(time), sensorID(sensor), attributeID(attrID), value(val), blacklisted(black) {}
    Measurement(const Measurement &m)
        : timestamp(m.timestamp), sensorID(m.sensorID), attributeID(m.attributeID), value(m.value), blacklisted(m.blacklisted) {}
    Measurement(const string &);

    // Destructor
    virtual ~Measurement() {}

    // Getters
    // int getMeasurementID() const { return measurementID; }
    Time getTimestamp() const { return timestamp; }
    int getSensorID() const { return sensorID; }
    PollutantType getAttributeID() const { return attributeID; }
    double getValue() const { return value; }
    bool isBlacklisted() const { return blacklisted; }

    // Setters
    void setBlacklisted(bool isBlacklisted) { blacklisted = isBlacklisted; };

    // Operators
    friend std::ostream &operator<<(std::ostream &os, const Measurement &measurement);

    

protected:
    // int measurementID;
    Time timestamp;
    int sensorID;
    PollutantType attributeID;
    double value;
    bool blacklisted;
};

#endif // MEASUREMENT_H
