#include <algorithm>
#include <iostream>
#include <cstring>
#include <fstream>

#include "System.h"

using namespace std;

System::System(const string &sensorsFilePath, const string &cleanersFilePath, const string &usersFilePath, const string &measurementsFilePath)
{
    ifstream cleanersFile(cleanersFilePath);
    if (!cleanersFile.is_open())
    {
        cerr << "Unable to open cleanersFile: " << cleanersFilePath << endl;
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
        cerr << "Unable to open usersFile: " << usersFilePath << endl;
        return;
    }

    string userLine;
    while (getline(usersFile, userLine))
    {
        PrivateUser privateUser(userLine);   // Create an instance of the derived class PrivateUser
        privateUsers.push_back(privateUser); // Add the instance to the vector
    }

    usersFile.close();

    ifstream sensorsFile(sensorsFilePath);
    if (!sensorsFile.is_open())
    {
        cerr << "Unable to open sensorsFile: " << sensorsFilePath << endl;
        return;
    }

    string sensorLine;
    while (getline(sensorsFile, sensorLine))
    {
        Sensor sensor(sensorLine);
        sensors[sensor.getSensorID()] = sensor;
    }

    sensorsFile.close();

    ifstream measurementsFile(measurementsFilePath);
    if (!measurementsFile.is_open())
    {
        cerr << "Unable to open measurementsFile: " << measurementsFilePath << endl;
        return;
    }

    string measurementLine;
    while (getline(measurementsFile, measurementLine))
    {
        Measurement measurement(measurementLine);
        measurements[measurement.getSensorID()].push_back(measurement);
    }
    // sorts all measurements in each vector in chronological time
    for (auto &s : measurements)
    {
        sort(s.second.begin(), s.second.end());
    }

    measurementsFile.close();
}

void System::addMeasurement(const Measurement &m)
{
    measurements[m.getSensorID()].push_back(m);
    // sorts all measurements in each vector in chronological time
    vector<Measurement> &mVector = measurements[m.getSensorID()];
    sort(mVector.begin(), mVector.end());
}

void System::addCleaner(const Cleaner &cleaner)
{
    cleaners.push_back(cleaner);
}

void System::addSensor(const Sensor &sensor)
{
    sensors[sensor.getSensorID()] = sensor;
}

void System::addUser(const PrivateUser &p)
{
    privateUsers.push_back(p);
}