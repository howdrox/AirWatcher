#ifndef ZONE_H
#define ZONE_H

#include "Coord.h"

struct Zone : public Coord
{
    double radius;

    Zone(double lat, double lng, double rad) : Coord(lat, lng), radius(rad) {}

    Zone(const Zone &zone) : Coord(zone), radius(zone.radius) {}
};

#endif // ZONE_H
