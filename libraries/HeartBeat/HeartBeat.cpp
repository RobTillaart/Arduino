//
//    FILE: HeartBeat.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.4
// PURPOSE: Arduino library for HeartBeat with frequency and dutyCycle
//    DATE: 2019-06-12
//     URL: https://github.com/RobTillaart/HeartBeat


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
  _dutyCycle = dutyCycle;
  if (_dutyCycle < 0)   _dutyCycle = 0;
  if (_dutyCycle > 100) _dutyCycle = 100;
  _setFreqDuty();
}


float HeartBeat::getFrequency()
{
  return _frequency;
};


float HeartBeat::getDutyCycle()
{
  return _dutyCycle;
};


void HeartBeat::enable()
{
  _running = true;
};


void HeartBeat::disable()
{
  _running = false;
};


bool HeartBeat::isEnabled()
{
  return _running;
};


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


uint8_t HeartBeat::getState()
{
  return _state;
};


/////////////////////////////////
//
//  PROTECTED
//
void HeartBeat::_setFreqDuty()
{
  float time = 10000.0/_frequency;
  _dutyCycleHigh = round(_dutyCycle * time);
  _dutyCycleLow  = round((100 - _dutyCycle) * time);
}


/////////////////////////////////////////////////////////////////////////////
//
//  HEARTBEATDIAG
//
HeartBeatDiag::HeartBeatDiag():HeartBeat()
{
}


void HeartBeatDiag::beat()
{
  //  normal mode
  if (_codeMask == 0)
  {
    _codeStart = 0;
    HeartBeat::beat();
    return;
  }
  // _code mode
  if (_codeStart == 0)
  {
    //  force a LOW first.
    _codeStart = 1;
    _lastHeartBeat = micros();
    _state = LOW;
  }
  else
  {
    uint32_t period = (_dutyCycleLow + _dutyCycleHigh) / 2;
    uint32_t now = micros();
    if ((now - _lastHeartBeat) < period) return;
    _lastHeartBeat = now;
    if (_state == LOW)
    {
      while (_codeMask > _code)
      {
        _codeMask /= 10;
      }
      if (_codeMask == 0) return;
      _pulseLength = _code / _codeMask;
      _code -= ( _pulseLength * _codeMask );
      _state = HIGH;
    }
    else
    {
      _pulseLength--;
      if (_pulseLength == 0)
      {
        _state = LOW;
      }
    }
  }
  digitalWrite(_pin, _state);
}


bool HeartBeatDiag::code(uint32_t pattern)
{
  //  already running an errorCode?
  if (_code > 0) return false;
  // pattern too long
  if (pattern > 999999999) return false;

  _code = pattern;
  _codeMask = 100000000;
  return true;
}


void HeartBeatDiag::codeOff()
{
  _codeMask = 0;
}


bool HeartBeatDiag::codeCompleted()
{
  if (_codeMask > 0) return false;
  return true;
}


/////////////////////////////////////////////////////////////////////////////
//
//  HEARTBEATSL
//
//  string LS version is simpler and somewhat smaller footprint,
//

#define HEARTBEATSL_SHORT     1
#define HEARTBEATSL_LONG      3


HeartBeatSL::HeartBeatSL():HeartBeat()
{
}


void HeartBeatSL::beat()
{
  //  normal mode
  if (_codeMask == 0)
  {
    _codeStart = 0;
    HeartBeat::beat();
    return;
  }
  // _code mode
  if (_codeStart == 0)
  {
    //  force a LOW first.
    _codeStart = 1;
    _lastHeartBeat = micros();
    _state = LOW;
  }
  else
  {
    uint32_t period = (_dutyCycleLow + _dutyCycleHigh) / 2;
    uint32_t now = micros();
    if ((now - _lastHeartBeat) < period) return;
    _lastHeartBeat = now;
    if (_state == LOW)
    {
      _pulseLength = HEARTBEATSL_SHORT;
      if (_code & _codeMask)  //  1 ==> LONG
      {
        _pulseLength = HEARTBEATSL_LONG;
      }
      _codeMask >>= 1;
      _state = HIGH;
    }
    else
    {
      _pulseLength--;
      if (_pulseLength == 0)
      {
        _state = LOW;
      }
    }
  }
  digitalWrite(_pin, _state);
}


bool HeartBeatSL::code(const char * str)
{
  //  already running an errorCode?
  if (_codeMask > 0) return false;
  //  pattern too long
  uint8_t len = strlen(str);
  if (len > 7) return false;

  _code      = 0;
  _codeMask  = 1 << len;
  for (uint8_t i = 0; i < len; i++)
  {
    if (str[i] == 'L') _code |= 1;
    _code <<= 1;
  }
  return true;
}


void HeartBeatSL::codeOff()
{
  _codeMask = 0;
}


bool HeartBeatSL::codeCompleted()
{
  if (_codeMask > 0) return false;
  return true;
}


//  -- END OF FILE --

