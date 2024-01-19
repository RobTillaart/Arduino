//
//    FILE: Demo_getRawData.ino
//  AUTHOR: RobTillaart, (based upon FabioBrondo
// PURPOSE: thermocouple lib demo application
//     URL: https://github.com/RobTillaart/MAX6675


#include "MAX6675.h"


const int dataPin   = 7;
const int clockPin  = 6;
const int selectPin = 5;


MAX6675 thermoCouple(selectPin, dataPin, clockPin);


void setup ()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MAX6675_LIB_VERSION: ");
  Serial.println(MAX6675_LIB_VERSION);
  Serial.println();
  delay(250);

  SPI.begin();
  thermoCouple.begin();
}


void loop ()
{
  int status = thermoCouple.read();
  if (status != STATUS_OK)
  {
    Serial.println("ERROR!");
  }

  //  Read the raw Data value from the module
  uint32_t value = thermoCouple.getRawData();
  Serial.print("RAW:\t");

  //  Display the raw data value in BIN format
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

