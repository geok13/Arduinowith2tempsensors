# Arduinowith2tempsensors
Files needed for connecting two DS18B20 temperature sensors to Arduino and LCD I2C screen
In order to work with the Arduino IDE, each file should be put in a folder with the same name
The file DS18B20OneWireAddress is useful for finding the one-wire address of each of the DS18B20 sensors that should be put in lines 34 &  35 of the file TwoTempSensorsonSerial (they won't be the same as mine!)
The file I2C_AddressofLCD is useful for finding the one-wire address of the LCD I2C screen that should be put in line 30 of the file TwoTempSensorswithLCD (instead of 0x3F)
The file TwoTempSensorsonSerial prints the temperatures that the sensors read in the serial screen. The sampling rate can be set by changing the delay(20000) where the 20000 is in milliseconds 
The file TwoTempSensorswithLCD prints the temperatures that the sensors read in an I2C_LCD screen with 2 lines of 16 characters each. Unfortunately the values of the following lines
#define BACKLIGHT_PIN  3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7
worked with my I2C LCD but may not work with others. In that case you have to search the Internet for appropriate values. My first attempt was also unfortunate and my LCD (with the following values) didn't work
#define BACKLIGHT_PIN  7
#define En_pin  4
#define Rw_pin  5
#define Rs_pin  6
#define D4_pin  0
#define D5_pin  1
#define D6_pin  2
#define D7_pin  3
You can try these if the first don't work.

George Kountouriotis
