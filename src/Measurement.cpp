#include <iostream>
#include <sstream>
#include <vector>

#include "Measurement.h"

using namespace std;

Measurement::Measurement(const string &ligne)
{

    stringstream ss(ligne);
    string item;
    vector<string> elements;

    while (getline(ss, item, ';'))
    {
        elements.push_back(item);
    }
    
   
        timestamp = Time(elements[0]);
        sensorID = std::stoi(elements[1].substr(6));
        if (elements[2] == "O3") attributeID = O3;
        else if (elements[2] == "NO2") attributeID = NO2;
        else if (elements[2] == "SO2") attributeID = SO2;
        else if (elements[2] == "PM10") attributeID = PM10;
        
        value = stod(elements[3]);
        if (value < 0) {
            cerr << "Attention the measured value is negative and was changed to 0" << endl;
            value = 0;
        }
        blacklisted = false;
    
}

std::ostream& operator<<(std::ostream& os, const Measurement& measurement) {
    os << " , Measurement ID: " << measurement.measurementID 
       << " , Timestamp: " << measurement.timestamp 
       << " , Sensor ID: " << measurement.sensorID 
       << " , Attribute ID: " << static_cast<int>(measurement.attributeID) 
       << " , Value: " << measurement.value 
       << " , Blacklisted: " << (measurement.blacklisted ? "Yes" : "No");
    return os;
}