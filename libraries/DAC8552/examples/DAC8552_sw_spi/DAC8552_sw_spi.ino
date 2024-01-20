//
//    FILE: DAC8552_sw_spi.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo DAC8552 library Arduino with software SPI
// VERSION: 0.2.0
//     URL: https://github.com/RobTillaart/DAC8552
//


#include "DAC8552.h"


//  SW SPI pins select, data, clock
DAC8552 mydac(4, 5, 6);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("DAC8552_LIB_VERSION: ");
  Serial.println(DAC8552_LIB_VERSION);

  SPI.begin();

  mydac.begin();
}


void loop()
{
  uint8_t channel = 0;

  //  minimal sawtooth
  for (uint16_t val = 0; val < 65500; val+= 30)
  {
    mydac.setValue(channel, val);
    int av = analogRead(A0);

    Serial.print(val);
    Serial.print("\t ==> \t");
    Serial.print(av);
    if (val % 300 == 0) Serial.println();
  }
  Serial.println();

  //  minimal sinus
  for (long i = 0; i < 360; i++ )
  {
    long s = 32768 + 32768 * sin( i * (PI / 180.0));
    mydac.setValue(channel, s);
    int av = analogRead(A0);
    Serial.print(i);
    Serial.print("\t ==> \t");
    Serial.print(av);
    delay(100);
    if (i % 30 == 0) Serial.println();
  }
  Serial.println();
}


//  -- END OF FILE --

