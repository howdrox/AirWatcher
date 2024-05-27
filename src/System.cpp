#include <iostream>
#include <cstring>
#include <fstream>
#include "System.h"
using namespace std;

System::System()
{
#ifdef MAP
    cout << "Appel au constructeur de <System>" << endl;
#endif

    ifstream sensorsFile("sensors.csv");
    if (!sensorsFile.is_open())
    {
        cerr << "Unable to open sensorsFile sensors.csv" << endl;
        return;
    }

    string sensorLine;
    while (getline(sensorsFile, sensorLine))
    {
        Sensor sensor(sensorLine);
        sensors[sensor.getSensorID()]=sensor;
    }

    sensorsFile.close();

    ifstream cleanersFile("cleaners.csv");
    if (!cleanersFile.is_open())
    {
        cerr << "Unable to open cleanersFile cleaners.csv" << endl;
        return;
    }

    string cleanerLine;
    while (getline(cleanersFile, cleanerLine))
    {
        Cleaner cleaner(cleanerLine);
        cleaners.push_back(cleaner);
    }

    cleanersFile.close();

    ifstream usersFile("users.csv");
    if (!usersFile.is_open())
    {
        cerr << "Unable to open usersFile users.csv" << endl;
        return;
    }

    string userLine;
    while (getline(usersFile, userLine))
    {
        User user(userLine);
        users.push_back(user);
    }

    usersFile.close();

    ifstream measurementsFile("measurements.csv");
    if (!measurementsFile.is_open())
    {
        cerr << "Unable to open measurementsFile measurements.csv" << endl;
        return;
    }

    string measurementLine;
    while (getline(measurementsFile, measurementLine))
    {
        Measurement measurement(measurementLine);
        measurements[measurement.getSensorID()]=measurement;
    }

    usersFile.close();

}
System::~System() {}



const System::vector<Cleaner> &getCleaners()
{
    return cleaners;
}

const System::vector<Sensor> &getSensors()
{
    return sensors;
}
const System::map<int, Measurement> &getMeasurements()
{
    return measurements;
}
const System::vector<User> &getUsers()
{
    return users;
}

void System::addMeasurement(consr Measurement &measurement)
{
    measurements[measurement.getSensorID()] = measurement;
}
void System::addCleaner(const Cleaner &cleaner)
{
    cleaners.push_back(cleaner);
}
void System::addSensor(const Sensor &sensor)
{
    sensors.push_back(sensor);
}
void System::addUser(const User &user)
{
    users.push_back(user);
}
