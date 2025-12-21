
[![Arduino CI](https://github.com/RobTillaart/LC7822/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/LC7822/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/LC7822/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/LC7822/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/LC7822/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/LC7822.svg)](https://github.com/RobTillaart/LC7822/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/LC7822/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/LC7822.svg?maxAge=3600)](https://github.com/RobTillaart/LC7822/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/LC7822.svg)](https://registry.platformio.org/libraries/robtillaart/LC7822)


# LC7822

Arduino library for the LC7822 8 channel analogue switch.


## Description

**Experimental**

This library is to use the LC7821/22/23 with an Arduino.

The library allows to set the switches induvidually or set all 
switches in one call. 
Furthermore the library caches the current state of the switches. 
This allows to read back the state of the switches either as a
bit mask or read them individually (from cache).

The library uses a fixed address for the device, but allows 
multiple devices on the same "data pins" as every object should
have an unique sPin (select pin).

The library has derived classes for the LC7821 and LC7823 as 
these are pretty similar. The difference is the address used,
and the LC7823 only has 7 switches instead of 8.

The library is not tested with hardware yet.

Note the LC782x devices are old and may be obsolete.

Feedback, as always, is welcome.


### Addresses

|   Type   |  S  |  A0  |  A1  |  A2  |  A3  |  decimal  |
|:--------:|:---:|:----:|:----:|:----:|:----:|:---------:|
|  LC7821  |  L  |  0   |  1   |  0   |  1   |     5     |
|  LC7821  |  H  |  1   |  1   |  0   |  1   |    13     |
|  LC7822  |  L  |  0   |  0   |  1   |  1   |     3     |
|  LC7822  |  H  |  1   |  0   |  1   |  1   |    11     |
|  LC7823  |  L  |  0   |  1   |  1   |  1   |     7     |
|  LC7823  |  H  |  1   |  1   |  1   |  1   |    15     |


Effectively the S line sets the address bit A0, and works 
in the library as a select pin. When S == LOW, the device 
is not selected, when S == HIGH the device is selected.

So in theory one can use the S pin to select between multiple 
devices that use the same set of data and clock pin (like SPI).
Only the one with the HIGH sPin should react. 
**This need to be verified**


### Related

Todo


## Interface

```cpp
#include "LC7822.h"
```

### Constructor

- **LC7822(uint8_t dataPin, uint8_t clockPin, uint8_t cePin, uint8_t selectPin, uint8_t resetPin = 255)** Constructor, set pins needed.
- **bool begin()** Initializes the IO pins.
- **bool reset()** resets the device, returns false if reset Pin is not defined.
- **uint8_t getAddress()** returns cached address (debugging).

### Switches

- **bool setAll(uint8_t value)** mask to set all switches in one call.
- **uint8_t getAll()** get bit mask of all swicthes.
- **bool setSwitch(uint8_t sw, bool val)** set one switch.
- **bool getSwitch(uint8_t sw)** get state of single switch.

### Tune timing

- **void setMicroDelay(uint8_t udel)** set pulse delay.
- **uint8_t getMicroDelay()** return set value


## Future

#### Must

- improve documentation
- get hardware to test
- test reset() polarity.

#### Should

- add examples
  - performance sketch
  - array sketch

#### Could

- add error handling?
- add defaults for some parameters?


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


