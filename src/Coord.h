#if !defined(COORD_H)
#define COORD_H

typedef struct _Coord
{
    double latitude;
    double longitude;

    _Coord(double lat, double lng) : latitude(lat), longitude(lng){};

    _Coord(const Coord &coord) : latitude(coord.latitude), longitude(coord.longitude){};
} Coord;

#endif // COORD_H