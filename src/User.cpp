#include <iostream>
#include <sstream>

#include "User.h"

User::User(const Role &userRole) : role(userRole)
{
#ifdef MAP
    cout << "Appel au constructeur de <user>" << endl;
#endif
}

User::User(const User &user) : role(user.role)
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <user>" << endl;
#endif
}

User& User::operator=(const User &user)
{
    if (this != &user)
    {
        role = user.role;
    }
    return *this;
}

User::~User()
{
#ifdef MAP
    cout << "Appel au destructeur de <user>" << endl;
#endif
}

Role User::getRole() const
{
    return role;
}
