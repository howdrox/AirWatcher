#include<string>
#include "Date.h"


#if ! defined ( MEASUREMENT_H )
#define MEASUREMENT_H



class Measurement  
{
//----------------------------------------------------------------- PUBLIC

public:

     Sensor getCapteurID();

     DateTime getTimestamp();

     int getDay();  //on va utiliser int pour représenter les jours de la semaine(0 = Sunday, 1 = Monday, ..., 6 = Saturday)
     
//-------------------------------------------- Constructeurs - destructeur
    Measurement ( const Measurement & Measurement );

    Measurement ( string  & ligne);
    
    virtual ~Measurement ( );
      
protected:
    
    int measurementID;
    DateTime timestamp;
    std::string attributeID;
    double value;
    int sensorID;
   
    

};


#endif 

