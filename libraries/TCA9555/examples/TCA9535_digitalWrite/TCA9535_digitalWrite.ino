//
//    FILE: TCA9535_digitalWrite.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test TCA9555 library - TCA9535 derived class
//     URL: https://github.com/RobTillaart/TCA9555


#include "TCA9555.h"


TCA9535 TCA(0x27);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TCA9555_LIB_VERSION: ");
  Serial.println(TCA9555_LIB_VERSION);
  Serial.println();

  Wire.begin();
  TCA.begin();

  Wire.setClock(50000);


  Serial.println("Set pinMode1 OUTPUT");
  for (int i = 0; i < 16; i++)
  {
    TCA.pinMode1(i, OUTPUT);
    TCA.write1(i, LOW);
  }


  Serial.println("TEST write1(0)");
  for (int i = 0; i < 16; i++)
  {
    TCA.write1(0, i % 2);  //  alternating HIGH/LOW
    Serial.print(i % 2);
    Serial.print('\t');
    delay(250);
  }
  Serial.println();
  Serial.println();


  Serial.println("TEST write1(pin)");
  for (int pin = 0; pin < 16; pin++)
  {
    TCA.write1(pin, 1 - pin % 2);  //  alternating HIGH/LOW
    Serial.print(1 - pin % 2);
    Serial.print('\t');
  }
  Serial.println();
  Serial.println();


  Serial.println("TEST read back, read1()");
  for (int pin = 0; pin < 16; pin++)
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
