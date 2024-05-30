#include <iostream>
#include "../src/System.h"
#include "../src/Measurement.h"

using namespace std;

void test_getMeasurements()
{

    System system = System("../data/Sensors/test1.csv", "../data/Cleaners/test1.csv", "../data/Users/test1.csv", "../data/Measurements/test1.csv");
    cout << "Test getMeasurements()" << endl;

    // Cas de test : nombre non nul de mesures
    system.addMeasurement(Measurement(1, Time("2021-01-01 00:00"), 1, "O3", 20.5, false));
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
    system.addSensor(Sensor(1, Coord(45.763420, 4.834277), false));
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
    system.addUser(User("User1"));
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

int main()
{
    test_getMeasurements();
    test_getCleaners();
    test_getSensors();
    test_getUsers();

    return 0;
}
