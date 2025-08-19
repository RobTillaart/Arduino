
[![Arduino CI](https://github.com/RobTillaart/MAX14661/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MAX14661/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MAX14661/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MAX14661/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MAX14661/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MAX14661.svg)](https://github.com/RobTillaart/MAX14661/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MAX14661/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MAX14661.svg?maxAge=3600)](https://github.com/RobTillaart/MAX14661/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MAX14661.svg)](https://registry.platformio.org/libraries/robtillaart/MAX14661)


# MAX14661

Arduino library for MAX14661 multiplexer with I2C interface.


## Description

**Experimental**

The MAX14661 multiplexer is a sort of 16 x 2 channel multiplexer.
The device has 16 ABxx lines which can be connected to COM-A and/or COM-B.

The library provides four interfaces (details see below)
- **PAIR** switch A and B in pairs
- **SHADOW** use a shadow register to prepare and set all simultaneously.
- **MUX** open channels exclusively.
- **FULL** control all as you like.

Mixing these interfaces is allowed in theory but definitely not advised as
especially the **PAIR** interface assumes that A and B selections
are kept in sync.
So depending on your application choose the interface you want to use.

**Warning**

Be aware that by switching on both the A and B switch for any
line ABxx will short-circuit the COM-A and COM-B. such short-circuit would
also connect any ABxx line to any other if one of their switches is switched on.
There might be projects when such short-circuit is no problem and if
intended it can be done, but be careful.

Feedback as always is welcome, please open an issue on GitHub.


### SPI vs I2C

The MAX14661 device can be controlled by SPI or I2C.
This library implements only the I2C interface.
If you need a SPI library for the MAX14661, feel free to contact me.


### 0.3.0 Breaking change

Version 0.3.0 introduced a breaking change.

The PAIR interface got a **complete rewrite** so its functionality matches
the intention to work as a multiplexer for 2-wire based protocols like
I2C and Serial.
The PAIR functions of pre-0.3.0 version are all removed and new functions
have been added to replace them, see below.

The FULL CONTROL interface got a **complete rewrite**.
The FULL CONTROL functions of pre-0.3.0 version are all removed and new functions
have been added to replace them, see below.


### 0.2.0 Breaking change

Version 0.2.0 introduced a breaking change.
You cannot set the pins in **begin()** any more.
This reduces the dependency of processor dependent Wire implementations.
The user has to call **Wire.begin()** and can optionally set the Wire pins
before calling **begin()**.


### I2C address

The I2C address can be adjusted by 2 address lines A0 and A1.
Addresses go from 0x4C (76) .. 0x4F (79). See table 3 datasheet.
This implies you may have up to 4 MAX14661 multiplexers on one I2C bus.
If you need more, consider a TCA9548, see below.

According to the datasheet the I2C Serial-Clock Frequency is max 400 kHz.
This needs to be tested.
(SPI can do 10 MHz)


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


### Related

- https://github.com/RobTillaart/TCA9548 specific I2C multiplexer.
- https://github.com/RobTillaart/HC4067 1x16 channel multiplexer.
- https://github.com/RobTillaart/HC4051 1x8 channel multiplexer.
- https://github.com/RobTillaart/HC4052 2x4 channel multiplexer.
- https://github.com/RobTillaart/HC4053 2x3 channel multiplexer.


## Interface

```cpp
#include "MAX14661.h"
```


### Constructor

- **MAX14661(uint8_t deviceAddress, TwoWire \*wire = &Wire)** Constructor with device address,
and optional the Wire interface as parameter.
- **bool begin()** initializes the wire interface.
Returns true if device address is seen on I2C bus.
- **bool isConnected()** checks if the device address is visible on the I2C bus.


### PAIR interface

(note the PAIR interface is completely rewritten in 0.3.0)

The ABxx lines are considered to form 8 pairs { (0,1), (2,3), (4,5), ... (14,15) }.
The functions in this interface manage the switches in pairs, so when e.g. pair 3
is connected, AB06 connects with COM-A and AB07 connects with COM-B.
This allows one to multiplex an I2C bus, a Serial TX/RX pair, or any 2 wires based protocol.

|  pair  |  COM-A  |  COM-B  |  notes  |
|:------:|:-------:|:-------:|:--------|
|   0    |    0    |    1    |
|   1    |    2    |    3    |
|   2    |    4    |    5    |
|   3    |    6    |    7    |
|   4    |    8    |    9    |
|   5    |   10    |   11    |
|   6    |   12    |   13    |
|   7    |   14    |   15    |

The PAIR interface allows to have multiple pairs to be connected in parallel.

- **bool connectPair(uint8_t pair)** connects a pair of lines to COM-A, COM-B.
- **bool disconnectPair(uint8_t pair)** disconnects a pair of lines from COM-A, COM-B.
- **bool isConnectedPair(uint8_t pair)** returns true if pair is connected to COM-A, COM-B.
- **void disconnectAllPairs()** disconnects all pairs.


### SHADOW interface

The SHADOW interface allows one to prepare which switches should be set,
and activate them all (nearly) simultaneously.

- **bool shadowClear()** clears all shadow registers.
- **void activateShadow()** write all shadow registers to the direction
registers of COM-A and COM-B at once.

Prepare multiple channels at once. This is way faster than per channel.

- **bool setShadowChannelMaskA(uint16_t mask)** prepare all channels at once.
- **uint16_t getShadowChannelMaskA()** read the COM-A shadow registers.
- **bool setShadowChannelMaskB(uint16_t mask)** prepare all channels at once.
- **uint16_t getShadowChannelMaskB()** read COM-B shadow registers.

Prepare per channel for COM-A.

- **bool isOpenShadowChannelA(uint8_t channel)** read status of specific channel in COM-A shadow registers.
- **void openShadowChannelA(uint8_t channel)** prepare a specific channel to open.
- **void closeShadowChannelA(uint8_t channel)** prepare a specific channel to close.

Prepare per channel for COM-B.

- **bool isOpenShadowChannelB(uint8_t channel)** read status of specific channel in COM-B shadow registers.
- **void openShadowChannelB(uint8_t channel)** prepare a specific channel to open.
- **void closeShadowChannelB(uint8_t channel)** prepare a specific channel to close.

Note: there is no command that sets both A and B exactly simultaneously.


### MUX interface

The MUX interface allows one channel (0..15) to be open at a time.

- **void MUXA(uint8_t channel)** if channel < 16 only that channel will be selected.
It will disconnect previous selected channels.
All values > 15 will select no channel.
- **uint8_t getMUXA()** returns the selected channel.
255 means no channel is selected (all switches off)
- **void MUXB(uint8_t channel)** if channel < 16 only that channel will be selected.
It will disconnect previous selected channels.
All values > 15 will select no channel.
- **uint8_t getMUXB()** returns the selected channel.
255 means no channel is selected (all switches off)


### FULL CONTROL interface

Full control per channel, any combination of switches is possible.
Use with care as these can interfere e.g. with the PAIR interface,
or one can connect COM-A to COM-B, causing all pins to be connected to each other.

All functions return false if the channel > 15.

- **bool connectA(uint8_t channel)** idem
- **bool connectB(uint8_t channel)** idem
- **bool disconnectA(uint8_t channel)** idem
- **bool disconnectB(uint8_t channel)** idem
- **bool disconnectAll()** fast disconnect of all ABxx lines


### LOW LEVEL CONTROL interface

Check datasheet for the meaning of and the values in the registers.

- **uint8_t readRegister(uint8_t reg)** read low level device register.
- **int writeRegister(uint8_t reg, uint8_t value)** write value to device register.


### Error handling

- **int lastError()** returns the last error, resets the internal error flag.

|  Define                    |  value  |  notes  |
|:---------------------------|:-------:|:-------:|
|  MAX14661_OK               |  0x00   |
|  MAX14661_ERR_I2C_READ     |  0x80   |
|  MAX14661_ERR_I2C_REQUEST  |  0x81   |
|  MAX14661_ERR_CHANNEL      |  0x90   |
|  MAX14661_ERR_ADDRESS      |  0x91   |

Note: here are also low level Wire errors possible. (how to handle them).


## Future

#### Must

- improve documentation
- get hardware for testing.

#### Should

- test behaviour.

#### Could

- optimizations
  - low level bit set/clear/get
  - read/write 2 bytes at once.
  - cache direct registers. (faster, but possible incorrect).
  - only write register if changed.
- **ShutDown()** SD pin. For low power datasheet p.15
  - document it.
  - implement it.

#### Wont

- SPI interface.
  - separate (derived ?) class, upon request maybe
- initial values parameter for begin()?
  - depends on interface (PAIR MUX SHADOW FULL) used, so ambiguous.
  - ==> user task.
- use an internal mode to see which of the three interfaces is used
    consequently or not?  performance penalty
    ==> user responsibility
- write unit tests.
  - needs full mock,
- redo functions signature void() => bool() so more detail or even int()?
  => affects performance.
  => user can check lastError();


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

