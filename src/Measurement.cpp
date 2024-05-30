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
        attributeID = elements[2];
        value = stod(elements[3]);
    }
    else
    {
        cerr << "Erreur : ligne mal formée." << endl;
    }
}