
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
- adjust the K parameters (pid) runtime.
- stop / start computing runtime.

(to be elaborated)


### Some PID background

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
- **bool compute(float input)** does one iteration of the PID controller. See below.
Returns **true** after a calculation is done.
Returns **false** if not computed, either due to stop flag or not yet time to do the calculation.
See PID_ENABLE_INTERVAL_CHECK below.
- **float getOutput()** get the last calculated output value.
- **bool setK(float Kp, float Ki, float Kd)** Set the initial **P I D** parameters as a group.
Overwrites the values set in the constructor.


### PID_ENABLE_INTERVAL_CHECK

Since 0.1.8 a compile time flag **PID_ENABLE_INTERVAL_CHECK** has been added. (See #8). 
This flag allows the user to enable or disable the interval check in **compute()**.
Default the flag is enabled, and the function will check if the interval set has passed,
if not, it will return false, true otherwise.

If the **PID_ENABLE_INTERVAL_CHECK** is set to false, the user has to ensure the interval 
periodicity, e.g. by using a hardware timer, external interrupt, RTC or otherwise.

Note that using a hardware timer can improve the accuracy of the PID control.

See the PID_RT.h file.


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


### Debugging

- **float getInput()** read last input.
- **float getLastError()** read the last error.
- **uint32_t getLastTime()** get the last time **compute()** was called.

Note the lastTime value is incremented with **interval** every iteration so it 
may have an offset with respect to the actual time. 
This method is chosen as it is almost guarantees that no iterations will be missed.
To improve the timing of compute() calls, the user could use e.g. a hardware timer 
to call compute() at very regular intervals.
See also PID_ENABLE_INTERVAL_CHECK above.


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
- investigate if compute() can determine the interval
  - ```interval = millis() - lastTime;```
  - need to know start/stop moment to get the math right.

#### Could

- move all code to .cpp

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

