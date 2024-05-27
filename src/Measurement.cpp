

#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Measurement.h"

int Measurement::  getSensorID(){
    return sensorID;
}

    Time Measurement::  getTimestamp(){
        return timestamp;
    }

    int Measurement:: getDay(){
        //A faire
    }

//-------------------------------------------- Constructeurs - destructeur
Measurement::Measurement ( const Measurement & unMeasurement ) 
     : measurementID(unMeasurement.measurementID),
       timestamp(unMeasurement.timestamp),
       attributeID(unMeasurement.attributeID),
       value(unMeasurement.value),
       sensorID(unMeasurement.sensorID)
  
{

} 


 Measurement::Measurement(const string &ligne) {
    stringstream ss(ligne);
    string item;
    vector<string> elements;

    
    while (getline(ss, item, ';')) {
        elements.push_back(item);
    }

   
    if (elements.size() == 4) {
        timestamp = elements[0];
        sensorID = elements[1];  
        attributeID = elements[2];
        value = stod(elements[3]);  
    } else {
       
        cerr << "Erreur : ligne mal formée." << endl;
    }
}

Measurement::~Measurement ( )


{
    
} 



