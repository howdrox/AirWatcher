#include <sstream>

#include "Provider.h"


Provider::Provider() : User(Role::PROVIDER) {}

Provider::Provider(const std::string& providerInfo) : User(Role::PROVIDER), providerID(-1) {

    #ifdef MAP
        cout << "Appel au constructeur de <provider>" << endl;
    #endif 

    // Utilisation d'un flux de chaînes pour extraire les informations de providerInfo
    std::stringstream ss(providerInfo);

    // Extraction de l'ID du fournisseur
    ss.ignore(providerInfo.find_first_of("0123456789"));
    ss >> providerID;

    // Extraction des IDs des nettoyeurs
    int cleanerID;
    while (ss >> cleanerID) {
        cleanersID.push_back(cleanerID);
        ss.ignore(providerInfo.find_first_of("0123456789"));
    }
}

Provider::~Provider() {
    #ifdef MAP
        cout << "Appel au destructeur de <provider>" << endl;
    #endif 
    // Le destructeur peut être vide s'il n'y a rien à faire spécifiquement lors de la destruction
}

int Provider::getProviderID() const {
    return providerID;
}

const std::vector<int>& Provider::getCleanersID() const {
    return cleanersID;
}
