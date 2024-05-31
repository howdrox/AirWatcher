#include <sstream>

#include "PrivateUser.h"

PrivateUser::PrivateUser() : User(Role::PRIVATE_USER), points(0), blacklisted(false) {}

PrivateUser::PrivateUser(const PrivateUser &p) : User(Role::PRIVATE_USER), userID(p.userID), sensorsID(p.sensorsID), points(p.points), blacklisted(p.blacklisted) {}

PrivateUser::PrivateUser(const std::string &userInfo) : User(Role::PRIVATE_USER), points(0), blacklisted(false)
{
#ifdef MAP
    cout << "Appel au constructeur de <privateUser>" << endl;
#endif

    std::istringstream ss(userInfo);

    // Extract user ID
    std::string userIDString;
    std::getline(ss, userIDString, ';');
    // Assuming user ID is prefixed with "User"
    userID = std::stoi(userIDString.substr(4));

    // Extract sensor IDs
    std::string sensorIDString;
    while (std::getline(ss, sensorIDString, ';'))
    {
        // Assuming sensor ID is prefixed with "Sensor"
        int sensorID = std::stoi(sensorIDString.substr(6));
        sensorsID.push_back(sensorID);
    }
}

PrivateUser::~PrivateUser()
{
#ifdef MAP
    cout << "Appel au destructeur de <privateUser>" << endl;
#endif
    // Le destructeur peut être vide s'il n'y a rien à faire spécifiquement lors de la destruction
}

int PrivateUser::getUserID() const
{
    return userID;
}

const std::vector<int> &PrivateUser::getSensorsID() const
{
    return sensorsID;
}

int PrivateUser::getPoints() const
{
    return points;
}

bool PrivateUser::isBlacklisted() const
{
    return blacklisted;
}

void PrivateUser::setBlacklisted(bool isBlacklisted)
{
    blacklisted = isBlacklisted;
}

void PrivateUser::addPoints(int nbPoints)
{
    points += nbPoints; // Incrémentation du nombre de points
}
