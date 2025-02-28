
[![Arduino CI](https://github.com/RobTillaart/ADG2188/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/ADG2188/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/ADG2188/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/ADG2188/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/ADG2188/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/ADG2188.svg)](https://github.com/RobTillaart/ADG2188/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/ADG2188/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/ADG2188.svg?maxAge=3600)](https://github.com/RobTillaart/ADG2188/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/ADG2188.svg)](https://registry.platformio.org/libraries/robtillaart/ADG2188)


# ADG2188

Arduino library for ADG2188 8x8 (cross-point) matrix switch with I2C.


## Description

**Experimental**

The library is **NOT** tested with hardware yet. Feedback is welcome.

This library is to use an ADG2188 8x8 cross-point matrix switch from a microcontroller.
That means the ADG2188 device implements a matrix of switches of 8 rows and 8 columns.
Every row has a switch to every column, which can be on or off.

The device can operate in two modi, direct (transparent) or latched (delayed) mode.
In the first setting a switch will be visible immediately, while the latch mode 
waits until they can all be switched simultaneously.

The device has a reset line that can be "pulsed LOW" which will reset 
all registers and switches to OFF state.

The library is based on datasheet Rev. B, www.analog.com

- https://www.analog.com/media/en/technical-documentation/data-sheets/adg2188.pdf

Feedback as always is welcome.


### Related

- https://github.com/RobTillaart/ADG2128 8x12 cross-point switch
- https://github.com/RobTillaart/ADG2188 8x8 cross-point switch


## I2C

### I2C Address

The ADG2188 has three address pins, A0, A1, A2, which allows for a total of 
8 addresses. These are in the range 0x70..0x77  or decimal 112..119.


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

See example **TCA9548_demo_ADG2188.ino**


### I2C Performance

Should work in Standard mode 100 kHz, Fast mode 400 kHz and
High speed mode 1.7 / 3.4 MHz (see notes datasheet).

TODO: run performance sketch on hardware. feedback is welcome.

|  Clock     |  time (us)  |  Notes  |
|:----------:|:-----------:|:--------|
|   100 KHz  |             |  default
|   200 KHz  |             |
|   300 KHz  |             |
|   400 KHz  |             |
|   500 KHz  |             |
|   600 KHz  |             |


## Interface

```cpp
#include "ADG2188.h"
```

### Constructor

- **ADG2188(uint8_t address, TwoWire \*wire = &Wire)** optional select I2C bus.
- **bool begin()** checks if device is visible on the I2C bus.
- **bool isConnected()** Checks if device address can be found on I2C bus.
- **uint8_t getAddress()** Returns the address, 0x70-0x77 (112-119).

### On Off

- **void on(uint8_t row, uint8_t col)** idem.
- **void off(uint8_t row, uint8_t col)** idem.
- **bool isOn(uint8_t row, uint8_t col)** returns true if switch os on.
- **uint8_t isOnMask(uint8_t col)** get a whole column at once as bit mask.

Convenience wrappers, sw = 0..63, row = sw / 8, col = sw % 8;
- **void on(uint8_t sw)**
- **void off(uint8_t sw)**
- **bool isOn(uint8_t sw)**

### Mode

The default is direct (transparent) mode.

- **void setMode(bool latched = false)** set mode, default direct.
- **bool isLatchedMode()**idem.
- **bool isDirectMode()** idem.

### Reset

Using the reset pin is optional, keep it HIGH if you do not use it.
Otherwise you cannot write to the device.

- **void setResetPin(uint8_t resetPin)** set the reset pin.
- **void pulseResetPin()** resets all switches off, all registers ==> 0.

### Debug

Error handling is to be elaborated.

- **uint8_t getLastError()** returns last error of low level communication.

## Future

#### Must

- improve documentation
- get hardware to test
- keep in sync with ADG2188

#### Should

- create examples
  - performance sketch
  - read back sketch
  - unique per row/column.
- improve error handling

#### Could

- cache status of switches to speed up On/Off
  - import export cache
- some ideas.
```
  //  switches on all X, for a given y
  //  void  onUniqueX(x, y)
  //
  //  groups
  //  void     onRow(uint8_t col);
  //  void     onColumn(uint8_t row);
  //  void     offRow(uint8_t col);
  //  void     offColumn(uint8_t row);
```

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


