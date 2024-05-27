#if !defined(SERVICE_H)
#define SERVICE_H

#include <iostream>
#include "Time.h"
#include "Coord.h"
#include "System.h"
#include "Zone.h"
#include "Measurement.h"
#include <map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Service
{
public:
    double calculateQuality(const Zone &zone, const Time &start, const Time &end);

    map<int, Measurement> filterMeasurements(const Time &start, const Time &end, map<int, Measurement> measurements); // a voir si `measurements` est en const

    double calculateImpactRadius(const int &cleanerId);

    double distance(const Coord &coord1, const Coord &coord2);

    vector<Zone> getSimilarZones(const int &sensorID, const Time &start, const Time &end, const double &delta);

    double calculateQuality(const map<int, Measurement> &measurements);

    map<double, Sensor> sortSensors(vector<Sensor> sensors, const Coord &coord); // a voir si `sensors` peut être en const

    Service();

    Service(const System &system);

    virtual ~Service();

private:
    System system;

    int calculateSubIndex(double value, const std::string &pollutant) const;
};

#endif // SERVICE_H