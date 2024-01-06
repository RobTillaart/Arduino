//
//    FILE: TM1637_clock_4digits.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo TM1637 library
//     URL: https://github.com/RobTillaart/TM1637
//
//  Since 0.3.6 the library has the function displayTime(hh, mm, colon).
//  so part of this sketch is "historical".


#include "TM1637.h"

TM1637 TM;


uint32_t start, stop;
volatile uint32_t val  = 0;

uint8_t bright = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  TM.begin(7, 6, 4);       //  clockPin, dataPin, #digits

  TM.displayClear();
  delay(2000);

  TM.setBrightness(1);
  TM.displayHex(0xDCBA);
  delay(2000);

  TM.setBrightness(3);
  TM.displayHex(0x4321);
  delay(2000);

  TM.setBrightness(7);
  TM.displayInt(567);
  delay(2000);

  TM.setBrightness(5);
  TM.displayFloat(12.341);  //  shows : in middle of clock
  delay(2000);
}

//  mimic clock, not OK under 10 seconds
//  left as exercise for the programmer ;)
void loop()
{
  uint32_t now = millis() % 100000;             //  0 - 99999
  float value = now * 0.001;                    //  0 - 99.999
  if (value - int(value) < 0.5) value *= 100;   //  for blink :
  TM.displayFloat(value);
}


//  0-10 second, milliseconds timer?
void loop2()
{
  uint32_t now = millis() % 10000;
  float value = now * 0.001;
  TM.displayFloat(value);
}


//  -- END OF FILE --

