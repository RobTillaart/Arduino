
[![Arduino CI](https://github.com/RobTillaart/PERIPUMP/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PERIPUMP/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PERIPUMP/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PERIPUMP/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PERIPUMP/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/PERIPUMP.svg)](https://github.com/RobTillaart/PERIPUMP/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PERIPUMP/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PERIPUMP.svg?maxAge=3600)](https://github.com/RobTillaart/PERIPUMP/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/PERIPUMP.svg)](https://registry.platformio.org/libraries/robtillaart/PERIPUMP)


# PERIPUMP

Arduino library for peristaltic pump DFR0523 and compatibles.


## Description

**VERY EXPERIMENTAL - AVR (UNO) only for now** 

The DFR0523 is a peristaltic pump which can be controlled by a PWM signal. 
This PWM (Pulse Width Modulation) is provided by the Arduino Servo library.
To hide the details of the Servo library and provide an easy to use interface, 
this PERIPUMP library gives control by setting the speed of the pump as a percentage
ranging from -100.0% .. 100.0%. 

The Servo library allows 900 steps for 0..100% so **in theory** the precision is 
approximately around 1 decimal.
In my first tests however with a 5 volt lab power supply, the pump only started 
to run around 60% at 5 volt and around 50% at 6 volt.
Since 0.1.1 the mapping from 0..100% is done on the upper 500 steps of the servo,
to get the pump moving at lower percentages. This gives a practical precision of
around 0.2 % which is still very nice. 
Although there might still be low percentages that does not work on 5V, they might 
work on 6V, or when one goes from full speed to lower speed. (momentum differs).
At least there will be a larger "active range" for the percentages.

Not measured if the behaviour is linear.

The actual flow depends on BOTH the voltage used and the percentage set.

The library provides also a minimalistic time registration. 
It measures how long the pump has been running since the start of the sketch or 
since the last call to **resetRunTime()**. 
This run time does not take into account the speed of the pump, a feature that might
be implemented in the future.

Note however that given that the pump only runs from 50-60% the output of **getRunTime()**
is not accurate.

Feedback on the library is welcome.


## Hardware schema

In my first tests the DFR0523 pump drew a current between 330 -360 mA (5V) at full speed.
This implies an external power supply of 5 (or 6) volts is mandatory.

```
//  POWER SUPPLY       PROCESSOR       PUMP
//
//                        PWM----------PWM
//            GND---------GND----------GND
//
//  5-6 Volts VCC----------------------VCC 
//
```


## Interface

```cpp
#include "PERIPUMP.h"
```


### Base

- **PERIPUMP(uint8_t pumpPin)** constructor. pumpPin should be a PWM supporting pin.
- **void begin(float percentage = 0)** initialize the internal variables.
Default percentage = 0% == stop.
- **void stop()** set speed percentage to zero, effectively stop the pump.
Also stops the run time measurement counter.
- **void forward()** 100% forward.
- **void backward()** 100% backward.
- **void setPercentage(float percentage)** sets speed as a percentage of the full speed.
  - The percentage goes from -100.0 % .. +100.0 %.
  - If percentage == 0, the pump stops. 
  - Negative values set the pump in reverse.
  - Positive values set the pump in forward mode.
  - low values might not work.
- **float getPercentage()** returns set speed: -100.0 % .. +100.0 %.


### Invert (experimental / test)

- **void setInvert(bool flag = false)** inverts forward and backward to
easy swap direction without rebuilding hardware setup.
Default = false.
- **bool getInvert()** returns value invert flag.

### RunTime

- **float getRunTime()** returns total seconds running since last reset / start.
- **float resetRunTime()** returns total seconds running since last reset / start.
Resets the internal time counter to zero again.


## Operation

The examples show the basic working of the functions.


## Future

#### Must (next release)

- documentation
- investigate calibration process
  - function to set the ranges for percentage.
  - four values needed  500-VAR1    VAR2-2500
  - defaults for these variables.
  - could that be command line #defines?

#### Should

- test more
- examples
- investigate flow rate == (non) linear 
- investigate startup behaviour (had some hickups)

#### Could

- investigate flow support
  - add **void setVolumePerSecond(float flow)** indication cm^3 / sec
  - at full speed only?
  - linear / non linear interpolatable (multiMap).

#### Won't (for now lowest prio)

- unit test possible?
  - No servo.h include fails.
  - compilation of examples works for UNO and RP2040 pico.
- add **void pump_ml(int ml)**  auto stop after X ml? possible?
- investigate difference per pump (one pump behaves different enough)
  - calibration might solve this.
- investigate flow-accounting?
  - sum += time x speed - is that better?
  - two counters needed, one per direction
- **incr()** and **decr()** as they are direction dependant.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

