
[![Arduino CI](https://github.com/RobTillaart/RAIN/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/RAIN/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/RAIN/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/RAIN/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/RAIN/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/RAIN.svg)](https://github.com/RobTillaart/RAIN/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/RAIN/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/RAIN.svg?maxAge=3600)](https://github.com/RobTillaart/RAIN/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/RAIN.svg)](https://registry.platformio.org/libraries/robtillaart/RAIN)


# RAIN

RAIN is an Arduino library for a rain sensor (analog).


## Description

**Experimental**

A rain sensor like the **FC-37, YL-83, HM-RD** a.o. is a relative simple device.
It measures the resistance between wires when these are put in a liquid, water or in the ground.
The device converts the resistance to a voltage typical 0 .. 5 Volt.
The more the wires are covered by the liquid, the lower the voltage.
0.0 Volt is WET, and a high voltage is DRY.

The breakout (LM393 comparator) I used to test also has a digital output,
which goes LOW if a threshold (to be set with a potentiometer on the breakout) is reached.

The library is EXPERIMENTAL as it needs more testing.
Changes of the interface are definitely possible.


## Hardware connection

Typical connection

```
      Processor             LM393             SENSOR FC-37
   +-------------+      +----------+     +---------------------+
   |             |      |          |     |                     |
   |         GND |----->| GND      |     |                     |
   |    powerPin |----->| 5V       |-----|                     |
   |    analogIn |<-----| AO       |     |                     |
   |             |      |          |-----|                     |
   |  digital in |<-----| DO       |     |                     |
   |             |      |          |     |                     |
   +-------------+      +----------+     +---------------------+

```


## Interface

```cpp
#include "rain.h"
```

- **RAIN(uint8_t analogPort, uint8_t powerPin = 255)** constructor.
analogPort is the internal analog port to use.
powerPin is optional, but recommended.
The default 255 means **NO** powerPin selected.
- **bool begin(float maxVoltage, uint16_t maxSteps)** sets the ADC parameters.
Allows to be changed runtime, e.g. if voltage fluctuates the math can be adapted by calling **begin()** again.
Might be a separate **setVoltage()** is more efficient.
- **float raw(uint8_t times = 1)** makes 1 or more measurements and averages them.
returned value is the average number of ADC steps.
- **float read(uint8_t times = 1)** makes 1 or more measurements, averages them and convert the average to a voltage.
This voltage is returned, and also cached for **percentage()** and **getLevel()**.


#### powerControl

Will only work if the **powerPin** is set in the constructor.

- **void powerOn()** switch the sensor on.
- **void powerOff()** switch the sensor off.
- **void setPowerDelay(uint8_t powerDelay = 100)** delay in microseconds
in powerOn() to stabilize the rain sensor.
Default is 100 microseconds.
- **uint8_t getPowerDelay()** returns the set value.

The powerPin is used to switch the LM393 ON and OFF so the sensor is powered
only when the sensor is read.
This reduces corrosion and minimizes the usage of energy.
Note: when the power is OFF, the digital-out cannot be used e.g. for interrupts.
So check what your project needs.

Note: the powerOn() default delays for 100 us to give the LM393 time to stabilize.
Adjust this time if you want to optimize performance, power consumption or corrosion.
Values can be 0 .. 255.


#### Analysis

- **void setDryReference(float dryRef)** used to calibrate the voltage when the sensor is dry.
Use **read()** to read / calibrate the voltage when the sensor is dry.
If not explicitly set, the max ADC voltage os used.
- **void getDryReference()** returns the set value.
- **float percentage()** returns the last **read()** to a percentage.
Note one needs to call read() again to get a new value as this uses a cached value.
- **float delta()** returns the delta voltage compared to previous read.
It give the first derivative of the signal. How fast does it rise.
- **bool setLevel(uint8_t nr, uint16_t millivolts)** allows a user to set 4 voltage levels in milliVolts.
- **uint8_t getLevel()**
Returns the level of the current cached voltage.
See example.

The library allows the user to set 4 thresholds or levels for the **getLevel()** function.
These 4 levels + 1 zero level can help to control behaviour of a system at a certain level.
Typical levels are almost empty, almost full and full.
The level do not need to be on a linear mapping like 20% steps, if your project need
other levels you can define these.

Note it is possible to adjust the levels runTime with **setLevel()**


#### MultiMap

For a continuous mapping one can use the **MultiMap** library.
It allows to map the voltage to any other useful unit as it can handle
even non-linearities well.
See https://github.com/RobTillaart/MultiMap


## Operation

The examples show the basic working of the functions of the library.

The rain sensor can be used in different types of projects.
Every project has a typical orientation of the sensor.

|  project         |  orientation     |  measurement  |
|:-----------------|:----------------:|:-------------:|
|  rain sensor     |  angle e.g. 45°  |  polling
|  leak detection  |  horizontal      |  interrupt - digital OUT
|  water level     |  vertical        |  polling

For other applications it depends.


## Future

#### Must

- update documentation
  - links etc.

#### Should

- optimizations
  - a lot of floats...==> more uint16_t millivolts? (0.2.0)
- getLevel() split into level() + getLevel(nr);  //  semantics
  - breaking change == 0.2.0
  - level(0) should be settable too

#### Could

- add unit-tests
- **float readExt(float voltage)** for external ADC
  - See **ACS712** library how this can be done.
- investigate: **getLevel()** should it do a read()?
  - **setForcedRead(bool flag)** + getter
- investigate "a scale of wetness"
- investigate
  - different salinity
  - different liquids? which?
  - how linear is the device?

#### Won't (unless requested)

- example with multiMap
  - see multiMap library.
- **incrLevel(nr, amount = 1)** + **decrLevel(nr, amount = 1)**
  to allow easier runtime tuning
- investigate level-changed "event"
  - user should poll ==> keeps the lib simple.
- make the number of levels configurable
  - dynamic array allocation.?


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

