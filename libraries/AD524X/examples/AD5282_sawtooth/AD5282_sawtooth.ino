//
//    FILE: AD5282_sawtooth.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: AD524X demo program
//     URL: https://github.com/RobTillaart/AD524X
//
//  to be viewed with the IDE plotter


#include "AD524X.h"

AD5282 AD01(0x2C);  //  AD0 & AD1 == GND


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD524X_LIB_VERSION: ");
  Serial.println(AD524X_LIB_VERSION);

  Wire.begin();
  Wire.setClock(400000);

  bool b = AD01.begin();
  Serial.println(b ? "true" : "false");
  Serial.println(AD01.isConnected());
}


void loop()
{
  for (int val = 0; val < 256; val++)
  {
    //  two "inverted" sawtooths
    AD01.write(0, 255 - val);
    AD01.write(1, val);
    Serial.print(255 - val);
    Serial.print("\t");
    Serial.println(val);
    delay(20);
  }
}


//  -- END OF FILE --
