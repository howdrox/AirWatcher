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

<<<<<<< HEAD
    int getDay(); 

    //-------------------------------------------- Constructeurs - destructeur
=======
>>>>>>> 51e0ec6261baa12f115c88cdb2e3a320694bf549
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
