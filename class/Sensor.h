#if ! defined ( SENSOR_H )
#define SENSOR_H
#include "Measurement.h"
#include <vector>


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
        const vector<Measurement>& getMeasurements();

        void setSensorID(const int id);
        void setLocation(const Coord loc);
        void setStatus(const bool stat);
        void addMeasurement(Measurement measurement);


        ~Sensor ();
        
    

    protected:
        int sensorID;
        Coord location;
        bool status;
        vector<Measurement> measurements;

    
}
#endif