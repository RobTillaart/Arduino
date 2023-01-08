//
//    FILE: datetime_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo seconds2clock
//    DATE: 2020-07-01
//     URL: https://github.com/RobTillaart/datetimeHelpers


#include "dateTimeHelpers.h"

uint32_t start, stop, duration1;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  uint32_t seconds = 87654321 + random(1000000000UL);
  char * p;

  delay(100);
  start = micros();
  p = seconds2duration(seconds, false);
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(p);

  delay(100);
  start = micros();
  p = seconds2duration(seconds, true);
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(p);
  Serial.println();


  delay(100);
  start = micros();
  p = seconds2clock24(seconds, false);
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(p);

  delay(100);
  start = micros();
  p = seconds2clock24(seconds, true);
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(p);
  Serial.println();


  delay(100);
  start = micros();
  p = seconds2clockAMPM(seconds, false);
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(p);

  delay(100);
  start = micros();
  p = seconds2clockAMPM(seconds, true);
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(p);
  Serial.println();

  delay(100);
  start = micros();
  p = millis2duration(seconds);
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(p);

  delay(100);
  start = micros();
  p = millis2clock(seconds);
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(p);
  Serial.println();

  Serial.println("\ndone...");

  delay(3000);
}


void loop()
{
}


// -- END OF FILE --
