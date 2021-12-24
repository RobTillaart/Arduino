//
//    FILE: pattern_recorder.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: records and writes a pattern to serial
//    DATE: 2020-07-25


#include "Arduino.h"


uint8_t  pin = 4;
uint16_t minDuration = 50;
uint16_t units = 10;
uint32_t counter = 0;
uint32_t sum = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
}


void loop()
{
  uint32_t duration = recordPulse(pin, units, minDuration);
  sum += duration;
  counter++;
  Serial.print(duration);
  Serial.print("\t");
  Serial.println(sum/counter);
}


uint32_t recordPulse(uint8_t pin, uint16_t unit, uint16_t minperiod)
{
  static uint8_t state;
  static uint32_t start;
  static bool first = true;
  if (first)
  {
    first = false;
    pinMode(pin, INPUT_PULLUP);
    state = digitalRead(pin);
    start = millis();
  }
  uint8_t newState = state;
  while ((millis() - start) < minperiod - unit);

  uint32_t now = millis();
  while (newState == state)
  {
    while (millis() - now < unit);
    now = millis();
    newState = digitalRead(pin);
  }
  state = newState;
  uint32_t duration = (now - start + unit - 1) / unit;
  start = now;
  return duration;
}


// -- END OF FILE --

