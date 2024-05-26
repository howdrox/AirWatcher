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

        const map<int, Measurement>& getMeasurements();
        const vector<Cleaner>& getCleaners();
        const vector<Sensor>& getSensors();
        const  vector<User>& getUsers();

        void addMeasurement(const Measurement &measurement);
        void addCleaner(const Cleaner &cleaner);
        void addSensor(const Sensor &sensor);
        void addUser(const User &measurement);


        
        
    

    protected:
        vector<User> users;
        vector<Sensor> sensors;
        map<int,Measurement> measurements;
        vector<Cleaner> cleaners;

    
}
#endif