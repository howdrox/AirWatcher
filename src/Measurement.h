#if !defined(MEASUREMENT_H)
#define MEASUREMENT_H

#include <string>
#include "Time.h"
#include "Sensor.h"
class Measurement
{
    //----------------------------------------------------------------- PUBLIC

public:
    int getCapteurID();

    Time getTimestamp();

    int getDay(); 

    //-------------------------------------------- Constructeurs - destructeur
    Measurement(const Measurement &Measurement);

    Measurement(string &ligne);

    virtual ~Measurement();

protected:
    int measurementID;
    Time timestamp;
    std::string attributeID;
    double value;
    int sensorID;
};

#endif
