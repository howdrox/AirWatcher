#include <gtest/gtest.h>
#include "../src/Zone.h"

// Test fixture for Zone struct
class ZoneTest : public ::testing::Test
{
protected:
    // Variables used in the tests
    double latitude = 48.864716; // Example latitude
    double longitude = 2.349014; // Example longitude
    double radius = 1000.0;      // Example radius
};

// Test constructor with latitude, longitude, and radius
TEST_F(ZoneTest, ConstructorWithLatLongRad)
{
    Zone zone(latitude, longitude, radius);
    EXPECT_EQ(zone.latitude, latitude);
    EXPECT_EQ(zone.longitude, longitude);
    EXPECT_EQ(zone.radius, radius);
}

// Test constructor with Coord object and radius
TEST_F(ZoneTest, ConstructorWithCoordAndRad)
{
    Coord coord(latitude, longitude);
    Zone zone(coord, radius);
    EXPECT_EQ(zone.latitude, latitude);
    EXPECT_EQ(zone.longitude, longitude);
    EXPECT_EQ(zone.radius, radius);
}

// Test copy constructor
TEST_F(ZoneTest, CopyConstructor)
{
    Zone originalZone(latitude, longitude, radius);
    Zone copiedZone(originalZone);
    EXPECT_EQ(copiedZone.latitude, originalZone.latitude);
    EXPECT_EQ(copiedZone.longitude, originalZone.longitude);
    EXPECT_EQ(copiedZone.radius, originalZone.radius);
}