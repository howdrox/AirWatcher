#ifndef COORD_H
#define COORD_H

struct Coord
{
    double latitude;
    double longitude;

    Coord(double lat, double lng) : latitude(lat), longitude(lng) {}

    Coord(const Coord &coord) : latitude(coord.latitude), longitude(coord.longitude) {}

    Coord() {};
};

#endif // COORD_H
