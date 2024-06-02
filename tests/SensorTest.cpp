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
    EXPECT_TRUE(s.getMeasurements().empty());
}

// Test parameterized constructor
TEST(SensorTest, ParameterizedConstructor)
{
    Coord location(40.7128, -74.0060);
    Sensor s(1, location);
    EXPECT_EQ(s.getSensorID(), 1);
    EXPECT_EQ(s.getLocation().latitude, 40.7128);
    EXPECT_EQ(s.getLocation().longitude, -74.0060);
    EXPECT_TRUE(s.getMeasurements().empty());
}

// Test string constructor
TEST(SensorTest, StringConstructor)
{
    std::string sensorLine = "Sensor1;40.7128;-74.0060";
    Sensor s(sensorLine);
    EXPECT_EQ(s.getSensorID(), 1);
    EXPECT_EQ(s.getLocation().latitude, 40.7128);
    EXPECT_EQ(s.getLocation().longitude, -74.0060);
    EXPECT_TRUE(s.getMeasurements().empty());
}

// Test addMeasurement method
TEST(SensorTest, AddMeasurement)
{
    Coord location(40.7128, -74.0060);
    Sensor s(1, location);
    s.addMeasurement(Measurement("2019-01-01 12:00:00;Sensor1;O3;50.25;"));
    EXPECT_EQ(s.getMeasurements().size(), 1);
    EXPECT_EQ(s.getMeasurements()[0].getSensorID(), 1);
    EXPECT_EQ(s.getMeasurements()[0].getAttributeID(), O3);
    EXPECT_EQ(s.getMeasurements()[0].getValue(), 50.25);
}

// Test addMeasurement method with invalid sensor ID
TEST(SensorTest, AddMeasurementInvalidSensorID)
{
    Coord location(40.7128, -74.0060);
    Sensor s(1, location);
    EXPECT_THROW(s.addMeasurement(Measurement("2019-01-01 12:00:00;Sensor2;O3;50.25;")), std::invalid_argument);
}

// Test copy constructor
TEST(SensorTest, CopyConstructor)
{
    Coord location(40.7128, -74.0060);
    Sensor originalSensor(1, location);
    originalSensor.addMeasurement(Measurement("2019-01-01 12:00:00;Sensor1;O3;50.25;"));
    Sensor copiedSensor(originalSensor);
    EXPECT_EQ(copiedSensor.getSensorID(), originalSensor.getSensorID());
    EXPECT_EQ(copiedSensor.getLocation().latitude, originalSensor.getLocation().latitude);
    EXPECT_EQ(copiedSensor.getLocation().longitude, originalSensor.getLocation().longitude);
    EXPECT_FALSE(copiedSensor.getMeasurements().empty());
}

// Test assignment operator
TEST(SensorTest, AssignmentOperator)
{
    Coord location(40.7128, -74.0060);
    Sensor originalSensor(1, location);
    originalSensor.addMeasurement(Measurement("2019-01-01 12:00:00;Sensor1;O3;50.25;"));
    Sensor copiedSensor;
    copiedSensor = originalSensor;
    EXPECT_EQ(copiedSensor.getSensorID(), originalSensor.getSensorID());
    EXPECT_EQ(copiedSensor.getLocation().latitude, originalSensor.getLocation().latitude);
    EXPECT_EQ(copiedSensor.getLocation().longitude, originalSensor.getLocation().longitude);
    EXPECT_FALSE(copiedSensor.getMeasurements().empty());
}

// Test output stream operator
TEST(SensorTest, OutputStreamOperator)
{
    Coord location(40.7128, -74.0060);
    Sensor s(1, location);
    s.addMeasurement(Measurement("2019-01-01 12:00:00;Sensor1;O3;50.25;"));
    std::ostringstream os;
    os << s;
    std::string expectedOutput = "Sensor 1 at (40.7128, -74.006) with 1 measurements";
    EXPECT_EQ(os.str(), expectedOutput);
}