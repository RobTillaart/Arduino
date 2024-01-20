//
//    FILE: DAC8531_hw_spi.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo DAC8551 library Arduino with hardware SPI
//     URL: https://github.com/RobTillaart/DAC8551


#include "DAC8551.h"


//  select, data, clock
DAC8531 mydac(8, 11, 13);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("DAC8551_LIB_VERSION: ");
  Serial.println(DAC8551_LIB_VERSION);

  SPI.begin();

  mydac.begin();
}


void loop()
{
  //   minimal sawtooth
  for (uint16_t val = 0; val < 65500; val += 30)
  {
    mydac.setValue(val);
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
    mydac.setValue(s);
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

