using namespace std;
#include <cmath>
#include <iterator>
#include <iostream>
#include <map>

#include "Service.h"
#include "Coord.h"
#include "System.h"

double Service::distance(const Coord &coord1, const Coord &coord2)
{
    const double R = 6371.0; // Radius of the Earth in kilometers
    double lat1 = coord1.latitude;
    double lon1 = coord1.longitude;
    double lat2 = coord2.latitude;
    double lon2 = coord2.longitude;

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

multimap<double, Sensor> sortSensors(vector<Sensor> sensors, const Coord &coord){
    System system;
    multimap<double, Sensor> sortedSensors;
    map<int,Sensor> sensors = system.getSensors();
    for (auto it = sensors.begin(); it != sensors.end(); ++it){
        double distance = this.distance(it->second.getCoord(), coord);
        sortedSensors[distance] = it->second;
    }
    return sortedSensors;
}




}


double Service::calculateImpactRadius(const int &cleanerId)
{
    const vector<Cleaner>& cleaners = system.getCleaners();

    // Vérifier si cleanerId est dans la liste des nettoyeurs
    Coord cleanerCoord;
    Time start;
    Time end;
    bool cleanerFound = false;
    for (const Cleaner& c : cleaners) {
        if (c.getCleanerId() == cleanerId) {
            cleanerCoord = c.getCoord();
            start=c.getStartTime();
            end=c.getEndTime();
            cleanerFound = true;
            break;
        }
    }

    if (!cleanerFound) {
        throw invalid_argument("Cleaner ID not found");
    }

    map<int ,Sensor> sensors = system.getSensors();
    map<int, Measurement> measurements = system.getMeasurements();

    // Trier les capteurs par distance par rapport aux coordonnées du cleaner
    map<double, Sensor> sortedSensors = sortSensors(sensors, cleanerCoord);

    Time before_start(start.getYear(),start.getMonth(),start.getDay()-1,start.getHour(),start.getMinute(),start.getSecond());
    Time before_end(end.getYear(),end.getMonth(),end.getDay()-1,end.getHour(),end.getMinute(),end.getSecond());;

    // Filtrer les mesures pour les temps avant et après l'installation du cleaner
    map<int, Measurement> beforeMeasurements = filterMeasurements(before_start, start, measurements);
    map<int, Measurement> afterMeasurements = filterMeasurements(before_end, end, measurements);

    double beforeQuality = calculateQuality(beforeMeasurements);
    double afterQuality = calculateQuality(afterMeasurements);

    double impactRadius = 0.0;

    for (const auto& pair : sortedSensors) {
        double distance = pair.first;
        Sensor sensor = pair.second;

        // Filtrer les mesures pour ce capteur particulier
        map<int, Measurement> sensorBeforeMeasurements;
        map<int, Measurement> sensorAfterMeasurements;

        for (const auto& measurement : beforeMeasurements) {
            if (measurement.second.getSensorId() == sensor.getId()) {
                sensorBeforeMeasurements[measurement.first] = measurement.second;
            }
        }

        for (const auto& measurement : afterMeasurements) {
            if (measurement.second.getSensorId() == sensor.getId()) {
                sensorAfterMeasurements[measurement.first] = measurement.second;
            }
        }

        double sensorBeforeQuality = calculateQuality(sensorBeforeMeasurements);
        double sensorAfterQuality = calculateQuality(sensorAfterMeasurements);

        if (sensorAfterQuality < sensorBeforeQuality) {
            impactRadius = distance;
            break;
        }
    }

    return impactRadius;

    // Si cleanerId n'est pas trouvé, lancer une exception
    throw invalid_argument("Cleaner ID not found");
    
}

// map<int, vector<Measurement>> measurements;

double Service::calculateQuality(const Zone &zone, const Time &start, const Time &end)
{
    map<string, vector<double>> pollutantMaxValues;
    map<string, Time> pollutantLastTime;
    pollutantLastTime["O3"] = Time(0,0,0);
    pollutantLastTime["NO2"] = Time(0,0,0);
    pollutantLastTime["SO2"] = Time(0,0,0);
    pollutantLastTime["PM10"] = Time(0,0,0);

    for (const auto &sensorData : system.getMeasurements())
    {
        for (const auto &measurement : sensorData.second)
        {
            if (measurement.getTimestamp() >= start && measurement.getTimestamp() <= end && !measurement.isBlacklisted())
            {
                string attr = measurement.getAttributeID();
                double val = measurement.getValue();

                if (pollutantLastTime[attr].isSameHour(measurement.getTimestamp())) {
                    if (val > pollutantMaxValues[attr].back()) {
                        pollutantMaxValues[attr].back() = val;
                    }
                } else {
                    pollutantMaxValues[attr].push_back(val);
                }
            }
        }
    }

    // Get maximum values for pollutants
    double avgO3 = !pollutantMaxValues["O3"].empty() ? average(pollutantMaxValues["O3"]) : 0;
    double avgNO2 = !pollutantMaxValues["NO2"].empty() ? average(pollutantMaxValues["NO2"]) : 0;
    double avgSO2 = !pollutantMaxValues["SO2"].empty() ? average(pollutantMaxValues["SO2"]) : 0;
    double avgPM10 = !pollutantMaxValues["PM10"].empty() ? average(pollutantMaxValues["PM10"]) : 0;

    // Calculate sub-indices
    int indexO3 = calculateSubIndex(avgO3, "O3");
    int indexNO2 = calculateSubIndex(avgNO2, "NO2");
    int indexSO2 = calculateSubIndex(avgSO2, "SO2");
    int indexPM10 = calculateSubIndex(avgPM10, "PM10");

    // ATMO index is the maximum of the sub-indices
    return max({indexO3, indexNO2, indexSO2, indexPM10});
}

int Service::calculateSubIndex(const double &value, const string &pollutant) const
{
    if (pollutant == "O3")
    {
        if (value >= 240)
            return 10;
        if (value >= 210)
            return 9;
        if (value >= 180)
            return 8;
        if (value >= 150)
            return 7;
        if (value >= 130)
            return 6;
        if (value >= 105)
            return 5;
        if (value >= 80)
            return 4;
        if (value >= 55)
            return 3;
        if (value >= 30)
            return 2;
        return 1;
    }
    else if (pollutant == "NO2")
    {
        if (value >= 400)
            return 10;
        if (value >= 275)
            return 9;
        if (value >= 200)
            return 8;
        if (value >= 165)
            return 7;
        if (value >= 135)
            return 6;
        if (value >= 110)
            return 5;
        if (value >= 85)
            return 4;
        if (value >= 55)
            return 3;
        if (value >= 30)
            return 2;
        return 1;
    }
    else if (pollutant == "SO2")
    {
        if (value >= 500)
            return 10;
        if (value >= 400)
            return 9;
        if (value >= 300)
            return 8;
        if (value >= 250)
            return 7;
        if (value >= 200)
            return 6;
        if (value >= 160)
            return 5;
        if (value >= 120)
            return 4;
        if (value >= 80)
            return 3;
        if (value >= 40)
            return 2;
        return 1;
    }
    else if (pollutant == "PM10")
    {
        if (value >= 80)
            return 10;
        if (value >= 65)
            return 9;
        if (value >= 50)
            return 8;
        if (value >= 42)
            return 7;
        if (value >= 35)
            return 6;
        if (value >= 28)
            return 5;
        if (value >= 21)
            return 4;
        if (value >= 14)
            return 3;
        if (value >= 7)
            return 2;
        return 1;
    }
    return 0;
}

double Service::average(const vector<double> &v) {
    double sum = 0;

    for (const auto &i : v) {
        sum += i;
    }
    return sum / v.size();
}