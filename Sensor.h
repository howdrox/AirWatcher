#if ! defined ( SENSOR_H )
#define SENSOR_H
#include "Measurement.h"

typedef struct{
    double latitude;
    double longitude;
}Coord;

class Sensor{
    public:
        
        Sensor(int sensorID, Coord location,bool status);

        const int getSensorID();
        const Coord getLocation();
        const bool getStauts();
        const Measurement * getMeasurements();

        void setSensorID();
        void setLocation();
        void setStatus();
        void addMeasurement(Measurement measurement);


        ~Sensor ();
        
    

    protected:
        int sensorID;
        Coord location;
        bool status;
        Measurement * measurements;

    
}
#endif