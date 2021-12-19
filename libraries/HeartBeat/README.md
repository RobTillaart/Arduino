
[![Arduino CI](https://github.com/RobTillaart/HeartBeat/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/HeartBeat/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/HeartBeat/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/HeartBeat/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/HeartBeat/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/HeartBeat/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/HeartBeat.svg?maxAge=3600)](https://github.com/RobTillaart/HeartBeat/releases)


# HeartBeat

Arduino library for a HeartBeat with frequency and duty cycle.


## Description

The heartbeat library offers a simple HeartBeat by sending pulses to 
a digital pin. Typical usage is to blink a (built in) LED as indicator 
a program is still alive.

The library uses no hardware timer and is based upon micros() so the user 
is responsible to call the **beat()** function as often as needed or
better even more. 

The library allows to set the frequency runtime, so the HeartBeat
can be used as a first level debugging tool. Different frequencies can indicate
a different state of the program or a different level of some sensor.
No heart beat indicates the program is stuck or blocked.

For more complex patterns, please check my pulsePattern library.


## Interface

The interface consists of the following functions:

- **HeartBeat()** constructor
- **void begin(uint8_t pin, float frequency)** to configure the HeartBeat. 
The default frequency is 1.0
- **void setFrequency(float frequency)** change the frequency of the pulsing.  
Will not enable or disable the HeartBeat.  
Must be > 0.001 otherwise it will be constrained to 0.001.
On the upper side values beyond 10 Hz are hard for humans but are allowed.
- **void setDutyCycle(float dutyCycle = 50)** duty cycle in percentage time HIGH.
Must be between 0.00 and 100.0.  A value of 0 will put the heartbeat effectively off.
- **float getFrequency()** returns set frequency (or constrained value).
- **float getDutyCycle()** returns set duty cycle (or constrained value).
- **void enable()** enable the pulsing.
- **void disable()** disable the pulsing; will switch of the LED.
- **void beat()** the worker; this function checks if the HeartBeat is enabled 
and the LED  must be toggled.  
It must be called as often as possible to keep a steady pace,
at least 4 times the given frequency.  
Not calling **beat()** effectively stops the heartbeat.
- **uint8_t getState()** returns the state of the heartbeat.
Useful for debugging.


#### Obsolete

- **set(float freq)** is replaced by **setFrequency()**.


## Applications

Applications include but are not limited to
- show an alive sign, typical freq of 1 Hz is sufficient.
- show error code by means of different frequencies.
  - 1 Hz = OK
  - 2 Hz = Warning
  - 5 Hz = Error
  - no signal would indicate also an error.
- indicate power e.g. round(amps) - you might need to map the range!
- indicate the volume by increasing heartBeat
- indicate a changing distant - increasing or decreasing.
- Geiger counter style.


## Operation

See examples


## Future

- improve documentation
- add examples
- 

