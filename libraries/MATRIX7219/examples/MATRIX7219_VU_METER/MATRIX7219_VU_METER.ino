//
//    FILE: MATRIX7219_VU_METER.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of MATRIX7219 8x8 LED MATRIX MAX7219
//     URL: https://github.com/RobTillaart/MATRIX7219


#include "MATRIX7219.h"

uint8_t dataPin   = 2;
uint8_t selectPin = 3;
uint8_t clockPin  = 4;
uint8_t count     = 1;

MATRIX7219 mx(dataPin, selectPin, clockPin, count);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MATRIX7219_LIB_VERSION: ");
  Serial.println(MATRIX7219_LIB_VERSION);
  Serial.println();

  mx.begin();
  mx.clear();
  mx.setBrightness(3);
  mx.setReverse(true);
}


void loop()
{
  //  simulation of VU.
  for (int n = 1; n < 9; n++)
  {
    mx.setRow(n, (1 << random(7)) - 1, 1);
    delay(10);
  }
}


//  -- END OF FILE --