#ifndef ZONE_H
#define ZONE_H

#include "Coord.h"

struct Zone : public Coord
{
    double radius;

    Zone(double lat = 0, double lng = 0, double rad = 0) : Coord(lat, lng), radius(rad) {}
    Zone(const Coord& c, double rad = 0) : Coord(c), radius(rad) {}
    Zone(const Zone &zone) : Coord(zone), radius(zone.radius) {}
};

#endif // ZONE_H
