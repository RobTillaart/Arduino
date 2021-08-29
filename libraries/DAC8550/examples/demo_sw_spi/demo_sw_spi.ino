//
//    FILE: demo_sw_spi.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo DAC855X library Arduino with software SPI
// VERSION: 0.1.1
//     URL: https://github.com/RobTillaart/DAC8550


#include "DAC8550.h"


// SW SPI pins 4,5,6
DAC8550 myDAC(4, 5, 6);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  myDAC.begin();
}

void loop()
{
  // minimal sawtooth
  for (uint16_t val = 0; val < 65500; val+= 30)
  {
    myDAC.setValue(val);
    int av = analogRead(A0);

    Serial.print(val);
    Serial.print("\t ==> \t");
    Serial.print(av);
  }

  // minimal sinus
  for (long i = 0; i < 360; i++ )
  {
    uint16_t s = 32767 + 32767 * sin( i * (PI / 180.0));
    myDAC.setValue(s);
    int av = analogRead(A0);
    Serial.print(i);
    Serial.print("\t ==> \t");
    Serial.print(av);
    delay(100);
  }
}

// END OF FILE