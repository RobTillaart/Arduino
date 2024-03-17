//
//    FILE: AD5263_readBackRegister.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: AD5263 demo program
//     URL: https://github.com/RobTillaart/AD5263


#include "AD5263.h"

AD5263 AD01(0x2C);  //  AD0 & AD1 == GND


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD5263_LIB_VERSION: ");
  Serial.println(AD5263_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(400000);

  bool b = AD01.begin();
  Serial.println(b ? "true" : "false");
  Serial.println(AD01.isConnected());
}


void loop()
{
  for (int rdac = 0; rdac < 4; rdac++)
  {
    for (int val = 0; val < 255; val++)
    {
      test(rdac, val);
    }
  }
  delay(1000);
}

void test(uint8_t rdac, uint8_t val)
{
  Serial.print(val);
  AD01.write(rdac, val);
  delay(100);

  int x = AD01.read(rdac);
  int y = AD01.readBackRegister();
  Serial.print('\t');
  Serial.print(x);
  Serial.print('\t');
  Serial.println(y);
  delay(100);
}


//  -- END OF FILE --
