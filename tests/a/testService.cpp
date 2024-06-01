
void test_impactPurificateur()
{
    System system("data/Sensors/test1.csv", "data/Cleaners/test1.csv", "data/Users/test1.csv", "data/Measurements/test1.csv");
    Service service(system);

    cout << "Test impactPurificateur()" << endl;

    // Test with a valid cleaner ID
    try
    {
        double result = service.calculateImpactRadius(1);
        cout << "Result is: " << result << endl;
        cout << "----> Test with valid cleaner ID: Passed" << endl;
    }
    catch (const exception &e)
    {
        cout << "----> Test with valid cleaner ID: Failed" << endl;
    }

    // Test with an invalid cleaner ID
    try
    {
        double result = service.calculateImpactRadius(-1);
        cout << "Result is: " << result << endl;
        cout << "----> Test with invalid cleaner ID: Failed (no exception thrown)" << endl;
    }
    catch (const exception &e)
    {
        cout << "----> Test with invalid cleaner ID: Passed (exception thrown)" << endl;
    }

    // Test with insufficient improvement in air quality
    try
    {
        double result = service.calculateImpactRadius(2); // Assume ID 2 has insufficient improvement
        if (result == 0)
        {
            cout << "----> Test with insufficient improvement in air quality: Passed" << endl;
        }
        else
        {
            cout << "----> Test with insufficient improvement in air quality: Failed" << endl;
        }
    }
    catch (const exception &e)
    {
        cout << "----> Test with insufficient improvement in air quality: Failed (exception thrown)" << endl;
    }

    // Test with significant improvement in air quality
    try
    {
        double result = service.calculateImpactRadius(3); // Assume ID 3 has significant improvement
        if (result > 0)
        {
            cout << "----> Test with significant improvement in air quality: Passed" << endl;
        }
        else
        {
            cout << "----> Test with significant improvement in air quality: Failed" << endl;
        }
    }
    catch (const exception &e)
    {
        cout << "----> Test with significant improvement in air quality: Failed (exception thrown)" << endl;
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
        cout << "----> Test with different coordinates: Passed" << endl;
    }
    else
    {
        cout << "----> Test with different coordinates: Failed" << endl;
    }

    // Test with the same coordinates
    result = service.distance(coord1, coord1);
    if (result == 0)
    {
        cout << "----> Test with the same coordinates: Passed" << endl;
    }
    else
    {
        cout << "----> Test with the same coordinates: Failed" << endl;
    }

    // Test with null coordinates (assuming null check should return -1)
    try
    {
        Coord *nullCoord = nullptr;
        result = service.distance(*nullCoord, coord2);
        cout << "----> Test with null coordinates: Failed (no exception thrown)" << endl;
    }
    catch (const exception &e)
    {
        cout << "----> Test with null coordinates: Passed (exception thrown)" << endl;
    }

    // Test with very distant coordinates
    Coord coord3(21.0278, 105.8342); // Hanoi
    result = service.distance(coord1, coord3);
    if (result > 0)
    {
        cout << "----> Test with very distant coordinates: Passed" << endl;
    }
    else
    {
        cout << "----> Test with very distant coordinates: Failed" << endl;
    }
}

void test_chercherZones()
{
    System system("data/Sensors/test1.csv", "data/Cleaners/test1.csv", "data/Users/test1.csv", "data/Measurements/test1.csv");
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
            cout << "----> Test with existing sensor ID and valid time range: Passed" << endl;
        }
        else
        {
            cout << "----> Test with existing sensor ID and valid time range: Failed" << endl;
        }
    }
    catch (const exception &e)
    {
        cout << "----> Test with existing sensor ID and valid time range: Failed (exception thrown)" << endl;
    }

    // Test with non-existent sensor ID
    try
    {
        auto zones = service.getSimilarZones(-1, start, end, 0.1);
        if (zones.empty())
        {
            cout << "----> Test with non-existent sensor ID: Passed" << endl;
        }
        else
        {
            cout << "----> Test with non-existent sensor ID: Failed" << endl;
        }
    }
    catch (const exception &e)
    {
        cout << "----> Test with non-existent sensor ID: Failed (exception thrown)" << endl;
    }

    // Test with end date before start date
    try
    {
        auto zones = service.getSimilarZones(1, end, start, 0.1);
        if (zones.empty())
        {
            cout << "----> Test with end date before start date: Passed" << endl;
        }
        else
        {
            cout << "----> Test with end date before start date: Failed" << endl;
        }
    }
    catch (const exception &e)
    {
        cout << "----> Test with end date before start date: Failed (exception thrown)" << endl;
    }

    // Test with start date equal to end date
    try
    {
        auto zones = service.getSimilarZones(1, start, start, 0.1);
        if (!zones.empty())
        {
            cout << "----> Test with start date equal to end date: Passed" << endl;
        }
        else
        {
            cout << "----> Test with start date equal to end date: Failed" << endl;
        }
    }
    catch (const exception &e)
    {
        cout << "----> Test with start date equal to end date: Failed (exception thrown)" << endl;
    }

    // Test with invalid delta (<= 0)
    try
    {
        auto zones = service.getSimilarZones(1, start, end, -0.1);
        cout << "----> Test with invalid delta: Failed (no exception thrown)" << endl;
    }
    catch (const exception &e)
    {
        cout << "----> Test with invalid delta: Passed (exception thrown)" << endl;
    }
}