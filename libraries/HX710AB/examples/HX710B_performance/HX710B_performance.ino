//
//    FILE: HX710B_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic performance
//     URL: https://github.com/RobTillaart/HX710AB


#include "HX710AB.h"

uint8_t dataPin = 6;
uint8_t clockPin = 7;

HX710A HX(dataPin, clockPin);

uint32_t start, stop;
volatile int32_t value;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("HX710AB_LIB_VERSION: ");
  Serial.println(HX710AB_LIB_VERSION);
  Serial.println();

  HX.begin();
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    value = HX.read();
  }
  stop = micros();
  Serial.print("READ: \t");
  Serial.println((stop - start) * 0.001);

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
