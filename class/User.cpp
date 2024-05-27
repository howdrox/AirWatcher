#include "User.h"

User::User(Role userRole) : role(userRole) {
    #ifdef MAP
        cout << "Appel au constructeur de <user>" << endl;
    #endif 
} // Initialisation de l'attribut dans le constructeur

Role User::getRole() const {
    return role; // Retourne le rôle
}

User::~User() {
    #ifdef MAP
        cout << "Appel au destructeur de <user>" << endl;
    #endif 
    // Le destructeur peut être vide s'il n'y a rien à faire spécifiquement lors de la destruction
}
