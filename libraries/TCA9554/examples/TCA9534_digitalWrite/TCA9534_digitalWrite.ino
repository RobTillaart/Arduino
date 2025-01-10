//
//    FILE: TCA9534_digitalWrite.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test TCA9554 library - TCA9534 derived class
//     URL: https://github.com/RobTillaart/TCA9554


#include "TCA9554.h"


TCA9534 TCA(0x27);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TCA9554_LIB_VERSION: ");
  Serial.println(TCA9554_LIB_VERSION);
  Serial.println();

  Wire.begin();
  TCA.begin();

  Wire.setClock(50000);


  Serial.println("Set pinMode1 OUTPUT");
  for (int i = 0; i < 8; i++)
  {
    TCA.pinMode1(i, OUTPUT);
    TCA.write1(i, LOW);
  }


  Serial.println("TEST write1()");
  for (int i = 0; i < 8; i++)
  {
    TCA.write1(i, i % 2);  //  alternating HIGH/LOW
    Serial.print(i % 2);
    Serial.print('\t');
    delay(250);
  }
  Serial.println();
  Serial.println();


  Serial.println("TEST read back, read1()");
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
