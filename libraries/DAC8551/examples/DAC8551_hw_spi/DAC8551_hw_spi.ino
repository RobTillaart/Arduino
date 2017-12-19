//
//    FILE: DAC8551_hw_spi.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo DAC8551 library Arduino with hardware SPI
// VERSION: 0.1.0
// HISTORY:
//     URL:
//
// Released to the public domain
//

#include <SPI.h>
#include "DAC8551.h"

DAC8551 DAC;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println(DAC8551_LIB_VERSION);
  DAC.begin();
}

void loop()
{
  // minimal sawtooth
  for (uint16_t val = 0; val < 65500; val+= 30)
  {
    DAC.setValue(val);
    int av = analogRead(A0);

    Serial.print(val);
    Serial.print("\t ==> \t");
    Serial.print(av);
  }

  // minimal sinus
  for (long i = 0; i < 360; i++ )
  {
    long s = 32768 + 32768 * sin( i * (PI / 180.0));
    DAC.setValue(s);
    int av = analogRead(A0);
    Serial.print(i);
    Serial.print("\t ==> \t");
    Serial.print(av);
    delay(100);
  }
}

// END OF FILE