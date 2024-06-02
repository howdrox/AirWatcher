#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <map>

#include "PrivateUser.h"
#include "Sensor.h"
#include "Measurement.h"
#include "Cleaner.h"

class System
{
public:
    // Constructors
    System(){};
    System(const string &sensorsFilePath, const string &cleanersFilePath, const string &usersFilePath, const string &measurementsFilePath);

    // Destructor
    ~System(){};

    // Getters
    map<int, vector<Measurement>> &getMeasurements() { return measurements; };
    const vector<Cleaner> &getCleaners() { return cleaners; };
    const map<int, Sensor> &getSensors() { return sensors; };
    vector<PrivateUser> &getUsers() { return privateUsers; };

    // Methods
    void addMeasurement(const Measurement &measurement);
    void addCleaner(const Cleaner &cleaner);
    void addSensor(const Sensor &sensor);
    void addUser(const PrivateUser &privateUser);

protected:
    vector<PrivateUser> privateUsers;
    // Key: sensorID
    // Value: Sensor
    map<int, Sensor> sensors;
    // Key: sensorID
    // Value: vector of measurements
    map<int, vector<Measurement>> measurements;
    vector<Cleaner> cleaners;
};
#endif