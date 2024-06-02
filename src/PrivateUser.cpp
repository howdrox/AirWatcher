#include <sstream>

#include "PrivateUser.h"

PrivateUser::PrivateUser(const std::string &userInfo) : User(Role::PRIVATE_USER), points(0), blacklisted(false)
{
    std::stringstream ss(userInfo);
    std::string token;

    // Extract the user ID
    if (std::getline(ss, token, ';'))
    {
        if (token.find("User") == 0)
        {
            userID = std::stoi(token.substr(4));
        }
        else
        {
            throw std::invalid_argument("Invalid user format");
        }
    }

    // Extract sensor IDs
    while (std::getline(ss, token, ';'))
    {
        if (token.find("Sensor") == 0)
        {
            int sensorID = std::stoi(token.substr(6));
            sensorsID.push_back(sensorID);
        }
        else
        {
            throw std::invalid_argument("Invalid sensor format");
        }
    }
}

PrivateUser &PrivateUser::operator=(const PrivateUser &p)
{
    if (this != &p)
    {
        userID = p.userID;
        sensorsID = p.sensorsID;
        points = p.points;
        blacklisted = p.blacklisted;
    }
    return *this;
}

void PrivateUser::setBlacklisted(bool isBlacklisted)
{
    blacklisted = isBlacklisted;
}

void PrivateUser::addPoints(int nbPoints)
{
    points += nbPoints;
}
