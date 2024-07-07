
[![Arduino CI](https://github.com/RobTillaart/FunctionGenerator/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/FunctionGenerator/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/FunctionGenerator/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/FunctionGenerator/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/FunctionGenerator/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/FunctionGenerator.svg)](https://github.com/RobTillaart/FunctionGenerator/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/FunctionGenerator/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/FunctionGenerator.svg?maxAge=3600)](https://github.com/RobTillaart/FunctionGenerator/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/FunctionGenerator.svg)](https://registry.platformio.org/libraries/robtillaart/FunctionGenerator)


# FunctionGenerator

Arduino library to generate (numeric) wave forms for a DAC.


## Description

This library presents a class for a function generator in **software**. 
It is typical used to control one or more DAC's.
To maximize signal quality one has to apply all (or most) processor power 
to calculate new values over and over again to get enough resolution. 
In practice the generator is useful for low frequencies, 
0.01 - 25 Hz, depending on waveform and processor and number of DAC's.
(see indication below).

Note: this class generates float values, performance wise this can be optimized,
to achieve higher speeds at cost of accuracy / precision.

As always, feedback and ideas are welcome.


### Performance

You always have to verify your own performance measurements to see if 
your requirements are met by this library.

**Indication** of what performance can be expected (based upon 0.2.1 version).  
Note that the values need to be transported to a DAC or serial port too.  
Numbers based on performance example, for one single signal.


|  Processor    |  Clock    |  Waveform  |  usec/call  |  max freq  | max values/period |
|:--------------|----------:|:-----------|------------:|-----------:|--------:|
|  Arduino UNO  |  16 MHz   |  sawtooth  |   62        |    60 Hz   |   268   |
|  Arduino UNO  |  16 MHz   |  triangle  |   74        |    50 Hz   |   270   |
|  Arduino UNO  |  16 MHz   |  square    |   53        |  1000 Hz   |    19   |
|  Arduino UNO  |  16 MHz   |  sinus     |   164       |    25 Hz   |   152   |
|  Arduino UNO  |  16 MHz   |  stair     |   81        |    50 Hz   |   246   |
|  Arduino UNO  |  16 MHz   |  random    |   37        |  1000 Hz   |    27   |
|  ESP32        |  240 MHz  |  sawtooth  |   3.8       |  1000 Hz   |   263   |
|  ESP32        |  240 MHz  |  triangle  |   3.9       |  1000 Hz   |   256   |
|  ESP32        |  240 MHz  |  square    |   2.8       |  1000 Hz   |   357   |
|  ESP32        |  240 MHz  |  sinus     |   13.6      |   250 Hz   |   294   |
|  ESP32        |  240 MHz  |  stair     |   4.8       |   800 Hz   |   260   |
|  ESP32        |  240 MHz  |  random    |   1.3       |  1000 Hz   |   769   |


- Assumption minimal around 250 samples per period to get a smooth signal.
  If a rougher signal is OK, higher frequencies are possible.
  For **square()** and **random()** less samples per period are often acceptable.
- ESP32 can do more calculations however 1000 Hz seems to be a nice 
  upper limit for a software based function generator.
- If one needs to control multiple DAC's one should divide the numbers
  and round down to get an estimate.


Note: hardware function generator https://github.com/RobTillaart/AD985X


Note: 0.2.5 due to duty cycle the triangle and square 
have become slightly slower.

|  Processor    |  Clock    |  Waveform  |  usec/call  |  max freq  |
|:--------------|----------:|:-----------|------------:|-----------:|
|  Arduino UNO  |  16 MHz   |  triangle  |   84        |    50 Hz   |
|  Arduino UNO  |  16 MHz   |  square    |   57        |  1000 Hz   |
|  Arduino UNO  |  16 MHz   |  random_DC |   68        |   500 Hz   |

See **functionGeneratorPerformance.ino**


### Accuracy

If the time parameter **t** grows large, the internal math may have rounding 
problems after some time. This can and will affect the quality of the output.
It is advised to reset **t** after a number (e.g. 100) full periods

Needs further investigations.

### Related

- https://github.com/RobTillaart/AD9833 hardware waveform generator.
- https://github.com/RobTillaart/AD985X hardware waveform generator.
- https://github.com/RobTillaart/functionGenerator software waveform generator.
- https://pages.mtu.edu/~suits/notefreqs.html frequency table for notes.


## Interface

```cpp
#include "functionGenerator.h"
```

### Constructor

- **funcgen(float period = 1.0, float amplitude = 1.0, float phase = 0.0, float yShift = 0.0)**
All parameters (except duty cycle) can be set in the constructor but also later in configuration.
Default dutyCycle is 50%.


### Configuration

- **void setPeriod(float period = 1.0)** set the period of the wave in seconds.
This is the inverse of the frequency.
- **float getPeriod()** returns the set period.
- **void setFrequency(float frequency = 1.0)** set the frequency of the wave in Hertz (1/s).
This is the inverse of the period.
- **float getFrequency()** returns the set frequency in Hertz.
- **void setAmplitude(float amplitude = 1.0)** sets the amplitude of the wave.
The range is from **-amplitude** to **+amplitude**.
Setting the amplitude to 0 gives effectively a zero signal.
Setting the amplitude to a negative value effectively inverts the signal.
- **float getAmplitude()** returns the set amplitude.
- **void setPhase(float phase = 0.0)** shifts the phase of the wave. 
Will only be noticeable when compared with other waves.
Phase is also known as the X- or horizontal shift.
- **float getPhase()** returns the set phase.
- **void setYShift(float yShift = 0.0)** sets an Y-shift or vertical offset in amplitude.
This allows to set e.g. the zero level.
- **float getYShift()** returns the set Y-shift.
- **void setDutyCycle(float percentage = 100)** sets the duty cycle of the signal.
Experimental, not all waveforms have a duty cycle or interpret it differently, see below.
Duty cycle must be between 0 and 100% and will be clipped otherwise.
- **float getDutyCycle()** returns the set (clipped) duty cycle.
- **void setRandomSeed(uint32_t a, uint32_t b = 314159265)** sets the initial seeds for the
(Marsaglia) random number generator. The first is mandatory, the second is optional.


### Wave forms

The variable t == time in seconds.

- **float sawtooth(float t, uint8_t mode = 0)** mode 0 is default.
  - mode == 0 ==>  sawtooth /|. 
  - mode == 1 ==> sawtooth |\\. Effectively equals inverting the amplitude.
- **float triangle(float t)** triangle form, duty cycle default 50%. 
- **float square(float t)** square wave with duty cycle default 50%.
- **float sinus(float t)** sinus wave, has no duty cycle.
- **float stair(float t, uint16_t steps = 8, uint8_t mode = 0)** defaults to 8 steps up.
  - mode = 0 ==> steps up
  - mode = 1 ==> steps down. Effectively equals inverting the amplitude.
- **float random()** random noise generation between 0 and amplitude.
Uses Marsaglia random generator.
- **float line()** constant voltage line. 
Height depends on the YShift and amplitude.
- **float zero()** constant zero.

The functions **line()** and **zero()** can be used to drive a constant voltage 
from a DAC and can be used to calibrate the generator / DAC combination.


Experimental 0.2.7

- **float sinusDiode(float t)** sinus wave, only positive pulses.  
(better name welcome).
- **float sinusRectified(float t)** sinus wave, with "abs(negative pulses)".  
(better name welcome).
- **float trapezium1(float t)** trapezium wave.
DutyCycle changes steepness of the falling and rising edge.
The wave changes from a square wave, via trapezium to a triangle wave.
- **float trapezium2(float t)** trapezium wave.
DutyCycle changes duration HIGH vs LOW, wave stays trapezium like.
Note at 50% DC the two trapezium functions are identical.
- **float heartBeat(float t)** simplified heartbeat wave.
To get a regular BPM heartbeat one should **setFrequency(BPM/60.0)** e.g 72/60 = 1.2.
- **float freeWave(float t, int16_t arr, int16_t N)** define a free wave form.
It uses an array of **N+1** values, dividing a full period in **N** equidistant steps.
The last value should equal the first value to have a smooth transition.
The values of the array normally vary between -10000 and +10000 to manage
the set the relative amplitude in small steps. 
These are scaled back to -1.0 to +1.0 times the amplitude.


### Duty Cycle 

Since 0.2.5 the library has **experimental** support for duty cycle.
The meaning of duty cycle differs per wave form.
Implementation may change in the future.

In first iteration the following behaviour is implemented:

- **square()** implements duty cycle in a well known way. 
At the start of the period the signal goes "HIGH".
After duty cycle % of the period the signal goes LOW until the end of the period.
- **triangle()** function uses the duty cycle to shift the peak from the
begin (0%) to middle (50%) to end (100%) of the period. 
- **random_DC()** A duty cycle of 0% is no noise 100% is full amplitude noise 
with respect to previous value. 
Implemented as a weighed average between new and previous value.
Made a separate function as handling the duty cycle slows performance substantial.
Initial starts at zero and can be adjusted with **YShift()**.
- **float trapezium1(float t)** The duty cycle changes the steepness of the rising
and falling edges. This changes the form from square wave to trapezium to triangle.
The length of the HIGH LOW level go from 0 to half a period.
- **float trapezium2(float t)** The duty cycle determines the length of the HIGH level,
which is 0 for 0% DC and half a period for 100% DC. 
The rising and falling edges stay same.
- **float heartBeat(float t)** The duty cycle determines the part of the period
that the signal ~zero.

### No duty cycle

The other functions need to be investigated what duty cycle means.
Current ideas that are **NOT** implemented:

- **sawtooth()** - move from /|. to /|__  so 0% is a spike, 100% = normal.
Think of it as the halve of the triangle wave.
- **sinus()** move the two peaks like the triangle (adjusting steepness / freq)??
- **stair()** like sawtooth??
- **line()** has no period so does not make sense (yet).
- **zero()** has no period so does not make sense (yet).
- **float sinusDiode(float t)**
- **float sinusRectified(float t)**
- **float freeWave(float t, int16_t arr, int16_t N)**

## Future

#### Must

- improve documentation
  - reorganize
  - section per function might be better.

#### Should

- smart reseed needed for random().
  - initialize random generator with compile file + date + time.
  - use function values for seed bits.
- stand-alone functions in separate .h
- clean up code

#### Could

- ASDR wave 
  - https://en.wikipedia.org/wiki/Envelope_(music)
  - **float ADSR(float t, float A, float D, float S, float R)** 
  - ADSR are percentages, A + D + R < 1.0
  - S = % of amplitude.
- external clock to synchronize two or more software function generators.
- check for synergy with https://github.com/RobTillaart/AD985X
- investigate performance.
  - algorithms for DAC specific gains e.g. 10-12-16 bit.
  - improve performance sin() lookup table.
  - add float variable for ```_perDC = _period * _dutyCycle```
  - do we need **freq4** ? not since DC.
- heartBeat
  - small noise/variation parameter on amplitude and frequency.
  - reduce footprint ==> wrapper around freeWave()
- waves
  - white noise, pink noise (better done with hardware)
  - min() + max() => return +-amplitude + yshift?
  - RC function curve.
  - Gamma curve.
- create a function table? with what?
- create an example program to sample an arbitrary wave form
  - output in the right format.
  - slow sampling vs real time.


#### Examples

  - Amplitude modulation ?
  - heartbeat curve?
  - example ESP32 version as separate task.
  - example with DAC. 8 12 16 bit.
  - example with potentiometers for 4 parameters

#### Wont

- investigate duty cycle for waveforms
  - Derived class for the duty cycle variants? or functions!
  - **float squareDC()** performance (loss)
  - **float triangleDC()**
  - **float sawtoothDC()**
  - **float sinusDC()** duty-cycle for sinus what does it mean. 
    - ==> move peaks, two half sinus with diff frequency
  - **float stairDC()**
- Bezier curve? (too complex)
- record a signal and play back  ==> separate class
- document max frequency per wave form etc.
  Should this be in the library? differs per board.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

