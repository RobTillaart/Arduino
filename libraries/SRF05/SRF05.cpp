//
//    FILE: SRF05.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
//    DATE: 2021-05-17
// PURPOSE: Arduino library for the SRF05 distance sensor (and compatibles)
//     URL: https://github.com/RobTillaart/SRF05


#include "SRF05.h"


/////////////////////////////////////////////////////
//
//  CONSTRUCTORS
//
SRF05::SRF05(const uint8_t trigger, const uint8_t echo)
{
  _trigger = trigger;
  _echo    = echo;
  _mode    = SRF05_MODE_SINGLE;
  if (echo == 0)
  {
      _echo = _trigger;
  }
  pinMode(_trigger, OUTPUT);
  digitalWrite(_trigger, LOW);
}


void SRF05::setSpeedOfSound(float speedOfSound)
{
  _speedOfSound = speedOfSound;
}


float SRF05::getSpeedOfSound()
{
  return _speedOfSound;
}


bool SRF05::setCorrectionFactor(float factor)
{
  if (factor <= 0) return false;
  _correctionFactor = factor;
  return true;
}


float SRF05::getCorrectionFactor()
{
  return _correctionFactor;
}


//////////////////////////////////////////////////
//
//  OPERATIONAL MODE
//
void SRF05::setModeSingle()
{
  _mode  = SRF05_MODE_SINGLE;
  _count = 1;
}


void SRF05::setModeAverage(uint8_t count)
{
  _mode = SRF05_MODE_AVERAGE;
  if (_count == 0)  _count = 1;
  _count = count;
}


void SRF05::setModeMedian(uint8_t count)
{
  _mode  = SRF05_MODE_MEDIAN;
  _count = count;
  if (_count < 3)  _count = 3;
  if (_count > 15) _count = 15;
}


void SRF05::setModeRunningAverage(float alpha)
{
  _mode  = SRF05_MODE_RUN_AVERAGE;
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
  _lastTime = millis();

  switch(_mode)
  {
    default:
    case SRF05_MODE_SINGLE:
      return _read();

    case SRF05_MODE_AVERAGE:
    {
      float sum = 0;
      for (uint8_t s = 0; s < _count; s++)
      {
        sum += _read();
        delayMicroseconds(_sampleInterval);
      }
      return round(sum / _count);
    }

    case SRF05_MODE_MEDIAN:
    {
      uint32_t samples[15];
      for (uint8_t s = 0; s < _count; s++)
      {
        samples[s] = _read();
        delayMicroseconds(_sampleInterval);
      }
      _insertSort(samples, _count);
      if (_count & 0x01) return samples[_count / 2];
      return (samples[(_count + 1) / 2] + samples[_count / 2]) / 2;
    }

    case SRF05_MODE_RUN_AVERAGE:
      _value = (1 - _alpha) * _value + _alpha * _read();
      return _value;
  }
  return 0;  //  should not happen
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


float SRF05::getYards()
{
  return _speedOfSound * getTime() * 0.54681e-6;
}


//  EXPERIMENTAL
//  distance in meters (single trip)
float SRF05::determineSpeedOfSound(float distance, uint8_t count)
{
  float sum = 0;
  if (count == 0) count = 1;
  while (count--)
  {
    sum += _read();
    delayMicroseconds(_sampleInterval);
  }
  //  sos = distance travelled forth and back in micrometer
  //        divided by time in microseconds.
  float sos = (count * distance * 2e6) / sum;
  return sos;
}


void SRF05::setTriggerLength(uint8_t length)
{
  _triggerLength = length;
}


uint8_t SRF05::getTriggerLength()
{
  return _triggerLength;
}


uint32_t SRF05::lastTime()
{
  return _lastTime;
}


float SRF05::calculateSpeedOfSound(float temperature, float humidity)
{
  //  interpolate
  //  column RNH = 0%, from formula.
  float sos     = 331.45 * sqrt(1 + temperature/273.15);
  //  column RH = 100%, interpolation from spreadsheet
  float sos_100 = 332.392083694084 + 0.683791630591631 * temperature;

  //  interpolate the humidity between these 2
  if (humidity > 0)
  {
    sos += (sos_100 - sos) * humidity * 0.01;
  }
  return sos;
}


//////////////////////////////////////////////////
//
//  PRIVATE
//
uint32_t SRF05::_read()
{
  //  Send pulse
  pinMode(_trigger, OUTPUT);
  digitalWrite(_trigger, HIGH);
  delayMicroseconds(_triggerLength);
  digitalWrite(_trigger, LOW);

  //  Wait for echo
  pinMode(_echo, INPUT);
  uint32_t duration = pulseIn(_echo, HIGH, 200000);  //  was 300000 (50+ meter)
  if (_correctionFactor == 1.0)
  {
     return duration;
  }
  return round(duration * _correctionFactor);
}


//  for median
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


//  -- END OF FILE --

