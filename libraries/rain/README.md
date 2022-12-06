
[![Arduino CI](https://github.com/RobTillaart/RAIN/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/RAIN/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/RAIN/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/RAIN/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/RAIN/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/RAIN/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/RAIN.svg?maxAge=3600)](https://github.com/RobTillaart/RAIN/releases)


# RAIN

RAIN is an Arduino library for a rain sensor (analog).


## Description

A rain sensor is a relative simple device. 
It measures the resistance of a number of wires when these are put in a liquid (water)
The device converts the resistance to a voltage typical 0 .. 5 Volt.
The more the wires are covered by the liquid, the higher the voltage.

The breakout I used to test also has a digital output, which goes HIGH if a certain
threshold (to be set with a potentiometer on the breakout) is reached.
The meaning / potential of this digital-out for the library needs to be investigated.

The library is EXPERIMENTAL as it needs more testing. 
(changes of the interface are definitely possible).


## Interface

- **RAIN(uint8_t port)** constructor. 
port is the internal analog port to use.
- **bool  begin(float maxVoltage, uint16_t maxSteps)** sets the ADC parameters. 
Allows to be changed runtime, e.g. if voltage fluctuates the math can be adapted by calling **begin()** again. 
Might be a separate **setVoltage()** is more efficient.
- **float raw(uint8_t times = 1)** makes 1 or more measurements and averages them.
returned value is the average number of ADC steps.
- **float read(uint8_t times = 1)** makes 1 or more measurements, averages them and convert the average to a voltage.
THis voltage is returned, and also cached for **percentage()** and **getLevel()**.

#### Analysis

- **float percentage()** returns the last **read()** to a percentage.
Note one needs to call read() again to get a new value as this uses a cached value.
- **float delta()** returns the delta voltage compared to previous read.
It give the first derivative of the signal. How fast does it rise.
- **bool setLevel(uint8_t nr, uint16_t millivolts)** allows a user to set 5 voltage levels in milliVolts.
- **uint8_t getLevel()**
Returns the level of the current cached voltage. 
See example.

The library allows the user to set 5 thresholds or levels for the **getLevel()** function.
These 5 levels can help to control behaviour at a certain level. 
Typical levels are almost empty, to almost full and full. 
The level do not need to be on a linear mapping like 20% steps, if your project need 
other levels you can define these.

Note it is possible to adjust the levels runTime with **setLevel()**


#### MultiMap

For a continuous mapping one can use the **MultiMap** library. 
It allows to map the voltage to any other useful unit as it can handle 
even non-linearities well.
See https://github.com/RobTillaart/MultiMap


## Operation

The examples show the basic working of the functions.


## Future

#### Must
- update documentation
  - links etc.
- add interrupt example for digital output capture.


#### Should
- optimizations
  - a lot of floats...==> more uint16_t millivolts?
- add examples.
- investigate possibilities of the digital output 
  - how to include
  - example (see above)
- improve the **percentage()** maxVoltage setter?
  - 2 different meanings of maxVoltage. For ADC and sensor out.
  - is the device linear? does percentage make sense if it is not?


#### Could
- add unit-tests
- make the number of levels configurable
  - dynamic array allocation.?
- **float readExt(float voltage)** for external ADC
- investigate level-changed "event"
- investigate: **getLevel()** should it do a read()?
  - **setForcedRead(bool flag)** + getter
- investigate "a scale of wetness"
- investigate
  - different salinity
  - different liquids? which?
  - how linear is the device?
- **incrLevel(nr, amount = 1)** + **decrLevel(nr, amount = 1)**
  to allow easier runtime tuning

#### Won't
- example with multiMap
  - see multiMap library.

