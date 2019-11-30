//
//    FILE: demo_dual1.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.0.1
// PURPOSE: demo 2 I2C 4x7segment displays one uint32_t unsigned long
//     URL: http://www.adafruit.com/products/1002
// HISTORY:

#include <Wire.h>
#include "HT16K33.h"

HT16K33 left, right;

uint32_t counter = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  left.begin(0x70);
  right.begin(0x71);
  
  Wire.setClock(100000);

  left.displayOn();
  right.displayOn();
  left.suppressLeadingZeroPlaces(4);    // show no digit if not needed
  right.suppressLeadingZeroPlaces(3);   // show at least 1 digit if zero (0)
  
  Serial.println("dual displayTest");
}

void loop()
{
  uint16_t lval = counter / 10000;
  uint16_t rval = counter % 10000;
  
  right.suppressLeadingZeroPlaces(lval == 0 ? 3 : 0);
  left.displayInt(lval);
  right.displayInt(rval);

  delay(1);  
  counter++;
}

// -- END OF FILE -- 