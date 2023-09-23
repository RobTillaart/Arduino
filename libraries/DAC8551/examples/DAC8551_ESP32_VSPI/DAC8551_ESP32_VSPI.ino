//
//    FILE: DAC8551_ESP32_VSPI.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo DAC8551 library Arduino with hardware SPI
//     URL: https://github.com/RobTillaart/DAC8551


#include "DAC8551.h"
#include "Wire.h"

// HW SPI uses slave spin since 0.2.0
DAC8531 mydac(1);


void setup()
{
  Serial.begin(115200);
  mydac.selectVSPI();
  mydac.begin();
}


void loop()
{
  // minimal sawtooth
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

  // minimal sinus
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


// -- END OF FILE --
