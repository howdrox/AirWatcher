#include <gtest/gtest.h>
#include "../src/Sensor.h"
#include "../src/Coord.h"
#include "../src/Measurement.h"
#include <vector>
#include <string>

// Test default constructor
TEST(SensorTest, DefaultConstructor)
{
    Sensor s;
    EXPECT_EQ(s.getSensorID(), 0);
    EXPECT_EQ(s.getLocation().latitude, 0.0);
    EXPECT_EQ(s.getLocation().longitude, 0.0);
}

// Test parameterized constructor
TEST(SensorTest, ParameterizedConstructor)
{
    Coord location(40.7128, -74.0060);
    Sensor s(1, location);
    EXPECT_EQ(s.getSensorID(), 1);
    EXPECT_EQ(s.getLocation().latitude, 40.7128);
    EXPECT_EQ(s.getLocation().longitude, -74.0060);
}

// Test string constructor
TEST(SensorTest, StringConstructor)
{
    std::string sensorLine = "Sensor1;40.7128;-74.0060";
    Sensor s(sensorLine);
    EXPECT_EQ(s.getSensorID(), 1);
    EXPECT_EQ(s.getLocation().latitude, 40.7128);
    EXPECT_EQ(s.getLocation().longitude, -74.0060);
}


// Test copy constructor
TEST(SensorTest, CopyConstructor)
{
    Coord location(40.7128, -74.0060);
    Sensor originalSensor(1, location);
    Sensor copiedSensor(originalSensor);
    EXPECT_EQ(copiedSensor.getSensorID(), originalSensor.getSensorID());
    EXPECT_EQ(copiedSensor.getLocation().latitude, originalSensor.getLocation().latitude);
    EXPECT_EQ(copiedSensor.getLocation().longitude, originalSensor.getLocation().longitude);
}

// Test assignment operator
TEST(SensorTest, AssignmentOperator)
{
    Coord location(40.7128, -74.0060);
    Sensor originalSensor(1, location);
    Sensor copiedSensor;
    copiedSensor = originalSensor;
    EXPECT_EQ(copiedSensor.getSensorID(), originalSensor.getSensorID());
    EXPECT_EQ(copiedSensor.getLocation().latitude, originalSensor.getLocation().latitude);
    EXPECT_EQ(copiedSensor.getLocation().longitude, originalSensor.getLocation().longitude);
}

// Test output stream operator
TEST(SensorTest, OutputStreamOperator)
{
    Coord location(40.7128, -74.0060);
    Sensor s(1, location);
    std::ostringstream os;
    os << s;
    std::string expectedOutput = "Sensor 1 at (40.7128, -74.006)";
    EXPECT_EQ(os.str(), expectedOutput);
}