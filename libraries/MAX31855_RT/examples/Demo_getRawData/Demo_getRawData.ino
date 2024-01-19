//
//    FILE: Demo_getRawData.ino
//  AUTHOR: FabioBrondo
// PURPOSE: thermocouple lib demo application
//    DATE: 2020-08-24
//     URL: https://github.com/RobTillaart/MAX31855_RT


#include "MAX31855.h"


const int selectPin = 7;
const int dataPin   = 6;
const int clockPin  = 5;

MAX31855 thermoCouple(selectPin, dataPin, clockPin);


void setup ()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MAX31855_VERSION : ");
  Serial.println(MAX31855_VERSION);
  Serial.println();
  delay(250);

  SPI.begin();

  thermoCouple.begin();
}


void loop ()
{
  int status = thermoCouple.read();
  if (status == STATUS_NO_COMMUNICATION)
  {
    Serial.println("NO COMMUNICATION");
  }

  uint32_t value = thermoCouple.getRawData();  // Read the raw Data value from the module
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
  Serial.println(thermoCouple.getTemperature(), 3);

  delay(100);
}


//  -- END OF FILE --

