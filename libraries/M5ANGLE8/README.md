
[![Arduino CI](https://github.com/RobTillaart/M5ANGLE8/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/M5ANGLE8/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/M5ANGLE8/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/M5ANGLE8/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/M5ANGLE8/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/M5ANGLE8/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/M5ANGLE8.svg?maxAge=3600)](https://github.com/RobTillaart/M5ANGLE8/releases)


# M5ANGLE8

Arduino library for M5 8ANGLE 8x12 bit potentiometers.


## Description

**Experimental**

M5ANGLE8 is an Arduino class to read the potentiometers of the M5 8ANGLE module.
It also provides means to write RGB values to the 8 LED's in the same module.

The potentiometers can be read with 8 bit (faster) or 12 bit.
Derived from the latter this library also supports 9, 10 and 11 bit. 
So the range can be chosen to match your application.

Furthermore the library can set the RGB value + brightness of the 8 LEDS.
No tests with hardware have been done yet, so use with care.
Feedback welcome!


#### I2C

The address range is in theory from 0..127, however the I2C specification
states it should be between 8 and 119 as some addresses are reserved.

TODO to what clock does it work?
|  clock  |  works  |
|:-------:|:-------:|
| 100 KHz |         |
| 200 KHz |         |
| 400 KHz |         |
| 600 KHz |         |
| 800 KHz |         |


#### Accuracy

- how stable are the potentiometers? noise?
- how easy are they set "exactly"?
  280° for 4095 values is 14~15 steps per degree.


#### Related

- https://github.com/RobTillaart/GAMMA
- https://github.com/RobTillaart/map2colour


## Interface

```cpp
#include "M5ANGLE8.h"
```

- **M5ANGLE8(uint8_t address = M5ANGLE8_DEFAULT_ADDRESS, TwoWire \*wire = &Wire)** constructor.
Default address = 0x43, default Wire.
- **bool begin(int sda, int scl)** ESP32 et al.
- **bool begin()** initialize I2C, check if connected.
- **bool isConnected()** checks if address is on the I2C bus.
- **bool setAddress(uint8_t address = M5ANGLE8_DEFAULT_ADDRESS)** set a new address for the device.
Default 0x43.
- **uint8_t getAddress()** convenience function.
- **uint8_t getVersion()** get firmware version from device.

#### IO part

- **uint16_t analogRead(uint8_t channel, uint8_t resolution = 12)**
Read a potentiometer, resolution can be set from 8..12 bit, constrained.
- **uint8_t inputSwitch()** read status of the switch.
- **bool writeRGB(uint8_t channel, uint8_t R, uint8_t G, uint8_t B, uint8_t brightness)**
Set the RGB value and brightness of a LED.
- **bool allOff()** switch all LEDs off.
Returns true.


## Future

#### Must

- improve documentation
- test with hardware

#### Should

- error handling
- **bool writeBrightness(channel)**
- **bool readRGB(channel, &R, &G, &B, &brightness)**
- improve on return values of functions.

#### Could

- add examples
  - complex wave generator (freq, p0..p6 7 harmonics)
  - digital lock - 4096^8 possibilities in theory. 256^8 = 2^64 is enough...
    even 8^8 = 16 million.
    switch => verify trigger
  - dynamic "multi-mapping", set 8 points to match a curve.
  - equalizer 2x4 band (stereo)
  - LED colour mapping green -> yellow -> red.
- investigate pulsating LED, how much performance costs?
- investigate "optimal" polling frequency
- add unit tests
- check performance
- caching?
  - version (not interesting), 
  - RGB values = 32 bytes
- improve performance
  - faster **allOff()** writing 2x 16 bytes dedicated.
  - read all analog ports in one call. (array of values).


#### Wont (unless)

- write separate colour channels?


