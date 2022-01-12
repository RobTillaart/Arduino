//
//    FILE: Demo_getRawData.ino
//  AUTHOR: RobTillaart, (based upon FabioBrondo
// PURPOSE: thermocouple lib demo application
//     URL: https://github.com/RobTillaart/MAX6675


#include "SPI.h"
#include "MAX6675.h"


#define MAXDO     7 // Defining the MISO pin
#define MAXCS     6 // Defining the CS pin
#define MAXCLK    5 // Defining the SCK pin


MAX6675 thermocouple;


void setup ()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();
  delay(250);

  thermocouple.begin(MAXCLK, MAXCS, MAXDO);
}


void loop ()
{
  int status = thermocouple.read();
  if (status != STATUS_OK)
  {
    Serial.println("ERROR!");
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

