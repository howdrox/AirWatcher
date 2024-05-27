#if !defined(MEASUREMENT_H)
#define MEASUREMENT_H

#include <string>
#include "Time.h"
#include "Sensor.h"
class Measurement
{
    //----------------------------------------------------------------- PUBLIC

public:
    Sensor getCapteurID();

    Time getTimestamp();

    Measurement(const Measurement &Measurement);

    Measurement(string &ligne);

    virtual ~Measurement();

protected:
    int measurementID;
    Time timestamp;
    int sensorID;
    std::string attributeID;
    double value;
    bool blacklisted;
};

#endif
