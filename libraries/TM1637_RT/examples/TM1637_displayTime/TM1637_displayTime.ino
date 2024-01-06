//
//    FILE: TM1637_displayTime.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo TM1637 library
//     URL: https://github.com/RobTillaart/TM1637


#include "TM1637.h"

TM1637 TM;

uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  TM.begin(7, 6, 4);       //  clock pin, data pin, #digits

  delay(10);
  start = micros();
  TM.displayTime(59, 59, true);
  stop = micros();
  Serial.println(stop - start);
}


void loop()
{
  uint32_t now = 523 + millis() / 1000;
  uint8_t hh = now / 60;
  uint8_t mm = now - hh * 60;
  bool colon = (millis() % 1000 < 500);
  TM.displayTime(hh, mm, colon);
}


//  -- END OF FILE --
