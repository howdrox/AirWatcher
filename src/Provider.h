#ifndef PROVIDER_H
#define PROVIDER_H

#include <string>
#include <vector>

#include "User.h"

class Provider : public User
{
public:
    // Constructors
    Provider(int pID = -1, std::vector<int> c = {}) : User(Role::PROVIDER), providerID(pID), cleanersID(c){};
    Provider(const std::string &providerInfo);

    // Destructor
    ~Provider(){};

    // Getters
    int getProviderID() const { return providerID; };
    const std::vector<int> &getCleanersID() const { return cleanersID; };

private:
    int providerID;
    std::vector<int> cleanersID;
};

#endif // PROVIDER_H
