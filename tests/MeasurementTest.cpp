#include <gtest/gtest.h>
#include "../src/Measurement.h"

// Test parameterized constructor
TEST(MeasurementTest, ParameterizedConstructorTest)
{
    Time time(2024, 5, 31, 12, 30, 45);
    Measurement m(time, 100, NO2, 42.0, false);

    EXPECT_EQ(m.getTimestamp(), time);
    EXPECT_EQ(m.getSensorID(), 100);
    EXPECT_EQ(m.getAttributeID(), NO2);
    EXPECT_DOUBLE_EQ(m.getValue(), 42.0);
    EXPECT_FALSE(m.isBlacklisted());
}

// Test copy constructor
TEST(MeasurementTest, CopyConstructorTest)
{
    Time time(2024, 5, 31, 12, 30, 45);
    Measurement m1(time, 100, NO2, 42.0, true);
    Measurement m2(m1);

    EXPECT_EQ(m2.getTimestamp(), time);
    EXPECT_EQ(m2.getSensorID(), 100);
    EXPECT_EQ(m2.getAttributeID(), NO2);
    EXPECT_DOUBLE_EQ(m2.getValue(), 42.0);
    EXPECT_TRUE(m2.isBlacklisted());
}

// Test string-based constructor with valid input
TEST(MeasurementTest, StringConstructorTest)
{
    // Test valid input string
    string validInput = "2019-01-01 12:00:00;Sensor0;O3;50.25;";
    Measurement m(validInput);
    Time expectedTime(2019, 1, 1, 12, 0, 0);

    EXPECT_EQ(m.getTimestamp(), expectedTime);
    EXPECT_EQ(m.getSensorID(), 0);
    EXPECT_EQ(m.getAttributeID(), O3);
    EXPECT_DOUBLE_EQ(m.getValue(), 50.25);
    EXPECT_FALSE(m.isBlacklisted());
}

// Test string-based constructor with negative value
TEST(MeasurementTest, StringConstructorNegativeValueTest)
{
    // Test negative value
    string negativeValue = "2019-01-01 12:00:00;Sensor0;O3;-50.25;";
    Measurement m(negativeValue);
    Time expectedTime(2019, 1, 1, 12, 0, 0);

    EXPECT_EQ(m.getTimestamp(), expectedTime);
    EXPECT_EQ(m.getSensorID(), 0);
    EXPECT_EQ(m.getAttributeID(), O3);
    EXPECT_DOUBLE_EQ(m.getValue(), 0);
    EXPECT_FALSE(m.isBlacklisted());
}

// Test string-based constructor with invalid PollutantType
TEST(MeasurementTest, StringConstructorInvalidPollutantTypeTest)
{
    // Test invalid PollutantType
    EXPECT_THROW(Measurement("2019-01-01 12:00:00;Sensor0;O4;50.25;"), std::invalid_argument);
}

// Test output stream operator
TEST(MeasurementTest, OutputOperatorTest)
{
    Time time(2024, 5, 31, 12, 30, 45);
    Measurement m(time, 100, NO2, 42.0, false);

    std::ostringstream os;
    os << m;

    std::string expectedOutput = "Timestamp: 2024-05-31 12:30:45 , Sensor ID: 100 , Attribute ID: 1 , Value: 42 , Blacklisted: No";
    EXPECT_EQ(os.str(), expectedOutput);
}
