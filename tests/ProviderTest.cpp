#include <gtest/gtest.h>
#include "../src/Provider.h"

// Test default constructor
TEST(ProviderTest, DefaultConstructor)
{
    Provider p;
    EXPECT_EQ(p.getRole(), Role::PROVIDER);
    EXPECT_EQ(p.getProviderID(), -1);
    EXPECT_TRUE(p.getCleanersID().empty());
}

// Test parameterized constructor
TEST(ProviderTest, ParameterizedConstructor)
{
    Provider p(1, {2, 3});
    EXPECT_EQ(p.getRole(), Role::PROVIDER);
    EXPECT_EQ(p.getProviderID(), 1);
    EXPECT_FALSE(p.getCleanersID().empty());
}

// Test copy constructor
TEST(ProviderTest, CopyConstructor)
{
    Provider p1(1, {2, 3});
    Provider p2(p1);
    EXPECT_EQ(p2.getRole(), Role::PROVIDER);
    EXPECT_EQ(p2.getProviderID(), 1);
    EXPECT_EQ(p2.getCleanersID().size(), 2);
    EXPECT_EQ(p2.getCleanersID().at(0), 2);
    EXPECT_EQ(p2.getCleanersID().at(1), 3);
}

// Test string constructor with one cleaner
TEST(ProviderTest, StringConstructorWithOneCleaner)
{
    Provider p("Provider0;Cleaner0;");
    EXPECT_EQ(p.getRole(), Role::PROVIDER);
    EXPECT_EQ(p.getProviderID(), 0);
    EXPECT_EQ(p.getCleanersID().size(), 1);
    EXPECT_EQ(p.getCleanersID().at(0), 0);
}

// Test string constructor with multiple cleaners
TEST(ProviderTest, StringConstructorWithMultipleCleaners)
{
    Provider p("Provider0;Cleaner0;Cleaner1;Cleaner2;");
    EXPECT_EQ(p.getRole(), Role::PROVIDER);
    EXPECT_EQ(p.getProviderID(), 0);
    EXPECT_EQ(p.getCleanersID().size(), 3);
    EXPECT_EQ(p.getCleanersID().at(0), 0);
    EXPECT_EQ(p.getCleanersID().at(1), 1);
    EXPECT_EQ(p.getCleanersID().at(2), 2);
}