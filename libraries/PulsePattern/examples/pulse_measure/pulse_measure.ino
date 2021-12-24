//
//    FILE: pulse_measure.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: measure pulselength
//    DATE: 2020-08-07
//
// TEST
//   generate with one Arduino a pulse of 1000 ms
//   measure it with this sketch to determine the correction percentage


#include "Arduino.h"

// measure pin = A5 on UNO
uint8_t  pin = 19;


// record pulses in units of 10 milliseconds
// an a minimum duration of 20 miiliseconds.
uint16_t minDuration = 20;
uint16_t units = 10;


// to calc the average
uint32_t count = 0;
uint32_t sum = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  // wait for pulse edge to start
  recordPulse(pin, units, minDuration);
}


void loop()
{
  uint32_t duration = recordPulse(pin, units, minDuration);
  sum += duration;
  count++;
  Serial.print(duration);
  Serial.print("\t");
  Serial.println(sum / count);
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
  // wait minimal amount of time
  while ((millis() - start) < minperiod - unit);

  uint32_t now = millis();
  while (newState == state)
  {
    // have fixed units
    while (millis() - now < unit);
    now = millis();
    newState = digitalRead(pin);
  }
  state = newState;
  uint32_t duration = ((now - start + unit - 1) / unit) * unit;
  start = now;
  return duration;
}


// -- END OF FILE --

