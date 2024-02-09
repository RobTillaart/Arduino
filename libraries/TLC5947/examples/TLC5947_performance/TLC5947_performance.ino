//
//    FILE: TLC5947_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test performance main functions.
//     URL: https://github.com/RobTillaart/TLC5947


#include "TLC5947.h"

const int CLOCK = 13;
const int DATA  = 12;
const int LATCH = 11;
const int BLANK = 10;

TLC5947 tlc(CLOCK, DATA, LATCH, BLANK);

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
  testSetRGB();
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
  for (int channel = 0; channel < 24; channel++)
  {
    tlc.setPWM(channel, 42);
  }
  stop = micros();
  Serial.print("SETPWM\t");
  Serial.println(stop - start);
}


void testSetRGB()
{
  delay(100);
  start = micros();
  for (int led = 0; led < 8; led++)
  {
    tlc.setRGB(led, 42, 185, 17);
  }
  stop = micros();
  Serial.print("SETRGB\t");
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
