//
//    FILE: functionGenerator.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.3
// PURPOSE: wave form generating functions (use with care)
//     URL: https://github.com/RobTillaart/FunctionGenerator
//
//  HISTORY:
//  0.1.00  2015-01-01  initial version
//  0.1.01  2015-01-01  initial class version
//  0.1.02  2015-01-01  refactor and research
//  0.1.03  2015-01-02  added stair, more refactoring
//  0.1.04  2015-01-03  added integer versions - to be used with 8 bit DAC
//  0.1.5   2017-07-29  Fix issue #33 (dbl -> float)
//  0.2.0   2020-06-10  main refactoring and cleanup
//  0.2.1   2020-12-24  Arduino-CI + unit tests
//  0.2.2   2021-11-02  update Arduino-CI, badges
//                      add mode for sawtooth and stair.
//  0.2.3   2021-12-18  update library.json, license, minor edits


#include "functionGenerator.h"


funcgen::funcgen(float period, float amplitude, float phase, float yShift)
{
  setPeriod(period);
  setAmplitude(amplitude);
  setPhase(phase);
  setYShift(yShift);
}


void funcgen::setPeriod(float period)
{
  _period = period;
  _freq1 = 1 / period;
  _freq2 = 2 * _freq1;
  _freq4 = 4 * _freq1;
  _freq0 = TWO_PI * _freq1;
}


float funcgen::line()
{
  return _yShift + _amplitude;
}


float funcgen::zero()
{
  return 0;
}


float funcgen::sawtooth(float t, uint8_t mode)
{
  float rv;
  t += _phase;
  if (t >= 0.0)
  {
    if (t >= _period) t = fmod(t, _period);
    if (mode == 1) t = _period - t;
    rv = _amplitude * (-1.0 + t *_freq2);
  }
  else
  {
    t = -t;
    if (t >= _period) t = fmod(t, _period);
    if (mode == 1) t = _period - t;
    rv = _amplitude * ( 1.0 - t * _freq2);
  }
  rv += _yShift;
  return rv;
}


float funcgen::triangle(float t)
{
  float rv;
  t += _phase;
  if (t < 0.0)
  {
    t = -t;
  }
  if (t >= _period) t = fmod(t, _period);
  if ( t * 2 < _period)
  {
    rv = _amplitude * (-1.0 + t * _freq4);
  }
  else
  {
    rv = _amplitude * (3.0 - t * _freq4);
  }
  rv += _yShift;
  return rv;
}


float funcgen::square(float t)
{
  float rv;
  t += _phase;
  if (t >= 0)
  {
    if (t >= _period) t = fmod(t, _period);
    if ((t + t) < _period) rv = _amplitude;
    else rv = -_amplitude;
  }
  else
  {
    t = -t;
    if (t >= _period) t = fmod(t, _period);
    if ( t * 2 < _period) rv = -_amplitude;
    else rv = _amplitude;
  }
  rv += _yShift;
  return rv;
}


float funcgen::sinus(float t)
{
  float rv;
  t += _phase;
  rv = _amplitude * sin(t * _freq0);
  rv += _yShift;
  return rv;
}


float funcgen::stair(float t, uint16_t steps, uint8_t mode)
{
  t += _phase;
  if (t >= 0)
  {
    if (t >= _period) t = fmod(t, _period);
    if (mode == 1) t = _period - t;
    int level = steps * t / _period;
    return _yShift + _amplitude * (-1.0 + 2.0 * level / (steps - 1));
  }
  t = -t;
  if (t >= _period) t = fmod(t, _period);
  if (mode == 1) t = _period - t;
  int level = steps * t / _period;
  return _yShift + _amplitude * (1.0 - 2.0 * level / (steps - 1));
}


float funcgen::random()
{
  // TODO smart reseed needed
  float rv = _yShift + _amplitude * _random() * 0.2328306436E-9;  // div 0xFFFFFFFF
  return rv;
}


// An example of a simple pseudo-random number generator is the
// Multiply-with-carry method invented by George Marsaglia.
// two initializers (not null)
uint32_t funcgen::_random()
{
  _m_z = 36969L * (_m_z & 65535L) + (_m_z >> 16);
  _m_w = 18000L * (_m_w & 65535L) + (_m_w >> 16);
  return (_m_z << 16) + _m_w;  /* 32-bit result */
}


//
// INTEGER VERSIONS FOR 8 BIT DAC
//
// 8 bits version
// t = 0..9999 period 10000 in millis, returns 0..255

/*

uint8_t ifgsaw(uint16_t t, uint16_t period = 1000)
{
 return 255L * t / period;
}


uint8_t ifgtri(uint16_t t, uint16_t period = 1000)
{
 if (t * 2 < period) return 510L * t / period;
 return 255L - 510L * t / period;
}


uint8_t ifgsqr(uint16_t t, uint16_t period = 1000)
{
 if (t * 2 < period) return 510L * t / period;
 return 255L - 510L * t / period;
}


uint8_t ifgsin(uint16_t t, uint16_t period = 1000)
{
 return sin(355L * t / period / 113); // LUT
}


uint8_t ifgstr(uint16_t t, uint16_t period = 1000, uint16_t steps = 8)
{
 int level = 1L * steps * t / period;
 return 255L * level / (steps - 1);
}

*/


//
// SIMPLE float ONES
//
// t = 0..period
// period = 0.001 ... 10000 ?
/*

float fgsaw(float t, float period = 1.0)
{
 if (t >= 0) return -1.0 + 2 * t / period;
 return 1.0 + 2 * t / period;
}


float fgtri(float t, float period = 1.0)
{
 if (t < 0) t = -t;
 if (t * 2 < period) return -1.0 + 4 * t / period;
 return 3.0 - 4 * t / period;
}


float fgsqr(float t, float period = 1.0)
{
 if (t >= 0)
 {
 if ( 2 * t < period) return 1.0;
 return -1.0;
 }
 t = -t;
 if (2 * t < period) return -1.0;
 return 1.0;
}


float fgsin(float t, float period = 1.0)
{
 return sin(TWO_PI * t / period);
}


float fgstr(float t, float period = 1.0, uint16_t steps = 8)
{
 if (t >= 0)
 {
 int level = steps * t / period;
 return -1.0 + 2.0 * level / (steps - 1);
 }
 t = -t;
 int level = steps * t / period;
 return 1.0 - 2.0 * level / (steps - 1);
}

*/


//
// FULL floatS ONES
//
float fgsaw(float t, float period = 1.0, float amplitude = 1.0, float phase = 0.0, float yShift = 0.0)
{
  t += phase;
  if (t >= 0)
  {
    if (t >= period) t = fmod(t, period);
    return yShift + amplitude * (-1.0 + 2 * t / period);
  }
  t = -t;
  if (t >= period) t = fmod(t, period);
  return yShift + amplitude * ( 1.0 - 2 * t / period);
}


float fgtri(float t, float period = 1.0, float amplitude = 1.0, float phase = 0.0, float yShift = 0.0, float dutyCycle = 0.50)
{
  t += phase;
  if (t < 0) t = -t;
  if (t >= period) t = fmod(t, period);
  // 50 % dutyCycle = faster
  // if (t * 2 < period) return yShift + amplitude * (-1.0 + 4 * t / period);
  // return yShift + amplitude * (3.0 - 4 * t / period);
  if (t < dutyCycle * period) return yShift + amplitude * (-1.0 + 2 * t / (dutyCycle * period));
  // return yShift + amplitude * (-1.0 + 2 / (1 - dutyCycle) - 2 * t / ((1 - dutyCycle) * period));
  return yShift + amplitude * (-1.0 + 2 / (1 - dutyCycle) * ( 1 - t / period));
}


float fgsqr(float t, float period = 1.0, float amplitude = 1.0, float phase = 0.0, float yShift = 0.0, float dutyCycle = 0.50)
{
  t += phase;
  if (t >= 0)
  {
    if (t >= period) t = fmod(t, period);
    if (t < dutyCycle * period) return yShift + amplitude;
    return yShift - amplitude;
  }
  t = -t;
  if (t >= period) t = fmod(t, period);
  if (t < dutyCycle * period) return yShift - amplitude;
  return yShift + amplitude;
}


float fgsin(float t, float period = 1.0, float amplitude = 1.0, float phase = 0.0, float yShift = 0.0)
{
  t += phase;
  float rv = yShift + amplitude * sin(TWO_PI * t / period);
  return rv;
}


float fgstr(float t, float period = 1.0, float amplitude = 1.0, float phase = 0.0, float yShift = 0.0, uint16_t steps = 8)
{
  t += phase;
  if (t >= 0)
  {
    if (t >= period) t = fmod(t, period);
    int level = steps * t / period;
    return yShift + amplitude * (-1.0 + 2.0 * level / (steps - 1));
  }
  t = -t;
  if (t >= period) t = fmod(t, period);
  int level = steps * t / period;
  return yShift + amplitude * (1.0 - 2.0 * level / (steps - 1));
}


// -- END OF FILE --

