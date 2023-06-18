//
//    FILE: TLC5947_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/TLC5947


#include "TLC5947.h"


TLC5947 tlc(13, 12, 11, 10);

uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TLC5947_LIB_VERSION: \t");
  Serial.println(TLC5947_LIB_VERSION);

  if (tlc.begin() == false)
  {
    Serial.println("error");
    while (1);
  }

  testSetPWM();
  testWrite();

  Serial.println("\nDone...");
}


void loop()
{
}


void testSetPWM()
{
  delay(100);
  start = micros();
  for (int ch = 0; ch < 24; ch++)
  {
    tlc.setPWM(ch, 42);
  }
  stop = micros();
  Serial.print("SETPWM\t");
  Serial.println(stop - start);
}


void testWrite()
{
  delay(100);
  start = micros();
  tlc.write();
  stop = micros();
  Serial.print("WRITE\t");
  Serial.println(stop - start);
}


//  -- END OF FILE --
