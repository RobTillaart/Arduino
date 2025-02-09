
[![Arduino CI](https://github.com/RobTillaart/OUTPIN/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/OUTPIN/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/OUTPIN/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/OUTPIN/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/OUTPIN/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/OUTPIN.svg)](https://github.com/RobTillaart/OUTPIN/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/OUTPIN/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/OUTPIN.svg?maxAge=3600)](https://github.com/RobTillaart/OUTPIN/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/OUTPIN.svg)](https://registry.platformio.org/libraries/robtillaart/OUTPIN)


# OUTPIN

Arduino library for (AVR) faster and extended output pin.


## Description

**Experimental**

Arduino library for a faster output pin (AVR only) functions.
It can be used to replace **digitalWrite(pin, state)** when more performance
(AVR only) is needed. The trick is well known caching low level access. 

The interface of OUTPIN is straightforward. Besides setting a variable state it has 
optimized functions for **high()**, **low()** and **toggle()** which are all faster 
than equivalent code using digitalWrite().

The main reason to write this library was to optimize pulse lengths for a test setup.
This resulted in additional functions **pulseHigh()** and **pulseLow()**.
These have 255 steps between roughly 0.5 and 80 microseconds (step 0.3125 us).
Finally these is a **pulseOut(state, duration)** which is used for pulses above 80 us.

Do not forget a (strong) pullup resistor!

The library should work on other platforms, however the code is not optimized for them.
If you have (optimized) additions for other boards, please open a PR.

Feedback as always is welcome.


### Related

- https://github.com/RobTillaart/OUTPIN
- https://github.com/RobTillaart/PulsePattern
- digitalWriteFast()  TODO link


## Performance

See OUTPIN_performance.ino sketch, which is a mixed test for performance
and accuracy indication. The sketch has no correction for loop overhead 1000 calls.

Indicative time is per 1000 function calls, so digitalWrite() takes ~3.6 microseconds.

|  function       |  time us  |  factor   |  notes  |
|:----------------|:---------:|:---------:|:--------|
|  digitalWrite   |    3592   |   1.0 x   |  reference
|  set            |    2016   |   1.7 x   |
|  high           |    1136   |   3.1 x   |
|  low            |    1132   |   3.1 x   |
|  toggle         |    1136   |   3.1 x   |
|                 |           |           |
|  DW             |    6788   |   1.0 x   |  "pulseHigh" with digitalWrite() on UNO
|  pulseHigh()    |    1832   |   3.7 x   |  Actual pulse length is shorter (overhead).
|  pulseHigh(0)   |    2584   |   2.6 x   |
|  pulseHigh(20)  |    8864   |           |
|  step size      |  0.3140   |           |  tune pulseHigh() in these steps
|  pulseHigh(13)  |    6664   |   1.0 x   |   

Accuracy **pulseOut()**

|  range         |  accuracy         |  notes  |
|---------------:|:-----------------:|:-------:|
|    10 -   100  |  low              |  micros has step size 4 us.
|   100 -  1000  |  ~5.0% or better  |
|  1000 - 10000  |  ~0.5% or better  |



## Interface

```cpp
#include "OUTPIN.h"
```

### Constructor

- **OUTPIN(uint8_t pin, uint8_t state)** Constructor with initial state.

### Write functions

- **void set(uint8_t state)** sets pin state HIGH or LOW.
- **void high()** sets pin state HIGH.
- **void low()** sets pin state LOW.
- **void toggle()** reverses pin state.


### Pulse HIGH

- **void pulseHigh()** gives shortest possible HIGH pulse.
- **void pulseHigh(uint8_t nops)** extend HIGH pulse with NOPs.

_Note that different UNO's can have a slightly different clock speed,
which even may differ for different temperatures._

The formula for the pulse duration differs depending on compiler optimizations:
- (a) is nops a constant < 9  (known at compile time => optimized),  
   if nops > 8 timing is the same as (b).
- (b) is nops a (volatile) variable (unknown at compile time)

Indicative time of pulses in nano seconds, Arduino UNO R3, IDE: 1.8.19
Measured with oscilloscope, different resolutions 

|  nops  |   (b)   |   (a)   |  notes  |
|:------:|--------:|--------:|:--------|
|   0    |    880  |   688   |
|   1    |   1200  |   740   |
|   2    |   1504  |   820   |
|   3    |   1816  |   880   |
|   4    |   2120  |   940   |
|   5    |   2460  |  1000   |
|   6    |   2750  |  1060   |
|   7    |   3070  |  1120   |
|   8    |   3390  |  1190   |  almost equals column b with nops = 1
|   9    |   3700  |         |
|   10   |   4060  |         |
|   20   |   7120  |         |
|   50   |  16700  |         |
|   100  |  32600  |         |
|   150  |  48200  |         |
|   200  |  63800  |         |
|   250  |  79200  |         |
|   255  |  80800  |         |


The approximate formula for (a)  **time in ns = 687.0 + 63.5 x NOPs**  NOPs = 0..8

The approximate formula for (b)  **time in ns = 908.62 + 313.90 x NOPs**  MOPs 0..255

To calculate (b) the number of **NOPs = round((time - 908.62)/ 313.9)**.

Note: the actual pulse is smaller than the function duration as there is 
function call and some interrupt blocking overhead e.g. 159 NOPs => ~50 us.
To have a series of pulses have a look at the **pulsePattern** library.

Note: given that the "nopfactor" == 314 ns where 312.5 ns was expected might indicate
my UNO is a bit slow ~ 1.5/314 ==> 0.48%.


### Pulse LOW

- **void pulseLow()** gives shortest possible LOW pulse.
- **void pulseLow(uint8_t nops)** extend LOW pulse with NOPs.

Duration are assumed the same as for **pulseHigh(nops)**.

### PulseOut

- **void pulseOut(uint8_t state, uint16_t microseconds)** for longer pulses.
Note the resolution of the pulse generated by this function is about 1 microsecond.
The parameter microseconds should be > 75 for AVR UNO R3, to have reasonable accuracy.
Below 75 us one should use **pulseHigh()** or **pulseLow()**


Other boards might need tweak in the .cpp file.

See **OUTPIN_performance.ino** sketch for figures.


## Future

#### Must

- update documentation
- get performance figures
- add examples

#### Should

- make timing measurements with an oscilloscope to see actual pulse lengths.
- add unit tests?.

#### Could

- example e.g. DHT22 simulator.
- example pulse generator - potmeter to set pulse length?
- add nops parameter to tune **pulseOut()** duration ? add 0, 1 2 3 nops (0.3125 us)
- add **void multiPulseHigh(nopsHIGH, nopsLOW, times);**

```
void multiPulseHigh(nopsHIGH, nopsLOW, times)
{
  SREG
  //  local nopsH, nopsL
  while times--
    nopsH = nopsHIGH
    inline HIGH
    nopsL = nopsLOW
    inline LOW
  SREG
}
```


#### Wont



## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

