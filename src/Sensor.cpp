#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include "Sensor.h"
#include "Coord.h"

using namespace std;

Sensor::Sensor (const int id, const Coord loc, const bool stat){
#ifdef MAP
    cout << "Appel au constructeur de <Sensor>" << endl;
#endif
    sensorID = id;
    location.latitude = loc.latitude;
    location.longitude = loc.longitude;
    status = stat;

}

Sensor::Sensor (string &sensorLine){
#ifdef MAP
    cout << "Appel au constructeur de <Sensor>" << endl;
#endif
    string data = sensorLine.substr(6); 
    
    vector<string> attributes;
    string attribute;
    istringstream tokenStream(data);
    while (getline(tokenStream, attribute, ';')) {
        attributes.push_back(attribute);
    }
    
    if (attributes.size() >= 3) {
        sensorID = stoi(attributes[0]);
        location.latitude = stod(attributes[1]);
        location.longitude = stod(attributes[2]);
    }
   

}
Sensor::~Sensor ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <Sensor>" << endl;
#endif
    
}
   

const Sensor:: int & getSensorID(){
    return sensorID;
}
const Sensor:: Coord & getLocation(){
    return location;
}
const Sensor:: bool & getStauts(){
    return status;
}
const Sensor:: vector<Measurement> & getMeasurements(){
    return measurements;
}

Sensor:: void setSensorID(const int &id){
    sensorID = id;
}
Sensor:: void setLocation(const Coord &loc){
    location = loc;
}
Sensor:: void setStatus(const bool &stat){
    status = stat;
}
void Sensor::addMeasurement(const Measurement& measurement) {
    measurements.push_back(measurement);
}

