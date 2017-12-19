//
//    FILE: DAC8554_hw_spi.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo DAC8554 library Arduino with hardware SPI
// VERSION: 0.1.0
//     URL: https://github.com/RobTillaart/Arduino/tree/master/libraries/DAC8554
// HISTORY:
//   0.1.0: 2017-12-19 initial version
//
// Released to the public domain
//

#include <SPI.h>
#include "DAC8554.h"

DAC8554 DAC;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println(DAC8554_LIB_VERSION);
  DAC.begin();
}

void loop()
{
  static uint8_t channel = 0;

  // minimal sawtooth
  for (uint16_t val = 0; val < 65500; val+= 30)
  {
    DAC.setValue(channel, val);
    int av = analogRead(A0);

    Serial.print(val);
    Serial.print("\t ==> \t");
    Serial.print(av);
  }

  // minimal sinus
  for (long i = 0; i < 360; i++ )
  {
    long s = 32768 + 32768 * sin( i * (PI / 180.0));
    DAC.setValue(channel, s);
    int av = analogRead(A0);
    Serial.print(i);
    Serial.print("\t ==> \t");
    Serial.print(av);
    delay(100);
  }

  channel++;
  if (channel >= 4) channel = 0;
}

// END OF FILE