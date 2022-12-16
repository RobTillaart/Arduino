//
//    FILE: PIR_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo pir sensor class
//     URL: https://github.com/RobTillaart/PIR


#include "PIR.h"

PIR  P;

uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("PIR_LIB_VERSION: ");
  Serial.println(PIR_LIB_VERSION);

  //  fully loaded
  P.add(3);
  P.add(4);
  P.add(5);
  P.add(6);
  P.add(7);
  P.add(8);
  P.add(9);
  P.add(10);

  test_read();
  test_lastValue();
  test_changed();
}


void loop()
{
}


void test_read()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  delay(10);

  start = micros();
  uint8_t x = P.read();
  stop = micros();
  Serial.print("TIME:\t");
  Serial.println(stop - start);
  Serial.print("VAL:\t");
  Serial.println(x, HEX);
}


void test_lastValue()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  delay(10);

  start = micros();
  uint8_t x = P.lastValue();
  stop = micros();
  Serial.print("TIME:\t");
  Serial.println(stop - start);
  Serial.print("VAL:\t");
  Serial.println(x, HEX);
}


void test_changed()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  delay(10);

  start = micros();
  uint8_t x = P.changed();
  stop = micros();
  Serial.print("TIME:\t");
  Serial.println(stop - start);
  Serial.print("VAL:\t");
  Serial.println(x, HEX);
}


//  -- END OF FILE --
