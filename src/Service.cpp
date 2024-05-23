using namespace std;
#include <iostream>
#include <cmath>

#include "Coord.h"

double distance(const Coord &coord1, const Coord &coord2)
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