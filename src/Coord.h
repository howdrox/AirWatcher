#ifndef COORD_H
#define COORD_H

struct Coord {
public:
    double latitude;
    double longitude;

public:
    Coord(double lat, double lng) : latitude(lat), longitude(lng) {}

    Coord(const Coord &coord) : latitude(coord.latitude), longitude(coord.longitude) {}
};

#endif // COORD_H
