//
//    FILE: shiftInSlow_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test sketch
//     URL: https://github.com/RobTillaart/ShiftInSlow


#include "ShiftInSlow.h"


ShiftInSlow SIS(12, 13, LSBFIRST);

volatile int x = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__); 
  Serial.println(SHIFTINSLOW_LIB_VERSION);

  for (uint16_t d = 0; d <= 1000; d += 10)
  {
    SIS.setDelay(d);
    uint32_t start = micros();
    x = SIS.read();
    uint32_t stop = micros();
    float duration = stop - start;
    Serial.print(stop - start);
    Serial.print("\t");
    Serial.print(d);
    Serial.print("\t");
    Serial.print(duration / 8, 1);
    Serial.print("\n");
  }

  Serial.println("done...");
}


void loop()
{
}


// -- END OF FILE --
