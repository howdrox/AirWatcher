#include <gtest/gtest.h>
#include "../src/User.h"

// Test constructor with Role object
TEST(UserTest, ConstructorWithRole)
{
    User user(Role::GOVERNMENT_AGENT);
    EXPECT_EQ(user.getRole(), Role::GOVERNMENT_AGENT);
}

// Test copy constructor
TEST(UserTest, CopyConstructor)
{
    User originalUser(Role::PROVIDER);
    User copiedUser(originalUser);
    EXPECT_EQ(copiedUser.getRole(), originalUser.getRole());
}

// Test operator= overload
TEST(UserTest, OperatorOverload)
{
    User originalUser(Role::PRIVATE_USER);
    User copiedUser(Role::PROVIDER);
    copiedUser = originalUser;
    EXPECT_EQ(copiedUser.getRole(), originalUser.getRole());
}