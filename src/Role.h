#ifndef ROLE_H
#define ROLE_H

#include <string>

// Enumération définissant les différents types de rôles
enum class Role {
    GOVERNMENT_AGENT,
    PRIVATE_USER,
    PROVIDER
};

// Méthode statique pour obtenir une chaîne de caractères représentant le rôle
std::string roleToString(Role role);

#endif // ROLE_H
