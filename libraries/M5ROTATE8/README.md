
[![Arduino CI](https://github.com/RobTillaart/M5ROTATE8/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/M5ROTATE8/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/M5ROTATE8/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/M5ROTATE8/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/M5ROTATE8/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/M5ROTATE8/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/M5ROTATE8.svg?maxAge=3600)](https://github.com/RobTillaart/M5ROTATE8/releases)


# M5ROTATE8

Arduino library for M5 8ROTATE 8x rotary encoders.


## Description

**Experimental**

M5ROTATE8 is an Arduino class to read the 8 rotary encoders of the
M5 8ENCODER module.
It also provides means to write RGB values to the 8 LED's in the same module.

The rotary encoders can be read as an absolute counter (since start) or as an relative counter (since last time read). 
The value can be both positive and negative.
The absolute counter can be given an initial value.
The counters can be reset per channel.
The library can also read the key pressed status of every rotary encoder.

Finally the library can set the RGB value of the 8 LEDS.

No tests with hardware have been done yet, so use with care.
Feedback welcome!


#### I2C

The address range is in theory from 0..127, however the I2C specification
states it should be between 8 and 119 as some addresses are reserved.
The default address is 0x41.

TODO to what clock does it work?
|  clock  |  works  |
|:-------:|:-------:|
| 100 KHz |         |
| 200 KHz |         |
| 400 KHz |         |
| 600 KHz |         |
| 800 KHz |         |


#### Related

- https://github.com/RobTillaart/M5ANGLE8


## Interface

```cpp
#include "m5rotate8.h"
```

- **M5ROTATE8(uint8_t address = M5ROTATE8_DEFAULT_ADDRESS, TwoWire \*wire = &Wire)** constructor.
Default address = 0x41, default Wire.
- **bool begin(int sda, int scl)** ESP32 et al.
- **bool begin()** initialize I2C, check if connected.
- **bool isConnected()** checks if address is on the I2C bus.
- **bool setAddress(uint8_t address = M5ROTATE8_DEFAULT_ADDRESS)** set a new address for the device.
Default address = 0x41.
- **uint8_t getAddress()** convenience function. 
- **uint8_t getVersion()** get firmware version from device.

#### IO part

- **int32_t getAbsCounter(uint8_t channel)**
Read a absolute position of the rotary encoder since reset or start.
- **void setAbsCounter(uint8_t channel, int32_t value);
- **int32_t getRelCounter(uint8_t channel)**
Read a relative position of the rotary encoder since reset.
Note: this counter will reset after each read.
- **bool getKeyPressed(uint8_t channel)** get key status of the rotary encoder.
True is pressed.
- **bool resetCounter(uint8_t channel)** reset a rotary encoder.
- **void resetAll()** reset all counters to 0.
- **uint8_t inputSwitch()** read status of the switch.
- **bool writeRGB(uint8_t channel, uint8_t R, uint8_t G, uint8_t B)** Set the RGB value of a LED.
- **bool allOff()** switches all LEDs off.


## Future

#### Must

- improve documentation
- test with hardware
- keep in sync with M5ANGLE8 where possible.

#### Should

- error handling
- optimize low level calls
  - merge into two functions => read/write array + length.
  - resetAll() could be "one call"

#### Could

- add examples
- add unit tests
- check performance
- **uint32_t readRGB(uint8_t channel)**
  - write/readAllRGB() ? less overhead?

#### Wont (unless)



