//
//    FILE: AD5246_followA0.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: AD5246 demo program
//     URL: https://github.com/RobTillaart/AD5246


#include "AD5246.h"


AD5246 AD;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD5246_LIB_VERSION: ");
  Serial.println(AD5246_LIB_VERSION);

  Wire.begin();
  Wire.setClock(400000);

  bool b = AD.begin();
  Serial.println(b ? "true" : "false");
  Serial.println(AD.isConnected());
}


void loop()
{
  int x = analogRead(A0);
  Serial.print(x);
  Serial.print('\t');
  Serial.print(x / 8);   //  max 127 == 1023 / 8

  int rv = AD.write(x / 8);
  Serial.print('\t');
  Serial.println(rv);

  delay(100);
}


//  -- END OF FILE --

