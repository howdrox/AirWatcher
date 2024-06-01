#if !defined(SERVICE_H)
#define SERVICE_H

#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <iostream>

#include "Time.h"
#include "Coord.h"
#include "Sensor.h"
#include "System.h"
#include "Zone.h"
#include "Measurement.h"

using namespace std;

class Service
{
public:
    double calculateQuality(const Zone &zone, const Time &start, const Time &end);
    map<int, vector<Measurement>> filterMeasurements(const Time &start, const Time &end, map<int, vector<Measurement>> measurements); // a voir si `measurements` est en const
    double calculateImpactRadius(const int &cleanerId);
    double distance(const Coord &coord1, const Coord &coord2);
    multimap<double, int> getSimilarZones(const int &sensorID, const Time &start, const Time &end, const double &delta);
    double calculateQuality(const map<int, vector<Measurement>> &measurements);
    multimap<double, Sensor> sortSensors(map<int, Sensor> sensors, const Coord &coord); // a voir si `sensors` peut être en const
    int calculateSubIndex(const double &value, const PollutantType &pollutant) const;
    double average(const vector<double> &v);
    bool isInZone(const Coord c, const Zone z);

    Service();
    Service(const string &sensorsFilePath, const string &cleanersFilePath, const string &usersFilePath, const string &measurementsFilePath);
    Service(const System &sys) : system(sys) {}

    virtual ~Service();

    System &getSystem() { return system; }


private:
    System system;
};

#endif // SERVICE_H