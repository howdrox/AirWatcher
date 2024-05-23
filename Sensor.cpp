#include <iostream>
#include <cstring>
#include "Sensor.h"
using namespace std;

Sensor::Sensor (const int id, const Coord loc, const bool stat){
#ifdef MAP
    cout << "Appel au constructeur de <Sensor>" << endl;
#endif
    sensorID = id;
    location.latitude = loc.latitude;
    location.longitude = loc.longitude;
    status = stat;

}
Sensor::~Sensor ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <Sensor>" << endl;
#endif
    
}


        

        const Sensor:: int getSensorID(){
            return sensorID;
        }
        const Sensor:: Coord getLocation(){
            return location;
        }
        const Sensor:: bool getStauts(){
            return status;
        }
        const Sensor:: Measurement * getMeasurements(){
            return measurements;
        }

        Sensor:: void setSensorID(const int id){
            sensorID = id;
        }
        Sensor:: void setLocation(const Coord loc){
            location = loc;
        }
        Sensor:: void setStatus(const bool stat){
            status = stat;
        }
       void Sensor::addMeasurement(const Measurement& measurement) {
            measurements.push_back(measurement);
        }


        
        
    

    protected:
        int sensorID;
        Coord location;
        bool status;
        Measurement * measurements;