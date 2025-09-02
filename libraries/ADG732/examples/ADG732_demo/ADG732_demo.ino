//
//    FILE: ADG732_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: minimal sketch
//     URL: https://github.com/RobTillaart/ADG732


#include "ADG732.h"


ADG732 ADG(4, 5, 6, 7, 8, 9, 10, 11);

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ADG732_LIB_VERSION: ");
  Serial.println(ADG732_LIB_VERSION);
  Serial.println();
  delay(100);

  start = micros();
  for (int ch = 0; ch < 32; ch++)
  {
    ADG.setChannel(ch);
  }
  stop = micros();
  Serial.print("Time:\t");
  Serial.println((stop - start) / 32.0);
  delay(100);

  start = micros();
  ADG.setChannel(1);
  stop = micros();
  Serial.print("Time:\t");
  Serial.println(stop - start);
  delay(100);
}


void loop()
{
  for (int ch = 0; ch < 32; ch++)
  {
    ADG.setChannel(ch);

    Serial.print(ch);
    Serial.print("\t");
    Serial.println(ADG.getChannel());
    delay(1000);
  }
}


//  -- END OF FILE --
