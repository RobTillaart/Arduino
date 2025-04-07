//    FILE: LTC2991_test_conversion.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2025-03-27
// PURPOSE: test conversion code (development)
//     URL: https://github.com/RobTillaart/LTC2991
//
//  Compare table 16 datasheet page 21.


#include "Arduino.h"


void setup()
{
  //  while(!Serial);  //  uncomment if needed
  Serial.begin(115200);
  Serial.println(__FILE__);

              //  expected voltage
  P(0x3FFF);  //  > 5.0000
  P(0x2CCD);  //  +3.5000
  P(0x1FFF);  //  +2.5000
  P(0x028F);  //  +0.2000
  P(0x0001);  //  +0.000305
  P(0x0000);  //   0.0000
  P(0x7C29);  //  -0.3000
  P(0x7FFF);  //  -0.000305
  P(0x4000);  //  -5.0000
}


void P(int16_t val)
{
  int16_t v = val;
  v = v & 0x7FFF;  //  strip DATA_VALID bit
  Serial.print(v, HEX);
  Serial.print('\t');
  if ((v & 0x4000) == 0)
  {
    Serial.println(2.5 / 8192 * (float(v)), 6);
  }
  else
  {
    v = (v ^ 0x7FFF) + 1;
    Serial.println(2.5 / 8192 * (float(v)) * -1.0, 6);
  }
  Serial.println();

}


void loop()
{
}


//  -- END OF FILE --
