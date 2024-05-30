#include <iostream>
#include <cstring>
#include <fstream>

#include "System.h"
#include "Cleaner.h"
#include "PrivateUser.h"
#include "Measurement.h"

using namespace std;

System::System(string sensorsFilePath, string cleanersFilePath, string usersFilePath, string measurementsFilePath)
{
#ifdef MAP
    cout << "Appel au constructeur de <System>" << endl;
#endif

    ifstream sensorsFile(sensorsFilePath);
    if (!sensorsFile.is_open())
    {
        cerr << "Unable to open sensorsFile sensors.csv" << endl;
        return;
    }

    string sensorLine;
    while (getline(sensorsFile, sensorLine))
    {
        Sensor sensor(sensorLine);
        sensors[sensor.getSensorID()] = sensor;
    }

    sensorsFile.close();

    ifstream cleanersFile(cleanersFilePath);
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

    ifstream usersFile(usersFilePath);
    if (!usersFile.is_open())
    {
        cerr << "Unable to open usersFile users.csv" << endl;
        return;
    }

    string userLine;
    while (getline(usersFile, userLine))
    {
        PrivateUser privateUser(userLine);   // Create an instance of the derived class PrivateUser
        privateUsers.push_back(privateUser); // Add the instance to the vector
    }

    usersFile.close();

    ifstream measurementsFile(measurementsFilePath);
    if (!measurementsFile.is_open())
    {
        cerr << "Unable to open measurementsFile measurements.csv" << endl;
        return;
    }

    string measurementLine;
    while (getline(measurementsFile, measurementLine))
    {
        Measurement measurement(measurementLine);
        measurements[measurement.getSensorID()].push_back(measurement);
    }

    usersFile.close();
}

System::~System() {}

const vector<Cleaner> &System::getCleaners()
{
    return cleaners;
}

const map<int, Sensor> &System::getSensors()
{
    return sensors;
}
const map<int, vector<Measurement>> &System::getMeasurements()
{
    return measurements;
}
const vector<PrivateUser> &System::getUsers()
{
    return privateUsers;
}

void System::addMeasurement(const Measurement &measurement)
{
    // To change
    // measurements[measurement.getSensorID()] = measurement;
}
void System::addCleaner(const Cleaner &cleaner)
{
    cleaners.push_back(cleaner);
}
void System::addSensor(const Sensor &sensor)
{
    // To change
    // sensors.push_back(sensor);
}
void System::addMeasurement(const Measurement &m)
{
    // To change
    // users.push_back(m);
}
