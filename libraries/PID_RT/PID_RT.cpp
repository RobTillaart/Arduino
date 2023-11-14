//
//    FILE: PID_RT.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.7
// PURPOSE: PID library for Arduino
//     URL: https://github.com/RobTillaart/PID


#include "PID_RT.h"


PID_RT::PID_RT()
{
  reset();
}


PID_RT::PID_RT(float sp, float Kp, float Ki, float Kd)
{
  reset();
  setPoint(sp);
  setK(Kp, Ki, Kd);
}


void PID_RT::reset()
{
  _lastTime  = 0;
  _interval  = 250;
  _errorSum  = 0.0;
  _setPoint  = 0.0;
  _input     = 0.0;
  _lastInput = 0.0;
  _error     = 0.0;
  _output    = 0.0;
  _rangeMin  = 0.0;
  _rangeMax  = 100.0;
  _Kp        = 0.0;
  _Ki        = 0.0;
  _Kd        = 0.0;
  __Kp       = 0.0;
  __Ki       = 0.0;
  __Kd       = 0.0;
 _reverse    = false;
 _running    = false;
 _POI        = true;   //  Proportional On Input - Error
}


bool PID_RT::setK(float Kp, float Ki, float Kd)
{
  //  prevent short-cut evaluation.
  bool b = setKp(Kp);
  b = b && setKi(Ki);
  b = b && setKd(Kd);
  return  b;
}


bool PID_RT::setKp(float Kp)
{
  if (Kp < 0) return false;
  _Kp = Kp;
  __Kp = Kp;
  if (_reverse) __Kp = - __Kp;
  return true;
};


bool PID_RT::setKi(float Ki)
{
  if (Ki < 0) return false;
  _Ki = Ki;
  __Ki = _Ki * _interval * 0.001;   //  milliseconds.
  if (_reverse) __Ki = - __Ki;
  return true;
};


bool PID_RT::setKd(float Kd)
{
  if (Kd < 0) return false;
  _Kd = Kd;
  __Kd = Kd / (_interval * 0.001);
  if (_reverse) __Kd = - __Kd;
  return true;
};


bool PID_RT::compute(float input)
{
  if (_running == false)
  {
    return false;
  }
  if (millis() - _lastTime < _interval)
  {
    return false;
  }
  _lastTime += _interval;

  _input = input;
  _error = _setPoint - _input;
  float dI = _lastInput - _input;

  //  P - proportional on input or proportional on error
  if (_POI == false)
  {
    _output  = __Kp * _error;
  }
  else
  {
    _output = 0;
    _errorSum += __Kp * dI;
  }
  
  //  I
  _errorSum += __Ki * _error;
  if (_errorSum > _rangeMax) _errorSum = _rangeMax;
  else if (_errorSum < _rangeMin) _errorSum = _rangeMin;

  //  D
  _output += _errorSum + __Kd * dI;

  //  limit output to range
  if (_output > _rangeMax) _output = _rangeMax;
  else if (_output < _rangeMin) _output = _rangeMin;

  _lastInput = _input;
  return true;
}


bool PID_RT::setInterval(uint32_t interval)
{
  if (interval != _interval)
  {
    _interval = interval;
    //  recalculate __Ki and __Kd.
    setKi(_Ki);
    setKd(_Kd);
    return true;
  }
  return false;
}


//  -- END OF FILE -- 

