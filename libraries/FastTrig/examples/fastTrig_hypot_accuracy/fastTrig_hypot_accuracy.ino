//    FILE: fastTrig_hypot_accuracy.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2022-12-05
// PURPOSE: performance and accuracy measurement  
//     URL: https://github.com/RobTillaart/FastTrig


#include "Arduino.h"
#include "FastTrig.h"


uint32_t start, stop;
volatile float x, y;
float maxperc = 0;


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  delay(10);


  x = 10000;
  for (y = 0; y <= 10000; y += 1)
  {
    float a = hypot(x, y);
    float b = hypotFast(x, y);
    float p = 100.0 * (a - b)/a;
    if (fabs(p) > maxperc) maxperc = fabs(p);
    Serial.print(y);
    Serial.print("\t");
    Serial.print(a, 4);
    Serial.print("\t");
    Serial.print(b, 4);
    Serial.print("\t");
    Serial.print(a - b, 4);
    Serial.print("\t");
    Serial.print(p, 3);
    Serial.print("%");
    Serial.print("\n");
  }

  Serial.println();
  Serial.print("MAX PERC:\t");
  Serial.println(maxperc, 6);
  Serial.println("\ndone");
}


void loop()
{
}

// -- END OF FILE --
