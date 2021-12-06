//
//    FILE: map2colour_performance.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: map2colour demo
//    DATE: 2021-12-04
//     URL: https://github.com/RobTillaart/map2colour


#include "Arduino.h"
#include "map2colour.h"


map2colour mc;

// should be in increasing order; and 7 elements
float values[7] = { 0, 32, 64, 128, 256, 512, 1024 };
uint32_t colours[7] =
{
  M2C_RED, M2C_RED, M2C_YELLOW, M2C_LIME, M2C_YELLOW, M2C_RED, M2C_RED
};

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);


  Serial.println("begin()");
  delay(10);
  // use the default colour map.
  start = micros();
  mc.begin(values);
  stop = micros();
  Serial.println(stop - start);
  delay(10);


  // use the default colour map.
  start = micros();
  mc.begin(values, colours);
  stop = micros();
  Serial.println(stop - start);
  Serial.println();
  delay(1000);


  Serial.println("map2RGB()");
  delay(10);
  for (float i = 0; i < 1024; i += 10)
  {
    start = micros();
    uint32_t rgb = mc.map2RGB(i);
    stop = micros();
    Serial.print(stop - start);   //  120 - 172 us
    Serial.print("\t");
    Serial.print(i);
    Serial.print("\t");
    Serial.println(rgb, HEX);
    delay(10);
  }
  Serial.println();
  delay(1000);


  Serial.println("map2_565()");
  delay(10);
  for (float i = 0; i < 1024; i += 10)
  {
    uint32_t start = micros();
    uint32_t rgb = mc.map2_565(i);
    uint32_t stop = micros();
    Serial.print(stop - start);   //  120 - 172 us
    Serial.print("\t");
    Serial.print(i);
    Serial.print("\t");
    Serial.println(rgb, HEX);
    delay(10);
  }
  Serial.println();


  Serial.println("done...");
}


void loop()
{
}


// -- END OF FILE --
