//
//    FILE: AD524X_followA0.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: AD524X demo program
//     URL: https://github.com/RobTillaart/AD524X


#include "AD524X.h"

AD524X AD01(0x2C);  //  AD0 & AD1 == GND


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
  int x = analogRead(A0);
  Serial.print(x);
  Serial.print('\t');
  Serial.print(x/4);

  int rv = AD01.write(1, x/4);
  Serial.print('\t');
  Serial.print(rv);

  rv = AD01.write(0, x/4);
  Serial.print('\t');
  Serial.println(rv);

  delay(100);
}


//  -- END OF FILE --

