//
//    FILE: TM1637_displayTime2.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo TM1637 library
//     URL: https://github.com/RobTillaart/TM1637_RT


#include "TM1637.h"

TM1637 TM;

uint32_t start, stop;

void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("TM1637_LIB_VERSION: ");
  Serial.println(TM1637_LIB_VERSION);
  Serial.println();

  TM.begin(7, 6, 4);       //  clock pin, data pin, #digits

  //               AVR UNO
  //  BITDELAY     displayTime()
  //  0               1352
  //  2               1364
  //  4               1384
  //  8               1452
  //  10              1476   (default, datasheet)
  TM.setBitDelay(10);
}

//  timer with 1/100th of second
void loop()
{
  uint32_t now = (millis() / 10) % 10000;
  uint8_t hh = now / 100;
  uint8_t mm = now - hh * 100;
  bool colon = hh & 1;
  start = micros();
  TM.displayTime(hh, mm, colon);  //  takes ~1500 usec (UNO).
  stop = micros();
  Serial.println(stop - start);
  delay(1);
}


//  -- END OF FILE --
