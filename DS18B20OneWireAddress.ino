/* YourDuino Example: Find Address of 2 DS18B20 Temperature Sensors on the same bus
  Cut and paste the address to a text file for later use.
  Adapted by George Kountouriotis
 V1.0 01/18/2013
 Questions: terry@yourduino.com 
 
 Connections:
  DS18B20 Pinout for waterproof version
  - Black cable   = Ground
  - Yellow cable  = Signal (Pin 2):  (with a 4.7K resistor to +5 and Signal)
  - Red cable  = +5 V 
 This sketch looks for 1-wire devices and  prints their addresses (serial number)
 to the Serial Monitor in a format that is useful in Arduino sketches.
 Based on example at: 
 http://www.hacktronics.com/Tutorials/arduino-1-wire-address-finder.html
 */

/*-----( Import needed libraries )-----*/
#include <OneWire.h>

/*-----( Declare Constants and Pin Numbers )-----*/
#define SENSOR_1_PIN 2 // For BUS 1

/*-----( Declare objects )-----*/
OneWire  Bus1(SENSOR_1_PIN);  // Create a 1-wire object

void setup()  /****** SETUP: RUNS ONCE ******/
{
  Serial.begin(9600);
  Serial.println("Searching for DS18B20's on two different busses");
  Serial.println();
  
  Serial.println("Searching for DS18B20's on BUS ONE");  
  discoverBusOneWireDevices();  
  
  Serial.println();
  Serial.println();
  
  }//--(end setup )---

void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
  // Nothing happening here
}

/*-----( Declare User-written Functions )-----*/

void discoverBusOneWireDevices(void) 
{
  byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];

  Serial.print("Looking for 1-Wire devices...\n\r");// "\n\r" is NewLine 
  while(Bus1.search(addr)) {
    Serial.print("\n\rFound \'1-Wire\' device with address:\n\r");
    for( i = 0; i < 8; i++) {
      Serial.print("0x");
      if (addr[i] < 16) {
        Serial.print('0');
      }
      Serial.print(addr[i], HEX);
      if (i < 7) {
        Serial.print(", ");
      }
    }
    if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.print("CRC is not valid!\n\r");
      return;
    }
  }
  Serial.println();
  Serial.print("Done");
  Bus1.reset_search();
  return;
}// END

//------------------------------------------------------------




//*********( THE END )***********


