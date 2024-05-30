#include <iostream>
#include "Sensor.h"
#include "System.h"
#include <map>
#include <cstring>
#include <fstream>
using namespace std;

int main()
{
    map<int, Sensor> sensors;
    ifstream sensorsFile("data/sensors.csv");
    if (!sensorsFile.is_open())
    {
        cerr << "Unable to open sensorsFile sensors.csv" << endl;
        return 1;
    }

    string sensorLine;
    while (getline(sensorsFile, sensorLine))
    {
        Sensor sensor(sensorLine);
        sensors[sensor.getSensorID()] = sensor;
    }

    sensorsFile.close();
    for (auto it = sensors.begin(); it != sensors.end(); ++it)
    {
        cout << it->first << " sensorID: " << it->second.getSensorID() << " sensorLatitude: " << it->second.getLocation().latitude << " sensorLongitude: " << it->second.getLocation().longitude << endl;
    }
    return 0;
}