//
//    FILE: SRF05.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.3
//    DATE: 2021-05-17
// PURPOSE: Arduino library for the SRF05 distance sensor (and compatibles)
//     URL: https://github.com/RobTillaart/SRF05


#include "SRF05.h"


/////////////////////////////////////////////////////
//
//  CONSTRUCTORS
//
SRF05::SRF05(const uint8_t trigger, const uint8_t echo, const uint8_t out)
{
  _trigger = trigger;
  _echo    = echo;
  _out     = out;
  _mode    = 0;
  pinMode(_trigger, OUTPUT);
  digitalWrite(_trigger, LOW);
  pinMode(_echo, INPUT);
}


void SRF05::setSpeedOfSound(float sos)
{
  _speedOfSound = sos;
}

float SRF05::getSpeedOfSound()
{
  return _speedOfSound;
}


void SRF05::setCorrectionFactor(float factor)
{
  _correctionFactor = factor;
};


float SRF05::getCorrectionFactor()
{
  return _correctionFactor;
};


//////////////////////////////////////////////////
//
//  MODE
//
void SRF05::setModeSingle()
{
  _mode  = 0x00;
  _count = 1;
}


void SRF05::setModeAverage(uint8_t count)
{
  _mode  = 0x01;
  _count = count;
}


void SRF05::setModeMedian(uint8_t count)
{
  _mode  = 0x02;
  _count = count;
  if (_count < 3)  _count = 3;
  if (_count > 15) _count = 15;
}


void SRF05::setModeRunningAverage(float alpha)
{
  _mode  = 0x03;
  _count = 1;
  _alpha = alpha;
}


uint8_t SRF05::getOperationalMode()
{
  return _mode;
}


//////////////////////////////////////////////////
//
//  MEASUREMENTS
//
uint32_t SRF05::getTime()
{
  switch(_mode)
  {
    default:
    case 0x00:
      return _read();

    case 0x01:
    {
      float sum = 0;
      for (uint8_t s = 0; s < _count; s++)
      {
        sum += _read();
        delay(1);
      }
      return round(sum / _count);
    }
    case 0x02:
    {
      uint32_t samples[15];
      for (uint8_t s = 0; s < _count; s++)
      {
        samples[s] = _read();
        delay(1);
      }
      _insertSort(samples, _count);
      if (_count & 0x01) return samples[_count / 2];
      return (samples[(_count + 1) / 2] + samples[_count / 2]) / 2;
    }
    case 0x03:
      _value = (1 - _alpha) * _value + _alpha * _read();
      return _value;
  }
}


uint32_t SRF05::getMillimeter()
{
  return _speedOfSound * getTime() * 0.5e-3;
}


float SRF05::getCentimeter()
{
  return _speedOfSound * getTime() * 0.5e-4;
}


float SRF05::getMeter()
{
  return _speedOfSound * getTime() * 0.5e-6;
}


float SRF05::getInch()
{
  return _speedOfSound * getTime() * 1.9685e-5;
}


float SRF05::getFeet()
{
  return _speedOfSound * getTime() * 1.64042e-6;
}


//  assumes a distance of 1.00 meter
//  typically use 100 or 500 meter for distance to calibrate
float SRF05::determineSpeedOfSound(uint16_t distance)
{
  float sum = 0;
  for (uint16_t i = 0; i < distance; i++)
  {
    sum += _read();
    delay(1);
  }
  float sos = 2e6 * distance / sum;
  return sos;
}


//////////////////////////////////////////////////
//
// private
//
uint32_t SRF05::_read()
{
  digitalWrite(_trigger, HIGH);
  delayMicroseconds(_triggerLength);
  digitalWrite(_trigger, LOW);
  uint32_t duration = pulseIn(_echo, HIGH, 300000);
  if (_correctionFactor == 1)
  {
     return duration;
  }
  return round(duration * _correctionFactor);
}


void SRF05::_insertSort(uint32_t * array, uint8_t size)
{
  uint8_t t, z;
  uint32_t temp;
  for (t = 1; t < size; t++)
  {
    z = t;
    temp = array[z];
    while( (z > 0) && (temp < array[z - 1] ))
    {
      array[z] = array[z - 1];
      z--;
    }
    array[z] = temp;
    yield();
  }
}


// -- END OF FILE --

