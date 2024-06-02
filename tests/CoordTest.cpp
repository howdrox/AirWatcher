#include <gtest/gtest.h>
#include "../src/Coord.h"

// Test default constructor
TEST(CoordTest, DefaultConstructorTest)
{
    Coord c;
    EXPECT_DOUBLE_EQ(c.latitude, 0);
    EXPECT_DOUBLE_EQ(c.longitude, 0);
}

// Test parameterized constructor
TEST(CoordTest, ParameterizedConstructorTest)
{
    Coord c(45.5, 90.0);
    EXPECT_DOUBLE_EQ(c.latitude, 45.5);
    EXPECT_DOUBLE_EQ(c.longitude, 90.0);
}