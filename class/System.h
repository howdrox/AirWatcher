#if ! defined ( SYSTEM_H )
#define SYSTEM_H
#include "User.h"
#include "Sensor.h"
#include "Measurement.h"
#include "Cleaner.h"
#include <vector>
#include <map>




class System{
    public:
        
        System();
        ~System();

        const map<int,Measurement> getMeasurements();
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

    
}
#endif