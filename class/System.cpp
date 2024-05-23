#include <iostream>
#include <cstring>
#include "System.h"
using namespace std;
    


        System::System(){
            
        }
        ~System();





        System::const map<int,Measurement> getMeasurements(){

        }
        const vector<Cleaner> getCleaners();
        const vector <Sensor> getSensors();
        const map<int,Measurement>& getMeasurements();

        void addMeasurement(Measurement &measurement);
        void addCleaner(Cleaner &cleaner);
        void addSensor(Sensor &sensor);
        void addMeasurement(Measurement &measurement);


        
        
    

    protected:
        vector<User> users;
        vector <Sensor> sensors;
        map<int,Measurement> measurements;
        vector<Cleaner> cleaners;



        

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


        
        
    
