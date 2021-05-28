
[![Arduino CI](https://github.com/RobTillaart/PID_RT/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PID_RT/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PID_RT.svg?maxAge=3600)](https://github.com/RobTillaart/PID_RT/releases)

# PID_RT

Arduino library for PID controller


## Description

The PID_RT class allows the user to instantiate a PID controller.


## Interface

### Constructor

- **PID_RT()** minimal constructor.
- **PID_RT(float sp, float Kp, float Ki, float Kd)** constructor that sets minimal parameters to get started.


### Core

- **void reset()** resets internals to startup.
- **void setPoint(float sp)** sets setPoint, that needs to be reached.
- **float getSetPoint()** read setPoint.
- **bool  compute(float input)** does one iteration of the PID controller. Returns **true** after calculation. Returns **false** if not computed, either stop flag or not yet time to calculate.
- **float getOutput()** get the last calculated output value. 
- **bool  setK(float Kp, float Ki, float Kd)** Set the initial P I D parameters as a group.


### Start Stop

- **void start()** // enable the PID controller to compute new output values.
- **void stop()**  disable the PID controller **compute()**.
- **bool isRunning()**


### Additional parameters

- **bool setInterval(uint32_t interval)** set the interval between 2 **compute()** calls. Returns **true** if changed, otherwise **false**.
- **uint32_t getInterval()** read back setting
- **void setOutputRange(float rmin, float rmax)** tune the output range, default 0..100
- **float getOutputMin()** read back setting
- **float getOutputMax()** read back setting
- **void setReverse(bool reverse)** reverse behavior, seldom needed.
- **bool getReverse()** read back the setting.
- **bool setKp(float Kp)** runtime updates are allowed - at your own risk.
- **bool setKi(float Ki)** runtime updates are allowed - at your own risk.
- **bool setKd(float Kd)** runtime updates are allowed - at your own risk.
- **float getKp()** read back setting.
- **float getKi()** read back setting.
- **float getKd()** read back setting.
- **void setPropOnInput()** default.
- **void setPropOnError()** alternative.
- **bool isPropOnInput()** read back setting.
- **bool isPropOnError()** read back setting.


### debugging calls

Might be obsolete in future.

- **float getInput()** read last input.
- **float getLastError()** read the last error.
- **uint32_t getLastTime()** read the last.


## Operations

See examples.

