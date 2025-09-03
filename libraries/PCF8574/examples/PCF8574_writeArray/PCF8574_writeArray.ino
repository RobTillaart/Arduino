//
//    FILE: PCF8574_writeArray.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo writeArray function
//     URL: https://github.com/RobTillaart/PCF8574


#include "PCF8574.h"

PCF8574 PCF_01(0x38);

uint8_t arr[10] = {
  0b00000000,   //  no output
  0b00000001,   //  pin 0
  0b00000000,   //  no output
  0b00000011,   //  pin 0 and 1
  0b00000011,   //  pin 0 and 1
  0b00000010,   //  pin 1
  0b00000100,   //  pin 2
  0b00001000,   //  pin 4
  0b11111111,   //  all pins
  0b00000000,   //  no pin
};


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("PCF8574_LIB_VERSION: ");
  Serial.println(PCF8574_LIB_VERSION);
  Serial.println();

  Wire.begin();

  PCF_01.begin();
}


void loop()
{
  delay(2000);

  Wire.setClock(300000);
  PCF_01.writeArray(arr, 10);
  Wire.setClock(100000);
}


//  -- END OF FILE --
