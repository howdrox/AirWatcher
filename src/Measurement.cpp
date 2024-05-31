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

    if (elements.size() == 4)
    {
        timestamp = elements[0];
        sensorID = stoi(elements[1].substr(6));
        if (elements[2] == "O3") attributeID = O3;
        else if (elements[2] == "NO2") attributeID = NO2;
        else if (elements[2] == "SO2") attributeID = SO2;
        else if (elements[2] == "PM10") attributeID = PM10;
        
        value = stod(elements[3]);
    }
    else
    {
        cerr << "Erreur : ligne mal formée." << endl;
    }
}