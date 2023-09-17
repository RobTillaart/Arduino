
[![Arduino CI](https://github.com/RobTillaart/DRV8825/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DRV8825/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DRV8825/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DRV8825/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DRV8825/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DRV8825.svg)](https://github.com/RobTillaart/DRV8825/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DRV8825/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DRV8825.svg?maxAge=3600)](https://github.com/RobTillaart/DRV8825/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DRV8825.svg)](https://registry.platformio.org/libraries/robtillaart/DRV8825)


# DRV8825

Arduino library for DRV8825 stepper motor driver.


## Description

**DRV8825** is a library for DRV8825 stepper motor driver.

**Warning: experimental** needs testing.

The DRV8825 stepper motor library controls a stepper motor with
a direction signal and a step pulse.
The library has a default pulse length of 2 us however this can be 
adjusted to the specific requirements of the motor.

The library will probably work for similar controllers.
This is not tested. If you have some working, please let me know.


## Hardware connection

See datasheet.


## Interface

```cpp
#include "DRV8825.h"
```

### Constants

```cpp
//  setDirection
const uint8_t DRV8825_CLOCK_WISE         = 0;  //  LOW
const uint8_t DRV8825_COUNTERCLOCK_WISE  = 1;  //  HIGH
```

### Constructor

- **DRV8825()** Constructor.
- **bool begin(uint8_t DIR, uint8_t STEP, uint8_t EN = 255, uint8_t RST = 255, uint8_t SLP = 255)** 
set the direction pin and step pin.
Both pins are set to LOW. For direction this means DRV8825_CLOCK_WISE.
Optional the enable, reset and sleep pin can be set.
If these are set to 255 the related functions won't do anything.


### Direction

To define in which way the motor will turn.

- **bool setDirection(uint8_t direction = DRV8825_CLOCK_WISE)**
switch direction between DRV8825_CLOCK_WISE (0 = default) or
DRV8825_COUNTERCLOCK_WISE (1).
Returns false for other values.
- **uint8_t getDirection()** returns DRV8825_CLOCK_WISE (0) or
DRV8825_COUNTERCLOCK_WISE (1).


### Steps and position

- **void setStepsPerRotation(uint16_t stepsPerRotation)** specifies the steps per rotation for the specific stepper motor.
If set to zero, the steps and position will not be updated/valid.
Note this value depends on pins M0, M1 and M2.
- **uint16_t getStepsPerRotation()** returns the value set before
or zero default.
- **void step()** The workhorse, will give a pulse on the STEP pin.
This also updates the position and the steps counters.
- **uint32_t resetSteps(uint32_t s = 0 )** to reset the steps counter,
default to zero. 
Returns the last value of internal steps counter.
- **uint32_t getSteps()** returns the steps made since start of the program or the last **resetSteps()**.
Its purpose is  to have an indication of usage (wear and tear).
- **bool setPosition(uint16_t position = 0)** to calibrate the position of the motor. Default value is zero.
Works only if stepsPerRotation > 0.
Returns false if position > stepsPerRotation.  
Note: it does not rotate the motor to a position.  
Note: there is no relation between position and steps.
- **uint16_t getPosition()** returns the position which is kin the range 0 .. stepsPerRotation - 1.
This value can be converted to an angle in degrees or radians.


#### Some math

```cpp
//  angle in degrees.
float angle = position * (360.0 / stepsPerRotation);

//  angle in radians.
float angle = position * (2.0 * PI / stepsPerRotation);

//  wear and tear math.
float rotations = getSteps() * (1.0 / stepsPerRotation);
```

Note the behaviour of steps changed in 0.1.1.
This is done as the library added the position functions.


### Configuration

- **void setStepPulseLength(uint16_t pulseLength = 2)** configures the pulse length of one step.
This is defined in microseconds, default is 2 which is almost the 1.9 from the datasheet. 
Normally these need not to be changed.
- **uint16_t getStepPulseLength()** returns the set value in microseconds. 
Default the value = 2.


### Enable (EN)

- **bool enable()** sets the enable line LOW.
Returns false if enable line is not defined.
- **bool disable()** sets the enable line HIGH.
Returns false if enable line is not defined.
- **bool isEnabled()** reads back the line state.
True means enabled (or enable line not defined)
False means disabled.

After **enable()** the system needs 650 ns before **step()**
can be called. See 7.6 Timing Requirements.


### Reset (RST)

- **bool reset()** sends a reset pulse to the device.
Returns false if reset line is not defined.


### Sleep (SLP)

- **bool sleep()** sets the enable line LOW.
Returns false if sleep line is not defined.
- **bool wakeup()** sets the enable line HIGH.
Returns false if sleep line is not defined.
- **bool isSleeping()** reads back the line state.
True means enabled.

After **wakeup()** the system needs **1700 us** before **step()**
can be called. See 7.6 Timing Requirements.


### MicroSteps

The pins M0, M1 and M2 are to be used to set micro steps.
This library does not allow them to be set from code as
normally these won't change in a project.

|  STEP MODE  |  M2  |  M1  |  M0  |
|:-----------:|:----:|:----:|:----:|
|    full     |   0  |   0  |   0  |
|    half     |   0  |   0  |   1  |
|    1/4      |   0  |   1  |   0  |
|    1/8      |   0  |   1  |   1  |
|    1/16     |   1  |   0  |   0  |
|    1/32     |   1  |   0  |   1  |
|    1/32     |   1  |   1  |   0  |
|    1/32     |   1  |   1  |   1  |

Check datasheet for details.


### Fault (FLT)

The FLT pin indicates that an error has occurred. 
The library does not monitor this pin as that would need a background process.
The user is advised to check this pin at regular intervals
or connect the FLT pin to an interrupt pin of the processor. 

- **LOW**  == fault condition (overtemp, overcurrent)
- **HIGH** == OK

The device does not provide means to interpret the type of 
error, but one could at least call **disable()**.

Check datasheet for the details.


## Operational

The minimal code is:

```cpp
DRV8825 stepper;

void setup()
{
  Serial.begin(115200);
  ...
  stepper.begin(4, 5);  // direction + step pin
  stepper.setDirection(DRV8825_CLOCK_WISE);
  ...
}

void loop()
{
...
  stepper.step();
...
}
```

See examples.


## Future

Ideas are kept here so they won't get lost.
Some will only be worked on if requested and time permits.

#### Must

- test test test
- add examples
- update documentation
- investigate other pins
  - decay mode          8.3.3 there are 3 modi)
  - other?

#### Should

- step(uint16_t steps)
  - multiple steps in one call.
  - blocking
  - max 1 rotation?
  - optimize "position admin"
- should begin return bool?

#### Could

- stepCW() + stepCCW()
- base class STEPDIR
  - only when needed?
  - 8825 as derived? or as base class?
  - which others are similar?
    - A4988, DRV8824, more?

#### Wont

- left() + right();
- if stepsPerRotation is set to zero, should pos be set to zero?
  - NB it will not be updated any more.
  - leaving it as is, could allow "creative calibration"
- investigate controlling a DRV8825 with an PCF8574
  - pins needed (M0..M2, SLP, RST, EN, DIR, STEP)
  - first need a decent basic library.
  - would be a class on its own.
- gotoPosition(pos)..
  - needs steps(n) above? for loop!
  - shortest angle/path or via current CW/CCW mode.
  - user can implement his own strategy.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

