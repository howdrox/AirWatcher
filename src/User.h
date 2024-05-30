#if !defined(USER_H)
#define USER_H

#include "Role.h"

using namespace std;

class User
{
public:
    Role getRole() const;

    virtual void printDetails() const = 0;

    User(const Role &r);
    User(const User &user);
    virtual ~User();

protected:
    Role role;
};

#endif // USER_H
