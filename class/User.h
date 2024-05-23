#ifndef USER_H
#define USER_H

#include <string>
enum class Role {
        ADMIN,
        USER,
        GUEST
    };

class User {
    public:
        

        Role getRole() const; // Getter pour récupérer le rôle
        
        User(Role userRole); // Constructeur prenant un rôle en paramètre
        
        virtual ~User ( );

    private:
        Role role; // Attribut privé de type role
};

#endif // USER_H
