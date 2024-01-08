
[![Arduino CI](https://github.com/RobTillaart/PID_RT/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PID_RT/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PID_RT/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PID_RT/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PID_RT/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/PID_RT.svg)](https://github.com/RobTillaart/PID_RT/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PID_RT/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PID_RT.svg?maxAge=3600)](https://github.com/RobTillaart/PID_RT/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/PID_RT.svg)](https://registry.platformio.org/libraries/robtillaart/PID_RT)


# PID_RT

Arduino library for PID controller.


## Description

The PID_RT class allows the user to instantiate a PID controller.

This library allows one to 
- adjust the K parameters runtime.
- stop / start computing runtime.

(to be elaborated)


#### Some PID background

- https://en.wikipedia.org/wiki/PID_controller
- https://www.ni.com/nl-nl/innovations/white-papers/06/pid-theory-explained.html
- https://www.youtube.com/watch?v=wkfEZmsQqiA

E-book
- https://www.elektor.nl/pid-based-practical-digital-control-with-raspberry-pi-and-arduino-uno-e-book

WOKWI
- https://forum.arduino.cc/t/pid-with-simulated-heater-or-motor/1093539


## Interface

```cpp
#include "PID_RT.h"
```

### Constructor

- **PID_RT()** minimal constructor.
- **PID_RT(float sp, float Kp, float Ki, float Kd)** constructor that sets minimal parameters to get started.


### Core

- **void reset()** resets internals to startup (Kp == Ki == Kd == 0).
- **void setPoint(float sp)** sets the setPoint, that needs to be reached.
- **float getSetPoint()** read back the setPoint.
- **bool compute(float input)** does one iteration of the PID controller. 
Returns **true** after a calculation is done. 
Returns **false** if not computed, either due to stop flag or not yet time to do the calculation.
- **float getOutput()** get the last calculated output value. 
- **bool setK(float Kp, float Ki, float Kd)** Set the initial **P I D** parameters as a group.
Overwrites the values set in the constructor.


### Start Stop

- **void start()** enable the PID controller to **compute()** new output values.
- **void stop()** disable the PID controller, see **compute()**.
- **bool isRunning()** return the enable/disable flag.


### Behaviour parameters

- **bool setInterval(uint32_t interval)** set the interval between two **compute()** calls. 
Returns **true** if changed, otherwise **false**.
- **uint32_t getInterval()** read back interval set.
- **void setOutputRange(float rangeMin, float rangeMax)** tune the output range, default 0..100
- **float getOutputMin()** read back setting rangeMin.
- **float getOutputMax()** read back setting rangeMax.
- **void setReverse(bool reverse)** reverse behaviour, seldom needed.
- **bool getReverse()** read back the setting.


### K-parameters

- **bool setKp(float Kp)** runtime updates are allowed - at your own risk.
- **bool setKi(float Ki)** runtime updates are allowed - at your own risk.
- **bool setKd(float Kd)** runtime updates are allowed - at your own risk.
- **float getKp()** read back setting.
- **float getKi()** read back setting.
- **float getKd()** read back setting.


### Proportional

- **void setPropOnInput()** this is default behaviour.
- **void setPropOnError()** alternative.
- **bool isPropOnInput()** read back setting.
- **bool isPropOnError()** read back setting.


### debugging calls

- **float getInput()** read last input.
- **float getLastError()** read the last error.
- **uint32_t getLastTime()** get the last time **compute()** was called.
Note this value is incremented with **Interval** every iteration so it 
may have some offset of the actual time. This is chosen as this way it is 
almost sure that no iterations are missed. 


## Operations

See examples and 
- https://wokwi.com/projects/356437164264235009  (thanks to drf5n)


## Future

#### Must

- update / improve documentation
- more testing

#### Should

- investigate if it works as PI or P controller too.
  - PI as derived or base class?
- add examples to test more
- improve unit test

#### Could

- add reference to PID book / website?
- move all code to .cpp

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

