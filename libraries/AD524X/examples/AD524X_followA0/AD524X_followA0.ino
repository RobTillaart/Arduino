//
//    FILE: AD524X_followA0.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
// PURPOSE: AD524X demo program
//    DATE: 2013-10-12
//     URL:
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

// -- END OF FILE --
