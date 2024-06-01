#include <gtest/gtest.h>
#include "../src/Measurement.h"
#include "../src/Time.h"

// Test default constructor
TEST(MeasurementTest, ConstructorTest) {
    Time time(2024, 5, 31, 12, 30, 45);
    Measurement m(1, time, 100, NO2, 42.0, false);

    EXPECT_EQ(m.getMeasurementID(), 1);
    EXPECT_EQ(m.getTimestamp(), time);
    EXPECT_EQ(m.getSensorID(), 100);
    EXPECT_EQ(m.getAttributeID(), NO2);
    EXPECT_DOUBLE_EQ(m.getValue(), 42.0);
    EXPECT_FALSE(m.isBlacklisted());
}

// Test copy constructor
TEST(MeasurementTest, CopyConstructorTest) {
    Time time(2024, 5, 31, 12, 30, 45);
    Measurement m1(1, time, 100, NO2, 42.0, true);
    Measurement m2(m1);

    EXPECT_EQ(m2.getMeasurementID(), 1);
    EXPECT_EQ(m2.getTimestamp(), time);
    EXPECT_EQ(m2.getSensorID(), 100);
    EXPECT_EQ(m2.getAttributeID(), NO2);
    EXPECT_DOUBLE_EQ(m2.getValue(), 42.0);
    EXPECT_TRUE(m2.isBlacklisted());
}

// Test string-based constructor
TEST(MeasurementTest, StringConstructorTest) {
    // Test valid input string
    string validInput = "2019-01-01 12:00:00;Sensor0;O3;50.25;";
    Measurement m(validInput);
    Time expectedTime(2019, 1, 1, 12, 0, 0);

    EXPECT_EQ(m.getTimestamp(), expectedTime);
    EXPECT_EQ(m.getSensorID(), 0);
    EXPECT_EQ(m.getAttributeID(), O3);
    EXPECT_DOUBLE_EQ(m.getValue(), 50.25);
    EXPECT_FALSE(m.isBlacklisted());

    // Test with negative value (should be changed to 0)
    string negativeValueInput = "2019-01-01 12:00:00;Sensor101;PM10;-10.0";
    Measurement m2(negativeValueInput);

    EXPECT_EQ(m2.getTimestamp(), expectedTime);
    EXPECT_EQ(m2.getSensorID(), 101);
    EXPECT_EQ(m2.getAttributeID(), PM10);
    EXPECT_DOUBLE_EQ(m2.getValue(), 0.0); // value should be set to 0
    EXPECT_FALSE(m2.isBlacklisted());
}