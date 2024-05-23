//---------- Interface de la classe  <user> (fichier user.h) ----------------
#if ! defined ( USER_H )
#define USER_H

#include <iostream>
#include  "Role.h"

using namespace std;

class user
{
    public:
        string get_role () const;
    
        // Méthode virtuelle pure rendant la classe abstraite
        virtual void printDetails() const = 0;
    
        user ( const user & unuser );
    
        user ( const Role & leRole):role(leRole){}
    
        virtual ~user ( );
    
    protected:
    //----------------------------------------------------- Attributs protégés
        Role role;
};

#endif // USER_H

