#include <iostream>
#include <cmath>

#include "Service.h"
#include "Coord.h"
#include "Zone.h"

using namespace std;

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

// map<int, vector<Measurement>> measurements;

double Service::calculateQuality(const Zone &zone, const Time &start, const Time &end)
{
    map<string, vector<double>> polluantMaxValues;
    map<string, Time> polluantLastTime;

    for (const auto &sensorData : system.measurements)
    {
        for (const auto &measurement : sensorData.second)
        {
            if (measurement.getTimestamp() >= start && measurement.getTimestamp() <= end && !measurement.isBlacklisted())
            {
                string attr = measurement.getAttributeID();
                double val = measurement.getValue();
                
                pollutantMaxValues[attr].push_back(val);
            }
        }
    }

    // Calculate averages
    double avgPM10 = pm10Values["PM10"] / 24.0; // Assuming 24-hour day

    // Get maximum values for pollutants
    double maxO3 = !pollutantMaxValues["O3"].empty() ? *max_element(pollutantMaxValues["O3"].begin(), pollutantMaxValues["O3"].end()) : 0;
    double maxNO2 = !pollutantMaxValues["NO2"].empty() ? *max_element(pollutantMaxValues["NO2"].begin(), pollutantMaxValues["NO2"].end()) : 0;
    double maxSO2 = !pollutantMaxValues["SO2"].empty() ? *max_element(pollutantMaxValues["SO2"].begin(), pollutantMaxValues["SO2"].end()) : 0;

    // Calculate sub-indices
    int indexO3 = calculateSubIndex(maxO3, "O3");
    int indexNO2 = calculateSubIndex(maxNO2, "NO2");
    int indexSO2 = calculateSubIndex(maxSO2, "SO2");
    int indexPM10 = calculateSubIndex(avgPM10, "PM10");

    // ATMO index is the maximum of the sub-indices
    return max({indexO3, indexNO2, indexSO2, indexPM10});
}

int Service::calculateSubIndex(double value, const string &pollutant) const
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