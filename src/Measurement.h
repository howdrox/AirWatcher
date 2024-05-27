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

    int getDay(); // on va utiliser int pour représenter les jours de la semaine(0 = Sunday, 1 = Monday, ..., 6 = Saturday)

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
