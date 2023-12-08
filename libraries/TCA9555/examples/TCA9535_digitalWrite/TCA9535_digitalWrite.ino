//
//    FILE: TCA9535_digitalWrite.ino
//  AUTHOR: Rob Tillaart
// PUPROSE: test TCA9555 library - TCA9535 derived class
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

  Wire.setClock(50);

  Serial.println("TEST digitalWrite(0)");
  for (int i = 0; i < 16; i++)
  {
    TCA.digitalWrite(0, i % 2);  //  alternating HIGH/LOW
    Serial.print(i % 2);
    Serial.print('\t');
    delay(250);
  }
  Serial.println();
  Serial.println();

  Serial.println("TEST digitalWrite(pin)");
  for (int pin = 0; pin < 16; pin++)
  {
    TCA.digitalWrite(pin, 1 - pin % 2);  //  alternating HIGH/LOW
    Serial.print(1 - pin % 2);
    Serial.print('\t');
  }
  Serial.println();
  Serial.println();

  Serial.println("TEST read back");

  for (int pin = 0; pin < 16; pin++)
  {
    int val = TCA.digitalRead(pin);
    Serial.print(val);
    Serial.print('\t');
  }
  Serial.println();
  Serial.println();
}


void loop()
{
}


//  -- END OF FILE --
