
[![Arduino CI](https://github.com/RobTillaart/HeartBeat/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/HeartBeat/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/HeartBeat.svg?maxAge=3600)](https://github.com/RobTillaart/HeartBeat/releases)


# HeartBeat

Arduino library for a HeartBeat with frequency and dutycycle


## Description

The hearbeat library offers a simple HeartBeat by sending pulses to
a digital pin. Typical usage is to blink a (built in) LED as indicater 
a program is still alive.

The library uses no hardware timer and is based upon micros() so the user 
is responsible to call the **beat()** function as often as needed or
better even more. 

The library allows to set the frequency runtime, so the HeartBeat
can be used as a first level debugging tool. Different frequencies can indicate
a different state of the program or a different level of some sensor.
No heart beat indicates the program is stuck or blocked.

The current version does not allow to differ the ON and OFF time,
this might be an option in a future version.

For more complex patterns, please check my pulsePattern library.


## Interface

The interface consists of a small set of 

- **HeartBeat()** constructor
- **begin(uint8_t pin, float freq)**  to configure the HeartBeat. 
The default frequency is 1.0
- **setFrequency(float freq)** change the frequency of the pulsing.  
Will not enable or disable the HeartBeat. Must be > 0.0
- **setDutyCycle(float dutyCycle = 50)** duty cycle in percentage time HIGH.
Must be between 0.00 and 100.0.
- **enable()** enable the pulsing
- **disable()** disable the pulsing; will switch of the LED.
- **beat()** the worker; this function checks if the HeartBeat is enabled 
and the LED  must be toggled.  
It must be called as often as possible to keep a steady pace,
at least 4 times the given frequency.  
Not calling **beat()** effectively stops the hearbeat.


#### Obsolete

- **set(float freq)** Will become obsolete, use **setFrequency()** instead.

## Applications

Applications include but are not limited to
- show an alive sign, typical freq of 1 Hz is sufficient.
- show error code by means of different frequencies.
  - 1 Hz = OK
  - 2 Hz = Warning
  - 5 Hz = Error
- indicate power usage by increasing HeartBeat e.g. round(amps) 
- indicate sound volume by increasing HeartBeat
- indicate changing distant by hearbeat
- geiger counter style.


## Operation

See examples

