//
//    FILE: AD524X_followA0.ino
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
  Serial.print("\nStart AD524X_followA0 : ");
  Serial.println(AD524X_VERSION);
  Serial.println("Follow Analog A0");

  Wire.begin();
  TWBR = 72; // 100 KHz
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