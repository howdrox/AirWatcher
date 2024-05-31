using namespace std;

#define _USE_MATH_DEFINES
#include <cmath>
#include <iomanip>
#include <iterator>
#include <iostream>
#include <map>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include "Service.h"
#include "Coord.h"
#include "System.h"


Service::Service() {}

Service::Service(const string &sensorsFilePath, const string &cleanersFilePath, const string &usersFilePath, const string &measurementsFilePath)
{
    system = System(sensorsFilePath, cleanersFilePath, usersFilePath, measurementsFilePath);
}

/**
 * @brief calculates the distance between two coordinates
 *
 * @param coord1
 * @param coord2
 * @return double
 */
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

map<int, vector<Measurement>> Service::filterMeasurements(const Time &start, const Time &end, map<int, vector<Measurement>> measurements)
{
    map<int, vector<Measurement>> res;
    map<int, vector<Measurement>>::iterator itr;
    for (itr = measurements.begin(); itr != measurements.end(); ++itr)
    {
        // Key : itr->first
        // Value : itr->second
        vector<Measurement> measurementList = itr->second;
        vector<Measurement> filteredList;
        for (int i = 0; i < (int)measurementList.size(); i++)
        {
            Measurement m = measurementList[i];
            Time measureTime = m.getTimestamp();
            if (start < measureTime && measureTime < end)
            {
                filteredList.push_back(m);
            }
        }
        res[itr->first] = filteredList;
    }
    return res;
}
multimap<double, int> Service ::getSimilarZones(const int &sensorID, const Time &start, const Time &end, const double &delta)
{

    multimap<double, int> similarSensors;
    map<int, Sensor> sensors = system.getSensors();
    map<int, vector<Measurement>> measurements = system.getMeasurements();
    map<int, vector<Measurement>> filteredMeasurements = filterMeasurements(start, end, measurements);
    map<int, vector<Measurement>> parameterSensorMeasurements;
    parameterSensorMeasurements[sensorID] = filteredMeasurements[sensorID];
    double parameterQuality = this->calculateQuality(parameterSensorMeasurements);

    for (auto it = filteredMeasurements.begin(); it != filteredMeasurements.end(); ++it)
    {
        map<int, vector<Measurement>> filteredMeasurementsSensor;
        filteredMeasurementsSensor[sensorID] = filteredMeasurements[it->first];
        double sensorQuality = this->calculateQuality(filteredMeasurementsSensor);
        if (sensorQuality <= parameterQuality + delta && sensorQuality >= parameterQuality - delta)
        {
            double qualityDifference = sensorQuality - parameterQuality;
            if (sensorQuality < parameterQuality)
            {
                qualityDifference = parameterQuality - sensorQuality;
            }
            similarSensors.insert(pair<double, int>(qualityDifference, it->first));
        }
    }
    return similarSensors;
}

multimap<double, Sensor> Service::sortSensors(map<int, Sensor> sensors, const Coord &coord)
{
    System system;
    multimap<double, Sensor> sortedSensors;

    for (auto it = sensors.begin(); it != sensors.end(); ++it)
    {
        double distance = this->distance(it->second.getLocation(), coord);
        sortedSensors.insert(pair<double, Sensor>(distance, it->second));
    }
    return sortedSensors;
}

double Service::calculateImpactRadius(const int &cleanerId)
{
    const vector<Cleaner> &cleaners = system.getCleaners();

    // Vérifier si cleanerId est dans la liste des nettoyeurs
    Coord cleanerCoord;
    Time start;
    Time end;
    bool cleanerFound = false;
    for (const Cleaner &c : cleaners)
    {
        if (c.getCleanerId() == cleanerId)
        {
            cleanerCoord = c.getCoord();
            start = c.getStartTime();
            end = c.getEndTime();
            cleanerFound = true;
            break;
        }
    }

    if (!cleanerFound)
    {
        throw invalid_argument("Cleaner ID not found");
    }

    map<int, Sensor> sensors = system.getSensors();
    map<int, vector<Measurement>> measurements = system.getMeasurements();

    // Trier les capteurs par distance par rapport aux coordonnées du cleaner
    multimap<double, Sensor> sortedSensors = sortSensors(sensors, cleanerCoord);

    Time before_start(start.getYear(), start.getMonth(), start.getDay() - 1, start.getHour(), start.getMinute(), start.getSecond());
    Time before_end(end.getYear(), end.getMonth(), end.getDay() - 1, end.getHour(), end.getMinute(), end.getSecond());
    ;

    double impactRadius = 0.0;

    for (const auto &pair : sortedSensors)
    {
        double distance = pair.first;
        Sensor sensor = pair.second;

        // Filtrer les mesures pour ce capteur particulier
        map<int, vector<Measurement>> sensorMeasurements;
        sensorMeasurements[sensor.getSensorID()] = sensor.getMeasurements();

        map<int, vector<Measurement>> beforeMeasurements = filterMeasurements(before_start, start, sensorMeasurements);
        map<int, vector<Measurement>> afterMeasurements = filterMeasurements(before_end, end, sensorMeasurements);

        double qualityBeforeCleaner = calculateQuality(beforeMeasurements);
        double qualityAfterCleaner = calculateQuality(afterMeasurements);

        if (qualityAfterCleaner >= qualityBeforeCleaner)
        {
            impactRadius = distance;
        }
        else
        {
            break;
        }
    }

    return impactRadius;

    // Si cleanerId n'est pas trouvé, lancer une exception
    throw invalid_argument("Cleaner ID not found");
}

/**
 * @brief Calculates the ATMO for all the measurements in the specified zone and during the specified time
 *
 * @param zone
 * @param start
 * @param end
 * @return double
 */
double Service::calculateQuality(const Zone &zone, const Time &start, const Time &end)
{
    vector<vector<double>> pollutantMaxValues;
    vector<Time> pollutantLastTime;
    pollutantLastTime[O3] = Time(0, 0, 0, 0, 0, 0);
    pollutantLastTime[NO2] = Time(0, 0, 0, 0, 0, 0);
    pollutantLastTime[SO2] = Time(0, 0, 0, 0, 0, 0);
    pollutantLastTime[PM10] = Time(0, 0, 0, 0, 0, 0);
    
    // A map where:
    // - Key: Represents the day
    // - Value: map of measurements done during the day corresponding to the key
    map<int, map<int,vector<Measurement>>> filteredMeasurements;

    for (const auto &sensorData : system.getMeasurements())
    {
        for (const auto &measurement : sensorData.second)
        {
            // Check if measurement falls within the specified time range
            if (measurement.getTimestamp() >= start && measurement.getTimestamp() <= end && !measurement.isBlacklisted()) {
                // Check if measurement falls within the specified zone
                map<int, Sensor> s = system.getSensors();
                if (isInZone(s[measurement.getSensorID()].getLocation(), zone))
                {
                    filteredMeasurements[measurement.getTimestamp().getDay()][sensorData.first].push_back(measurement);
                }
            }
        }
    }
    double sum_indexes = 0.0;
    int count_days = 0;
    for(const auto &measurementsPerDay : filteredMeasurements){
       
            sum_indexes += calculateQuality(measurementsPerDay.second);
            count_days += 1;
    }
    double average_indexes = sum_indexes/count_days;

    return average_indexes;
}

double Service::calculateQuality(const map<int, vector<Measurement>> &measurements)
{
    vector<vector<double>> pollutantMaxValues;
    vector< Time> pollutantLastTime;
    pollutantLastTime[O3] = Time(0, 0, 0, 0, 0, 0);
    pollutantLastTime[NO2] = Time(0, 0, 0, 0, 0, 0);
    pollutantLastTime[SO2] = Time(0, 0, 0, 0, 0, 0);
    pollutantLastTime[PM10] = Time(0, 0, 0, 0, 0, 0);

    for (const auto &sensorData : measurements)
    {
        for (const auto &measurement : sensorData.second)
        {
            // Only consider non-blacklisted measurements
            if (!measurement.isBlacklisted())
            {
                PollutantType  attr = measurement.getAttributeID();
                double val = measurement.getValue();

                if (pollutantLastTime[attr].isSameHour(measurement.getTimestamp()))
                {
                    if (val > pollutantMaxValues[attr].back())
                    {
                        pollutantMaxValues[attr].back() = val;
                    }
                }
                else
                {
                    pollutantMaxValues[attr].push_back(val);
                }
            }
        }
    }

    // Get maximum values for pollutants
    double avgO3 = !pollutantMaxValues[O3].empty() ? average(pollutantMaxValues[O3]) : 0;
    double avgNO2 = !pollutantMaxValues[NO2].empty() ? average(pollutantMaxValues[NO2]) : 0;
    double avgSO2 = !pollutantMaxValues[SO2].empty() ? average(pollutantMaxValues[SO2]) : 0;
    double avgPM10 = !pollutantMaxValues[PM10].empty() ? average(pollutantMaxValues[PM10]) : 0;

    // Calculate sub-indices
    int indexO3 = calculateSubIndex(avgO3, O3);
    int indexNO2 = calculateSubIndex(avgNO2, NO2);
    int indexSO2 = calculateSubIndex(avgSO2, SO2);
    int indexPM10 = calculateSubIndex(avgPM10, PM10);

    // Calculate the Atmo index as the maximum of sub-indices
    return max({avgO3, avgNO2, avgSO2, avgPM10});
}

/**
 * @brief calculates the index for a particular pollutant
 *
 * @param value
 * @param pollutant
 * @return int
 */
int Service::calculateSubIndex(const double &value, const PollutantType &pollutant) const
{
    if (pollutant == O3)
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
    else if (pollutant == NO2)
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
    else if (pollutant == SO2)
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
    else if (pollutant == PM10)
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

/**
 * @brief calculates the average of a vector<double>
 *
 * @param v
 * @return double
 */
double Service::average(const vector<double> &v)
{
    double sum = 0;

    for (const auto &i : v)
    {
        sum += i;
    }
    return sum / v.size();
}

/**
 * @brief checks if the coord is inside the zone
 *
 * @param c
 * @param z
 * @return true
 * @return false
 */
bool Service::isInZone(const Coord c, const Zone z)
{
    double d = distance(c, z);
    return d < z.radius;
}

// /**
//  * @brief Construct a new Service:: Service object
//  *
//  * @param system
//  */
// Service::Service(const System &s) : system(s) {}

Service::~Service(){};