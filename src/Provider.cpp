#include <sstream>

#include "Provider.h"

Provider::Provider(const std::string &providerInfo) : User(Role::PROVIDER)
{
    std::stringstream ss(providerInfo);
    std::string token;

    // Extract the provider ID
    if (std::getline(ss, token, ';'))
    {
        if (token.find("Provider") == 0)
        {
            providerID = std::stoi(token.substr(8));
        }
        else
        {
            throw std::invalid_argument("Invalid provider format");
        }
    }

    // Extract cleaner IDs
    while (std::getline(ss, token, ';'))
    {
        if (token.find("Cleaner") == 0)
        {
            int cleanerID = std::stoi(token.substr(7));
            cleanersID.push_back(cleanerID);
        }
        else
        {
            throw std::invalid_argument("Invalid cleaner format");
        }
    }
}