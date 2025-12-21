//
//    FILE: LC7822_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour

//     URL: https://github.com/RobTillaart/LC7822


#include "LC7822.h"

//  LC7822(dataPin, clockPin, cePin, sPin, resetPin);
LC7822 LC(4,5,6,7);  //  no reset Pin.

uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LC7822_LIB_VERSION: ");
  Serial.println(LC7822_LIB_VERSION);
  Serial.println();

  if (LC.begin() == false)
  {
    Serial.println("error begin()");
  }
  //  tune timing.
  for (int del = 0; del <= 10; del++)
  {
    LC.setMicroDelay(del);
    test(del);
  }

  Serial.println("Done...");
}


void loop()
{
}


void test(int del)
{
  Serial.println();
  Serial.print("delay:\t");
  Serial.println(del);
  delay(100);
  start = micros();
  for (int sw = 0; sw < 8; sw ++)
  {
    LC.setSwitch(sw, 1);
  }
  stop = micros();
  Serial.print("8x ON:\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  for (int sw = 0; sw < 8; sw ++)
  {
    LC.setSwitch(sw, 0);
  }
  stop = micros();
  Serial.print("8x OFF:\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  LC.setAll(0xFF);
  stop = micros();
  Serial.print("setAll:\t");
  Serial.println(stop - start);
  delay(100);
}

//  -- END OF FILE --
