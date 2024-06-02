#include <iostream>
#include "Sensor.h"
#include "Service.h"
#include <map>
#include <cstring>
#include <fstream>
#include <regex>
#include "Zone.h"
#include <cstring>


using namespace std;

//Doxygen
void showMenu() {
    cout << "Menu Options:" << endl;
    cout << "1. Calculate impact radius of a cleaner" << endl;
    cout << "2. Display a list of similar sensors to a sensor" << endl;
    cout << "3. Calculate air quality of a certain zone and time period" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
}
bool isValidDateFormat(const string& date) {
    // Regex pattern for 'yyyy-mm-dd hh:mm:ss'
    const regex pattern(R"(\d{4}-\d{2}-\d{2}\s\d{2}:\d{2}:\d{2})");
    return regex_match(date, pattern);
}

int main(){
   
    
    Service service = Service("data/Sensors/test1.csv", "data/Cleaners/test1.csv", "data/Users/test1.csv", "data/Measurements/test1.csv");
    /*map<int,Sensor> sensors= service.getSystem().getSensors();
     for (auto it = sensors.rbegin(); it != sensors.rend(); ++it){
                    cout<< it->second <<endl;
                    
                }*/

    int choice;
    string sensorLine;

    do {
        showMenu();
        cin >> choice;
        cin.ignore(); // To consume the newline character after the choice input

        switch (choice) {
            case 1:{
                cout<<"Please enter the cleaner id!"<<endl;
                int cleanerID;
                cin>> cleanerID;
                cin.ignore();
                long cleanedAreaRadius = service.calculateImpactRadius(cleanerID);
                cout<<"The impact radius of the chosen cleaner is "<<cleanedAreaRadius<<"."<<endl;
                break;
            }
            case 2:{
                cout<<"Please enter the sensor id!"<<endl;
                int sensorID;
                cin>> sensorID;
                cin.ignore();

                cout<<"Period selection :(You need to enter two valid timestamps for this)"<<endl;
                cout<<"Starting date :(please respect this format : 'yyyy-mm-dd hh:mm:ss'))"<<endl;
                string startDate,endDate;
                
                
                while (true) {
                    cout << "Enter a valid date format (yyyy-mm-dd hh:mm:ss):" << endl;
                    getline(cin, startDate);

                    if (isValidDateFormat(startDate)) {
                        break; // Exit loop if the date format is valid
                    } else {
                        
                        cout << "Invalid date format! Please try again" << endl;
                    }
                }
                cout<<"Ending date :(please respect this format : '/yyyy-mm-dd hh:mm:ss'))"<<endl;
                while (true) {
                    cout << "Enter a valid date format (yyyy-mm-dd hh:mm:ss):" << endl;
                    getline(cin, endDate);

                    if (isValidDateFormat(endDate)) {
                        break; // Exit loop if the date format is valid
                    } else {
                        
                        cout << "Invalid date format! Please try again" << endl;
                    }
                }
                Time start = Time(startDate);
                Time end = Time(endDate);
                
                
                map<double, vector<int>> sensorsMap = service.rankSimilarSensors(sensorID,start,end);
                cout<<"List of similar sensors sorted by the the level of smilarity : "<<endl;
                for (auto it = sensorsMap.rbegin(); it != sensorsMap.rend(); ++it){
                    cout << "Air quality difference: " << it->first << ", Sensors ID: ";
                    for (auto &sensID: it->second){
                        cout << sensID << ", ";
                    }
                    cout << endl;
                }
                break;
            }
            case 3:{
                cout<<"Zone selection :(You need to enter a valid latitude , longitude and radius for this)"<<endl;
                cout<<"Please enter a latitude :"<<endl;
                double  latitude,longitude,radius;
                cin>> latitude;
                cin.ignore();
                cout<<"Please enter a longitude :"<<endl;
                cin>> longitude;
                cin.ignore();
                cout<<"Please enter a radius :"<<endl;
                cin>> radius;
                cin.ignore();
                Zone zone =Zone(latitude,longitude,radius);
                string startDate,endDate;
                cout<<"Period selection :(You need to enter two valid timestamps for this)"<<endl;
                cout<<"Starting date :(please respect this format : 'yyyy-mm-dd hh:mm:ss'))"<<endl;
                while (true) {
                    cout << "Enter a valid date format (yyyy-mm-dd hh:mm:ss):" << endl;
                    getline(cin, startDate);

                    if (isValidDateFormat(startDate)) {
                        break; // Exit loop if the date format is valid
                    } else {
                        
                        cout << "Invalid date format! Please try again" << endl;
                    }
                }
                cout<<"Ending date :(please respect this format : '/yyyy-mm-dd hh:mm:ss'))"<<endl;
                while (true) {
                    cout << "Enter a valid date format (yyyy-mm-dd hh:mm:ss):" << endl;
                    getline(cin, endDate);

                    if (isValidDateFormat(endDate)) {
                        break; // Exit loop if the date format is valid
                    } else {
                        
                        cout << "Invalid date format! Please try again" << endl;
                    }
                }
                Time start = Time(startDate);
                Time end = Time(endDate);
                double quality = service.calculateQuality( zone, start, end);
                cout<<"The quality of the selected zone and period is : "<<quality<<endl;
                break;
            }
            case 4:
                break;

            default:
                cout << "Invalid choice, please try again." << endl;
        }

        cout << endl;
    } while (choice != 4);

    

    return 0;
}