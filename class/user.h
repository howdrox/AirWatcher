#if ! defined ( USER_H )
#define USER_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
using namespace std;

enum Role { ADMIN, GOVERNMENT_AGENT, PROVIDER, PRIVATE_USER };

class User
{
//----------------------------------------------------------------- PUBLIC
//----------------------------------------------------- Méthodes publiques


    public:

    //-------------------------------------------- Constructeurs - destructeur
        User ();

        virtual ~User ( );
        // Mode d'emploi :
        // Destructeur.
        // Contrat :

    protected:
    //----------------------------------------------------- Attributs protégés
        int userID;
        string username;
        Role role;

};

#endif // USER_H
