//
//    FILE: TCA9555_digitalRead.ino
//  AUTHOR: Rob Tillaart
///    DATE: 2021-06-09
// PUPROSE: test TCA9555 library


#include "TCA9555.h"
#include "Wire.h"


TCA9555 TCA(0x27);

void setup()
{
  Serial.begin(115200);
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


// -- END OF FILE --
