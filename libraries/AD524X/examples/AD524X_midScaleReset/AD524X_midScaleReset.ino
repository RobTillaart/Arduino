//
//    FILE: AD524X_midScaleReset.ino
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
  Serial.print("\nStart AD524X_midScaleReset : ");
  Serial.println(AD524X_VERSION);

  Wire.begin();
  TWBR = 12;  // 400 KHz
}

void loop()
{
  Serial.println(255);
  AD01.write(1, 255);
  delay(1000);

  Serial.println("reset");
  AD01.midScaleReset(1);
  delay(1000);

  Serial.println(0);
  AD01.write(1, 0);
  delay(1000);

  Serial.println("reset");
  AD01.midScaleReset(1);
  delay(1000);
}