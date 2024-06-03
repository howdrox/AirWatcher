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
        Sensor s = system.getSensors().at(sensorData.first);
        if (isInZone(s.getLocation(), zone))
        {
            for (const auto &measurement : sensorData.second)
            {
                // Check if measurement falls within the specified time range
                if (measurement.getTimestamp() >= start && measurement.getTimestamp() <= end && !measurement.isBlacklisted())
                {
                    filteredMeasurements[measurement.getTimestamp().zeroOutHour()][sensorData.first].push_back(measurement);
                }
            }
        }
    }

    // Calculates average index
    double sum_indexes = 0.0;
    int count_days = 0;
    for (const auto &measurementsPerDay : filteredMeasurements)
    {
        double temp = calculateQuality(measurementsPerDay.second);
        sum_indexes += temp;
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
    // A map where:
    // - Key: Represents the pollutant name
    // - Value: a pair where the first element represents the sum of the concentrations of the pollutant and the value is the number of measures
    map<PollutantType, pair<double, int>> measurementsSumPerPollutant;
    for (const auto &sensorData : measurements)
    {
        for (const auto &measurement : sensorData.second)
        {
            if (!measurement.isBlacklisted())
            {
                measurementsSumPerPollutant[measurement.getAttributeID()].first += measurement.getValue();
                measurementsSumPerPollutant[measurement.getAttributeID()].second += 1;
            }
        }
    }

    // Get maximum values for pollutants
    double avgO3 = !(measurementsSumPerPollutant[O3].second == 0) ? (measurementsSumPerPollutant[O3].first / measurementsSumPerPollutant[O3].second) : 0;
    double avgNO2 = !(measurementsSumPerPollutant[NO2].second == 0) ? (measurementsSumPerPollutant[NO2].first / measurementsSumPerPollutant[NO2].second) : 0;
    double avgSO2 = !(measurementsSumPerPollutant[SO2].second == 0) ? (measurementsSumPerPollutant[SO2].first / measurementsSumPerPollutant[SO2].second) : 0;
    double avgPM10 = !(measurementsSumPerPollutant[PM10].second == 0) ? (measurementsSumPerPollutant[PM10].first / measurementsSumPerPollutant[PM10].second) : 0;
    // if no values added (all blacklisted)
    if (max({avgO3, avgNO2, avgSO2, avgPM10}) == 0)
    {
        return 0;
    }

    // Calculate sub-indices
    int indexO3 = calculateSubIndex(avgO3, O3);
    int indexNO2 = calculateSubIndex(avgNO2, NO2);
    int indexSO2 = calculateSubIndex(avgSO2, SO2);
    int indexPM10 = calculateSubIndex(avgPM10, PM10);

    // Calculate the Atmo index as the maximum of sub-indices
    return max({indexO3, indexNO2, indexSO2, indexPM10});
}

/**
 * @brief Ranks the sensors based on the quality difference between the specified sensor and the other sensors
 *
 * @details Returns the ranking as a map with key: quality difference and value:vector of sensor IDs
 * If no measurements for a sensors are found, the sensor's quality is set to 0
 *
 * @param sensorID
 * @param start
 * @param end
 * @return map<double, vector<int>>
 */
map<double, vector<int>> Service::rankSimilarSensors(int sensorID, const Time &start, const Time &end)
{
    // Key: sensorID, Value: Sensor
    map<int, Sensor> sensors = system.getSensors();

    // Check if sensorID is in the list of sensors
    if (sensors.find(sensorID) == sensors.end())
    {
        throw invalid_argument("Sensor ID not found");
    }

    // Key: quality difference, Value: vector of sensor IDs
    map<double, vector<int>> ranking;
    // Key: sensorID, Value: vector of Measurements
    map<int, vector<Measurement>> filteredMeasurements = filterMeasurements(start, end, system.getMeasurements());
    double sensorQuality = calculateQuality({{sensorID, filteredMeasurements[sensorID]}});

    // For each sensor, calculate the quality difference
    for (const auto &sensor : sensors)
    {
        int otherSensorID = sensor.first;

        if (otherSensorID != sensorID && filteredMeasurements.find(otherSensorID) != filteredMeasurements.end() && !filteredMeasurements[otherSensorID].empty())
        {
            double otherSensorQuality = calculateQuality({{otherSensorID, filteredMeasurements[otherSensorID]}});

            double qualityDifference = abs(sensorQuality - otherSensorQuality);
            ranking[qualityDifference].push_back(otherSensorID);
        }
    }

    return ranking;
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
        if (it->getCleanerID() == cleanerId)
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

    // Sort sensors by distance from the cleaner
    multimap<double, Sensor> sortedSensors = sortSensors(system.getSensors(), cleanerCoord);

    Time before_start = start.addDays(-1);
    Time before_end = end.addDays(-1);

    double impactRadius = 0.0;

    for (const auto &pair : sortedSensors)
    {
        double distance = pair.first;
        const Sensor &sensor = pair.second;

        auto measurements = system.getMeasurements();
        if (measurements[sensor.getSensorID()].empty())
        {
            continue;
        }

        auto sensorMeasurements = measurements[sensor.getSensorID()];

        auto beforeMeasurements = filterMeasurements(before_start, start, {{sensor.getSensorID(), sensorMeasurements}});
        auto afterMeasurements = filterMeasurements(before_end, end, {{sensor.getSensorID(), sensorMeasurements}});

        // Incrémenter les points des utilisateurs privés
        auto privateUsers = system.getUsers();

        for (const auto &measurement : beforeMeasurements)
        {
            int sensorID = measurement.first;
            for (auto &user : privateUsers)
            {
                if (std::find(user.getSensorsID().begin(), user.getSensorsID().end(), sensorID) != user.getSensorsID().end() && !user.isBlacklisted())
                {
                    user.addPoints(measurement.second.size()); // Ajoute un point pour chaque mesure avant le nettoyage
                    break;
                }
            }
        }

        for (const auto &measurement : afterMeasurements)
        {
            int sensorID = measurement.first;
            for (auto &user : privateUsers)
            {
                if (std::find(user.getSensorsID().begin(), user.getSensorsID().end(), sensorID) != user.getSensorsID().end() && !user.isBlacklisted())
                {
                    user.addPoints(measurement.second.size()); // Ajoute un point pour chaque mesure après le nettoyage
                    break;
                }
            }
        }

        double qualityBeforeCleaner = calculateQuality(beforeMeasurements);
        double qualityAfterCleaner = calculateQuality(afterMeasurements);

        if (qualityAfterCleaner < qualityBeforeCleaner)
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
 * @brief Blacklists a private user and all of his measurements
 *
 * @param userID
 */
void Service::blacklistPrivateUser(int userID)
{
    vector<PrivateUser> &users = system.getUsers();
    auto userIt = find_if(users.begin(), users.end(), [userID](PrivateUser &user)
                          { return user.getUserID() == userID; });

    if (userIt != users.end())
    {
        userIt->setBlacklisted(true);

        for (const auto &sensorID : userIt->getSensorsID())
        {
            auto sensorIt = system.getSensors().find(sensorID);
            if (sensorIt != system.getSensors().end())
            {
                auto &measurements = system.getMeasurements().at(sensorID);
                for (auto &measurement : measurements)
                {
                    measurement.setBlacklisted(true);
                }
            }
            else
            {
                continue;
            }
        }
    }
    else
    {
        throw invalid_argument("User ID not found");
    }
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
    if (value < 0)
    {
        return 0;
    }
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