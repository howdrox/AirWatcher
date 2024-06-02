#if !defined(USER_H)
#define USER_H

#include "Role.h"

using namespace std;

class User
{
public:
    // Constructors
    User(const Role &r) : role(r) {};
    User(const User &user) : role(user.role) {};

    // Destructor
    virtual ~User();

    // Operator overload
    User &operator=(const User &user);

    // Getters
    Role getRole() const { return role; };

protected:
    Role role;
};

#endif // USER_H
