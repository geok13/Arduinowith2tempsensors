/* Adapted from a similar example found on * 
 * YourDuino.com: Multiple DS18B20 Temperature Sensors
   Displayed on 2x16 character LCD display by George Kountouriotis
   
   DS18B20 Pinout for waterproof version
  - Black cable   = Ground
  - Yellow cable  = Signal (Pin 10):  (with a 4.7K resistor to +5 and Signal)
  - Red cable  = +5 V
   
   terry@yourduino.com */

/*-----( Import needed libraries )-----*/
// Get 1-wire Library here: http://www.pjrc.com/teensy/td_libs_OneWire.html
#include <OneWire.h>

//Get DallasTemperature Library here:  http://milesburton.com/Main_Page?title=Dallas_Temperature_Control_Library
#include <DallasTemperature.h>
// Wire (I2C) Library
#include <Wire.h>
// LCD Library
#include <LiquidCrystal_I2C.h>  // F Malpartida's NewLiquidCrystal library
//Download: https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
// Move original LiquidCrystal library elsewhere, copy this in it's place


/*-----( Declare Constants and Pin Numbers )-----*/
// Data wire is plugged into port 10 on the Arduino (can be changed)
#define ONE_WIRE_BUS 10    // NOTE: No ";" on #define  

#define I2C_ADDR    0x3F  // Define I2C Address
//---(Following are the LCD specific pin assignments to LCD connections )----
// This can be different than earlier/different I2C LCD displays
#define BACKLIGHT_PIN  3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

#define  LED_OFF  0
#define  LED_ON  1

/*-----( Declare objects )-----*/
// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass address of our oneWire instance to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// Start the LCD display library
LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

/*-----( Declare Variables )-----*/
// Assign the addresses of your 1-Wire temp sensors.
// See the tutorial on how to obtain these addresses:
// http://arduino-info.wikispaces.com/Brick-Temperature-DS18B20#Read%20individual


 // WP 1
DeviceAddress Probe01 = { 0x28, 0xFF, 0x06, 0x0E, 0x63, 0x16, 0x03, 0x024 }; // "1"
DeviceAddress Probe02 = { 0x28, 0xFF, 0xBC, 0xE5, 0x62, 0x16, 0x04, 0x23 }; // "2"


void setup()   /****** SETUP: RUNS ONCE ******/
{
//------- Initialize the Temperature measurement library--------------
  sensors.begin();
  // set the resolution to 10 bit (Can be 9 to 12 bits .. lower is faster)
  sensors.setResolution(Probe01, 12);
  sensors.setResolution(Probe02, 12);
  //sensors.setResolution(Probe03, 10);
  //sensors.setResolution(Probe04, 10);

//---------------- Initialize the lcd ------------------  
  lcd.begin (16,2);  // 20 characters, 4 lines
  lcd.clear();
// Switch on the backlight
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(LED_ON);  

}//--(end setup )---


void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
  sensors.requestTemperatures(); // Send the command to get temperatures

  lcd.clear();  // Reset the display  
  lcd.home();
  //lcd.backlight();  //Backlight ON if under program control  
  delay(1000);
// Print our characters on the LCD
// NOTE: Line number and character number start at 0 not 1
  
  lcd.setCursor(0,0); //Start at character 0 on line 0
  lcd.print("1: ");
  displayTemperature(Probe01);  
  
  lcd.setCursor(0,1); //Start at character 0 on line 1
  lcd.print("2: ");
  displayTemperature(Probe02);  
  
  delay(29000);

}//--(end main loop )---

/*-----( Declare User-written Functions )-----*/
void displayTemperature(DeviceAddress deviceAddress)
{
int Temp;
float tempC = sensors.getTempC(deviceAddress);

   if (tempC == -127.00) // Measurement failed or no device found
   {
    lcd.print("Temp Error");
   } 
   else
   {
   lcd.print("C=");
   Temp=int(tempC);
   lcd.print(Temp);
   
   }
}// End printTemperature

//*********( THE END )***********


