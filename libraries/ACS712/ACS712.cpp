//
//    FILE: ACS712.cpp
//  AUTHOR: Rob Tillaart, Pete Thompson
// VERSION: 0.3.1
//    DATE: 2020-08-02
// PURPOSE: ACS712 library - current measurement
//
//  HISTORY:
//  0.1.0  2020-03-17  initial version
//  0.1.1  2020-03-18  first release version
//  0.1.2  2020-03-21  automatic form factor test
//  0.1.3  2020-05-27  fix library.json
//  0.1.4  2020-08-02  Allow for faster processors
//
//  0.2.0  2020-08-02  Add autoMidPoint
//  0.2.1  2020-12-06  Add Arduino-CI + readme + unit test + refactor
//  0.2.2  2021-06-23  support for more frequencies.
//  0.2.3  2021-10-15  changed frequencies to float, for optimal tuning.
//                     updated build CI, readme.md
//  0.2.4  2021-11-22  add experimental detectFrequency()
//  0.2.5  2021-12-03  add timeout to detectFrequency()
//  0.2.6  2021-12-09  update readme.md + license
//  0.2.7  2022-08-10  change mVperAmp to float
//                     add ACS712_FF_SAWTOOTH
//                     update readme.md + unit test + minor edits
//  0.2.8  2022-08-19  prepare for 0.3.0
//                     Fix #21 FormFactor
//                     add mA_AC_sampling() as method to determine
//                     current when FormFactor is unknown.
//                     added float _AmperePerStep cached value.
//                     added getAmperePerStep();
//                     moved several functions to .cpp
//                     improve documentation
//
//  0.3.0  2022-09-01  return midPoint value in MP functions.
//                     float return type for mA() functions
//                     add float mA_peak2peak(freq, cycles)
//                     add debug getMinimum(), getmaximum();
//                     update Readme.md
//  0.3.1  2022-09-xx  add float mVNoiseLevel(frequency, cycles)
//                     add void suppressNoise(bool flag) 
//                         experimental suppression by averaging two samples.
//                     update readme.md
//                     improve midPoint functions
//                     add resetMidPoint()
//                     add RP2040 pico in build-ci


#include "ACS712.h"


//  CONSTRUCTOR
ACS712::ACS712(uint8_t analogPin, float volts, uint16_t maxADC, float mVperAmpere)
{
  _pin         = analogPin;
  _maxADC      = maxADC;
  _mVperStep   = 1000.0 * volts / maxADC;  //  1x 1000 for V -> mV
  _mVperAmpere = mVperAmpere;
  _mAPerStep   = 1000.0 * _mVperStep / _mVperAmpere;
  _formFactor  = ACS712_FF_SINUS;
  _midPoint    = maxADC / 2;
  _noisemV     = ACS712_DEFAULT_NOISE;    //  21mV according to datasheet
}


//  MEASUREMENTS
float ACS712::mA_peak2peak(float frequency, uint16_t cycles)
{
  uint16_t period = round(1000000UL / frequency);

  if (cycles == 0) cycles = 1;
  float sum = 0;

  for (uint16_t i = 0; i < cycles; i++)
  {
    int minimum, maximum;
    //  Better than using midPoint
    minimum = maximum = analogRead(_pin);

    //  find minimum and maximum
    uint32_t start = micros();
    while (micros() - start < period)  // UNO ~180 samples...
    {
      int value = analogRead(_pin);
      if (_suppresNoise)               //  average 2 samples.
      {
        value = (value + analogRead(_pin))/2;
      }
      //  determine extremes
      if (value < minimum) minimum = value;
      else if (value > maximum) maximum = value;
    }
    sum += (maximum - minimum);
  }
  float peak2peak = sum * _mAPerStep;
  if (cycles > 1) peak2peak /= cycles;

  return peak2peak;
}


float ACS712::mA_AC(float frequency, uint16_t cycles)
{
  uint16_t period  = round(1000000UL / frequency);

  if (cycles == 0) cycles = 1;
  float sum = 0;

  //  remove float operation from loop.
  uint16_t zeroLevel = round(_noisemV/_mVperStep);

  for (uint16_t i = 0; i < cycles; i++)
  {
    uint16_t samples = 0;
    uint16_t zeros   = 0;

    int _min, _max;
    _min = _max = analogRead(_pin);

    //  find minimum and maximum and count the zero-level "percentage"
    uint32_t start = micros();
    while (micros() - start < period)  // UNO ~180 samples...
    {
      samples++;
      int value = analogRead(_pin);
      if (_suppresNoise)  //  average 2 samples.
      {
        value = (value + analogRead(_pin))/2;
      }
      //  determine extremes
      if (value < _min) _min = value;
      else if (value > _max) _max = value;
      //  count zeros
      if (abs(value - _midPoint) <= zeroLevel ) zeros++;
    }
    int peak2peak = _max - _min;

    //  automatic determine _formFactor / crest factor
    float D = 0;
    float FF = 0;
    if (zeros > samples * 0.025)          //  more than 2% zero's
    {
      D = 1.0 - (1.0 * zeros) / samples;  //  % SAMPLES NONE ZERO
      FF = sqrt(D) * _formFactor;         //  ASSUME NON ZERO PART ~ SINUS
    }
    else                  //  # zeros is small => D --> 1 --> sqrt(D) --> 1
    {
      FF = _formFactor;
    }

    //  value could be partially pre-calculated: C = 1000.0 * 0.5 * _mVperStep / _mVperAmpere;
    //  return 1000.0 * 0.5 * peak2peak * _mVperStep * _formFactor / _mVperAmpere);
    sum += peak2peak * FF;
  }
  float mA = 0.5 * sum * _mAPerStep;
  if (cycles > 1) mA /= cycles;

  return mA;
}


float ACS712::mA_AC_sampling(float frequency, uint16_t cycles)
{
  uint32_t period = round(1000000UL / frequency);

  if (cycles == 0) cycles = 1;
  float sum = 0;

  // float noiseLevel = _noisemV/_mVperStep;

  for (uint16_t i = 0; i < cycles; i++)
  {
    uint16_t samples    = 0;
    float    sumSquared = 0;

    uint32_t start = micros();
    while (micros() - start < period)
    {
      samples++;
      int value = analogRead(_pin);
      if (_suppresNoise)  //  average 2 samples.
      {
        value = (value + analogRead(_pin))/2;
      }
      float current = value - _midPoint;
      sumSquared += (current * current);
      // if (abs(current) > noiseLevel)
      // {
      //   sumSquared += (current * current);
      // }
    }
    sum += sqrt(sumSquared / samples);
  }
  float mA = sum * _mAPerStep;
  if (cycles > 1) mA /= cycles;

  return mA;
}


float ACS712::mA_DC(uint16_t cycles)
{
  //  read at least twice to stabilize the ADC
  analogRead(_pin);
  if (cycles == 0) cycles = 1;
  float sum = 0;
  for (uint16_t i = 0; i < cycles; i++)
  {
    int value = analogRead(_pin);
    if (_suppresNoise)  //  average 2 samples.
    {
      value = (value + analogRead(_pin))/2;
    }
    sum += (value - _midPoint);
  }
  float mA = sum * _mAPerStep;
  if (cycles > 1) mA /= cycles;

  return mA;
}


//  CALIBRATION MIDPOINT
uint16_t ACS712::setMidPoint(uint16_t midPoint)
{
  if (midPoint <= _maxADC) _midPoint = midPoint;
  return _midPoint;
};


uint16_t ACS712::getMidPoint()
{
  return _midPoint;
};


uint16_t ACS712::incMidPoint()
{
  if (_midPoint < _maxADC) _midPoint += 1;
  return _midPoint;
};


uint16_t ACS712::decMidPoint()
{
  if (_midPoint > 0) _midPoint -= 1;
  return _midPoint;
};


//  configure by sampling for 2 cycles of AC
//  Also works for DC as long as no current flowing
//  note this is blocking!
uint16_t ACS712::autoMidPoint(float frequency, uint16_t cycles)
{
  uint16_t twoPeriods = round(2000000UL / frequency);

  if (cycles == 0) cycles = 1;

  uint32_t total = 0;
  for (uint16_t i = 0; i < cycles; i++)
  {
    uint32_t subTotal = 0;
    uint32_t samples  = 0;
    uint32_t start    = micros();
    while (micros() - start < twoPeriods)
    {
      uint16_t reading = analogRead(_pin);
      subTotal += reading;
      samples++;
      //  Delaying prevents overflow
      //  since we'll perform a maximum of 40,000 reads @ 50 Hz.
      delayMicroseconds(1);
    }
    total += (subTotal / samples);
  }
  _midPoint = total / cycles;
  return _midPoint;
}


uint16_t ACS712::resetMidPoint()
{
  _midPoint = _maxADC / 2;
  return _midPoint;
};


//  CALIBRATION FORM FACTOR
void ACS712::setFormFactor(float formFactor)
{
  _formFactor = formFactor;
};


float ACS712::getFormFactor()
{
  return _formFactor;
};


//  CALIBRATION NOISE
//  noise defaults 21 datasheet
void  ACS712::setNoisemV(uint8_t noisemV)
{
  _noisemV = noisemV;
};


uint8_t ACS712::getNoisemV()
{
  return _noisemV;
};


float ACS712::mVNoiseLevel(float frequency, uint16_t cycles)
{
  float mA = mA_peak2peak(frequency, cycles);
  //  divide by 2 as the level is half of the peak to peak range
  return mA * _mVperAmpere * 0.001 / 2;
}


void ACS712::suppressNoise(bool flag)
{
  _suppresNoise = flag;
}


//  CALIBRATION mV PER AMP
//  Adjusting resolution AC and DC
void ACS712::setmVperAmp(float mVperAmpere)
{
  _mVperAmpere = mVperAmpere;
  _mAPerStep = 1000.0 * _mVperStep / _mVperAmpere;
};


float ACS712::getmVperAmp()
{
  return _mVperAmpere;
};


float ACS712::getmAPerStep()
{
  return _mAPerStep;
};


float ACS712::getAmperePerStep()
{
  return _mAPerStep * 0.001;
};


//  FREQUENCY DETECTION
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

  //  10x passing Quantile points
  //  wait for the right moment to start
  //  to prevent endless loop a timeout is checked.
  timeOut *= 10;
  start = micros();
  //  casting to int to keep compiler happy.
  while ((int(analogRead(_pin)) >  Q1) && ((micros() - start) < timeOut));
  while ((int(analogRead(_pin)) <= Q3) && ((micros() - start) < timeOut));
  start = micros();
  for (int i = 0; i < 10; i++)
  {
    while ((int(analogRead(_pin)) >  Q1) && ((micros() - start) < timeOut));
    while ((int(analogRead(_pin)) <= Q3) && ((micros() - start) < timeOut));
  }
  uint32_t stop = micros();

  //  calculate frequency
  float wavelength = stop - start;
  float frequency = 1e7 / wavelength;
  if (_microsAdjust != 1.0) frequency *= _microsAdjust;
  return frequency;
}


//  timing for FREQUENCY DETECTION
void ACS712::setMicrosAdjust(float factor)
{
  _microsAdjust = factor;
};


float ACS712::getMicrosAdjust()
{
  return _microsAdjust;
};


//  DEBUG
uint16_t ACS712::getMinimum(uint16_t milliSeconds)
{
  uint16_t minimum = analogRead(_pin);

  //  find minimum
  uint32_t start = millis();
  while (millis() - start < milliSeconds)
  {
    uint16_t value = analogRead(_pin);
    if (value < minimum) minimum = value;
  }
  return minimum;
}


uint16_t ACS712::getMaximum(uint16_t milliSeconds)
{
  uint16_t maximum = analogRead(_pin);

  //  find minimum
  uint32_t start = millis();
  while (millis() - start < milliSeconds)
  {
    uint16_t value = analogRead(_pin);
    if (value > maximum) maximum = value;
  }
  return maximum;
}


// -- END OF FILE --

