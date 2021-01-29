//
//    FILE: ACS712.cpp
//  AUTHOR: Rob Tillaart, Pete Thompson
// VERSION: 0.2.1
//    DATE: 2020-08-02
// PURPOSE: ACS712 library - current measurement
//
// HISTORY:
// 0.1.0    2020-03-17 initial version
// 0.1.1    2020-03-18 first release version
// 0.1.2    2020-03-21 automatic formfactor test
// 0.1.3    2020-05-27 fix library.json
// 0.1.4    2020-08-02 Allow for faster processors
// 0.2.0    2020-08-02 Add autoMidPoint
// 0.2.1    2020-12-06 Add arduino-CI + readme + unittest + refactor

#include "ACS712.h"

ACS712::ACS712(uint8_t analogPin, float volts, uint16_t maxADC, uint8_t mVperA)
{
  _pin = analogPin;
  _mVpstep     = 1000.0 * volts / maxADC;  // 1x 1000 for V -> mV
  _mVperAmpere = mVperA;
  _formFactor  = 0.70710678119;  // 0.5 * sqrt(2);  TODO: should be smaller in practice 0.5 ?
  _midPoint    = maxADC / 2;
  _noisemV     = 21;             // Noise is 21mV according to datasheet
}

int ACS712::mA_AC(uint8_t freq)
{
  uint32_t start = micros();
  uint16_t period = ((freq == 60) ? 16670 : 20000);
  uint16_t samples = 0;
  uint16_t zeros = 0;

  int _min, _max;
  _min = _max = analogRead(_pin);

  while (micros() - start < period)  // UNO ~180 samples...
  {
    samples++;
    int val = analogRead(_pin);
    if (val < _min) _min = val;
    if (val > _max) _max = val;
    if (abs(val - _midPoint) <= (_noisemV/_mVpstep)) zeros++;
  }
  int point2point = (_max - _min);

  // automatic determine _formFactor / crest factor
  float D = 0;
  float FF = 0;
  if (zeros > samples * 0.025)
  {
    D = 1.0 - (1.0 * zeros) / samples;    // % SAMPLES NONE ZERO
    FF = sqrt(D) * 0.5 * sqrt(2);         // ASSUME NON ZERO PART ~ SINUS
  }
  else  // # zeros is small => D --> 1 --> sqrt(D) --> 1
  {
    FF = 0.5 * sqrt(2);
  }
  _formFactor = FF;

  // math could be partially precalculated: C = 1000.0 * 0.5 * _mVpstep / _mVperAmpere;
  // rounding?
  return 1000.0 * 0.5 * point2point * _mVpstep * _formFactor / _mVperAmpere;
}

int ACS712::mA_DC()
{
    // read twice to stabilize...
    analogRead(_pin);
    int steps = analogRead(_pin) - _midPoint;
    return 1000.0 * steps * _mVpstep / _mVperAmpere;
}

// configure by sampling for 2 cycles of AC
// Also works for DC as long as no current flowing
void ACS712::autoMidPoint(uint8_t freq)
{
  uint32_t start = micros();
  uint16_t twoPeriods = ((freq == 60) ? 16670 : 20000) * 2;
  uint32_t total = 0;
  uint32_t samples = 0;
  while (micros() - start < twoPeriods) {
    uint16_t reading = analogRead(_pin);
    total += reading;
    samples ++;
    // Delaying ensures we won't overflow since we'll perform a maximum of 40,000 reads
    delayMicroseconds(1);
  }
  _midPoint = total / samples;
}

// END OF FILE
