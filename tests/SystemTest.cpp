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

    // SetUp() method: Called before each test
    void SetUp() override
    {
        // Set up empty system
        emptySystem = System("data/Sensors/test0.csv", "data/Cleaners/test0.csv", "data/Users/test0.csv", "data/Measurements/test0.csv");
    }
};

// Test getMeasurements() method
TEST_F(SystemTest, GetMeasurements)
{
    // Check empty system
    EXPECT_EQ(emptySystem.getMeasurements().size(), 0);

    // Check non-empty system
    EXPECT_GT(system.getMeasurements().size(), 0);
}

// Test getCleaners() method
TEST_F(SystemTest, GetCleaners)
{
    // Check empty system
    EXPECT_EQ(emptySystem.getCleaners().size(), 0);

    // Check non-empty system
    EXPECT_GT(system.getCleaners().size(), 0);
}

// Test getSensors() method
TEST_F(SystemTest, GetSensors)
{
    // Check empty system
    EXPECT_EQ(emptySystem.getSensors().size(), 0);

    // Check non-empty system
    EXPECT_GT(system.getSensors().size(), 0);
}

// Test getUsers() method
TEST_F(SystemTest, GetUsers)
{
    // Check empty system
    EXPECT_EQ(emptySystem.getUsers().size(), 0);

    // Check non-empty system
    EXPECT_GT(system.getUsers().size(), 0);
}

// Test addMeasurement() method
TEST_F(SystemTest, AddMeasurement)
{
    Measurement measurement("2029-01-02 12:00:00;Sensor0;O3;50.5;");

    // Check on empty system
    emptySystem.addMeasurement(measurement);
    EXPECT_EQ(emptySystem.getMeasurements().at(0).at(0).getSensorID(), 0);
    EXPECT_EQ(emptySystem.getMeasurements().at(0).back().getValue(), 50.5);

    // Check non-empty system
    system.addMeasurement(measurement);
    EXPECT_EQ(system.getMeasurements().at(0).at(0).getSensorID(), 0);
    EXPECT_EQ(system.getMeasurements().at(0).back().getValue(), 50.5);
}

// Test load measurements in chronological order
TEST_F(SystemTest, LoadMeasurementsChronologicalTest)
{
    vector<Measurement> measurements = system.getMeasurements()[5];
    Measurement last = Measurement("0000-00-00 00:00:00;Sensor1;SO2;9999;");
    for (auto &m : measurements)
    {
        EXPECT_TRUE(last < m);
    }
}

// Test addMeasurement for chronological order
TEST_F(SystemTest, AddMeasurementChronologicalTest)
{
    Measurement m1("2019-01-02 12:00:00;Sensor0;O3;1;");
    Measurement m2("2018-01-01 12:00:00;Sensor0;O3;2;");
    Measurement m3("2019-01-03 12:00:00;Sensor0;O3;3;");
    // Measurement m4("2019-01-02 12:00:00;Sensor0;O3;4;");
    // Measurement m5("2019-01-02 12:00:00;Sensor0;O3;5;");

    emptySystem.addMeasurement(m1);
    EXPECT_DOUBLE_EQ(emptySystem.getMeasurements().at(0).back().getValue(), 1);

    emptySystem.addMeasurement(m2);
    EXPECT_DOUBLE_EQ(emptySystem.getMeasurements().at(0).at(0).getValue(), 2);
    EXPECT_DOUBLE_EQ(emptySystem.getMeasurements().at(0).back().getValue(), 1);

    emptySystem.addMeasurement(m3);
    EXPECT_DOUBLE_EQ(emptySystem.getMeasurements().at(0).at(0).getValue(), 2);
    EXPECT_DOUBLE_EQ(emptySystem.getMeasurements().at(0).at(1).getValue(), 1);
    EXPECT_DOUBLE_EQ(emptySystem.getMeasurements().at(0).back().getValue(), 3);
}

// Test addCleaner() method
TEST_F(SystemTest, AddCleaner)
{
    Cleaner cleaner("Cleaner13;45.333333;1.333333;2019-01-02 12:00:00;2019-01-05 00:00:00;");

    // Check on empty system
    emptySystem.addCleaner(cleaner);
    EXPECT_EQ(emptySystem.getCleaners().back().getCleanerID(), 13);

    // Check non-empty system
    system.addCleaner(cleaner);
    EXPECT_EQ(system.getCleaners().back().getCleanerID(), 13);
}

// Test addSensor() method
TEST_F(SystemTest, AddSensor)
{
    Sensor sensor("Sensor13;45.333333;1.333333;");

    // Check on empty system
    emptySystem.addSensor(sensor);
    EXPECT_EQ(emptySystem.getSensors().at(13).getSensorID(), 13);

    // Check non-empty system
    system.addSensor(sensor);
    EXPECT_EQ(system.getSensors().at(13).getSensorID(), 13);
}

// Test addUser() method
TEST_F(SystemTest, AddUser)
{
    PrivateUser privateUser("User13;Sensor13;");

    // Check on empty system
    emptySystem.addUser(privateUser);
    EXPECT_EQ(emptySystem.getUsers().back().getUserID(), 13);

    // Check non-empty system
    system.addUser(privateUser);
    EXPECT_EQ(system.getUsers().back().getUserID(), 13);
}