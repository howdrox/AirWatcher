#include "Role.h"

std::string roleToString(Role role) {
    switch (role) {
        case Role::GOVERNMENT_AGENT: return "GOVERNMENT_AGENT";
        case Role::PRIVATE_USER: return "PRIVATE_USER";
        case Role::PROVIDER: return "PROVIDER";
        default: return "UNKNOWN";
    }
}
