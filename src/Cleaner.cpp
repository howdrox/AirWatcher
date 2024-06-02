#include <sstream>
#include <vector>

#include "Cleaner.h"

Cleaner::Cleaner(const std::string &data)
{
    std::vector<std::string> values;
    std::stringstream ss(data);
    std::string item;

    while (std::getline(ss, item, ';'))
    {
        values.push_back(item);
    }

    // Id
    std::string idStr = values[0].substr(7); // take only the number value in value[0], example: 'Cleaner0' --> '0'
    cleanerID = std::stoi(idStr);

    // Location
    double lat = std::stod(values[1]);
    double lng = std::stod(values[2]);
    location = Coord(lat, lng);

    // Start + end Timestamp
    startTime = Time(values[3]);
    endTime = Time(values[4]);
}
