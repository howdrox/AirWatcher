using namespace std;


#include <iostream>
#include <string>

#include "User.h"


Role User::get_role () const
{
    return role;
}


User::User ( const User & unUser )
{
    #ifdef MAP
        cout << "Appel au constructeur de copie de <User>" << endl;
    #endif
        role=unUser.role;
}


User::User ( Role lerole)
{
    #ifdef MAP
        cout << "Appel au constructeur de <User>" << endl;
    #endif
  role=lerole;
}


User::~User ( )
{
    #ifdef MAP
        cout << "Appel au destructeur de <User>" << endl;
    #endif 
}
