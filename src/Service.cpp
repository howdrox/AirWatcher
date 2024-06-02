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
#include "System.h"

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

/**
 * @brief Checks if the coord is inside the zone
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

/**
 * @brief Returns a `map` of measurements that fall within the specified time range
 *
 * @param start
 * @param end
 * @param measurements
 * @return map<int, vector<Measurement>>
 */
map<int, vector<Measurement>> Service::filterMeasurements(const Time &start, const Time &end, map<int, vector<Measurement>> measurements)
{
    if (start > end)
    {
        throw invalid_argument("Start time must be before end time");
    }
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
            if (measureTime >= start && measureTime < end)
            {
                filteredList.push_back(m);
            }
        }
        if (!filteredList.empty())
        {
            res[itr->first] = filteredList;
        }
    }
    return res;
}

/**
 * @brief Sorts the sensors by distance from a specified coordinate
 *
 * @param sensors
 * @param coord
 * @return multimap<double, Sensor>
 */
multimap<double, Sensor> Service::sortSensors(const map<int, Sensor> &sensors, const Coord &coord)
{
    multimap<double, Sensor> sortedSensors;

    for (auto it = sensors.begin(); it != sensors.end(); ++it)
    {
        double distance = this->distance(it->second.getLocation(), coord);
        sortedSensors.insert(pair<double, Sensor>(distance, it->second));
    }
    return sortedSensors;
}

/**
 * @brief Calculates the ATMO for all the measurements in the specified zone and during the specified time
 *
 * @details Calculates the ATMO index per day and then averages it for the total number of days
 *
 * @param zone
 * @param start
 * @param end
 * @return double
 */
double Service::calculateQuality(const Zone &zone, const Time &start, const Time &end)
{
    if (start > end)
    {
        throw invalid_argument("Start time must be before end time");
    }
    // A map where:
    // - Key: Represents the day
    // - Value: map of measurements done during the day corresponding to the key
    map<Time, map<int, vector<Measurement>>> filteredMeasurements;

    for (const auto &sensorData : system.getMeasurements())
    {
        for (const auto &measurement : sensorData.second)
        {
            // Check if measurement falls within the specified time range
            if (measurement.getTimestamp() >= start && measurement.getTimestamp() <= end && !measurement.isBlacklisted())
            {
                // Check if measurement falls within the specified zone
                map<int, Sensor> s = system.getSensors();
                if (isInZone(s[measurement.getSensorID()].getLocation(), zone))
                {
                    Time timestamp = measurement.getTimestamp();
                    Time date = timestamp.zeroOutHour();
                    filteredMeasurements[date][sensorData.first].push_back(measurement);
                }
            }
        }
    }
    double sum_indexes = 0.0;
    int count_days = 0;
    for (const auto &measurementsPerDay : filteredMeasurements)
    {
        sum_indexes += calculateQuality(measurementsPerDay.second);
        count_days += 1;
    }
    double average_indexes = (count_days > 0) ? (sum_indexes / count_days) : 0;

    return average_indexes;
}

/**
 * @brief Calculates the ATMO index for all the measurements
 *
 * @details For each pollutant, stores the maximum value for each hour, then caculates the average to get the sub index
 * The ATMO index is the maximum of all the sub indexes
 *
 * @pre The function does group up the measurements per day
 *
 * @param measurements
 * @return double
 */
double Service::calculateQuality(const map<int, vector<Measurement>> &measurements)
{
    if (measurements.empty())
    {
        return 0; // Return a default value, such as 0, when there are no measurements
    }

    map<PollutantType, vector<double>> pollutantMaxValues;
    map<PollutantType, Time> pollutantLastTime;
    pollutantLastTime[O3] = Time(0, 0, 0, 0, 0, 0);
    pollutantLastTime[NO2] = Time(0, 0, 0, 0, 0, 0);
    pollutantLastTime[SO2] = Time(0, 0, 0, 0, 0, 0);
    pollutantLastTime[PM10] = Time(0, 0, 0, 0, 0, 0);

    for (const auto &sensorData : measurements)
    {
        for (const auto &measurement : sensorData.second)
        {
            if (!measurement.isBlacklisted())
            {
                PollutantType attr = measurement.getAttributeID();
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
    // cout << "first pollutantMaxValues: " << pollutantMaxValues[O3][0] << endl;

    // Get maximum values for pollutants
    double avgO3 = !pollutantMaxValues[O3].empty() ? average(pollutantMaxValues[O3]) : 0;
    // cout << "avgO3: " << avgO3 << endl;
    double avgNO2 = !pollutantMaxValues[NO2].empty() ? average(pollutantMaxValues[NO2]) : 0;
    double avgSO2 = !pollutantMaxValues[SO2].empty() ? average(pollutantMaxValues[SO2]) : 0;
    double avgPM10 = !pollutantMaxValues[PM10].empty() ? average(pollutantMaxValues[PM10]) : 0;

    // Calculate sub-indices
    int indexO3 = calculateSubIndex(avgO3, O3);
    int indexNO2 = calculateSubIndex(avgNO2, NO2);
    int indexSO2 = calculateSubIndex(avgSO2, SO2);
    int indexPM10 = calculateSubIndex(avgPM10, PM10);

    // Calculate the Atmo index as the maximum of sub-indices
    return max({indexO3, indexNO2, indexSO2, indexPM10});
}

multimap<double, int> Service ::getSimilarZones(const int &sensorID, const Time &start, const Time &end, const double &delta)
{

    multimap<double, int> similarSensors;
    map<int, Sensor> sensors = system.getSensors();
    // Vérifier si sensorId est dans la liste des sensors
    bool sensorFound = false;
    for (const auto &pair : sensors)
    {
        Sensor s = pair.second;
        if (s.getSensorID() == sensorID)
        {
            sensorFound = true;
            break;
        }
    }

    if (!sensorFound)
    {
        throw invalid_argument("Sensor ID not found");
    }
    if (delta <= 0)
    {
        throw invalid_argument("Delta invalid");
    }

    map<int, vector<Measurement>> measurements = system.getMeasurements();
    map<int, vector<Measurement>> filteredMeasurements = filterMeasurements(start, end, measurements);
    map<int, vector<Measurement>> parameterSensorMeasurements;
    if (filteredMeasurements.empty())
    {
        return similarSensors;
    }
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

/**
 * @brief Calculates the impact radius of a cleaner
 *
 * @param cleanerId
 * @return double
 */
double Service::calculateImpactRadius(int cleanerId)
{
    const vector<Cleaner> &cleaners = system.getCleaners();
    Coord cleanerCoord;
    Time start, end;

    auto it = cleaners.begin();
    while (it != cleaners.end())
    {
        if (it->getCleanerId() == cleanerId)
        {
            cleanerCoord = it->getCoord();
            start = it->getStartTime();
            end = it->getEndTime();
            break;
        }
        ++it;
    }

    if (it == cleaners.end())
    {
        throw std::invalid_argument("Cleaner ID not found");
    }
    cout << "Cleaner ID: " << cleanerId << " Coord: " << cleanerCoord.latitude << ", " << cleanerCoord.longitude << endl;

    // Sort sensors by distance from the cleaner
    multimap<double, Sensor> sortedSensors = sortSensors(system.getSensors(), cleanerCoord);

    Time before_start = start.addDays(-1);
    Time before_end = end.addDays(-1);

    cout << "before start: " << before_start << " start: " << start << endl;
    cout << "before end: " << before_end << " end: " << end << endl;

    double impactRadius = 0.0;

    for (const auto &pair : sortedSensors)
    {
        double distance = pair.first;
        const Sensor &sensor = pair.second;

        auto sensorMeasurements = sensor.getMeasurements();
        map<int, vector<Measurement>> measurements;
        measurements[sensor.getSensorID()] = sensorMeasurements;
        cout << "Measurements: " << sensorMeasurements.size() << endl;

        auto beforeMeasurements = filterMeasurements(before_start, start, measurements);
        auto afterMeasurements = filterMeasurements(before_end, end, measurements);

        cout << "beforeMeasurements: " << beforeMeasurements.size() << endl;
        cout << "afterMeasurements: " << afterMeasurements.size() << endl;

        double qualityBeforeCleaner = calculateQuality(beforeMeasurements);
        double qualityAfterCleaner = calculateQuality(afterMeasurements);

        cout << "Quality before cleaner: " << qualityBeforeCleaner << endl;
        cout << "Quality after cleaner: " << qualityAfterCleaner << endl;
        cout << "Distance: " << distance << endl;

        if (qualityAfterCleaner > qualityBeforeCleaner)
        {
            impactRadius = distance;
        }
        else
        {
            break;
        }
    }

    return impactRadius;
}

/**
 * @brief Calculates the sub index for a particular pollutant
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
 * @brief Calculates the average of a vector<double>
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
    return v.size() > 0 ? sum / v.size() : 0;
}