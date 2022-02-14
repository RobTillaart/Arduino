
[![Arduino CI](https://github.com/RobTillaart/X9C10X/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/X9C10X/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/X9C10X/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/X9C10X/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/X9C10X/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/X9C10X/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/X9C10X.svg?maxAge=3600)](https://github.com/RobTillaart/X9C10X/releases)


# X9C10X

Arduino Library for X9C10X series digital potentiometer.


## Description

This experimental library provides a X9C10X base class and four derived classes for specific digital potentiometer.

| type   | resistance |  notes       |
|:------:|:----------:|:-------------|
| X9C10X |    generic |  base class  |
| X9C102 |    1 KΩ    |  10 \* 10^2  |
| X9C103 |   10 KΩ    |  10 \* 10^3  |
| X9C104 |  100 KΩ    |  10 \* 10^4  |
| X9C503 |   50 KΩ    |  50 \* 10^3  |


_Note: Ω ohm sign = ALT-234_

The library keeps cache of the position. 


## Interface


## X9C10X base class

Use **\#include "X9C10X.h"**

- **X9C10X(uint32_t ohm = 10000)** Constructor, default initializes the resistance to 10000 Ω. 
To calibrate one can fill in any other value e.g. 9950 Ω.
- **void begin(uint8_t pulsePin, uint8_t directionPin, uint8_t selectPin, uint8_t position = 0)** 
sets the pins used by the device, and resets the position (default to 0).
The position parameter allows to start the device with a previous stored position. 
Use this position with care.

Note: **begin()** has a hard coded 500uS delay so the device can wake up.

Note: multiple devices can be controlled, just by giving them an unique selectPin.
This behaviour is similar to the SPI select pin.

- **void setPosition(uint8_t position)** sets the wiper to a position between 0 and 99. 
- **uint8_t getPosition()** returns the current position.
- **void incr()** moves one position up (if possible).
- **void decr()** moves one position down (if possible).
- **uint32_t getOhm()** returns the position expressed in ohm.
The returned value does depend on the value passed in the constructor.
- **uint32_t getMaxOhm()** returns the maximum value ( =  parameter from constructor). 


#### Store 

Warning: use with care.

- **uint8_t store()** stores the current position in the NVRAM of the device, 
and returns the current position so it can later be used as position parameter for **begin()**. 

If one uses an incorrect parameter position in **begin()** the internal state and the device 
will probably be out of sync. One way to sync is call **begin()** with the right parameters. 
The other way is to call **setPosition(0)** followed by **setPosition(99)** (or vice versa) 
to get a defined internal state.


## derived classes 

There are 4 derived classes, each with a other (appropriate) default value for the resistance. 

- **X9C102(uint32_t ohm = 1000)**
- **X9C103(uint32_t ohm = 10000)**
- **X9C104(uint32_t ohm = 100000)**
- **X9C503(uint32_t ohm = 50000)**

These classes have the same interface as the base class.


#### Performance

No hardware to test yet.


## Operation

See examples.


## Future

- buy and test different versions of the hardware
- test different platform
- test performance
- documentation
- optimize **setPosition()**
- do we need the hardcoded 500us delay in **begin()**?
- do we need **getType()**
- add error codes?

