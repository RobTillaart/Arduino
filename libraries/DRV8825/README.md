
[![Arduino CI](https://github.com/RobTillaart/DRV8825/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DRV8825/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DRV8825/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DRV8825/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DRV8825/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DRV8825/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DRV8825.svg?maxAge=3600)](https://github.com/RobTillaart/DRV8825/releases)


# DRV8825

Arduino library for DRV8825 stepper motor driver.


## Description

**DRV8825** is a library for DRV8825 stepper motor driver.

**Warning: experimental**

The 8825 stepper motor driver control a stepper motor with
a direction signal and a step pulse. 


## Hardware connection

See datasheet.


## Interface


### Constants

```cpp
//  setDirection
const uint8_t DRV8825_CLOCK_WISE         = 0;  //  LOW
const uint8_t DRV8825_COUNTERCLOCK_WISE  = 1;  //  HIGH
```

### Constructor

- **DRV8825()** Constructor.

 with steps per rotation as parameter.
This parameter is optional and if set to zero, steps will not be counted.
- **bool begin(uint8_t dirPin, uint8_t stepPin)** set the direction and step pin.
Both pins are initially set to LOW.


### Direction

To define in which way the motor will turn.

- **void setDirection(uint8_t direction = DRV8825_CLOCK_WISE)** idem.
- **uint8_t getDirection()** returns DRV8825_CLOCK_WISE (0) or
DRV8825_COUNTERCLOCK_WISE (1).


### Steps

- **void setStepsPerRotation(uint16_t stepsPerRotation)** specifies the steps per rotation for the specific stepper motor. 
If set to zero, the steps will not be counted.
- **uint16_t getStepsPerRotation()** returns the value set before
or zero default.
- **void step()** The workhorse, will give a pulse on the STEP pin.
- **int32_t resetSteps(int32_t s = 0; )** 
- **int32_t getSteps()** returns the sum of the steps made. 
CW = + and CWW = - so one can go back to a relative position.

The combination getSteps with stepsPerRotation indicates the position of the motor.


## Operational

The base functions are:

```cpp
DRV8825 stpr;

void setup()
{
  Serial.begin(115200);
  ...
  stpr.begin(4, 5);  // direction + step pin
  stpr.setDirection(DRV8825_CLOCK_WISE);
  ...
}

void loop()
{
...
  stpr.step;
...
}
```

See examples.


## Future

Ideas are kept here so they won't get lost.

- redo interface
  - stepCW() + stepCCW();  or just CW(); and CCW();
  - left() + right();
  - step(nr of steps)  blocking!!
- add position
  - = steps % steps/rotation
- base class DIRSTEP
  - 8825 as derived?
  - other too
