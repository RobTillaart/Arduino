//
//    FILE: AD524X_setO.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
// PURPOSE: AD524X demo program
//    DATE: 2013-10-12
//     URL: https://github.com/RobTillaart/AD524X
//

#include "AD524X.h"

AD524X AD01(0x2C);  // AD0 & AD1 == GND

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println(AD524X_VERSION);

  Wire.begin();
  Wire.setClock(400000);
}

void loop()
{
  int x = 10+analogRead(A0);
  AD01.setO1(LOW);
  AD01.setO2(HIGH);
  Serial.print(AD01.getO1());
  Serial.print('\t');
  Serial.println(AD01.getO2());
  delay(x);

  x = 10+analogRead(A0);
  AD01.setO1(HIGH);
  AD01.setO2(LOW);
  Serial.print(AD01.getO1());
  Serial.print('\t');
  Serial.println(AD01.getO2());
  delay(x);
}

// -- END OF FILE --
