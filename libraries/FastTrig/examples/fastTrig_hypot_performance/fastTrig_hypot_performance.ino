//    FILE: fastTrig_hypot_performance.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2022-12-05
// PURPOSE: performance and accuracy measurement  
//     URL: https://github.com/RobTillaart/FastTrig


#include "Arduino.h"
#include "FastTrig.h"


uint32_t start, stop;
volatile float x, y;
float angle, length;


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  delay(10);

  x = random(100);
  y = x + random(100);

  Serial.println(x);
  Serial.println(y);
  delay(10);
  
  //////////////////////////////////////////
  Serial.println("\nPERFORMANCE");
  Serial.println("ALGORITHM\tVALUE\t\tTIME");
  delay(10);
  
  start = micros();
  for (int i = 0; i < 1000; i++)
    length = sqrt(x * x + y * y);
  stop = micros();
  Serial.print("SQRT:\t\t");
  Serial.print(length, 5);
  Serial.print("\t");
  Serial.println((stop - start) * 0.001, 3);
  delay(10);


  start = micros();
  for (int i = 0; i < 1000; i++)
    length = hypot(x, y);
  stop = micros();
  Serial.print("HYPOT:\t\t");
  Serial.print(length, 5);
  Serial.print("\t");
  Serial.println((stop - start) * 0.001, 3);
  delay(10);

  start = micros();
  for (int i = 0; i < 1000; i++)
    length = hypotFast(x, y);
  stop = micros();
  Serial.print("HYPOTFAST:\t");
  Serial.print(length, 5);
  Serial.print("\t");
  Serial.println((stop - start) * 0.001, 3);
  delay(10);

  Serial.println("\ndone");

}


void loop()
{
}

// -- END OF FILE --
