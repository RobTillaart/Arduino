//
//    FILE: AD5263_write.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: AD5263 demo program
//     URL: https://github.com/RobTillaart/AD5263


#include "AD5263.h"

//  AD0 == GND
//  AD1 == GND
//  DIS == +5V
AD5263 AD01(0x2C);


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
    AD01.write(1, val);
    if (val == 200)
    {
      AD01.write(1, val, HIGH, LOW);
    }
    if (val == 0)
    {
      AD01.write(1, val, LOW, LOW);
    }
    Serial.println(val);
    delay(1000);
  }
}


//  -- END OF FILE --
