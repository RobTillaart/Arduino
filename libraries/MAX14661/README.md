
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

The MAX14661 multiplexer is a 16 x 2 channel multiplexer. 
It has 2 lines A and B which can be 
connected up to 16 A lines and 16 B lines.

The library provides 4 kinds of interfaces (see below)
- **PAIR** switch A and B in pairs
- **SHADOW** use a shadow register to set all simultaneously.
- **MUX** open channels exclusively.
- **FULL** control all as you like.

Mixing these interfaces is allowed but definitely not advised as 
especially the **PAIR** interface assumes that A and B selections 
are kept in sync.
So depending on your application choose the interface you want to use.

The MAX14661 device can be controlled by SPI or I2C. 
This library implements the I2C interface.


#### I2C address

The I2C address can be adjusted by 2 address lines A0 and A1.
Addresses go from 0x4C (76) .. 0x4F (79). See table 3 datasheet.

This implies you may have up to 4 MAX14661 multiplexers on one I2C bus.
If you need more, consider a TCA9548.

According to the datasheet the I2C Serial-Clock Frequency is max 400 kHz.
(SPI can do 10 MHz)


#### 0.2.0 Breaking change

Version 0.2.0 introduced a breaking change.
You cannot set the pins in **begin()** any more.
This reduces the dependency of processor dependent Wire implementations.
The user has to call **Wire.begin()** and can optionally set the Wire pins 
before calling **begin()**.


#### Related

- https://github.com/RobTillaart/TCA9548 specific I2C multiplexer.
- https://github.com/RobTillaart/HC4067 1x16 channel multiplexer.
- https://github.com/RobTillaart/HC4051 1x8 channel multiplexer.
- https://github.com/RobTillaart/HC4052 2x4 channel multiplexer.
- https://github.com/RobTillaart/HC4053 2x3 channel multiplexer.


## Interface

```cpp
#include "MAX14661.h"
```


#### Constructor

- **MAX14661(uint8_t deviceAddress, TwoWire \*wire = &Wire)** Constructor with device address, 
and optional the Wire interface as parameter.
- **bool begin()** initializes the wire interface.
Returns true if device address is seen on I2C bus.
- **bool isConnected()** checks if the device address is visible on the I2C bus.


#### PAIR interface

The functions in this interface part all work symmetrical on the A and B line. 
They are managed as a PAIR. So this is ideal e.g. to multiplex an I2C bus or 
a Serial TX/RX pair line.

The interface allows to have multiple lines A/B open in parallel.

  // open ==> connect
- **bool openChannel(uint8_t channel)** connects A/B to chosen channel.
- **bool closeChannel(uint8_t channel)** disconnects channel from A/B.
- **bool isOpenChannel(uint8_t channel)** returns true if connected to A/B.
- **void openAllChannels()** connects all channels.
- **void closeAllChannels()** disconnects all channels.
- **void setChannels(uint16_t mask)** connect multiple channels with a bit mask.
- **uint16_t getChannels()** returns a bit mask of the channels connected.

Note: 
**setChannels(mask)** is the only way to set channels at the very same moment
in the **PAIR** interface.


#### SHADOW interface

Experimental - to be tested.

The SHADOW interface allows one to prepare which channels should be selected, 
and activate them all at once. 

- **bool shadowClear()** clears all shadow registers.
- **void activateShadow()** write all shadow registers to the direction 
registers of A and B at once. 

Prepare multiple channels at once. This is way faster than per channel.

- **bool setShadowChannelMaskA(uint16_t mask)** write all channels at once.
- **uint16_t getShadowChannelMaskA()** read shadow registers.
- **bool setShadowChannelMaskB(uint16_t mask)** write all channels at once.
- **uint16_t getShadowChannelMaskB()** read shadow registers.

Prepare per channel.

- **bool isOpenShadowChannelA(uint8_t channel)** read status of specific channel in shadow registers.
- **void openShadowChannelA(uint8_t channel)** prepare a specific channel to open.
- **void closeShadowChannelA(uint8_t channel)** prepare a specific channel to close.
- **bool isOpenShadowChannelB(uint8_t channel)** read status of specific channel in shadow registers.
- **void openShadowChannelB(uint8_t channel)** prepare a specific channel to open.
- **void closeShadowChannelB(uint8_t channel)** prepare a specific channel to close.

Note: there is no command that sets both A and B simultaneously.

#### MUX interface

The MUX interface allows one channel (0..15) to be open at a time.

- **void MUXA(uint8_t channel)** if channel < 16 only that channel will be selected. 
All other values will select no channel.
- **uint8_t getMUXA()** returns the selected channel.
255 means none selected.
- **void MUXB(uint8_t channel)** if channel < 16 only that channel will be selected. 
All other values will select no channel.
- **uint8_t getMUXB()** returns the selected channel.
255 means none selected.


#### FULL CONTROL interface

Full control per channel, any combination is possible.
Use with care as these can interfere e.g. with the PAIR interface.
All functions return false if channel > 15.

- **bool openA(uint8_t channel)** idem
- **bool openB(uint8_t channel)** idem
- **bool closeA(uint8_t channel)** idem
- **bool closeB(uint8_t channel)** idem


#### LOW LEVEL CONTROL interface

Check datasheet for the meaning of and the values in the registers.

- **uint8_t readRegister(uint8_t reg)** read low level device register.
- **int writeRegister(uint8_t reg, uint8_t value)** write value to device register.


#### Error handling

- **int lastError()** returns the last error, limited to low level I2C for now.

to be elaborated  / implemented(see future)

|  Define                |  value  |  notes  |
|:-----------------------|:-------:|:-------:|
|  MAX14661_OK           |  0x00   |
|  MAX14661_ERR_I2C      |  0x80   |  not implemented yet  |
|  MAX14661_ERR_CHANNEL  |  0x81   |  not implemented yet  |


## Operation

See examples


## Future

#### Must

- improve documentation

#### Should

- test behaviour.
- write unit tests.
- implement error handling.
  - use an internal mode to see which of the three interfaces is used
    consequently or not?
  - MAX14661_ERR_ADDRESS ?


#### Could

- optimize low level bit set/clr/get read/write 2 bytes at once.
- test I2C communication speed.
  - 100- 400 kHz and up.
- measure performance.
- cache direct registers. (fast response).
- **ShutDown()** SD pin. for low power datasheet p.15
  - document it.
  - implement.


#### Wont

- SPI interface.
  - separate (derived ?) class
- initial values parameter for begin()?
  - depends on interface (PAIR MUX SHADOW) used, ambiguous. 
  - ==> user task.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

