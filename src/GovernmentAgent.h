#ifndef GOVERNMENTAGENT_H
#define GOVERNMENTAGENT_H

#include "User.h"

class GovernmentAgent : public User
{
public:
    // Constructors
    GovernmentAgent() : User(Role::GOVERNMENT_AGENT){};

    // Destructor
    ~GovernmentAgent(){};
};

#endif // GOVERNMENTAGENT_H
