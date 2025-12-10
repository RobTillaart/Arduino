//    FILE: DS1804_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/DS1804


#include "DS1804.h"


//  adjust pins if needed
const uint8_t CSPIN  = 5;
const uint8_t INCPIN = 6;
const uint8_t UDPIN  = 7;

DS1804 ds(CSPIN, INCPIN, UDPIN);


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("DS1804_LIB_VERSION: ");
  Serial.println(DS1804_LIB_VERSION);
  Serial.println();

  ds.begin();
  ds.select(true);
}


void loop()
{
  if (Serial.available())
  {
    int c = Serial.read();
    if (c == 'T') ds.select(true);
    if (c == 'F') ds.select(false);
    if (c == 'U') ds.moveUp();
    if (c == 'D') ds.moveDown();
  }
}


//  -- END OF FILE --
