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

// Test default constructor
TEST_F(ServiceTest, DefaultConstructorTest)
{
    system = System();
    service = Service(system);
    EXPECT_EQ(service.getSystem().getCleaners().size(), 0);
    EXPECT_EQ(service.getSystem().getSensors().size(), 0);
    EXPECT_EQ(service.getSystem().getUsers().size(), 0);
    EXPECT_EQ(service.getSystem().getMeasurements().size(), 0);
}

// Test parameterized constructor
TEST_F(ServiceTest, ParameterizedConstructorTest)
{
    // Test with empty system
    EXPECT_EQ(emptyService.getSystem().getSensors().size(), 0);
    EXPECT_EQ(emptyService.getSystem().getCleaners().size(), 0);
    EXPECT_EQ(emptyService.getSystem().getUsers().size(), 0);
    EXPECT_EQ(emptyService.getSystem().getMeasurements().size(), 0);

    // Test with non-empty system
    EXPECT_GT(service.getSystem().getSensors().size(), 0);
    EXPECT_GT(service.getSystem().getCleaners().size(), 0);
    EXPECT_GT(service.getSystem().getUsers().size(), 0);
    EXPECT_GT(service.getSystem().getMeasurements().size(), 0);
}

// Test copy constructor
TEST_F(ServiceTest, CopyConstructorTest)
{
    // Test with empty system
    Service emptyServiceCopy(emptyService);
    EXPECT_EQ(emptyServiceCopy.getSystem().getSensors().size(), 0);
    EXPECT_EQ(emptyServiceCopy.getSystem().getCleaners().size(), 0);
    EXPECT_EQ(emptyServiceCopy.getSystem().getUsers().size(), 0);
    EXPECT_EQ(emptyServiceCopy.getSystem().getMeasurements().size(), 0);

    // Test with non-empty system
    Service serviceCopy(service);
    EXPECT_GT(serviceCopy.getSystem().getSensors().size(), 0);
    EXPECT_GT(serviceCopy.getSystem().getCleaners().size(), 0);
    EXPECT_GT(serviceCopy.getSystem().getUsers().size(), 0);
    EXPECT_GT(serviceCopy.getSystem().getMeasurements().size(), 0);
}

// Test case for distance method
TEST_F(ServiceTest, DistanceTest)
{
    // Test with different coordinates
    Coord coord1(48.8575, 2.3514);
    Coord coord2(45.7640, 4.8357);
    EXPECT_GT(service.distance(coord1, coord2), 0.0);

    // Test with the same coordinates
    EXPECT_DOUBLE_EQ(service.distance(coord1, coord1), 0.0);

    // Test with null coordinates
    Coord coord3;
    EXPECT_GT(service.distance(coord1, coord3), 0.0);

    // Test with negative lat and long
    Coord coord4(-48.8575, -2.3514);
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

    // Test with coord inside the zone
    Coord insideCoord(44.2, -1.1);
    EXPECT_TRUE(service.isInZone(insideCoord, zone));

    // Test with coord on the edge (outside) of the zone
    Coord edgeCoord(44.1 + 20 / 111.0, -1); // Approximation: 1 degree latitude is ~111 km
    EXPECT_FALSE(service.isInZone(edgeCoord, zone));

    // Test with coord outside the zone
    Coord outsideCoord(45.1, -1);
    EXPECT_FALSE(service.isInZone(outsideCoord, zone));
}

// Test average method
TEST_F(ServiceTest, AverageTest)
{
    // Test with empty vector
    vector<double> emptyVector;
    EXPECT_DOUBLE_EQ(service.average(emptyVector), 0.0);

    // Test with one element
    vector<double> oneElementVector = {5.0};
    EXPECT_DOUBLE_EQ(service.average(oneElementVector), 5.0);

    // Test with multiple elements
    vector<double> multipleElementsVector = {1.0, 2.0, 3.0, 4.0, 5.0};
    EXPECT_DOUBLE_EQ(service.average(multipleElementsVector), 3.0);
}

// Test case for filterMeasurements method
TEST_F(ServiceTest, FilterMeasurementsTest)
{
    Time start(2019, 1, 1, 0, 0, 0);
    Time end(2019, 1, 4, 0, 0, 0);

    // Test with valid date range and existing measurements
    EXPECT_FALSE(service.filterMeasurements(start, end, system.getMeasurements()).empty());

    // Test with valid date range containing no measurements
    EXPECT_TRUE(service.filterMeasurements(start, end, emptySystem.getMeasurements()).empty());

    // Test with start date equal to end date
    Time start2(2019, 1, 1, 12, 0, 0);
    Time end2(2019, 1, 1, 12, 0, 0);
    EXPECT_TRUE(service.filterMeasurements(start2, end2, system.getMeasurements()).empty());

    // Test with start date equal measurement date
    Time start3("2019-01-01 12:00:00");
    Time end3("2019-01-03 13:00:00");
    EXPECT_FALSE(service.filterMeasurements(start3, end3, system.getMeasurements()).empty());
    EXPECT_EQ(service.filterMeasurements(start3, end3, system.getMeasurements()).size(), 2);
    EXPECT_EQ(service.filterMeasurements(start3, end3, system.getMeasurements()).at(0).size(), 12);

    // Test with end date before start date
    EXPECT_THROW(service.filterMeasurements(end, start, system.getMeasurements()), std::exception);
}

// Test case for calculateQuality method with emptySystem
TEST_F(ServiceTest, CalculateQualityWithMeasurementParameterTest)
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

// Test sortSensors function with empty sensors
TEST_F(ServiceTest, SortSensorsTestWithEmptySystem)
{
    // Test with empty sensors
    Coord testCoord(44, 1.2);
    multimap<double, Sensor> sortedSensors = emptyService.sortSensors(emptySystem.getSensors(), testCoord);
    EXPECT_TRUE(sortedSensors.empty());
}

// Test case for sortSensors function
TEST_F(ServiceTest, SortSensorsTestFromManualData)
{
    // Create test sensors
    map<int, Sensor> sensors;
    sensors[1] = Sensor(1, Coord(48.8566, 2.3522));   // Paris
    sensors[2] = Sensor(2, Coord(51.5074, -0.1278));  // London
    sensors[3] = Sensor(3, Coord(40.7128, -74.0060)); // New York

    // Coordinate to sort sensors by distance from
    Coord testCoord(48.8566, 2.3522); // Paris

    // Call sortSensors function
    multimap<double, Sensor> sortedSensors = service.sortSensors(sensors, testCoord);

    // Verify that the sensors are sorted by distance
    auto it = sortedSensors.begin();
    EXPECT_EQ(it->second.getSensorID(), 1); // Paris (distance 0)
    ++it;
    EXPECT_EQ(it->second.getSensorID(), 2); // London
    ++it;
    EXPECT_EQ(it->second.getSensorID(), 3); // New York
}

// Test sortSensors function with sensors at the same coordinates
TEST_F(ServiceTest, SortSensorsTestWithSameCoordinates)
{
    // Create test sensors
    map<int, Sensor> sensors;
    sensors[1] = Sensor(1, Coord(44, 1.2));
    sensors[2] = Sensor(2, Coord(44, 1.2));
    sensors[3] = Sensor(3, Coord(44, 1.3));

    // Coordinate to sort sensors by distance from
    Coord testCoord(44, 1.2);

    // Call sortSensors function
    multimap<double, Sensor> sortedSensors = service.sortSensors(sensors, testCoord);

    // Verify that the sensors are sorted by distance
    auto it = sortedSensors.begin();
    EXPECT_EQ(it->second.getSensorID(), 1);
    ++it;
    EXPECT_EQ(it->second.getSensorID(), 2);
    ++it;
    EXPECT_EQ(it->second.getSensorID(), 3);
}

TEST_F(ServiceTest, SortSensorsTestFromCSVTestData)
{
    // Coordinate to sort sensors by distance from
    Coord testCoord(44, 1.2);

    // Call sortSensors function
    auto sensors = system.getSensors();
    multimap<double, Sensor> sortedSensors = service.sortSensors(sensors, testCoord);

    EXPECT_GT(sortedSensors.size(), 0);

    // Verify that the sensors are sorted by distance
    auto it = sortedSensors.begin();
    EXPECT_EQ(it->second.getSensorID(), 4);
    EXPECT_GT(system.getMeasurements().at(it->second.getSensorID()).size(), 0);
    ++it;
    EXPECT_EQ(it->second.getSensorID(), 2);
}

// Test case for impactPurificateur method
TEST_F(ServiceTest, CalculateImpactRadius)
{
    // Test with a valid cleaner ID
    EXPECT_NO_THROW(service.calculateImpactRadius(0));
    EXPECT_GT(service.calculateImpactRadius(3), 0.0);

    // Test with an invalid cleaner ID
    EXPECT_THROW(service.calculateImpactRadius(-1), std::exception);

    // Test with valid cleaner ID that has no measurements in its date range
    EXPECT_DOUBLE_EQ(service.calculateImpactRadius(2), 0.0);
}

// Test rankSimilarSensors method
TEST_F(ServiceTest, RankSimilarSensorsTest)
{
    Time start(2019, 1, 1, 0, 0, 0);
    Time end(2019, 2, 2, 0, 0, 0);

    // Test with valid sensor ID and time range with measurements
    EXPECT_GT(service.rankSimilarSensors(0, start, end).size(), 0);

    // Test with valid sensor ID and time range without measurements
    EXPECT_GT(service.rankSimilarSensors(2, start, end).size(), 0);
}

// Test rankSimilarSensors method with exceptions
TEST_F(ServiceTest, RankSimilarSensorsExceptionsTest)
{
    Time start(2019, 1, 1, 0, 0, 0);
    Time end(2019, 2, 2, 0, 0, 0);

    // Test with invalid sensor ID
    EXPECT_THROW(service.rankSimilarSensors(-1, start, end), std::invalid_argument);

    // Test with invalid time range
    EXPECT_THROW(service.rankSimilarSensors(0, end, start), std::invalid_argument);
}

// Test blacklistPrivateUser method
TEST_F(ServiceTest, BlacklistPrivateUserTest)
{
    // Test with invalid user ID
    EXPECT_THROW(service.blacklistPrivateUser(-1), std::invalid_argument);

    // Test with user ID that does not have measurements
    EXPECT_THROW(service.blacklistPrivateUser(1), std::invalid_argument);

    // Test with valid user ID
    EXPECT_NO_THROW(service.blacklistPrivateUser(0));
    EXPECT_TRUE(service.getSystem().getUsers().at(0).isBlacklisted());
    for (auto &measurement : service.getSystem().getMeasurements().at(0))
    {
        EXPECT_TRUE(measurement.isBlacklisted());
    }
}

// Test calculateQuality for blacklisted measurements
TEST_F(ServiceTest, CalculateQualityWithBlacklistedMeasurements)
{
    // Blacklist a user
    service.blacklistPrivateUser(0);

    // Calculates the quality of blacklisted measurements
    EXPECT_EQ(service.calculateQuality({{0, service.getSystem().getMeasurements().at(0)}}), 0.0);
}
