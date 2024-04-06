//
//    FILE: analogKeypad.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo 4x4 analogue keypad
//
// https://www.tinytronics.nl/shop/nl/arduino/accessoires/robotdyn-keypad-4x4-matrix-analoog?search=matrix


#include "AnalogKeypad.h"

AnalogKeypad AKP(A0);
uint32_t start, stop;

volatile int button;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ANALOGKEYPAD_LIB_VERSION:\t");
  Serial.println(ANALOGKEYPAD_LIB_VERSION);

  Serial.println();

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    button = AKP.read();
  }
  stop = micros();
  Serial.print("READ: \t");
  Serial.print((stop - start) * 0.001, 2);
  Serial.println(" us");

  Serial.println("\ndone...");
}

void loop()
{
}

//  -- END OF FILE --
