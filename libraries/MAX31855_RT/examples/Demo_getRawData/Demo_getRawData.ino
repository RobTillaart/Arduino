//
//    FILE: Demo_getRawData.ino
//  AUTHOR: FabioBrondo
// VERSION: 0.1.1
// PURPOSE: thermocouple lib demo application
//    DATE: 2020-08-24
//     URL: https://github.com/RobTillaart/MAX31855_RT
//

#include <SPI.h>
#include <MAX31855.h>

#define MAXDO     7 // Defining the MISO pin
#define MAXCS     6 // Defining the CS pin
#define MAXCLK    5 // Defining the SCK pin


MAX31855 thermocouple(MAXCLK, MAXCS, MAXDO);

void setup ()
{
  Serial.begin(115200);
  delay(250);
  thermocouple.begin();
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
  Serial.println(value, BIN);                  // Display the raw data value in BIN format

  Serial.print("TMP:\t");
  Serial.println(thermocouple.getTemperature());

  delay(100);
}

// -- END OF FILE --
