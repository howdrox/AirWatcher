#include <gtest/gtest.h>
#include "../src/Service.h"

// Define a test fixture for Service class
class ServiceTest : public ::testing::Test
{
protected:
    // Variables used in the tests
    System emptySystem;
    System system;
    Service emptyService;
    Service service;

    // Constructor: Set up non-empty system
    ServiceTest() : system("data/Sensors/test1.csv", "data/Cleaners/test1.csv", "data/Users/test1.csv", "data/Measurements/test1.csv"), service(system) {}

    // Set up common objects and data before each test case
    void SetUp() override
    {
        // Set up empty system
        emptySystem = System("data/Sensors/test0.csv", "data/Cleaners/test0.csv", "data/Users/test0.csv", "data/Measurements/test0.csv");
        emptyService = Service(emptySystem);
    }
};

// Test case for distance method
TEST_F(ServiceTest, DistanceTest)
{
    Service service;
    // Test with different coordinates
    Coord coord1(48.8575, 2.3514);
    Coord coord2(45.7640, 4.8357);
    EXPECT_GT(service.distance(coord1, coord2), 0.0);

    // Test with the same coordinates
    EXPECT_DOUBLE_EQ(service.distance(coord1, coord1), 0.0);

    // Test with null coordinates
    Coord coord3;
    EXPECT_GT(service.distance(coord1, coord3), 0.0);

    // Test with very distant coordinates
    Coord coord4(21.0278, 105.8342); // Hanoi
    EXPECT_GT(service.distance(coord1, coord4), 0.0);

    // Test with coord and zone
    Zone zone2(coord2, 0);
    EXPECT_GT(service.distance(coord1, zone2), 0.0);
}

// Test case for isInZone function with nonEmptySystem
TEST_F(ServiceTest, IsInZoneTest)
{
    Coord center(44.1, -1);
    Zone zone(center, 20);

    // Test case 1: Point inside the zone
    Coord insidePoint(44.2, -1.1);
    EXPECT_TRUE(service.isInZone(insidePoint, zone));

    // Test case 2: Point on the edge (outside) of the zone
    Coord edgePoint(44.1 + 20 / 111.0, -1); // Approximation: 1 degree latitude is ~111 km
    EXPECT_FALSE(service.isInZone(edgePoint, zone));

    // Test case 3: Point outside the zone
    Coord outsidePoint(45.1, -1);
    EXPECT_FALSE(service.isInZone(outsidePoint, zone));
}

// Test case for calculateQuality method with emptySystem
TEST_F(ServiceTest, CalculateQualityEmptySystemTest)
{
    // Test with no measurements
    EXPECT_EQ(emptyService.calculateQuality(emptySystem.getMeasurements()), 0.0);

    // Test with one measurement
    Measurement m("2019-01-01 12:00:00;Sensor0;O3;50.25;");
    emptySystem.addMeasurement(m);
    EXPECT_EQ(emptyService.calculateQuality(emptySystem.getMeasurements()), 2.0);
}

// Test case for calculateQuality method with Zone, start time, and end time
TEST_F(ServiceTest, CalculateQualityWithZoneAndTimeRangeTest)
{
    Coord center(44.1, -1);
    Time start(2019, 1, 1, 0, 0, 0);
    Time end(2019, 1, 3, 0, 0, 0);

    // Test with valid measurements in the specified zone and time range
    Zone zone(center, 20);
    EXPECT_EQ(service.calculateQuality(zone, start, end), 7.5);

    // Test with no measurements in the specified zone
    Zone smallZone(center, 0.1);
    EXPECT_EQ(service.calculateQuality(smallZone, start, end), 0.0);

    // Test with measurements outside the specified time range
    Time start1(2024, 1, 1, 0, 0, 0);
    Time end1(2024, 1, 4, 0, 0, 0);
    EXPECT_EQ(service.calculateQuality(zone, start1, end1), 0.0);

    // Test with zero radius
    Zone zeroRadiusZone(center, 0.0);
    EXPECT_EQ(service.calculateQuality(zeroRadiusZone, start, end), 0.0);

    // Test with start date later than end date (exception expected)
    EXPECT_THROW(service.calculateQuality(zone, end, start), std::exception);
}

// Test case for filterMeasurements method
TEST_F(ServiceTest, FilterMeasurementsTest)
{
    Time start(2019, 1, 1, 0, 0, 0);
    Time end(2019, 1, 4, 0, 0, 0);

    // Test with valid date range and existing measurements
    auto filtered = service.filterMeasurements(start, end, system.getMeasurements());
    EXPECT_FALSE(filtered.empty());

    // Test with valid date range containing no measurements
    Time start1(2024, 1, 1, 0, 0, 0);
    Time end1(2024, 1, 4, 0, 0, 0);
    filtered = service.filterMeasurements(start1, end1, system.getMeasurements());
    // cout << filtered[0][0].getMeasurementID() << endl;
    // cout << filtered[1][0].getMeasurementID() << endl;
    EXPECT_TRUE(filtered.empty());

    // Test with start date equal to end date
    Time start2(2019, 1, 1, 12, 0, 0);
    Time end2(2019, 1, 1, 12, 0, 0);
    filtered = service.filterMeasurements(start2, end2, system.getMeasurements());
    EXPECT_TRUE(filtered.empty());

    // Test with end date before start date
    EXPECT_THROW(service.filterMeasurements(end, start, system.getMeasurements()), std::exception);

    // Test with valid date range but empty measurements
    filtered = service.filterMeasurements(start, end, emptySystem.getMeasurements());
    EXPECT_TRUE(filtered.empty());
}

// Test case for impactPurificateur method
TEST_F(ServiceTest, ImpactPurificateurTest)
{
    // Test with a valid cleaner ID
    EXPECT_NO_THROW(service.calculateImpactRadius(1));
    EXPECT_GT(service.calculateImpactRadius(1), 0.0);

    // Test with an invalid cleaner ID
    EXPECT_THROW(service.calculateImpactRadius(-1), std::exception);

    // Test with valid date range containing no measurements
    EXPECT_GT(service.calculateImpactRadius(2), 0.0);
}

// Test case for chercherZones method
TEST_F(ServiceTest, ChercherZonesTest)
{
    Time start(2019, 1, 1, 0, 0, 0);
    Time end(2019, 12, 31, 23, 59, 59);
    // Test with existing sensor ID and valid time range
    EXPECT_FALSE(service.getSimilarZones(1, start, end, 0.1).empty());

    // Test with non-existent sensor ID
    EXPECT_THROW(service.getSimilarZones(-1, start, end, 0.1), std::exception);

    // Test with end date before start date
    EXPECT_THROW(service.getSimilarZones(1, end, start, 0.1), std::exception);

    // Test with start date equal to end date
    EXPECT_FALSE(service.getSimilarZones(1, start, start, 0.1).empty());

    // Test with invalid delta (<= 0)
    EXPECT_THROW(service.getSimilarZones(1, start, end, -0.1), std::exception);
}