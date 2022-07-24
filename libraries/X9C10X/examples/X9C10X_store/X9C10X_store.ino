//
//    FILE: X9C10X_store.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo store

//    NOTE: AVR Arduino UNO only
//          be aware the internal EEPROM can wear out !

// WARNING: the restore mechanism demonstrated here will only work if the device
//          has not moved since the last call to store() as in this example.
//          It is the responsibility of the user to verify if that is the case.
//


#include "Arduino.h"
#include "X9C10X.h"
#include "EEPROM.h"


//  PINOUT  X9C10X TOP VIEW  (see datasheet)
//
//       +--------+
//  INC  | o    o |  VCC
//  U/D  | o    o |  CS
//  RH   | o    o |  RL
//  GND  | o    o |  Rwiper
//       +--------+
//
//  INC     pulses
//  U/D     UP = 1   DOWN = 0
//  VCC     +5V
//  GND     ground
//  RH      resistor high end
//  RL      resistor low end
//  Rwiper  resistor wiper
//  CS      chip select
//


X9C10X pot(12345);  //  100KΩ  (ALT-234)


const uint8_t POT_ADDR = 0x10;   //   for EEPROM


void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.println();
  Serial.print("X9C10X_LIB_VERSION: ");
  Serial.println(X9C10X_LIB_VERSION);
  Serial.println();

  pot.begin(8, 9, 10);  //  pulse, direction, select

  uint8_t pos = 0;
  EEPROM.get(POT_ADDR, pos);
  //  if EEPROM has no valid value or not been used (255).
  if (pos > 99)
  {
    pot.setPosition(0, true);   //  adjust to your needs.
  }
  else
  {
    pot.restoreInternalPosition(pos);
  }

  Serial.print("RESTORE:\t");
  Serial.println(pot.getPosition());
}


void loop()
{
  if (Serial.available() > 0)
  {
    int c = Serial.read();
    switch (c)
    {
      case '+' :
        pot.incr();
        Serial.print("POS:\t");
        Serial.println(pot.getPosition());
        break;

      case '-' :
        pot.decr();
        Serial.print("POS:\t");
        Serial.println(pot.getPosition());
        break;

      //  QUIT
      case 'q' :
        uint8_t p = pot.store();
        EEPROM.update(POT_ADDR, p);
        Serial.print("\nSTORE:\t");
        Serial.println(pot.getPosition());
        Serial.println("\nreset to start again...");
        while (1);  //  block forever after quit.
        break;
    }
  }
}


// -- END OF FILE --

