#include <gtest/gtest.h>

#include "../src/Time.h"

// Test constructor with default parameters
TEST(TimeTest, DefaultConstructor)
{
    Time time;
    EXPECT_EQ(time.getYear(), 0);
    EXPECT_EQ(time.getMonth(), 0);
    EXPECT_EQ(time.getDay(), 0);
    EXPECT_EQ(time.getHour(), 0);
    EXPECT_EQ(time.getMinute(), 0);
    EXPECT_EQ(time.getSecond(), 0);
}

// Test constructor with specific parameters
TEST(TimeTest, ParameterizedConstructor)
{
    Time time(2024, 6, 1, 12, 30, 45);
    EXPECT_EQ(time.getYear(), 2024);
    EXPECT_EQ(time.getMonth(), 6);
    EXPECT_EQ(time.getDay(), 1);
    EXPECT_EQ(time.getHour(), 12);
    EXPECT_EQ(time.getMinute(), 30);
    EXPECT_EQ(time.getSecond(), 45);
}

// Test constructor with string parameter
TEST(TimeTest, StringConstructor)
{
    Time time("2024-06-01 12:30:45");
    EXPECT_EQ(time.getYear(), 2024);
    EXPECT_EQ(time.getMonth(), 6);
    EXPECT_EQ(time.getDay(), 1);
    EXPECT_EQ(time.getHour(), 12);
    EXPECT_EQ(time.getMinute(), 30);
    EXPECT_EQ(time.getSecond(), 45);
}

// Test copy constructor
TEST(TimeTest, CopyConstructor)
{
    Time time1(2024, 6, 1, 12, 30, 45);
    Time time2 = time1;
    EXPECT_EQ(time2.getYear(), 2024);
    EXPECT_EQ(time2.getMonth(), 6);
    EXPECT_EQ(time2.getDay(), 1);
    EXPECT_EQ(time2.getHour(), 12);
    EXPECT_EQ(time2.getMinute(), 30);
    EXPECT_EQ(time2.getSecond(), 45);
}

// Test assignment operator
TEST(TimeTest, AssignmentOperator)
{
    Time time1(2024, 6, 1, 12, 30, 45);
    Time time2;
    time2 = time1;
    EXPECT_EQ(time2.getYear(), 2024);
    EXPECT_EQ(time2.getMonth(), 6);
    EXPECT_EQ(time2.getDay(), 1);
    EXPECT_EQ(time2.getHour(), 12);
    EXPECT_EQ(time2.getMinute(), 30);
    EXPECT_EQ(time2.getSecond(), 45);
}

// Test isSameHour method
TEST(TimeTest, IsSameHour)
{
    Time time1(2024, 6, 1, 12, 30, 45);
    Time time2(2024, 6, 1, 12, 15, 30);
    Time time3(2024, 6, 1, 13, 30, 45);
    EXPECT_TRUE(time1.isSameHour(time2));
    EXPECT_FALSE(time1.isSameHour(time3));
}

// Test comparison operators
TEST(TimeTest, ComparisonOperators)
{
    Time time1(2024, 6, 1, 12, 30, 45);
    Time time2(2024, 6, 1, 12, 30, 45);
    Time time3(2024, 6, 1, 13, 30, 45);
    EXPECT_TRUE(time1 <= time2);
    EXPECT_TRUE(time1 >= time2);
    EXPECT_TRUE(time1 < time3);
    EXPECT_TRUE(time3 > time1);
}

// Test output operator
TEST(TimeTest, OutputOperator)
{
    Time time(2024, 6, 1, 12, 30, 45);
    std::ostringstream oss;
    oss << time;
    EXPECT_EQ(oss.str(), "2024-06-01 12:30:45");
}

// Test getDate method
TEST(TimeTest, GetDate)
{
    Time time(2024, 6, 1, 12, 30, 45);
    Date date = time.getDate();
    EXPECT_EQ(date.year, 2024);
    EXPECT_EQ(date.month, 6);
    EXPECT_EQ(date.day, 1);
}

// Test destructor (no specific test needed, just ensure no memory leaks)
TEST(TimeTest, Destructor)
{
    Time *time = new Time(2024, 6, 1, 12, 30, 45);
    delete time;
    SUCCEED();
}