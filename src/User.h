#if !defined(USER_H)
#define USER_H

#include <iostream>
#include "Role.h"

using namespace std;

class User
{
public:
    string get_role() const;

    // Méthode virtuelle pure rendant la classe abstraite
    virtual void printDetails() const = 0;

    User(const User &unuser);

    User(const Role &leRole) : role(leRole) {}

    virtual ~User();

protected:
    Role role;
};

#endif // USER_H
