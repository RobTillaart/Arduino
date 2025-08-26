//
//    FILE: X9C10X_sweeper.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/X9C10X


#include "Arduino.h"
#include "X9C10X.h"


//  PINOUT  X9C10X TOP VIEW  (see datasheet)
//
//       +--------+
//  INC  | o    o |  VCC
//  U/D  | o    o |  CS
//  RH   | o    o |  RL
//  GND  | o    o |  Rwiper
//       +--------+
//
//  INC   pulses
//  U/D   UP = 1 DOWN = 0
//  VCC   +5V


X9C10X pot(10000);  //  10 KΩ  (ALT-234)

uint8_t direction = LOW;
uint8_t step = 1;

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("X9C10X_LIB_VERSION: ");
  Serial.println(X9C10X_LIB_VERSION);
  Serial.println();

  pot.begin(8, 9, 10);  //  pulse, direction, select
  pot.setPosition(0);
}


void loop()
{
  for (uint8_t i = 0; i < 100; i++)
  {
    pot.incr();
    delay(100);
  }
  Serial.println(millis());

  for (uint8_t i = 0; i < 100; i++)
  {
    pot.decr();
    delay(100);
  }
  Serial.println(millis());
}


//  -- END OF FILE --
