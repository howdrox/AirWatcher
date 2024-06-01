#ifndef COORD_H
#define COORD_H

struct Coord
{
    double latitude;
    double longitude;

    Coord(double lat = 0, double lng = 0) : latitude(lat), longitude(lng) {}
};

#endif // COORD_H
