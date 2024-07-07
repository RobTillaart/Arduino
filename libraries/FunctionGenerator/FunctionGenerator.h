#pragma once
//
//    FILE: functionGenerator.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
// PURPOSE: wave form generating functions (use with care)
//     URL: https://github.com/RobTillaart/FunctionGenerator


#include "Arduino.h"

#define FUNCTIONGENERATOR_LIB_VERSION           (F("0.3.0"))


class funcgen
{
public:
  funcgen(float period = 1.0, float amplitude = 1.0, float phase = 0.0, float yShift = 0.0);


  /////////////////////////////////////////////////////////////
  //
  //  CONFIGURATION
  //
  void  setPeriod(float period = 1.0);
  float getPeriod();

  void  setFrequency(float freq = 1.0);
  float getFrequency();

  void  setAmplitude(float ampl = 1.0);
  float getAmplitude();

  void  setPhase(float phase = 0.0);
  float getPhase();

  void  setYShift(float yShift = 0.0);
  float getYShift();

  void  setDutyCycle(float dutyCycle);
  float getDutyCycle();

  void  setRandomSeed(uint32_t a, uint32_t b = 314159265);


  /////////////////////////////////////////////////////////////
  //
  //  FUNCTIONS
  //
  //  constant amplitude
  float line();
  //  constant zero for calibration.
  float zero();

  //  standard wave forms
  float sawtooth(float t, uint8_t mode = 0);  //  0 ==>  /|.   1 ==> sawtooth |\.
  float triangle(float t);
  float square(float t);
  float sinus(float t);
  float stair(float t, uint16_t steps = 8, uint8_t mode = 0);

  float random();
  float random_DC();  //  duty cycle variant. Experimental.

  /////////////////////////////////////////////////////////////
  //
  //  EXPERIMENTAL 0.2.7
  //
  float sinusDiode(float t);
  float sinusRectified(float t);
  float trapezium1(float t);
  float trapezium2(float t);
  float heartBeat(float t);  //  72 BPM = 72/60 = 1 setFrequency(1.2)
  float freeWave(float t, int16_t * arr, int16_t size);  //  arr must be size+1 long


private:
  float _period;
  float _freq0;
  float _freq1;
  float _freq2;
  float _freq4;
  float _amplitude;
  float _phase;
  float _yShift;
  float _dutyCycle;

  //  Marsaglia 'constants'
  uint32_t _m_w = 1;
  uint32_t _m_z = 2;
  uint32_t _random();
};


//  -- END OF FILE --

