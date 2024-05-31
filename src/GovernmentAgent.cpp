#include <iostream>

#include "GovernmentAgent.h"

using namespace std;

GovernmentAgent::GovernmentAgent() : User(Role::GOVERNMENT_AGENT) {
    #ifdef MAP
        cout << "Appel au constructeur de <governmentAgent>" << endl;
    #endif 
    // Utilisation du constructeur de User avec le rôle GOVERNMENT_AGENT
}

GovernmentAgent::~GovernmentAgent() {
    #ifdef MAP
        cout << "Appel au destructeur de <governmentAgent>" << endl;
    #endif 
    // Le destructeur peut être vide s'il n'y a rien à faire spécifiquement lors de la destruction
}
