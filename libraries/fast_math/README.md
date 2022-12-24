
[![Arduino CI](https://github.com/RobTillaart/fast_math/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/fast_math/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/fast_math/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/fast_math/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/fast_math/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/fast_math/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/fast_math.svg?maxAge=3600)](https://github.com/RobTillaart/fast_math/releases)


# fast_math

Arduino library for fast math algorithms.


## Description

The fast_math library is a collection of algorithms that are faster 
than the default code. 
These algorithms are to be used when you are in a need for speed. 
Only tested on Arduino UNO as one of the "slower" boards.

**Warning:** verify if the algorithms works for your project. (no warranty).

Note: I am interested in your feedback e.g. results on other platforms.
Also improvements or other fast code is welcome. Please open an issue.

These algorithms are collected and improved over a long time, and started
with improving decades ago when computers were slower than an Arduino UNO.

Related libraries:

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
|:----------------|:------:|:-------:|:-------:|
|  dec2bcd (ref)  |  5.88  |   1.0   |  100 iterations
|  dec2bcd        |  1.04  |   4.8   |
|  dec2bcdRTC     |  0.88  |   5.7   |
|                 |        |         |
|  bcd2dec (ref)  |  5.96  |   1.0   |
|  bcd2dec        |  2.20  |   2.7   |


### DIV

- **void divmod10(uint32_t in, uint32_t \*div, uint8_t \*mod)**
function calculates both divide and modulo 10 faster than the default  / 10 and % 10.

This function is very useful for extracting the individual digits.
Typical use is print digits on a display, in a file or send them as ASCII.

Indicative performance Arduino UNO.

|  function  |   us   |  factor |  notes  |
|:-----------|:------:|:-------:|:-------:|
|  i % 10    |  38.2  |   1.0   |
|  i / 10    |  38.1  |   1.0   |
|  divmod10  |   9.1  |   4.1   | 

Backgrounder - https://forum.arduino.cc/t/divmod10-a-fast-replacement-for-10-and-10-unsigned/163586

Note: For every element of N (natural numbers) one could develop a divmodN() function. 


### PING

For distance sensors that work with a acoustic pulse, one often see the formula:
```cm = us / 29;``` to calculate the distance in cm.
In float it should be ``cm = us / 29.15;``` or ``cm = us * 0.0345;```
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
- **uint16_t ping2inch(uint16_t in)**
- **uint16_t ping2sixteenths(uint16_t in)**

32 bit interface
- **uint32_t ping2cm32(uint32_t in)**
- **uint32_t ping2mm32(uint32_t in)**


#### temperature corrected

- **float ping2cm_tempC(uint16_t duration, int Celsius)** temperature corrected speed of sound.
  - duration in us, temperature in Celsius.
  - this function is relative slow, a faster version is not tested.
- **float ping2inch_tempC(uint16_t duration, int Celsius)** temperature corrected speed of sound.


Indicative performance Arduino UNO.

|  function         |   us   |  factor |  notes  |
|:------------------|:------:|:-------:|:-------:|
|  us / 29  (ref)   |  38.1  |   1.0   | sos == 345 m/s  (integer only)
|  us \* 0.0345     |  18.5  |   2.0   |
|  ping2cm          |  3.08  |  12.4   | sos == 340 m/s
|  ping2mm          |  5.66  |   6.7   | sos == 340 m/s
|  ping2cm_tempC    |  36.8  |   1.0   | adds temperature correction.
|                   |        |         |
|  ping2inch        |  3.90  |   9.8   | not as exact as inches are rather large units
|  ping2sixteenths  |  8.11  |   4.8   | way more accurate than inches


### polynome

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

#### must
- update documentation
  - links, research?


#### should
- unit tests
  - or examples that test a lot.
- examples


#### could
- split up in multiple .h files, one per group.
  - fast_math.h includes all individual .h files.
- There are several divide functions to be included.
  div3(), div5(), div7(), div10(), mod10()
  These need more testing (range)
- constants?
  - GOLDEN_RATIO 1.61803398875

#### TODO Functions

DIV
- **uint16_t divmod10()** 16 bit overload version 
- **uint32_t div10(x, \*d)** would be a bit faster 
- **uint32_t mod10(x, \*m)** would be a bit faster too
- clock
  - **divmod24** == div3 >>3   (minutes to days)
  - **divmod12** == div3 >>2
  - **divmod60** == div15 >>2  of div5 div3 >>2 (seconds to minutes + minutes to hours)
- **div7** days - weeks.


PING
- **float ping2inch_tempF(uint16_t in, int Fahrenheit)**
- **uint32_t ping2inch(uint32_t in)** + sixteenth
- **uint32_t ping2sixteenth(uint32_t in)**


