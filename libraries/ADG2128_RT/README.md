
[![Arduino CI](https://github.com/RobTillaart/ADG2128/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/ADG2128/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/ADG2128/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/ADG2128/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/ADG2128/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/ADG2128.svg)](https://github.com/RobTillaart/ADG2128/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/ADG2128/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/ADG2128.svg?maxAge=3600)](https://github.com/RobTillaart/ADG2128/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/ADG2128.svg)](https://registry.platformio.org/libraries/robtillaart/ADG2128)


# ADG2128

Arduino library for ADG2128 8x12 (cross-point) matrix switch with I2C.


## Description

**Experimental**

The library is **NOT** tested with hardware yet. Feedback is welcome.

This library is to use an ADG2128 8x12 cross-point matrix switch from a microcontroller.
That means the ADG2128 device implements a matrix of switches of 12 rows (X) and 8 columns (Y).
Every row has a switch to every column, which can be on or off.
In total this makes 96 switches.

The device can operate in two modi, direct (transparent) or latched (delayed) mode.
In the direct mode a switch on or off will be visible immediately, while the latch mode 
waits until they can all be switched simultaneously.

The device has a reset line that can be "pulsed LOW" which will reset 
all registers and switches to OFF state.

The library is based on datasheet Rev. E,

- https://www.analog.com/media/en/technical-documentation/data-sheets/ADG2128.pdf

Feedback as always is welcome.


### Breaking change 0.2.0

Swapped columns and rows to match figure 1 of the datasheet. (See #2).
Furthermore the interface of the library has been changed a bit.

This makes version 0.1.0 obsolete.


### Related

- https://github.com/RobTillaart/ADG2128 8x12 cross-point switch
- https://github.com/RobTillaart/ADG2188 8x8 cross-point switch


## I2C

### I2C Address

The ADG2128 has three address pins, A0, A1, A2, which allows for a total of 
8 addresses. These are in the range 0x70..0x77 or decimal 112..119.


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

See example **TCA9548_demo_ADG2128.ino**


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
#include "ADG2128.h"
```

### Constructor

- **ADG2128(uint8_t address = 0x70, TwoWire \*wire = &Wire)** optional set address and select I2C bus.
- **bool begin()** checks address range and if address can be found on I2C bus.
- **bool isConnected()** checks if address can be found on I2C bus.
- **uint8_t getAddress()** returns the address, 0x70-0x77 (112-119).


### On Off

Columns and rows match figure 1 of the datasheet.

- **bool on(uint8_t row, uint8_t column)** idem, row (X) = 0..11, column (Y) = (0..7)
Returns false if row or column is out of range.
- **bool off(uint8_t row, uint8_t column)** idem.
Returns false if row or column is out of range.
- **bool isOn(uint8_t row, uint8_t column)** returns true if switch is on.
Returns false if switch off of OR row or column is out of range.
User should check this difference as the library does not report this in a neat way.
- **uint16_t isOnRow(uint8_t row)** get a whole row at once as bit mask.


Convenience wrappers, switch sw = 0..95, row (X) = sw / 8, column (Y) = sw % 8;
- **bool on(uint8_t sw)** returns false if sw is out of range.
- **bool off(uint8_t sw)** returns false if sw is out of range.
- **bool isOn(uint8_t sw)** returns true if sw is on.
Returns false if sw off of OR out of range.
User should check this difference as the library does not report this in a neat way.


### Mode

The default is direct (transparent) mode.

- **void setDirectMode()** set mode, default direct.
- **void setLatchMode()** set mode to latch.
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
- improve error handling

#### Could

- cache status of switches to speed up On/Off
  - import export cache for reboot / reset purposes.
  - extern buffer of 12 bytes.
- add **uint16_t isOnColumn(uint8_t column)** get a whole column at once as bit mask.
  - needs cache to be performant
- add **latch()**, remember the last value sent,
  - one time overrule the latch mode.
- add **allOff(direct / latch)** sort of SW reset.
  pretty expensive function. might use the onOnRow() to only reset the ones needed.
- add **select(row, col)** select only one column per row.
- add **unique(row, col)** select only one switch to be on.
- group commands.
  - **void onRow(uint8_t col)**
  - **void onColumn(uint8_t row)**
  - **void offRow(uint8_t col)**
  - **void offColumn(uint8_t row)**

#### Wont

- technically one can connect modules to generate a "super module"
  - 8x24 or 16x24 or ...
  - not supported in this library as many configurations are possible.
  - might be an idea for an example?

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


