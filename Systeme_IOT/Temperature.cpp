//******************************************************************
// First we include the libraries
#include <OneWire.h> 
#include <DallasTemperature.h>
#include "Temperature.h"
//******************************************************************
// Data wire is plugged into pin 2 on the Arduino 
#define ONE_WIRE_BUS 2 
//******************************************************************
// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS); 
//******************************************************************
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// Char* globale var
char* char_temp = new char[10];

void TEMP_setup(void) 
{ 
 // start serial port 
 Serial.begin(115200); 
 Serial.println("Dallas Temperature IC Control Library Demo"); 
 // Start up the library 
 sensors.begin(); 
}

int TEMP_mes() 
{ 
  int Temp = 0;
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus 

  //Serial.print(" Requesting temperatures..."); 
  sensors.requestTemperatures(); // Send the command to get temperature readings 
  //Serial.println("DONE"); 

  Temp=(int)(sensors.getTempCByIndex(0) * 10); // Why "byIndex"?  
  // You can have more than one DS18B20 on the same bus.  
  // 0 refers to the first IC on the wire 
  delay (50);
  return Temp;
}
