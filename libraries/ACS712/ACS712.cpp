//
//    FILE: ACS712.cpp
//  AUTHOR: Rob Tillaart, Pete Thompson
// VERSION: 0.2.6
//    DATE: 2020-08-02
// PURPOSE: ACS712 library - current measurement
//
//  HISTORY:
//  0.1.0  2020-03-17  initial version
//  0.1.1  2020-03-18  first release version
//  0.1.2  2020-03-21  automatic form factor test
//  0.1.3  2020-05-27  fix library.json
//  0.1.4  2020-08-02  Allow for faster processors
//  0.2.0  2020-08-02  Add autoMidPoint
//  0.2.1  2020-12-06  Add Arduino-CI + readme + unit test + refactor
//  0.2.2  2021-06-23  support for more frequencies.
//  0.2.3  2021-10-15  changed frequencies to float, for optimal tuning.
//                     updated build CI, readme.md
//  0.2.4  2021-11-22  add experimental detectFrequency()
//  0.2.5  2021-12-03  add timeout to detectFrequency()
//  0.2.6  2021-12-09  update readme.md + license


#include "ACS712.h"


ACS712::ACS712(uint8_t analogPin, float volts, uint16_t maxADC, uint8_t mVperA)
{
  _pin = analogPin;
  _mVpstep     = 1000.0 * volts / maxADC;  // 1x 1000 for V -> mV
  _mVperAmpere = mVperA;
  _formFactor  = ACS712_FF_SINUS;  
  _midPoint    = maxADC / 2;
  _noisemV     = 21;             // Noise is 21mV according to datasheet
}


int ACS712::mA_AC(float freq)
{
  uint16_t period  = round(1000000UL / freq);
  uint16_t samples = 0;
  uint16_t zeros   = 0;

  int _min, _max;
  _min = _max = analogRead(_pin);

  //  remove expensive float operation from loop.
  uint16_t zeroLevel = round(_noisemV/_mVpstep);

  uint32_t start = micros();
  while (micros() - start < period)  // UNO ~180 samples...
  {
    samples++;
    int val = analogRead(_pin);
    if (val < _min) _min = val;
    else if (val > _max) _max = val;
    if (abs(val - _midPoint) <= zeroLevel ) zeros++;
  }
  int point2point = (_max - _min);

  // automatic determine _formFactor / crest factor
  float D = 0;
  float FF = 0;
  if (zeros > samples * 0.025)  // more than 2% zero's
  {
    D = 1.0 - (1.0 * zeros) / samples;  // % SAMPLES NONE ZERO
    FF = sqrt(D) * ACS712_FF_SINUS;     // ASSUME NON ZERO PART ~ SINUS
  }
  else  // # zeros is small => D --> 1 --> sqrt(D) --> 1
  {
    FF = ACS712_FF_SINUS;
  }
  _formFactor = FF;

  // value could be partially precalculated: C = 1000.0 * 0.5 * _mVpstep / _mVperAmpere;
  // return 1000.0 * 0.5 * point2point * _mVpstep * _formFactor / _mVperAmpere);
  return round( (500.0 * point2point) * _mVpstep * _formFactor / _mVperAmpere);
}


int ACS712::mA_DC()
{
  //  read twice to stabilize the ADC
  analogRead(_pin);
  int steps = analogRead(_pin) - _midPoint;
  return 1000.0 * steps * _mVpstep / _mVperAmpere;
}


//  configure by sampling for 2 cycles of AC
//  Also works for DC as long as no current flowing
//  note this is blocking!
void ACS712::autoMidPoint(float freq)
{
  uint16_t twoPeriods = round(2000000UL / freq);

  uint32_t total   = 0;
  uint32_t samples = 0;
  uint32_t start   = micros();
  while (micros() - start < twoPeriods)
  {
    uint16_t reading = analogRead(_pin);
    total += reading;
    samples ++;
    // Delaying ensures we won't overflow since we'll perform a maximum of 40,000 reads
    delayMicroseconds(1);
  }
  _midPoint = total / samples;
}


//  Experimental frequency detection.
//  uses oversampling and averaging to minimize variation
//  blocks for substantial amount of time, depending on minimalFrequency
float ACS712::detectFrequency(float minimalFrequency)
{
  int maximum = 0;
  int minimum = 0;
  maximum = minimum = analogRead(_pin);

  //  determine maxima
  uint32_t timeOut = round(1000000.0 / minimalFrequency);
  uint32_t start = micros();
  while (micros() - start < timeOut)
  {
    int value = analogRead(_pin);
    if (value > maximum) maximum = value;
    if (value < minimum) minimum = value;
  }

  //  calculate quarter points
  //  using quarter points is less noise prone than using one single midpoint
  int Q1 = (3 * minimum + maximum ) / 4;
  int Q3 = (minimum + 3 * maximum ) / 4;

  // 10x passing Quantile points
  // wait for the right moment to start
  // to prevent endless loop a timeout is checked.
  timeOut *= 10;
  start = micros();
  while ((analogRead(_pin) >  Q1) && ((micros() - start) < timeOut));
  while ((analogRead(_pin) <= Q3) && ((micros() - start) < timeOut));
  start = micros();
  for (int i = 0; i < 10; i++)
  {
    while ((analogRead(_pin) >  Q1) && ((micros() - start) < timeOut));
    while ((analogRead(_pin) <= Q3) && ((micros() - start) < timeOut));
  }
  uint32_t stop = micros();

  //  calculate frequency
  float wavelength = stop - start;
  float frequency = 1e7 / wavelength;
  if (_microsAdjust != 1.0) frequency *= _microsAdjust;
  return frequency;
}


// -- END OF FILE --

