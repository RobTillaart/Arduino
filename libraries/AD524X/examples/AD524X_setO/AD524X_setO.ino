//
//    FILE: AD524X_setO.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.01
// PURPOSE: AD524X demo program
//    DATE: 2013-10-12
//     URL:
//
// Released to the public domain
//

#include "AD524X.h"
#include "Wire.h"

AD524X AD01(0x2C);  // AD0 & AD1 == GND

void setup()
{
  Serial.begin(115200);
  Serial.print("\nStart AD524X_setO : ");
  Serial.println(AD524X_VERSION);

  Wire.begin();
  TWBR = 72;  // 100 KHz
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