#include <iostream>
#include "Sensor.h"
#include "Service.h"
#include <map>
#include <cstring>
#include <fstream>
#include <regex>
#include "Zone.h"
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
    // Regex pattern for 'dd/mm/yyyy'
    const regex pattern("\\d{2}/\\d{2}/\\d{4}");
    return regex_match(date, pattern);
}

int main(){
   
    
    Service service = Service("../data/sensors.csv","../data/cleaners.csv","../data/users.csv","../data/measurements.csv"); // 
    int choice;
    string sensorLine;

    do {
        showMenu();
        cin >> choice;
        cin.ignore(); // To consume the newline character after the choice input

        switch (choice) {
            case 1:
                cout<<"Please enter the cleaner id!"<<endl;
                int cleanerID;
                cin>> cleanerID;
                cin.ignore();
                long radius = service.calculateImpactRadius(cleanerID);
                cout<<"The impact radius of the chosen cleaner is "<<radius<<"."<<endl;
                break;
            case 2:
                cout<<"Please enter the cleaner id!"<<endl;
                int cleanerID;
                cin>> cleanerID;
                cin.ignore();

                cout<<"Period selection :(You need to enter two valid timestamps for this)"<<endl;
                cout<<"Starting date :(please respect this format : 'dd/mm/yyyy hh:mm:ss'))"<<endl;
                string startDate,endDate;
                cin>> startDate;
                cin.ignore();
                while (!isValidDateFormat(startDate)){
                    cout<<"Invalid date format! Please try again"<<endl;
                    cin>> startDate;
                    cin.ignore();
                }
                cout<<"Ending date :(please respect this format : 'dd/mm/yyyy dd/mm/yyyy hh:mm:ss'))"<<endl;
                cin>> endDate;
                cin.ignore();
                while (!isValidDateFormat(endDate)){
                    cout<<"Invalid date format! Please try again"<<endl;
                    cin>> endDate;
                    cin.ignore();
                }
                Time start = Time(startDate);
                Time end = Time(endDate);
                
                cout<<"Please enter the tolerance level (delta) :"<<endl;
                double delta;
                cin>> delta;
                cin.ignore();
                
                
                multimap<double,int> sensors = service.getSimilarZones(cleanerID,start,end,delta);
                cout<<"List of similar sensors sorted by the the level of smilarity : "<<endl;
                for (auto it = sensors.rbegin(); it != sensors.rend(); ++it){
                    cout<<"Sensor id : "<<it->second <<" Air quality difference : "<<it->first<<" ."<<endl;
                    
                }
                break;
            case 3:
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

                cout<<"Period selection :(You need to enter two valid timestamps for this)"<<endl;
                cout<<"Starting date :(please respect this format : 'dd/mm/yyyy hh:mm:ss'))"<<endl;
                string startDate,endDate;
                cin>> startDate;
                cin.ignore();
                while (!isValidDateFormat(startDate)){
                    cout<<"Invalid date format! Please try again"<<endl;
                    cin>> startDate;
                    cin.ignore();
                }
                cout<<"Ending date :(please respect this format : 'dd/mm/yyyy dd/mm/yyyy hh:mm:ss'))"<<endl;
                cin>> endDate;
                cin.ignore();
                while (!isValidDateFormat(endDate)){
                    cout<<"Invalid date format! Please try again"<<endl;
                    cin>> endDate;
                    cin.ignore();
                }
                Time start = Time(startDate);
                Time end = Time(endDate);
                double quality = service.calculateQuality( zone, start, end);
                cout<<"The quality of the selected zone and period is : "<<quality<<endl;
                break;
            case 4:
                break;

            default:
                cout << "Invalid choice, please try again." << endl;
        }

        cout << endl;
    } while (choice != 4);

    return 0;
}