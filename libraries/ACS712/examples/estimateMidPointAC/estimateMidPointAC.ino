//    FILE: estimateMidPointAC.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: experimental 
//     URL: https://github.com/RobTillaart/ACS712/issues/37
//
//  Estimates the midpoint by taking many (short-blocking) samples
//  instead of many samples in a long blocking period.
//  The function adjusts the confidence (or quality) of the midpoint 
//  depending on the value read.
//  This code is experimental and meant to investigate a non-blocking
//  way to find the midPoint for the ACS712 when measuring AC currents.
//
//  It will not be included in the library
//
//  Use with care.


#include "Arduino.h"


uint32_t start, stop;
int _pin = A0;
uint32_t count = 0;
volatile uint16_t mp;
float conf = 0;


uint16_t estimateMidPointAC(float &confidence, bool reset = false)
{
  static bool _firstCall = true;
  static float _minimum, _maximum, _confidence;

  int value = analogRead(_pin);
  if (_firstCall || reset)
  {
    _firstCall = false;
    _minimum = _maximum = value;
    _confidence = 0;
    confidence = _confidence;
    return _minimum;
  }
  if (value > _maximum)
  {
    _maximum = value;
    _confidence /= 2;
  }
  else if (value < _minimum)
  {
    _minimum = value;
    _confidence /= 2;
  }
  else if (_confidence < 100)
  {
    _confidence += 1;
  }
  confidence = _confidence;
  return (_minimum + _maximum) / 2;
}


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
}


void loop()
{
  count++;
  start = micros();
  mp = estimateMidPointAC(conf, true);
  stop = micros();
  Serial.print(millis());
  Serial.print("\t");
  Serial.print(count);
  Serial.print("\t");
  Serial.print(conf);
  Serial.print("\t");
  Serial.print(mp);
  Serial.print("\t");
  Serial.print(stop - start);
  Serial.println();
  delay(random(100));
}


//  -- END OF FILE --
