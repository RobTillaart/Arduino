//
//    FILE: AD5263_setO.ino
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
  int x = 10 + analogRead(A0);
  AD01.setO1(LOW);
  AD01.setO2(HIGH);
  Serial.print(AD01.getO1());
  Serial.print('\t');
  Serial.println(AD01.getO2());
  delay(x);

  x = 10 + analogRead(A0);
  AD01.setO1(HIGH);
  AD01.setO2(LOW);
  Serial.print(AD01.getO1());
  Serial.print('\t');
  Serial.println(AD01.getO2());
  delay(x);
}


//  -- END OF FILE --
