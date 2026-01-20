
[![Arduino CI](https://github.com/RobTillaart/PT2257/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PT2257/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PT2257/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PT2257/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PT2257/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/PT2257.svg)](https://github.com/RobTillaart/PT2257/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PT2257/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PT2257.svg?maxAge=3600)](https://github.com/RobTillaart/PT2257/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/PT2257.svg)](https://registry.platformio.org/libraries/robtillaart/PT2257)


# PT2257

Arduino library for the PT2257 two channel volume controller.


## Description

**Experimental**

The PT2257 is a 2 channel, stereo, volume controller with an I2C interface.

TODO elaborate

Feedback as always is welcome.


### Special characters

Ω == Ohm = ALT-234 (Windows)
µ == micro = ALT-0181 (Windows)


### Hardware

Check datasheet for details

```
             TOPVIEW PT2257
         +--------------------+
         |                    |
   pin 1 | o                o |  pin 8
   pin 2 | o                o |  pin 7
   pin 3 | o                o |  pin 6
   pin 4 | o                o |  pin 5
         |                    |
         +--------------------+
```

|  pin  |   name   |  description   |  Notes  |
|:-----:|:--------:|:---------------|:-------:|
|   1   |  IN-L    |  input left    |
|   2   |  OUT-L   |  output left   |
|   3   |  Vss/GND |  Ground        |
|   4   |  SDA     |  I2C data      |
|   5   |  SCL     |  I2C clock     |
|   6   |  Vdd     |  +4 - +9V      |
|   7   |  OUT-R   |  output right  |
|   8   |  IN-R    |  input right   |



### Related

- https://github.com/RobTillaart/HC4052 (multiplexer for more inputs)
- https://github.com/RobTillaart/TCA9548 (I2C multiplexer)
- https://github.com/RobTillaart/PT2257 I2C 2 channel volume controller
- https://github.com/RobTillaart/PT2314 I2C 4 channel audio processor


### Tested

TODO: Test on Arduino UNO and ESP32


## I2C

The device has a fixed I2C address of 0x44 (68).


### I2C multiplexing

Sometimes you need to control more devices than possible with the default
address range the device provides.
This is possible with an I2C multiplexer e.g. TCA9548 which creates up 
to eight channels (think of it as I2C subnets) which can use the complete 
address range of the device. 

Drawback of using a multiplexer is that it takes more administration in 
your code e.g. which device is on which channel. 
This will slow down the access, which must be taken into account when
deciding which devices are on which channel.
Also note that switching between channels will slow down other devices 
too if they are behind the multiplexer.

- https://github.com/RobTillaart/TCA9548


### I2C Performance

Only test **xxxxxxxx()** as that is the main function.

The PT2257 only supports 100 kHz.


|  Clock     |  time (us)  |  Notes  |
|:----------:|:-----------:|:--------|
|   100 KHz  |             |  max speed supported. 


TODO: add + run performance sketch on hardware.


## Interface

```cpp
#include "PT2257.h"
```

### Constructor

- **PT2257(uint8_t address, TwoWire \*wire = &Wire)** optional select I2C bus.
- **bool begin()** checks if device is visible on the I2C bus.
- **bool isConnected()** Checks if device address can be found on I2C bus.
- **uint8_t getAddress()** Returns the fixed address 0x2A (42).

### Core

- **void allOff()**
- **void mute(bool mute)**
- **bool isMuted()**

//  dB = attenuation of 0..-79, out of range => return false
- **bool stereo(int dB)**
- **bool left(int dB)**
- **bool right(int dB)**
- **int getLeft()**
- **int getRight()**


### Debug

- **uint8_t getLastError()** returns last error of the low level communication.

- PT2257_OK = 0


## Future

#### Must

- improve documentation
- get hardware to test
- test functionality

#### Should

- add examples

#### Could

- create unit tests if possible


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


