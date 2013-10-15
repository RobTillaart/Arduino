//
//    FILE: AD524X_sawtooth.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
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
  Serial.print("\nStart AD524X_sawtooth : ");
  Serial.println(AD524X_VERSION);

  Wire.begin();
  TWBR=72;  // 100KHz
}

void loop() 
{
  for (int i=0; i<255; i++)
  {
    AD01.write(1, i);
    Serial.println(i);
    delay(20);
  }
}

