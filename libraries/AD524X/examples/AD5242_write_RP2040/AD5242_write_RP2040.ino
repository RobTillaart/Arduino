//
//    FILE: AD5242_write_RP2040.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: AD524X demo program
//     URL: https://github.com/RobTillaart/AD524X


#include "AD524X.h"

AD5242 AD01(0x2C);  //  AD0 & AD1 == GND


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD524X_LIB_VERSION: ");
  Serial.println(AD524X_LIB_VERSION);

  Wire.setSDA(12);  //  adjust if needed
  Wire.setSCL(13);  //  adjust if needed
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
    delay(20);
  }
}


//  -- END OF FILE --
