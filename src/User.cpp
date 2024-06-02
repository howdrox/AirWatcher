#include <iostream>
#include <sstream>

#include "User.h"

User::~User() {}

User &User::operator=(const User &user)
{
    if (this != &user)
    {
        role = user.role;
    }
    return *this;
}
