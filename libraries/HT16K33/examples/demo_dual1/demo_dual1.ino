//
//    FILE: demo_dual1.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo 2 I2C 4x7segment displays one uint32_t unsigned long
//     URL: http://www.adafruit.com/products/1002
//     URL: https://github.com/RobTillaart/HT16K33


#include "HT16K33.h"

HT16K33 left(0x71);
HT16K33 right(0x70);

uint32_t counter = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("HT16K33_LIB_VERSION: ");
  Serial.println(HT16K33_LIB_VERSION);

  Wire.begin();
  Wire.setClock(100000);

  left.begin();
  right.begin();

  left.displayOn();
  right.displayOn();

  Serial.println("dual displayTest");
}


void loop()
{
  display_ulong(counter);

  delay(1);
  counter++;
}


void display_ulong(uint32_t value)
{
  uint16_t lval = value / 10000;
  uint16_t rval = value % 10000;

  // left show no digit if not needed
  left.setDigits(0);
  // right show at least 1 digit if value < 10000, otherwise leading zero's needed
  right.setDigits(lval > 0 ? 4 : 0);

  left.displayInt(lval);
  right.displayInt(rval);
}


// -- END OF FILE --

