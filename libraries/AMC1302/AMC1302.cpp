//
//    FILE: AMC1302.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-03-14
// VERSION: 0.1.1
// PURPOSE: Arduino library for AMC1302
//     URL: https://github.com/RobTillaart/AMC1302


#include "AMC1302.h"


AMC1302::AMC1302(uint8_t outNpin, uint8_t outPpin)
{
  _outNpin = outNpin;
  _outPpin = outPpin;
  _lastError = AMC1302_OK;
  _gain = 41;
  _formFactor  = AMC_FF_SINUS;
}


bool AMC1302::begin(float voltsPerStep, float shunt)
{
  if (_shunt < 1e-3) _shunt = 1e-3;
  if (_voltsPerStep < 1e-6) _voltsPerStep = 1e-6;

  _shunt = shunt;
  _voltsPerStep = voltsPerStep;
  _amperePerVolt = 1.0 / (_shunt * _gain);
  return true;
}


float AMC1302::calibrateVoltsPerStep(float current)
{
  if (current != 0)
  {
    float measured = mA_DC() * 1000;
    if (measured != 0)
    {
      _voltsPerStep = _voltsPerStep * current / measured;
    }
  }
  return _voltsPerStep;
}


void AMC1302::setFrequency(float frequency)
{
  _frequency = frequency;
}


float AMC1302::getFrequency()
{
  return _frequency;
}


//  FREQUENCY DETECTION
//  uses oversampling and averaging to minimize variation
//  blocks for substantial amount of time, depending on minimalFrequency
float AMC1302::detectFrequency(float minimalFrequency)
{
  int maximum = 0;
  int minimum = 0;
  maximum = minimum = analogRead(_outPpin);

  //  determine maxima
  uint32_t timeOut = round(1000000.0 / minimalFrequency);
  uint32_t start = micros();
  while (micros() - start < timeOut)
  {
    int value = analogRead(_outPpin);
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
  while ((int(analogRead(_outPpin)) >  Q1) && ((micros() - start) < timeOut));
  while ((int(analogRead(_outPpin)) <= Q3) && ((micros() - start) < timeOut));
  start = micros();
  for (int i = 0; i < 10; i++)
  {
    while ((int(analogRead(_outPpin)) >  Q1) && ((micros() - start) < timeOut));
    while ((int(analogRead(_outPpin)) <= Q3) && ((micros() - start) < timeOut));
  }
  uint32_t stop = micros();

  //  calculate frequency
  float wavelength = stop - start;
  _frequency = 1e7 / wavelength;
  if (_microsAdjust != 1.0) _frequency *= _microsAdjust;
  return _frequency;
}


//  timing for FREQUENCY DETECTION
void AMC1302::setMicrosAdjust(float factor)
{
  _microsAdjust = factor;
}


float AMC1302::getMicrosAdjust()
{
  return _microsAdjust;
}


//  MEASUREMENTS
float AMC1302::mA_peak2peak(uint16_t cycles)
{
  if (cycles == 0) cycles = 1;
  uint16_t period = round(1000000UL / _frequency);

  float sum = 0;
  for (uint16_t i = 0; i < cycles; i++)
  {
    int minimum, maximum;
    //  Better than using midPoint
    minimum = maximum = analogRead(_outPpin);

    //  find minimum and maximum
    uint32_t start = micros();
    while (micros() - start < period)  //  UNO ~180 samples...
    {
      int value = analogRead(_outPpin);
      //  determine extremes
      if (value < minimum) minimum = value;
      else if (value > maximum) maximum = value;
    }
    sum += (maximum - minimum);
  }
  float peak2peak = sum * _voltsPerStep * _amperePerVolt * 1000;
  if (cycles > 1) peak2peak /= cycles;
  return peak2peak;
}


float AMC1302::mA_AC(uint16_t cycles)
{
  if (cycles == 0) cycles = 1;
  uint16_t period  = round(1000000UL / _frequency);

  float sum = 0;
  for (uint16_t i = 0; i < cycles; i++)
  {
    uint16_t samples = 0;
    uint16_t zeros   = 0;

    int minimum, maximum;
    minimum = maximum = analogRead(_outPpin);

    //  find minimum and maximum and count the zero-level "percentage"
    uint32_t start = micros();
    while (micros() - start < period)  // UNO ~180 samples...
    {
      samples++;
      int value = analogRead(_outPpin);
      //  determine extremes
      if (value < minimum) minimum = value;
      else if (value > maximum) maximum = value;
      //  count zeros
      if (abs(value - analogRead(_outNpin)) <= 2) zeros++;
    }
    int peak2peak = maximum - minimum;

    //  automatic determine _formFactor / crest factor
    float D = 0;
    float FF = 0;
    if (zeros > samples * 0.025)          //  more than 2% zero's
    {
      D = 1.0 - (1.0 * zeros) / samples;  //  % SAMPLES NONE ZERO
      FF = sqrt(D) * _formFactor;         //  ASSUME NON ZERO PART ~ SINUS
    }
    else  //  # zeros is small => D --> 1 --> sqrt(D) --> 1
    {
      FF = _formFactor;
    }

    sum += peak2peak * FF;
  }
  float mA = 0.5 * sum * _voltsPerStep * _amperePerVolt * 1000;
  if (cycles > 1) mA /= cycles;

  return mA;
}


float AMC1302::mA_AC_sampling(uint16_t cycles)
{
  if (cycles == 0) cycles = 1;
  uint32_t period = round(1000000UL / _frequency);

  float sum = 0;
  for (uint16_t i = 0; i < cycles; i++)
  {
    uint16_t samples    = 0;
    float    sumSquared = 0;

    uint32_t start = micros();
    while (micros() - start < period)
    {
      samples++;
      float value = analogRead(_outPpin) - analogRead(_outNpin);
      sumSquared += (value * value);
    }
    sum += sqrt(sumSquared / samples);
  }
  float mA = sum * _voltsPerStep * _amperePerVolt * 1000;
  if (cycles > 1) mA /= cycles;
  return mA;
}


float AMC1302::mA_DC(uint16_t cycles)
{
  if (cycles == 0) cycles = 1;
  float sum = 0;
  for (uint16_t i = 0; i < cycles; i++)
  {
    int32_t steps = analogRead(_outPpin) - analogRead(_outNpin);
    sum += steps;
  }
  float mA = sum * _voltsPerStep * _amperePerVolt * 1000;
  if (cycles > 1) mA /= cycles;
  return mA;
}


//  CALIBRATION FORM FACTOR
void AMC1302::setFormFactor(float formFactor)
{
  _formFactor = formFactor;
}


float AMC1302::getFormFactor()
{
  return _formFactor;
}


//  DEBUG
uint32_t AMC1302::getMinimum()
{
  uint16_t period  = round(1000000UL / _frequency);
  uint32_t minimum = analogRead(_outPpin);

  //  find minimum
  uint32_t start = millis();
  while (millis() - start < period)
  {
    uint32_t value = analogRead(_outPpin);
    if (value < minimum) minimum = value;
  }
  return minimum;
}


uint32_t AMC1302::getMaximum()
{
  uint16_t period  = round(1000000UL / _frequency);
  uint32_t maximum = analogRead(_outPpin);

  //  find maximum
  uint32_t start = millis();
  while (millis() - start < period)
  {
    uint32_t value = analogRead(_outPpin);
    if (value > maximum) maximum = value;
  }
  return maximum;
}


float AMC1302::readVoltageN()
{
  return analogRead(_outNpin) * _voltsPerStep;
}


float AMC1302::readVoltageP()
{
  return analogRead(_outPpin) * _voltsPerStep;
}


int32_t AMC1302::rawDifference()
{
  int32_t rawN = analogRead(_outNpin);
  int32_t rawP = analogRead(_outPpin);
  return rawP - rawN;
}


float AMC1302::getGain()
{
  return _gain;
}


int16_t AMC1302::getLastError()
{
  int16_t e = _lastError;
  _lastError = AMC1302_OK;
  return e;
}


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//
AMC1200::AMC1200(uint8_t outNpin, uint8_t outPpin)
        :AMC1302(outNpin, outPpin)
{
  _gain = 8.0f;
}

AMC1300::AMC1300(uint8_t outNpin, uint8_t outPpin)
        :AMC1302(outNpin, outPpin)
{
  _gain = 8.2f;
}

AMC1301::AMC1301(uint8_t outNpin, uint8_t outPpin)
        :AMC1302(outNpin, outPpin)
{
  _gain = 8.2f;
}

AMC1311::AMC1311(uint8_t outNpin, uint8_t outPpin)
        :AMC1302(outNpin, outPpin)
{
  _gain = 1.0f;
}

AMC1351::AMC1351(uint8_t outNpin, uint8_t outPpin)
        :AMC1302(outNpin, outPpin)
{
  _gain = 0.4f;
}



//  -- END OF FILE --

