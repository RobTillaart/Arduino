//
//    FILE: HeartBeat.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
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
//  0.2.0   2021-11-02  update Build-CI, add badges
//                      add getFrequency(), getDutyCycle();
//                      add getState().
//                      removed set()


#include "HeartBeat.h"


HeartBeat::HeartBeat()
{
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
  _frequency = frequency;
  if (_frequency < 0) _frequency = -frequency;
  if (_frequency < 0.001) _frequency = 0.001;
  _setFreqDuty();
}


void HeartBeat::setDutyCycle(float dutyCycle)
{
  _dutyCycle = constrain(dutyCycle, 0, 100);  // percentage
  _setFreqDuty();
}


void HeartBeat::beat()
{
  if (_running == false) 
  {
    _state = LOW;
  }
  else
  {
    uint32_t now = micros();
    if ((_state == LOW)  && (now - _lastHeartBeat) < _dutyCycleLow)  return;
    if ((_state == HIGH) && (now - _lastHeartBeat) < _dutyCycleHigh) return;
    _lastHeartBeat = now;
    _state = !_state;
  }
  digitalWrite(_pin, _state);
}


/////////////////////////////////
//
//  PRIVATE
//
void HeartBeat::_setFreqDuty()
{
  float time = 10000.0/_frequency;
  _dutyCycleHigh = round(_dutyCycle * time);
  _dutyCycleLow  = round((100 - _dutyCycle) * time);
}


// -- END OF FILE --

