#include <iostream>
#include "System.h"
#include "Service.h"

using namespace std;

void test_getMeasurements()
{

    System system = System("../data/Sensors/test1.csv", "../data/Cleaners/test1.csv", "../data/Users/test1.csv", "../data/Measurements/test1.csv");
    cout << "Test getMeasurements()" << endl;

    // Cas de test : nombre non nul de mesures
    system.addMeasurement(Measurement("2021-01-01 00:00:00;Sensor1;O3;20.5"));
    if (system.getMeasurements().size() > 0)
    {
        cout << "Test getMeasurements() avec mesures non nulles : Réussi" << endl;
    }
    else
    {
        cout << "Test getMeasurements() avec mesures non nulles : Échoué" << endl;
    }

    // Cas de test : nombre nul de mesures
    System emptySystem = System("../data/Sensors/test0.csv", "../data/Cleaners/test0.csv", "../data/Users/test0.csv", "../data/Measurements/test0.csv");
    if (emptySystem.getMeasurements().size() == 0)
    {
        cout << "Test getMeasurements() avec mesures nulles : Réussi" << endl;
    }
    else
    {
        cout << "Test getMeasurements() avec mesures nulles : Échoué" << endl;
    }
}

void test_getCleaners()
{
    System system = System("../data/Sensors/test1.csv", "../data/Cleaners/test1.csv", "../data/Users/test1.csv", "../data/Measurements/test1.csv");
    cout << "Test getCleaners()" << endl;

    // Cas de test : nombre non nul de nettoyeurs
    system.addCleaner(Cleaner("Cleaner1"));
    if (system.getCleaners().size() > 0)
    {
        cout << "Test getCleaners() avec nettoyeurs non nuls : Réussi" << endl;
    }
    else
    {
        cout << "Test getCleaners() avec nettoyeurs non nuls : Échoué" << endl;
    }

    // Cas de test : nombre nul de nettoyeurs
    System emptySystem = System("../data/Sensors/test0.csv", "../data/Cleaners/test0.csv", "../data/Users/test0.csv", "../data/Measurements/test0.csv");
    if (emptySystem.getCleaners().size() == 0)
    {
        cout << "Test getCleaners() avec nettoyeurs nuls : Réussi" << endl;
    }
    else
    {
        cout << "Test getCleaners() avec nettoyeurs nuls : Échoué" << endl;
    }
}

void test_getSensors()
{
    System system = System("../data/Sensors/test1.csv", "../data/Cleaners/test1.csv", "../data/Users/test1.csv", "../data/Measurements/test1.csv");
    cout << "Test getSensors()" << endl;

    // Cas de test : nombre non nul de capteurs
    system.addSensor(Sensor("Sensor1"));
    if (system.getSensors().size() > 0)
    {
        cout << "Test getSensors() avec capteurs non nuls : Réussi" << endl;
    }
    else
    {
        cout << "Test getSensors() avec capteurs non nuls : Échoué" << endl;
    }

    // Cas de test : nombre nul de capteurs
    System emptySystem = System("../data/Sensors/test0.csv", "../data/Cleaners/test0.csv", "../data/Users/test0.csv", "../data/Measurements/test0.csv");
    if (emptySystem.getSensors().size() == 0)
    {
        cout << "Test getSensors() avec capteurs nuls : Réussi" << endl;
    }
    else
    {
        cout << "Test getSensors() avec capteurs nuls : Échoué" << endl;
    }
}

void test_getUsers()
{
    System system = System("../data/Sensors/test1.csv", "../data/Cleaners/test1.csv", "../data/Users/test1.csv", "../data/Measurements/test1.csv");
    cout << "Test getUsers()" << endl;

    // Cas de test : nombre non nul d'utilisateurs
    system.addUser(PrivateUser("User1"));
    if (system.getUsers().size() > 0)
    {
        cout << "Test getUsers() avec utilisateurs non nuls : Réussi" << endl;
    }
    else
    {
        cout << "Test getUsers() avec utilisateurs non nuls : Échoué" << endl;
    }

    // Cas de test : nombre nul d'utilisateurs
    System emptySystem = System("../data/Sensors/test0.csv", "../data/Cleaners/test0.csv", "../data/Users/test0.csv", "../data/Measurements/test0.csv");
    if (emptySystem.getUsers().size() == 0)
    {
        cout << "Test getUsers() avec utilisateurs nuls : Réussi" << endl;
    }
    else
    {
        cout << "Test getUsers() avec utilisateurs nuls : Échoué" << endl;
    }
}

void test_calculateQuality()
{
    System system("../data/Sensors/test1.csv", "../data/Cleaners/test1.csv", "../data/Users/test1.csv", "../data/Measurements/test1.csv");
    Service service(system);

    Coord center(44.8, 2.3);
    Time start(2019, 1, 1, 0, 0, 0);
    Time end(2019, 1, 4, 0, 0, 0);

    cout << "Test calculateQuality()" << endl;

    // Test with valid measurements in the specified zone and time range
    Zone zone(center.latitude, center.longitude, 10.0);
    double result = service.calculateQuality(zone, start, end);
    if (result > 0)
    {
        cout << "Test with valid measurements: Passed" << endl;
    }
    else
    {
        cout << "Test with valid measurements: Failed" << endl;
    }

    // Test with no measurements in the specified zone
    Zone smallZone(center.latitude, center.longitude, 0.1);
    result = service.calculateQuality(smallZone, start, end);
    if (result == 0)
    {
        cout << "Test with no measurements in the zone: Passed" << endl;
    }
    else
    {
        cout << "Test with no measurements in the zone: Failed" << endl;
    }

    // Test with measurements outside the specified time range
    Time start1(2024, 1, 1, 0, 0, 0);
    Time end1(2024, 1, 4, 0, 0, 0);
    result = service.calculateQuality(zone, start1, end1);
    if (result == 0)
    {
        cout << "Test with measurements outside time range: Passed" << endl;
    }
    else
    {
        cout << "Test with measurements outside time range: Failed" << endl;
    }

    // Test with zero radius
    try
    {
        Zone zeroRadiusZone(center.latitude, center.longitude, 0.0);
        result = service.calculateQuality(zeroRadiusZone, start, end);
        cout << "Test with zero radius: Failed (no exception thrown)" << endl;
    }
    catch (const exception &e)
    {
        cout << "Test with zero radius: Passed (exception thrown)" << endl;
    }

    // Test with very large radius
    Zone largeZone(center.latitude, center.longitude, 10000.0);
    result = service.calculateQuality(largeZone, start, end);
    if (result > 0)
    {
        cout << "Test with very large radius: Passed" << endl;
    }
    else
    {
        cout << "Test with very large radius: Failed" << endl;
    }

    // Test with start date later than end date
    try
    {
        result = service.calculateQuality(zone, end, start);
        cout << "Test with start date later than end date: Failed (no exception thrown)" << endl;
    }
    catch (const exception &e)
    {
        cout << "Test with start date later than end date: Passed (exception thrown)" << endl;
    }
}

void test_filterMeasurements()
{
    System system("../data/Sensors/test1.csv", "../data/Cleaners/test1.csv", "../data/Users/test1.csv", "../data/Measurements/test1.csv");
    Service service(system);

    Time start(2019, 1, 1, 0, 0, 0);
    Time end(2019, 1, 4, 0, 0, 0);
    map<int, vector<Measurement>> measurements = system.getMeasurements();

    cout << "Test filterMeasurements()" << endl;

    // Test with valid date range and existing measurements
    auto filtered = service.filterMeasurements(start, end, measurements);
    if (!filtered.empty())
    {
        cout << "Test with valid date range and existing measurements: Passed" << endl;
    }
    else
    {
        cout << "Test with valid date range and existing measurements: Failed" << endl;
    }

    // Test with valid date range containing no measurements
    Time start1(2024, 1, 1, 0, 0, 0);
    Time end1(2024, 1, 4, 0, 0, 0);
    filtered = service.filterMeasurements(start1, end1, measurements);
    if (filtered.empty())
    {
        cout << "Test with valid date range containing no measurements: Passed" << endl;
    }
    else
    {
        cout << "Test with valid date range containing no measurements: Failed" << endl;
    }

    // Test with start date equal to end date
    Time start2(2019, 1, 1, 0, 0, 0);
    Time end2(2019, 1, 1, 23, 59, 59);
    filtered = service.filterMeasurements(start2, end2, measurements);
    if (!filtered.empty())
    {
        cout << "Test with start date equal to end date: Passed" << endl;
    }
    else
    {
        cout << "Test with start date equal to end date: Failed" << endl;
    }

    // Test with end date before start date
    filtered = service.filterMeasurements(end, start, measurements);
    if (filtered.empty())
    {
        cout << "Test with end date before start date: Passed" << endl;
    }
    else
    {
        cout << "Test with end date before start date: Failed" << endl;
    }

    // Test with valid date range but empty measurements
    map<int, vector<Measurement>> emptyMeasurements;
    filtered = service.filterMeasurements(start, end, emptyMeasurements);
    if (filtered.empty())
    {
        cout << "Test with valid date range but empty measurements: Passed" << endl;
    }
    else
    {
        cout << "Test with valid date range but empty measurements: Failed" << endl;
    }
}

void test_impactPurificateur()
{
    System system("../data/Sensors/test1.csv", "../data/Cleaners/test1.csv", "../data/Users/test1.csv", "../data/Measurements/test1.csv");
    Service service(system);

    cout << "Test impactPurificateur()" << endl;

    // Test with a valid cleaner ID
    try
    {
        double result = service.calculateImpactRadius(1);
        cout << "Test with valid cleaner ID: Passed" << endl;
    }
    catch (const exception &e)
    {
        cout << "Test with valid cleaner ID: Failed" << endl;
    }

    // Test with an invalid cleaner ID
    try
    {
        double result = service.calculateImpactRadius(-1);
        cout << "Test with invalid cleaner ID: Failed (no exception thrown)" << endl;
    }
    catch (const exception &e)
    {
        cout << "Test with invalid cleaner ID: Passed (exception thrown)" << endl;
    }

    // Test with insufficient improvement in air quality
    try
    {
        double result = service.calculateImpactRadius(2); // Assume ID 2 has insufficient improvement
        if (result == 0)
        {
            cout << "Test with insufficient improvement in air quality: Passed" << endl;
        }
        else
        {
            cout << "Test with insufficient improvement in air quality: Failed" << endl;
        }
    }
    catch (const exception &e)
    {
        cout << "Test with insufficient improvement in air quality: Failed (exception thrown)" << endl;
    }

    // Test with significant improvement in air quality
    try
    {
        double result = service.calculateImpactRadius(3); // Assume ID 3 has significant improvement
        if (result > 0)
        {
            cout << "Test with significant improvement in air quality: Passed" << endl;
        }
        else
        {
            cout << "Test with significant improvement in air quality: Failed" << endl;
        }
    }
    catch (const exception &e)
    {
        cout << "Test with significant improvement in air quality: Failed (exception thrown)" << endl;
    }
}

void test_distance()
{
    Service service;

    cout << "Test distance()" << endl;

    // Test with different coordinates
    Coord coord1(48.8575, 2.3514);
    Coord coord2(45.7640, 4.8357);
    double result = service.distance(coord1, coord2);
    if (result > 0)
    {
        cout << "Test with different coordinates: Passed" << endl;
    }
    else
    {
        cout << "Test with different coordinates: Failed" << endl;
    }

    // Test with the same coordinates
    result = service.distance(coord1, coord1);
    if (result == 0)
    {
        cout << "Test with the same coordinates: Passed" << endl;
    }
    else
    {
        cout << "Test with the same coordinates: Failed" << endl;
    }

    // Test with null coordinates (assuming null check should return -1)
    try
    {
        Coord *nullCoord = nullptr;
        result = service.distance(*nullCoord, coord2);
        cout << "Test with null coordinates: Failed (no exception thrown)" << endl;
    }
    catch (const exception &e)
    {
        cout << "Test with null coordinates: Passed (exception thrown)" << endl;
    }

    // Test with very distant coordinates
    Coord coord3(21.0278, 105.8342); // Hanoi
    result = service.distance(coord1, coord3);
    if (result > 0)
    {
        cout << "Test with very distant coordinates: Passed" << endl;
    }
    else
    {
        cout << "Test with very distant coordinates: Failed" << endl;
    }
}

void test_chercherZones()
{
    System system("../data/Sensors/test1.csv", "../data/Cleaners/test1.csv", "../data/Users/test1.csv", "../data/Measurements/test1.csv");
    Service service(system);

    Time start(2023, 1, 1, 0, 0, 0);
    Time end(2023, 12, 31, 23, 59, 59);

    cout << "Test chercherZones()" << endl;

    // Test with existing sensor ID and valid time range
    try
    {
        auto zones = service.getSimilarZones(1, start, end, 0.1);
        if (!zones.empty())
        {
            cout << "Test with existing sensor ID and valid time range: Passed" << endl;
        }
        else
        {
            cout << "Test with existing sensor ID and valid time range: Failed" << endl;
        }
    }
    catch (const exception &e)
    {
        cout << "Test with existing sensor ID and valid time range: Failed (exception thrown)" << endl;
    }

    // Test with non-existent sensor ID
    try
    {
        auto zones = service.getSimilarZones(-1, start, end, 0.1);
        if (zones.empty())
        {
            cout << "Test with non-existent sensor ID: Passed" << endl;
        }
        else
        {
            cout << "Test with non-existent sensor ID: Failed" << endl;
        }
    }
    catch (const exception &e)
    {
        cout << "Test with non-existent sensor ID: Failed (exception thrown)" << endl;
    }

    // Test with end date before start date
    try
    {
        auto zones = service.getSimilarZones(1, end, start, 0.1);
        if (zones.empty())
        {
            cout << "Test with end date before start date: Passed" << endl;
        }
        else
        {
            cout << "Test with end date before start date: Failed" << endl;
        }
    }
    catch (const exception &e)
    {
        cout << "Test with end date before start date: Failed (exception thrown)" << endl;
    }

    // Test with start date equal to end date
    try
    {
        auto zones = service.getSimilarZones(1, start, start, 0.1);
        if (!zones.empty())
        {
            cout << "Test with start date equal to end date: Passed" << endl;
        }
        else
        {
            cout << "Test with start date equal to end date: Failed" << endl;
        }
    }
    catch (const exception &e)
    {
        cout << "Test with start date equal to end date: Failed (exception thrown)" << endl;
    }

    // Test with invalid delta (<= 0)
    try
    {
        auto zones = service.getSimilarZones(1, start, end, -0.1);
        cout << "Test with invalid delta: Failed (no exception thrown)" << endl;
    }
    catch (const exception &e)
    {
        cout << "Test with invalid delta: Passed (exception thrown)" << endl;
    }
}

int main()
{
    test_getMeasurements();
    test_getCleaners();
    test_getSensors();
    test_getUsers();

    return 0;
}
