# FunctionGenerator

Arduino library to generate wave forms (nummeric) for a DAC

## Description

**Constructor**
* funcgen(float period = 1.0, float amplitude = 1.0, float phase = 0.0, float yShift = 0.0);
All parameters can be set in the constructor but also later in configuration.

**Configuration**
* void  setPeriod(float period = 1.0);  // seconds
* float getPeriod();
* void  setFrequency(float freq = 1.0);  // Hertz
* float getFrequency();
* void  setAmplitude(float ampl = 1.0);  // -
* float getAmplitude();
* void  setPhase(float phase = 0.0);     // phase of period
* float getPhase();
* void  setYShift(float yShift = 0.0);   // shift in amplitude, zero point.
* float getYShift();

**Wave forms**
t is time in seconds
* float sawtooth(float t);
* float triangle(float t);
* float square(float t);
* float sinus(float t);
* float stair(float t, uint16_t steps = 8);
* float random();
* float line();
* float zero();

Line() and zero() are functions that can be used
to drive a constant voltage from a DAC and can be 
used to calibrate the generator / DAC combination.

## Operational

See examples.

TODO example with DAC. 8 12 16 bit.
TODO example with potmeters for 4 parameters

