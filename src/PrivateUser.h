#ifndef PRIVATEUSER_H
#define PRIVATEUSER_H

#include <string>
#include <vector>

#include "User.h" // Pour hériter de la classe User

class PrivateUser : public User
{
public:
    // Constructors
    PrivateUser() : User(Role::PRIVATE_USER), userID(-1), sensorsID({}), points(0), blacklisted(false){};
    PrivateUser(const PrivateUser &p) : User(Role::PRIVATE_USER), userID(p.userID), sensorsID(p.sensorsID), points(p.points), blacklisted(p.blacklisted){};
    PrivateUser(const std::string &userInfo);

    // Destructor
    ~PrivateUser() {};

    // Overloaded operators
    PrivateUser &operator=(const PrivateUser &p);

    // Getters
    int getUserID() const { return userID; };
    const std::vector<int> &getSensorsID() const { return sensorsID; };
    int getPoints() const { return points; };
    bool isBlacklisted() const { return blacklisted; };

    // Methods
    void setBlacklisted(bool isBlacklisted);
    void addPoints(int nbPoints);

private:
    int userID;
    std::vector<int> sensorsID;
    int points;
    bool blacklisted;
};

#endif // PRIVATEUSER_H
