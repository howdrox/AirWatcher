#include <gtest/gtest.h>
#include "../src/GovernmentAgent.h"

// Test default constructor
TEST(GovernmentAgentTest, ConstructorTest)
{
    GovernmentAgent ga;
    EXPECT_EQ(ga.getRole(), GOVERNMENT_AGENT);
}