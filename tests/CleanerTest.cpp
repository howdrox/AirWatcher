#include <gtest/gtest.h>
#include "../src/Cleaner.h"

// Test string constructor
TEST(CleanerTest, ConstructorTest)
{
    std::string data = "Cleaner0;45.333333;1.333333;2019-01-02 12:00:00;2019-01-05 00:00:00;";
    Time startTime("2019-01-02 12:00:00");
    Time endTime("2019-01-05 00:00:00");

    Cleaner cleaner(data);
    EXPECT_EQ(cleaner.getCleanerId(), 0);
    EXPECT_EQ(cleaner.getCoord().latitude, 45.333333);
    EXPECT_EQ(cleaner.getCoord().longitude, 1.333333);
    EXPECT_EQ(cleaner.getStartTime(), startTime);
    EXPECT_EQ(cleaner.getEndTime(), endTime);
}