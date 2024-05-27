#ifndef GOVERNMENTAGENT_H
#define GOVERNMENTAGENT_H

#include "User.h" // Pour hériter de la classe User

class GovernmentAgent : public User {
public:
    GovernmentAgent(); // Constructeur par défaut
    ~GovernmentAgent(); // Destructeur
};

#endif // GOVERNMENTAGENT_H
