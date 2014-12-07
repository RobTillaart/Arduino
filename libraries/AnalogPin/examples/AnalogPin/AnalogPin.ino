//
//    FILE: AnalogPin.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.02
// PURPOSE: example sketch
//     URL:
//
// Released to the public domain
//

#include "AnalogPin.h"

AnalogPin INA(A0);
AnalogPin INB(A1);

void setup()
{
  Serial.begin(115200);
  Serial.print("example AnalogPin: "); 
  Serial.println(ANALOGPIN_LIB_VERSION);
}


void loop()
{
  Serial.print(INA.read());
  Serial.print('\t');

  Serial.print(INA.read(10));
  Serial.print('\t');

  Serial.print(INA.readSmoothed(16));
  Serial.print('\t');

  Serial.print(INA.readPrevious());

  Serial.println();
  delay(100);
}

