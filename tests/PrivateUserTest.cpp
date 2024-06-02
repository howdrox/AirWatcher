#include <gtest/gtest.h>
#include "../src/PrivateUser.h"

// Test default constructor
TEST(PrivateUserTest, DefaultConstructor)
{
    PrivateUser p;
    EXPECT_EQ(p.getRole(), Role::PRIVATE_USER);
    EXPECT_EQ(p.getUserID(), -1);
    EXPECT_TRUE(p.getSensorsID().empty());
    EXPECT_EQ(p.getPoints(), 0);
    EXPECT_FALSE(p.isBlacklisted());
}

// Test constructor with string with one sensor
TEST(PrivateUserTest, ConstructorWithStringWithOneSensor)
{
    PrivateUser p("User1;Sensor1");
    EXPECT_EQ(p.getRole(), Role::PRIVATE_USER);
    EXPECT_EQ(p.getUserID(), 1);
    EXPECT_EQ(p.getSensorsID().size(), 1);
    EXPECT_EQ(p.getSensorsID().at(0), 1);
    EXPECT_EQ(p.getPoints(), 0);
    EXPECT_FALSE(p.isBlacklisted());
}

// Test constructor with string with multiple sensors
TEST(PrivateUserTest, ConstructorWithStringWithMultipleSensors)
{
    PrivateUser p("User1;Sensor1;Sensor2;Sensor3");
    EXPECT_EQ(p.getRole(), Role::PRIVATE_USER);
    EXPECT_EQ(p.getUserID(), 1);
    EXPECT_EQ(p.getSensorsID().size(), 3);
    EXPECT_EQ(p.getSensorsID().at(0), 1);
    EXPECT_EQ(p.getSensorsID().at(1), 2);
    EXPECT_EQ(p.getSensorsID().at(2), 3);
    EXPECT_EQ(p.getPoints(), 0);
    EXPECT_FALSE(p.isBlacklisted());
}

// Test constructor with string with invalid user format
TEST(PrivateUserTest, ConstructorWithStringWithInvalidUserFormat)
{
    EXPECT_THROW(PrivateUser("Invalid"), std::invalid_argument);
}

// Test copy constructor
TEST(PrivateUserTest, CopyConstructor)
{
    PrivateUser p1("User1;Sensor1;Sensor2;Sensor3");
    PrivateUser p2(p1);
    EXPECT_EQ(p2.getRole(), Role::PRIVATE_USER);
    EXPECT_EQ(p2.getUserID(), 1);
    EXPECT_EQ(p2.getSensorsID().size(), 3);
    EXPECT_EQ(p2.getSensorsID().at(0), 1);
    EXPECT_EQ(p2.getSensorsID().at(1), 2);
    EXPECT_EQ(p2.getSensorsID().at(2), 3);
    EXPECT_EQ(p2.getPoints(), 0);
    EXPECT_FALSE(p2.isBlacklisted());
}

// Test assignment operator
TEST(PrivateUserTest, AssignmentOperator)
{
    PrivateUser p1("User1;Sensor1;Sensor2;Sensor3");
    PrivateUser p2;
    p2 = p1;
    EXPECT_EQ(p2.getRole(), Role::PRIVATE_USER);
    EXPECT_EQ(p2.getUserID(), 1);
    EXPECT_EQ(p2.getSensorsID().size(), 3);
    EXPECT_EQ(p2.getSensorsID().at(0), 1);
    EXPECT_EQ(p2.getSensorsID().at(1), 2);
    EXPECT_EQ(p2.getSensorsID().at(2), 3);
    EXPECT_EQ(p2.getPoints(), 0);
    EXPECT_FALSE(p2.isBlacklisted());
}

// Test setBlacklisted method
TEST(PrivateUserTest, SetBlacklisted)
{
    PrivateUser p;
    p.setBlacklisted(true);
    EXPECT_TRUE(p.isBlacklisted());
    p.setBlacklisted(false);
    EXPECT_FALSE(p.isBlacklisted());
}

// Test addPoints method
TEST(PrivateUserTest, AddPoints)
{
    PrivateUser p;
    p.addPoints(10);
    EXPECT_EQ(p.getPoints(), 10);
    p.addPoints(-5);
    EXPECT_EQ(p.getPoints(), 5);
}