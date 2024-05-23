#ifndef PRIVATEUSER_H
#define PRIVATEUSER_H

#include "User.h" // Pour hériter de la classe User
#include <string>
#include <vector>

class PrivateUser : public User {
public:
    PrivateUser(const std::string& userInfo); // Constructeur prenant une chaîne de caractères en entrée
    ~PrivateUser(); // Destructeur

    int getUserID() const; // Getter pour récupérer l'ID de l'utilisateur privé
    const std::vector<int>& getSensorsID() const; // Getter pour récupérer la liste des IDs des capteurs
    int getPoints() const; // Getter pour récupérer le nombre de points
    bool isBlacklisted() const; // Getter pour vérifier si l'utilisateur est sur liste noire

    void setBlacklisted(bool isBlacklisted); // Méthode pour blacklister ou déblacklister

    void addPoints(int nbPoints); // Méthode pour incrémenter le nombre de points

private:
    int userID; // Attribut privé pour l'ID de l'utilisateur privé
    std::vector<int> sensorsID; // Attribut privé pour la liste des IDs des capteurs
    int points; // Attribut privé pour le nombre de points
    bool blacklisted; // Attribut privé pour indiquer si l'utilisateur est sur liste noire
};

#endif // PRIVATEUSER_H
