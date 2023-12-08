//
//    FILE: TCA9535_digitalRead.ino
//  AUTHOR: Rob Tillaart
// PUPROSE: test TCA9555 library
//     URL: https://github.com/RobTillaart/TCA9555


#include "Wire.h"
#include "TCA9555.h"


TCA9535 TCA(0x27);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TCA9555_LIB_VERSION: ");
  Serial.println(TCA9555_LIB_VERSION);

  Wire.begin();
  TCA.begin();

  Serial.println("TEST digitalRead(pin)");
  for (int pin = 0; pin < 16; pin++)
  {
    int val = TCA.digitalRead(pin);
    Serial.print(val);
    Serial.print('\t');
  }
  Serial.println(); 
}


void loop()
{
}


//  -- END OF FILE --

