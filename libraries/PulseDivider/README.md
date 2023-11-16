
[![Arduino CI](https://github.com/RobTillaart/PulseDivider/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PulseDivider/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PulseDivider/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PulseDivider/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PulseDivider/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/PulseDivider.svg)](https://github.com/RobTillaart/PulseDivider/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PulseDivider/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PulseDivider.svg?maxAge=3600)](https://github.com/RobTillaart/PulseDivider/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/PulseDivider.svg)](https://registry.platformio.org/libraries/robtillaart/PulseDivider)


# PulseDivider

Arduino library to divide a pulse stream with a fraction factor.


## Description

**Experimental**

The PulseDivider (PD) is an **experimental** library to be used to scale down pulse streams.
The most important feature is that the library can reduce a pulse stream with fractions.
This means that e.g. for every 17 input pulses there are 3 output pulses,
or for every 355 input pulses it gives 113 output pulses.
Of course one can reduce the pulse stream with **n to 1**.

The library **polls** for an input pulse and if there is one, the math is done and a decision 
is made if there will be an output pulse or not. This approach has a number of consequences.
Most important is that the output pulses are definitely **not equidistant**.
Furthermore as the library polls the input for pulses, the timing is not as exact as 
when it would be interrupt driven.

As the library is generic it will always be slower than a dedicated divide strategy and
definitely slower than dedicated hardware.

Not being interrupt driven is by choice to keep the (first versions of) the library portable
over different boards. There is therefore no optimization done for any board.
The polling also causes the library to be suitable for a limited range of frequencies.
On the other hand, this is what makes the library very portable.

The library allows to instantiate multiple PulseDivider objects, so one can run a 10 -> 1 
divider besides a 13 -> 5 divider or more. 
However due to the polling implementation the range of frequency used per input will drop.

Finally it should be noted that multiple objects can share same input pin.
This is not optimized either but it allows to have one input and have e.g. both a 10 -> 1 
divider and a 100 -> 1 divider running side by side.
One could use this library to have a single 1 Hz input and divide it into a minutes
output and an hours output.

The library is still **experimental** and under test, so as always feedback is welcome. 


#### Tests

Indicative maximum input frequencies.
(based upon **PulseDivider_multi.ino**)

**version 0.1.0**

For the Arduino UNO the maximum sum of polling is around 62 KHz, so in practice 
assume 50 KHz. As the signal has to restore from HIGH to LOW the 
effective input frequency is max 25 KHz.
One has to divide this "range" over the number of parallel running objects. 
This can be done with equal load or with an optimized schedule.
(See example.)

Tested with a 1 KHz base signal (from a scope) in combination with the example
**PulseDivider_same_input.ino** which divides the input signal by 10, 100 and 1000.
This setup worked very well.

For ESP32 the maximum sum of polling is around 430 KHz, so in practice 400 KHz, 
so the effective input frequency is max 200 KHz. 
However in the first tests the ESP32 seems to scale "very optimistically", so 
this need to be investigated in more detail.

**Version 0.1.1**

Optimized scanning for change and optimized resetting the output.
This means for all that the system is more reactive.
This does not mean that higher frequencies can be handled correctly.

Actual performance is more complex and depends on ratio and duration.

- For the Arduino UNO the maximum check frequency (idle state) is around 190 KHz.
- For ESP32 the maximum check frequency (idle state) is around 4600 KHz.
The scaling for checking multiple dividers now looks far more linear (good).


**Conclusion**

In short, it is strongly advised to run your own tests to see if the library
meets your performance and quality needs. 
As said before the numbers above are indicative at best.


**TODO**

test with calibrated pulse generator and highest division rate 1 -> 1 .
And rewrite this section.


#### Accuracy

The output pulses are not distributed equally as an output pulse is only
generated when there is an input pulse and an output pulse is "lagging".

In the first tests the library seems to work well, however more testing is needed. 


#### Related

- https://github.com/RobTillaart/PulsePattern


## Interface

```cpp
#include PulseDivider.h
```


#### Constructor

- **PulseDivider(uint8_t inPin, uint8_t outPin, uint16_t inCount, uint16_t outCount, uint32_t duration = 1, uint8_t edge = RISING, bool invert = false)**
  - Define input pin and output pin.
  - inCount and outCount define the ratio, (8,1) defines 8 input pulses will have 1 output pulse.
    These numbers may be a fraction e.g. (355, 113) = 3.141592...  
    The user must take care that inCount >= outCount > 0.
    The range for inCount can be 1..65534 max, the sum of inCount and outCount should not exceed 65535.
    Typically both are less than 1000.
  - duration, default 1 is the number of micros the output pulse will minimally take. 
    The accuracy is board dependent. 
  - edge is RISING or FALLING (same as interrupt parameter).
  - invert, inverts the output pulse with respect to the input pulse.

The PulseDivider can do an 65534 to 1 reduction. 


#### Getters / Setters

See description Constructor.

- **void setInPin(uint8_t inPin)** set or change the input pin (runtime).
- **uint8_t getInPin()** returns the set input pin.
- **void setOutPin(uint8_t outPin)** set or change the output pin (runtime).
- **uint8_t getOutPin()** returns the set output pin.
- **void setRatio(uint16_t inCount, uint16_t outCount = 1)** set the ratio between
input pulses and the output pulses. inCount >= outCount > 0.
The range for inCount can be 1..65534 max, the sum of inCount and outCount should not exceed 65535, 
Typically both are less than 1000.
- **float getRatio()** returns float(inCount)/outCount;
- **void setDuration(uint32_t duration)** set the duration of the pulse.
Note the unit is microseconds.
- **uint32_t getDuration()** returns the set duration.
- **void setEdge(uint8_t edge)** sets the "trigger" edge, RISING or FALLING.
- **uint8_t getEdge()** returns the set trigger.
- **void setInvert(bool invert)** inverts the output pulse with respect to the input pulse.
- **bool getInvert()** returns the set flag.
- **uint16_t getCounter()** returns the internal counter (for debugging).


#### Control

The pulseDivider can be started or stopped in software,
and the state can be requested.
Note that running other code besides the PulseDivider object(s)
scales down the max frequency the library can handle.

- **void start()** needed to get the PulseDIvider started.
Default the PulseDivider is not running.
- **void stop()** stops the PulseDivider, will also bring the
output to "default" state LOW (unless inverted).
- **bool isRunning()** returns true if running .


#### Worker

- **void check()** Call as often as possible as this worker does the
polling, math and calls **doPulse()** when an output pulse is needed. 
- **void doPulse()** start a pulse on the output line.


## Future

#### Must

- update / rewrite documentation
- test with (calibrated) hardware.

#### Should

- performance measurements
- test different platforms, configurations, ratios etc.
- optimize math possible? (16 bit instead of 32 bit for UNO).
- for many pulses - **PulseDivider(32 bit counters)**
  - allow e.g. 100000 to 1 or even 1000000 to 1 or more.
  - separate PulseDivider32 class?

#### Could

- add examples
- extend unit tests
  - getters/setters
- interrupt based ?
  - derived class ?
  - platform specific ?
- **uint8_t check()** return status of in as that is most often polled?
  - can this give a performance gain?
- make inCount and outCount 32 bit? even finer fractions.
  - would slow it down
  - would 8 bit make it faster?

#### Won't (unless requested)


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,




