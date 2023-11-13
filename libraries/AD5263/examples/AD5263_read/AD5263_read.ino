//
//    FILE: AD5263_read.ino
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
  for (int val = 0; val < 255; val++)
  {
    Serial.print(val);
    AD01.write(1, val);
    delay(100);

    int x = AD01.read(1);
    Serial.print('\t');
    Serial.println(x);
    delay(100);
  }
  delay(1000);
}


//  -- END OF FILE --
