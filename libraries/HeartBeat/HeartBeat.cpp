//
//    FILE: HeartBeat.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.3
// PURPOSE: Arduino library for HeartBeat with frequency and dutyCycle
//    DATE: 2019-06-12
//     URL: https://github.com/RobTillaart/HeartBeat
//
//  HISTORY:
//  0.1.0   2019-06-12  initial version
//  0.1.1   2020-12-24  arduino-CI 
//  0.1.2   2021-01-15  renamed all to HeartBeat
//                      added dutyCycle
//  0.1.3   2021-05-27  fix arduino-lint


#include "HeartBeat.h"


HeartBeat::HeartBeat()
{
  _dutyCycle = 50;
}


void HeartBeat::begin(const uint8_t pin, float frequency)
{
  _pin = pin;
  pinMode(_pin, OUTPUT);

  setFrequency(frequency);
  enable();
}


void HeartBeat::setFrequency(float frequency)
{
  _frequency = abs(frequency);
  _setFreqDuty();
}


void HeartBeat::setDutyCycle(float dutyCycle)
{
  
  _dutyCycle = constrain(dutyCycle, 0, 100);  // percentage
  _setFreqDuty();
}


void HeartBeat::beat()
{
  static uint8_t state = LOW;
  if (_running == false) 
  {
    state = LOW;
  }
  else
  {
    uint32_t now = micros();
    if ((state == LOW)  && (now - _lastHeartBeat) < _dutyCycleLow)  return;
    if ((state == HIGH) && (now - _lastHeartBeat) < _dutyCycleHigh) return;
    _lastHeartBeat = now;
    state = !state;
  }
  digitalWrite(_pin, state);
}


/////////////////////////////////


void HeartBeat::_setFreqDuty()
{
  _lastHeartBeat = 0;
  float time = 10000.0/_frequency;
  _dutyCycleHigh = round(_dutyCycle * time);
  _dutyCycleLow  = round((100 - _dutyCycle) * time);
}


// -- END OF FILE --
