
[![Arduino CI](https://github.com/RobTillaart/fast_math/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/fast_math/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/fast_math/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/fast_math/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/fast_math/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/fast_math.svg)](https://github.com/RobTillaart/fast_math/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/fast_math/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/fast_math.svg?maxAge=3600)](https://github.com/RobTillaart/fast_math/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/fast_math.svg)](https://registry.platformio.org/libraries/robtillaart/fast_math)


# fast_math

Arduino library for fast math algorithms.


## Description

The fast_math library is a collection of algorithms that are faster 
than the default code. 
These algorithms are to be used when you are in a need for speed. 
Only tested on Arduino UNO as one of the "slower" boards.

**Warning:** verify if the algorithms works for your project. (no warranty).

These algorithms are collected and improved over a long time, and started
with improving decades ago when computers were slower than an Arduino UNO.

Note: I am interested in your feedback e.g. results on other platforms.
Also improvements or other fast code is welcome. Please open an issue.


#### Related

- https://github.com/RobTillaart/fastTrig Gonio functions (less exact but faster)


## Interface

```cpp
#include "fast_math.h"
```


### BCD

Two conversion functions, typical used in an RTC to convert register values
in **BCD** = binary coded decimal, to normal integer values and back..
- **uint8_t dec2bcd(uint8_t value)**
- **uint8_t bcd2dec(uint8_t value)**
- **dec2bcdRTC(uint8_t value)** Even faster version, for the range 0..60. 
Limited to be used in RTC's. (in fact it does 0..68 correct)

Backgrounder - https://forum.arduino.cc/t/faster-dec2bcd-routine-especial-for-rtc-libraries/180741/13


Indicative performance Arduino UNO.

|  function       |   us   |  factor |  notes  |
|:----------------|:------:|:-------:|:--------|
|  dec2bcd (ref)  |  5.88  |   1.0   |  100 iterations
|  dec2bcd        |  1.04  |   4.8   |
|  dec2bcdRTC     |  0.88  |   5.7   |  range 0..68
|                 |        |         |
|  bcd2dec (ref)  |  5.96  |   1.0   |
|  bcd2dec        |  2.20  |   2.7   |


### DIVMOD

Calculation of DIV and MOD simultaneous.

- **void divmod10(uint32_t in, uint32_t \*div, uint8_t \*mod)**
  - calculates both divide and modulo 10 faster than the default / 10 and % 10.

The **divmod10()** function is very useful for extracting the individual digits.
Typical use is to print digits on a display, in a file or send them as ASCII over a network.

Indicative performance Arduino UNO.

|  function  |   us   |  factor |  notes  |
|:-----------|:------:|:-------:|:--------|
|  i % 10    |  38.2  |   1.0   |
|  i / 10    |  38.1  |   1.0   |
|  divmod10  |   9.1  |   4.1   |

Note that for printing the gain in time per digit is 65 us.
E.g. for a 4 digit number this adds up to ~quarter millisecond.


Backgrounder - https://forum.arduino.cc/t/divmod10-a-fast-replacement-for-10-and-10-unsigned/163586


- **void divmod3(uint32_t in, uint32_t \*div, uint8_t \*mod)** used by divmod12/24
- **void divmod5(uint32_t in, uint32_t \*div, uint8_t \*mod)** 
- **void divmod12(uint32_t in, uint32_t \*div, uint8_t \*mod)** for hours
- **void divmod24(uint32_t in, uint32_t \*div, uint8_t \*mod)** for hours
- **void divmod60(uint32_t in, uint32_t \*div, uint8_t \*mod)** for minutes seconds


For every element of N (natural numbers) one could develop a divmodN() function.
The idea is to split the fraction 1/N into a sum of selected 1/(2^n) so the division 
becomes a series of adds and shifts. 
Sometimes there are patterns that can be optimized even more.

Furthermore for limited ranges a division can be replaced by a single multiply shift pair.


### PING distance sensor

For distance sensors that work with a acoustic pulse, one often see the formula:
```cm = us / 29;``` to calculate the distance in cm.
In float it should be ```cm = us / 29.15;``` or ```cm = us * 0.0345;```
Note that as this is the turnaround distance (forth & back) so one 
need a divide by two often. (maybe I should include that)

This library has functions to improve on speed.
The maximum input for the 16 bit functions is 65535 us 
which translates to approx. 2250 cm or 22500 mm  (20+ meter)
This is enough range for most ping sensors, which are typical 
in the range 0 - 10 meter.

The functions assume a speed of sound of 340 m/sec.

16 bit interface
- **uint16_t ping2cm(uint16_t in)**
- **uint16_t ping2mm(uint16_t in)**

32 bit interface
- **uint32_t ping2cm32(uint32_t in)** for lengths > 10 meter
- **uint32_t ping2mm32(uint32_t in)** for lengths > 10 meter
Performance wise the 32 bit versions have a gain ~10%.

Imperial
- **uint16_t ping2inch(uint16_t in)**
- **uint16_t ping2quarter(uint16_t in)**
- **uint16_t ping2sixteenths(uint16_t in)**


Indicative performance Arduino UNO.

|  function         |   us   |  factor  |  notes  |
|:------------------|:------:|:--------:|:--------|
|  us / 29  (ref)   |  38.3  |    1.0   | sos == 345 m/s  (integer only)
|  us \* 0.0345     |  18.5  |    2.0   | sos == 345 m/s
|  ping2cm          |  3.08  |   12.4   | sos == 340 m/s
|  ping2mm          |  5.66  |    6.7   | sos == 340 m/s
|                   |        |          |
|  ping2inch        |  4.34  |    8.8   | not precise as inches are rather large units
|  ping2quarter     |  7.55  |    5.0   | in between
|  ping2sixteenths  |  8.55  |    4.4   | way more accurate than inches


#### Temperature corrected

Instead of taking a fixed value a temperature corrected speed of sound will
be 0-5% more accurate. Of course this depends on the temperature.

The temperature is in whole degrees C or F. 

- **float ping2cm_tempC(uint16_t duration, int Celsius)** 
  - duration in us, temperature in Celsius.
  - this function is relative slow, a faster version is not tested.
- **float ping2inch_tempC(uint16_t duration, int Celsius)**
- **float ping2inch_tempF(uint16_t duration, int Fahrenheit)**


Indicative performance Arduino UNO.

|  function         |   us   |  factor  |  notes  |
|:------------------|:------:|:--------:|:--------|
|  normal division  |  38.3  |    1.0   |  not Temperature corrected
|  ping2cm_tempC    |  17.2  |    2.2   |
|  ping2inch_tempC  |  16.6  |    2.3   |
|  ping2inch_tempF  |  16.4  |    2.3   |



### Polynome

Routine to evaluate a polynome and be able to change its weights runtime.
E.g   y = 3x^2 + 5x + 7 ==> ar\[3] = { 7, 5, 3 };  degree = 2;
- **double polynome(double x, double ar[], uint8_t degree)**
  - degree >= 1, ar\[0] exists, and could be 0.
  
This function is useful for evaluating a polynome many times and be able to
adjust the weights. This can be used for finding the optimal weights to fit
a curve for a polynome of degree N. See example.

Another application can be to implement a calibration / offset function that
can be tuned (runtime).


## Future

#### Must

- update documentation
  - links, research?

#### Should

- unit tests
  - or examples that test a lot.
- examples
  - check output examples.
- keep investigating faster versions.
- **divmod()** performance table other versions

#### Could

- split up in multiple .h files, one per group.
  - fast_math.h includes all individual .h files.
- There are several divide functions to be included?
  div3(), div5(), div7(), div10() depends on application.
  These need more testing (range)
- constants?
  - GOLDEN_RATIO 1.61803398875
- check temperature corrected float?

#### TODO Functions

DIV
- **uint16_t divmod10()** 16 bit overload version ?
- **uint32_t div10(x, \*d)** would be a bit faster than divmod10()
- **uint32_t mod10(x, \*m)** would be a bit faster too
- **div7()** days - weeks.

BCD
- **uint16_t dec2bcd()** +  32 bit + back?


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


