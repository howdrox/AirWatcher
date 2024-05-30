#ifndef SYSTEM_H
#define SYSTEM_H
#include "PrivateUser.h"
#include "Sensor.h"
#include "Measurement.h"
#include "Cleaner.h"
#include <vector>
#include <map>

class System
{
public:
    System();
    System(const string &sensorsFilePath, const string &cleanersFilePath, const string &usersFilePath, const string &measurementsFilePath);
    ~System();

    const map<int, vector<Measurement>> &getMeasurements();
    const vector<Cleaner> &getCleaners();
    const map<int, Sensor> &getSensors();
    const vector<PrivateUser> &getUsers();

    void addMeasurement(const Measurement &measurement);
    void addCleaner(const Cleaner &cleaner);
    void addSensor(const Sensor &sensor);
    void addUser(const PrivateUser &privateUser);

protected:
    vector<PrivateUser> privateUsers;
    map<int, Sensor> sensors;
    map<int, vector<Measurement>> measurements;
    vector<Cleaner> cleaners;
};
#endif