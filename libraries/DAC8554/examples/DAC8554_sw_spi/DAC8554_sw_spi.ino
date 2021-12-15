//
//    FILE: DAC8554_sw_spi.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo DAC8554 library Arduino with software SPI
// VERSION: 0.2.0
//     URL: https://github.com/RobTillaart/Arduino/DAC8554
//


#include "DAC8554.h"


// SW SPI pins 4,5,6
DAC8554 mydac(4, 5, 6);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println(DAC8554_LIB_VERSION);
  mydac.begin();
}


void loop()
{
  uint8_t channel = 0;

  // minimal sawtooth
  for (uint16_t val = 0; val < 65500; val+= 30)
  {
    mydac.setValue(channel, val);
    int av = analogRead(A0);

    Serial.print(val);
    Serial.print("\t ==> \t");
    Serial.print(av);
  }

  // minimal sinus
  for (long i = 0; i < 360; i++ )
  {
    long s = 32768 + 32768 * sin( i * (PI / 180.0));
    mydac.setValue(channel, s);
    int av = analogRead(A0);
    Serial.print(i);
    Serial.print("\t ==> \t");
    Serial.print(av);
    delay(100);
  }
}


// -- END OF FILE --

