//
//    FILE: LC7822_multi_pumps.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo masks
//     URL: https://github.com/RobTillaart/LC7822
//
//  Has an array of prepared values and the number send
//  over serial determines the nr of switches that are on.
//  To be used to switch on more or less pumps (or lights etc)


#include "LC7822.h"

//  LC7822(dataPin, clockPin, cePin, sPin, resetPin);
LC7822 LC(4, 5, 6, 7); //  no reset Pin.

//  prepared masks to switch on/off 0..8 pumps
uint8_t pumps[9] = { 0x00, 0x01, 0x11, 0x15, 0x55, 0x57, 0x77, 0x7F, 0xFF};


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
  LC.setMicroDelay(10);
}


void loop()
{
  if (Serial.available())
  {
    char c = Serial.read();
    if (('0' <= c) && (c <= '8'))
    {
      uint8_t index = c - '0';
      LC.setAll(pumps[index]);
    }
  }
}


//  -- END OF FILE --
