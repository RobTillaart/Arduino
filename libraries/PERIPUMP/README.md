
[![Arduino CI](https://github.com/RobTillaart/PERIPUMP/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PERIPUMP/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PERIPUMP/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PERIPUMP/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PERIPUMP/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PERIPUMP/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PERIPUMP.svg?maxAge=3600)](https://github.com/RobTillaart/PERIPUMP/releases)


# PERIPUMP

Arduino library for peristaltic pump DFR0523 and compatibles.


## Description

VERY EXPERIMENTAL - AVR (UNO) only for now. 

The DFR0523 is a peristaltic pump which can be controlled by a PWM signal. 
This PWM (Pulse Width Modulation) is provided by the Arduino Servo library.
To hide the details of the Servo library and provide an easy to use interface, 
this PERIPUMP library gives control by setting the speed of the pump as a percentage
ranging from -100.0% .. 100.0%. 

The Servo library allows 900 steps for 0..100% so in theory the precision is 
approximately around 1 decimal.
In my first tests however with a 5Volt lab power supply, the pump only started 
to run around 60% at 5 volt and around 50% at 6 volt. 
Not measured if the behaviour was linear for the remaining 50%.

This implies that the actual flow depends on BOTH the voltage used and the percentage set.

The library provides also a minimalistic time registration. 
It measures how long the pump has been running since the start of the sketch or 
since the last call to **resetRunTime()**. 
This run time does not take into account the speed of the pump, a feature that might
be implemented in the future.

Note however that given that the pump only runs from 50-60% the output of **getRunTime()**
is not accurate.

Feedback on the library is welcome.


## Hardware schema

In my first tests the DFR0523 pump drew a current between 330 -360 mA at full speed.
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

### Base

- **PERIPUMP(uint8_t pumpPin)** constructor. pumpPin should be a PWM supporting pin.
- **void begin()** initialize the internal variables.
- **void stop()** set speed percentage to zero, effectively stop the pump.
Also stops the run time measurement counter.
- **void setPercentage(float percentage)** sets speed as a percentage of the full speed.
The range goes from -100.0 % .. +100.0 %.
  - If percentage == 0, the pump stops. 
  - Negative values set the pump in reverse.
  - Positive values set the pump in forward mode.
- **float getPercentage()** returns set speed: -100.0 % .. +100.0 %.


### RunTime

- **float getRunTime()** returns total seconds running since last reset / start.
- **float resetRunTime()** returns total seconds running since last reset / start.
Resets the internal time counter to zero again.


## Operation

The examples show the basic working of the functions.


#### 0.1.0 release

- low percentages < 50% do not work.


## Future

#### Must (next release)

- investigate a possible solution for the **lower 50% problem**.
  - map the range 1-100% only on the top 500 steps of the underlying Servo lib.
- initial speed as parameter for **begin()**
  - default percentage == 0 ?


#### Should

- update readme.md
- test more
- examples
- investigate flow rate == (non) linear 
- investigate startup behaviour (had some hickups)


#### Could

- investigate flow support
  - add **void setVolumePerSecond(float flow)** indication cm^3 / sec
  - at full speed only?
  - linear / non linear interpolatable (multiMap).
- investigate calibration process.
- add **void forward()** **void reverse()**
- add **void setInvert(bool true)** (if pump is connected reverse it would be easy to fix in software.


#### Won't (for now lowest prio)

- unit test possible?
  - No servo.h include fails.
  - compilation of examples works for UNO and RP2040 pico.
- add **void pump_ml(int ml)**  auto stop after X ml? possible?
- investigate difference per pump (one pump behaves different enough)
- investigate flow-accounting?
  - sum += time x speed - is that better?
  - two counters needed, one per direction

