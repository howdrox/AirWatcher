#include <gtest/gtest.h>
#include "../src/System.h"

// Test fixture for System class
class SystemTest : public ::testing::Test
{
protected:
    // System instances for testing
    System system;
    System emptySystem;

    // Constructor: Set up non-empty system
    SystemTest() : system("data/Sensors/test1.csv", "data/Cleaners/test1.csv", "data/Users/test1.csv", "data/Measurements/test1.csv") {}

    // SetUp() function: Called before each test
    void SetUp() override
    {
        // Set up empty system
        emptySystem = System("data/Sensors/test0.csv", "data/Cleaners/test0.csv", "data/Users/test0.csv", "data/Measurements/test0.csv");
    }
};

// Test getMeasurements() function
TEST_F(SystemTest, GetMeasurements)
{
    // Check non-empty system
    EXPECT_GT(system.getMeasurements().size(), 0);

    // Check empty system
    EXPECT_EQ(emptySystem.getMeasurements().size(), 0);
}

// Test getCleaners() function
TEST_F(SystemTest, GetCleaners)
{
    // Check non-empty system
    system.addCleaner(Cleaner("Cleaner1;48.888887;3.888887;2019-02-02 12:00:00;2019-03-02 00:00:00;"));
    EXPECT_GT(system.getCleaners().size(), 0);

    // Check empty system
    EXPECT_EQ(emptySystem.getCleaners().size(), 0);
}

// Test getSensors() function
TEST_F(SystemTest, GetSensors)
{
    // Check non-empty system
    system.addSensor(Sensor("Sensor0;45;-2.0;"));
    EXPECT_GT(system.getSensors().size(), 0);

    // Check empty system
    EXPECT_EQ(emptySystem.getSensors().size(), 0);
}

// Test getUsers() function
TEST_F(SystemTest, GetUsers)
{
    // Check non-empty system
    system.addUser(PrivateUser("User1"));
    EXPECT_GT(system.getUsers().size(), 0);

    // Check empty system
    EXPECT_EQ(emptySystem.getUsers().size(), 0);
}
