
[![Arduino CI](https://github.com/RobTillaart/RAIN/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/RAIN/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/RAIN/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/RAIN/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/RAIN/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/RAIN/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/RAIN.svg?maxAge=3600)](https://github.com/RobTillaart/RAIN/releases)


# RAIN

Arduino library for rain sensor (analog).


## Description

The RAIN sensor is a relative simple device. 
It measures the resistance of a number of wires when these are put un a liquid (water)
The device converts that resistance to a voltage 0..VCC - typical 5V.
The more the wires are covered by the liquid, the higher the voltage.

Furthermore the breakout I used to test had a digital output, which becomes HIGH if a certain
threshold (to be set with a potentiometer) was reached.
The meaning / potential of this digi-out for the library is not clear yet.

The library is EXPERIMENTAL as it needs more testing. 
(changes of the interface are possible).


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
- **bool setLevel(uint8_t nr, float voltage)** allows a user to set 5 voltage levels. 
- **uint8_t  getLevel()**
Returns the level of the current cached voltage. 
See example.


#### MultiMap

One might use the **MultiMap** library to map the voltage read to some
other, more useful unit.
See https://github.com/RobTillaart/MultiMap


## Operation

The examples show the basic working of the functions.


## Future

#### Must
- update documentation
  - a lot, 
  - links etc.
- test more
  - different salinity
  - different liquids? which?
  - how linear is the device?


#### Should
- investigate "a scale of wetness"
- add unit-tests
- add examples.
  - interrupt example for digital output capture.
  - multimap example 
- investigate possibilities of the digital output 
  - how to include
  - example (see above)
- **float readExt(float voltage)** for external ADC


#### Could


#### Won't


