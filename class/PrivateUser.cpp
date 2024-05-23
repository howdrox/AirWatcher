#include "PrivateUser.h"
#include <sstream>

PrivateUser::PrivateUser(const std::string& userInfo) : User(Role::PRIVATE_USER), points(0), blacklisted(false) {

    #ifdef MAP
        cout << "Appel au constructeur de <privateUser>" << endl;
    #endif 

    // Utilisation d'un flux de chaînes pour extraire les informations de userInfo
    std::stringstream ss(userInfo);

    // Extraction de l'ID de l'utilisateur privé
    ss.ignore(userInfo.find_first_of("0123456789"));
    ss >> userID;

    // Extraction des IDs des capteurs
    int sensorID;
    while (ss >> sensorID) {
        sensorsID.push_back(sensorID);
        ss.ignore(userInfo.find_first_of("0123456789"));
    }
}

PrivateUser::~PrivateUser() {
    #ifdef MAP
        cout << "Appel au destructeur de <privateUser>" << endl;
    #endif 
    // Le destructeur peut être vide s'il n'y a rien à faire spécifiquement lors de la destruction
}

int PrivateUser::getUserID() const {
    return userID;
}

const std::vector<int>& PrivateUser::getSensorsID() const {
    return sensorsID;
}

int PrivateUser::getPoints() const {
    return points;
}

bool PrivateUser::isBlacklisted() const {
    return blacklisted;
}

void PrivateUser::setBlacklisted(bool isBlacklisted){
    blacklisted= isBlacklisted;
}

void PrivateUser::addPoints(int nbPoints) {
    points += nbPoints; // Incrémentation du nombre de points
}

