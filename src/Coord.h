#ifndef COORD_H
#define COORD_H

struct Coord {
protected:
    double latitude;
    double longitude;

public:
    Coord(double lat, double lng) : latitude(lat), longitude(lng) {}

    Coord(const Coord &coord) : latitude(coord.latitude), longitude(coord.longitude) {}

    double getLatitude() const {
        return latitude;
    }

    double getLongitude() const {
        return longitude;
    }
};

#endif // COORD_H
