
[![Arduino CI](https://github.com/RobTillaart/MAX14661/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MAX14661/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MAX14661/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MAX14661/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MAX14661/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MAX14661/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MAX14661.svg?maxAge=3600)](https://github.com/RobTillaart/MAX14661/releases)

# MAX14661

Arduino library for MAX14661 multiplexer with I2C interface.


## Description

The MAX14661 multiplexer is a 16x2 channel multiplexer. 
It has 2 lines A and B which can be 
connected up to 16 A lines and 16 B lines.

The device can be controlled by SPI or I2C. 
This library implements only an I2C interface

The I2C address can be adjusted by 2 address lines A0 and A1.
Addresses go from 0x4C (76) .. 0x4F (79). See table 3 datasheet.


## Interface

The library provides 3 kinds of interfaces. 
Mixing these interfaces is allowed but definitely not advised as 
especially the PAIR interface assumes that A and B selections 
are kept in sync.

So depending on your application choose the interface you want to use.


### Constructor

- **MAX14661(deviceAddress, TwoWire \*wire = &Wire)** Constructor with device address, 
and optional the Wire interface as parameter.
- **bool begin()** initializes the wire interface 
- **bool begin(sda, scl)** idem, for the ESP32 where one can choose the I2C pins.
- **bool isConnected()** checks if the address is visible on the I2C bus.


### PAIR interface

The functions in this interface part all work symmetrical on the A and B line. 
They are managed as a PAIR. So this is ideal e.g. to multiplex an I2C bus or 
a Serial TX/RX pair line.

The interface allows to have multiple lines A/B open in parallel.

  // open ==> connect
- **bool openChannel(uint8_t channel)** connects A/B to output channel
- **bool closeChannel(uint8_t channel)** disconnects channel from A/B
- **bool isOpenChannel(uint8_t channel)** returns true if connected to A/B
- **void openAllChannels()** connects all channels
- **void closeAllChannels()** disconnects all channels
- **void setChannels(uint16_t mask)** connect multiple channels with a bit mask.
- **uint16_t getChannels()** returns a bit mask of the channels connected.


### SHADOW interface

experimental - to be tested.

The SHADOW interface allows one to prepare which channels should be selected 
and activate them all at once. 

- **bool shadowClear()** clears all shadow registers.
- **void activateShadow()** write all shadow registers to the direction 
registers of A and B at once. 

prepare multiple channels at once. This is way faster than per channel.

- **bool setShadowChannelMaskA(uint16_t mask)** write all channels at once.
- **uint16_t getShadowChannelMaskA()** read shadow registers 
- **bool setShadowChannelMaskB(uint16_t mask)** write all channels at once.
- **uint16_t getShadowChannelMaskB()** read shadow registers

prepare per channel

- **bool isOpenShadowChannelA(uint8_t channel)** read status of specific channel in shadow registers.
- **void openShadowChannelA(uint8_t channel)** prepare a specific channel to open
- **void closeShadowChannelA(uint8_t channel)** prepare a specific channel to close
- **bool isOpenShadowChannelB(uint8_t channel)** read status of specific channel in shadow registers.
- **void openShadowChannelB(uint8_t channel)** prepare a specific channel to open.
- **void closeShadowChannelB(uint8_t channel)** prepare a specific channel to close.


### MUX interface

The MUX interface allows one channel to be open at a time.

- **void MUXA(uint8_t channel)** if channel < 16 only that channel will be selected. All other values will select no channel.
- **uint8_t getMUXA()** returns the selected channel. 255 means none selected.
- **void MUXB(uint8_t channel)** if channel < 16 only that channel will be selected. All other values will select no channel.
- **uint8_t getMUXB()** returns the selected channel. 255 means none selected.


### FULL CONTROL interface

full control per channel, any combination is possible.
Use with care as these can interfere e.g. with the PAIR interface.
All functions return false if channel > 15.

- **bool openA(uint8_t channel)** idem
- **bool openB(uint8_t channel)** idem
- **bool closeA(uint8_t channel)** idem
- **bool closeB(uint8_t channel)** idem


### LOW LEVEL CONTROL interface

Check datasheet for these values of the registers.

- **uint8_t readRegister(uint8_t reg)** read low level device register.
- **int writeRegister(uint8_t reg, uint8_t value)** write value to device register.


### Misc

- **int lastError()** returns the last error, limited to I2C for now.


## Error codes

to be elaborated


## Future

- test behaviour
- test I2C speed.
- measure performance
- optimize low level bit set/clr/get read/write 2bytes at once.
- write unit tests.
- error handling
- improve documentation
- initial values parameter for begin()?


## Operation

See examples
