#include <gtest/gtest.h>
#include "../src/Sensor.h"
#include "../src/Coord.h"
#include "../src/Measurement.h"
#include <vector>
#include <string>

// Test default constructor
TEST(SensorTest, DefaultConstructor) {
    Sensor s;

    EXPECT_EQ(s.getSensorID(), 0);
    EXPECT_EQ(s.getLocation().latitude, 0.0);
    EXPECT_EQ(s.getLocation().longitude, 0.0);
    EXPECT_TRUE(s.getMeasurements().empty());
}

// Test parameterized constructor
TEST(SensorTest, ParameterizedConstructor) {
    Coord location(40.7128, -74.0060);
    Sensor s(1, location);

    EXPECT_EQ(s.getSensorID(), 1);
    EXPECT_EQ(s.getLocation().latitude, 40.7128);
    EXPECT_EQ(s.getLocation().longitude, -74.0060);
    EXPECT_TRUE(s.getMeasurements().empty());
}

// Test string constructor
TEST(SensorTest, StringConstructor) {
    std::string sensorLine = "Sensor1;40.7128;-74.0060";
    Sensor s(sensorLine);

    EXPECT_EQ(s.getSensorID(), 1);
    EXPECT_EQ(s.getLocation().latitude, 40.7128);
    EXPECT_EQ(s.getLocation().longitude, -74.0060);
    EXPECT_TRUE(s.getMeasurements().empty());
}

