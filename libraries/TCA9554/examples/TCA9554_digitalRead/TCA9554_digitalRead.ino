//
//    FILE: TCA9554_digitalRead.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test TCA9554 library
//     URL: https://github.com/RobTillaart/TCA9554


#include "TCA9554.h"


TCA9554 TCA(0x27);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TCA9554_LIB_VERSION: ");
  Serial.println(TCA9554_LIB_VERSION);
  Serial.println();

  Wire.begin();
  TCA.begin();


  Serial.println("Set pinMode8 INPUT");
  TCA.pinMode8(0xFF);


  Serial.println("TEST read1(pin)");
  for (int pin = 0; pin < 8; pin++)
  {
    int val = TCA.read1(pin);
    Serial.print(val);
    Serial.print('\t');
  }
  Serial.println();
  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --

