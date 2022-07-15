//
//    FILE: X9C_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo minimalistic base class for X9Cxxx devices.


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
//


X9C pot;  //  unknown Ω  (ALT-234)


void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.println();
  Serial.print("X9C10X_LIB_VERSION: ");
  Serial.println(X9C10X_LIB_VERSION);

  pot.begin(8, 9, 10);  //  pulse, direction, select

  //  force to the end of the wiper.
  for (uint8_t i = 0; i < 99; i++)
  {
    pot.incr();
    Serial.print('+');
  }
  Serial.println();

  //  go to the wanted position.  (99 - 24 = 75)
  for (uint8_t i = 0; i < 24; i++)
  {
    pot.decr();
    Serial.print('-');
  }
  Serial.println();

  //  store the current position in NV-RAM.
  pot.store();
}


void loop()
{
}


// -- END OF FILE --
