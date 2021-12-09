//
//    FILE: Demo_getRawData.ino
//  AUTHOR: FabioBrondo
// VERSION: 0.4.0
// PURPOSE: thermocouple lib demo application
//    DATE: 2020-08-24
//     URL: https://github.com/RobTillaart/MAX31855_RT
//


#include <SPI.h>
#include <MAX31855.h>


#define MAXDO     7 // Defining the MISO pin
#define MAXCS     6 // Defining the CS pin
#define MAXCLK    5 // Defining the SCK pin


MAX31855 thermocouple;


void setup ()
{
  Serial.begin(115200);
  delay(250);
  thermocouple.begin(MAXCLK, MAXCS, MAXDO);
}


void loop ()
{
  int status = thermocouple.read();
  if (status == STATUS_NO_COMMUNICATION)
  {
    Serial.println("NO COMMUNICATION");
  }

  uint32_t value = thermocouple.getRawData();  // Read the raw Data value from the module
  Serial.print("RAW:\t");

  // Display the raw data value in BIN format
  uint32_t mask = 0x80000000; 
  for (int i = 0; i < 32; i++) 
  {
    if ((i > 0)  && (i % 4 == 0)) Serial.print("-");
    Serial.print((value & mask) ? 1 : 0);
    mask >>= 1;
  }
  Serial.println();

  Serial.print("TMP:\t");
  Serial.println(thermocouple.getTemperature(), 3);

  delay(100);
}


// -- END OF FILE --

