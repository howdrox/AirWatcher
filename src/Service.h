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
using namespace std;

class Service
{
public:
    double calculateQuality(Zone zone, Time start, Time end);

    map<int, Measurement> filterMeasurements(Time start, Time end, map<int, Measurement> measurements);
    
    double calculateImpactRadius(int cleanerId);

    double distance(Coord coord1, Coord coord2);

    vector<Zone> getSimilarZones(int sensorID, Time start, Time end, double delta);

    double calculateQuality(map<int, Measurement> measurements);

    map<double,Sensor> sortSensors(vector<Sensor> sensors, Coord coord);

    Service();

    Service(System system);
    
    virtual ~Service();

private:
    System system;
};

#endif // SERVICE_H