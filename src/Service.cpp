using namespace std;
#include <iostream>
#include <cmath>

#include "Service.h"
#include "Coord.h"

double Service::distance(const Coord &coord1, const Coord &coord2)
{
    const double R = 6371.0; // Radius of the Earth in kilometers
    double lat1 = coord1.getLatitude();
    double lon1 = coord1.getLongitude();
    double lat2 = coord2.getLatitude();
    double lon2 = coord2.getLongitude();

    // Convert degrees to radians
    lat1 = lat1 * M_PI / 180.0;
    lon1 = lon1 * M_PI / 180.0;
    lat2 = lat2 * M_PI / 180.0;
    lon2 = lon2 * M_PI / 180.0;

    // Haversine formula
    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;
    double a = sin(dlat / 2) * sin(dlat / 2) +
               cos(lat1) * cos(lat2) * sin(dlon / 2) * sin(dlon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distance = R * c;

    return distance;
}

map<int, vector<Measurement> > Service::filterMeasurements(const Time &start, const Time &end, map<int, vector<Measurement> > measurements) {
    map<int, vector<Measurement> > res;
    map<int, vector<Measurement> >::iterator itr;
    for (itr = measurements.begin(); itr != measurements.end(); ++itr) {
        // Key : itr->first
        // Value : itr->second
        vector<Measurement> measurementList = itr->second;
        vector<Measurement> filteredList;
        for (int i = 0; i < measurementList.size(); i++) {
            Measurement m = measurementList[i];
            Time measureTime = m.getTimestamp();
            if (start < measureTime && measureTime < end) {
                filteredList.push_back(m);
            }
        } 
        res[itr->first] = filteredList;
    }
    return res;
} 
multimap<double,int> Service ::getSimilarZones(const int &sensorID, const Time &start, const Time &end, const double &delta){
    System system;
    multimap<double,int> similarSensors;
    map<int,Sensor> sensors = system.getSensors();
    map<int,vector<Measurement>> measurements = system.getMeasurements();
    map<int,vector<Measurement>> filteredMeasurements = this.filterMeasurements(start, end,  measurements);
    double parameterQuality = this.calculateQuality( filteredMeasurements[sensorID]);

    for (auto it = filteredMeasurements.begin(); it != filteredMeasurements.end(); ++it){
        double sensorQuality = this.calculateQuality(it->second);
        if (sensorQuality<= parameterQuality+delta && sensorQuality>= parameterQuality-delta){
            double qualityDifference = sensorQuality - parameterQuality;
            if (sensorQuality<parameterQuality){
                qualityDifference = parameterQuality - sensorQuality;
            }
            similarSensors[qualityDifference] = it->first;
        }
    }

    return similarSensors;



}
