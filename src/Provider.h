#ifndef PROVIDER_H
#define PROVIDER_H

#include <string>
#include <vector>

#include "User.h" // Pour hériter de la classe User

class Provider : public User {
public:
    Provider();
    Provider(const std::string& providerInfo); // Constructeur prenant une chaîne de caractères en entrée
    ~Provider(); // Destructeur

    int getProviderID() const; // Getter pour récupérer l'ID du fournisseur
    const std::vector<int>& getCleanersID() const; // Getter pour récupérer la liste des IDs des nettoyeurs

private:
    int providerID; // Attribut privé pour l'ID du fournisseur
    std::vector<int> cleanersID; // Attribut privé pour la liste des IDs des nettoyeurs
};

#endif // PROVIDER_H
