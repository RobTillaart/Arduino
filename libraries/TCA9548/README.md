
[![Arduino CI](https://github.com/RobTillaart/TCA9548/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/TCA9548/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/TCA9548/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/TCA9548/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/TCA9548/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/TCA9548/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/TCA9548.svg?maxAge=3600)](https://github.com/RobTillaart/TCA9548/releases)


# TCA9548

Arduino Library for TCA9548 I2C multiplexer.


## Description

Library for the TCA9548 and TCA9548a I2C multiplexer.
The library allows you to enable 0 to 7 I2C channels (ports) uniquely or simultaneously.
This is especially useful if you have multiple devices/sensors that have a fixed address,
or you have address conflicts between I2C devices

**Warning**
The library is not tested extensively.

I2C address is 0x70 .. 0x77.

The library caches the channels enabled, and if a channel is enabled,
it will not be enabled again (low level) to optimize performance.


## Interface


### Constructor

- **TCA9548(const uint8_t deviceAddress, TwoWire \*wire = &Wire)** Constructor, address = 0x70 .. 0x77, wire = Wire or WireN.
- **bool begin(uint8_t sda, uint8_t scl, uint8_t mask = 0x00)**  Set I2C pins for ESP32, set mask of channels to be enabled.
- **bool begin(uint8_t mask = 0x00)**  set mask of channels to be enabled.
- **bool isConnected()** returns true if address of the multiplexer is found on I2C bus.


### Find device

- **bool isConnected(uint8_t address)** returns true if arbitrary address is found on I2C bus.
This can be used to verify a certain device is available (or not) on an enabled channel.


### Channel functions

- **void enableChannel(uint8_t channel)** enables channel 0 .. 7. Multiple channels can be enabled in parallel.
- **void disableChannel(uint8_t channel)** disables channel 0 .. 7. Will not disable other channels.
- **void selectChannel(uint8_t channel)** enables a single channel 0 .. 7 uniquely. 
All other channels will be disabled, although these can be set again with enableChannel.
- **bool isEnabled(uint8_t channel)** returns true is a channel is enabled.
- **void setChannelMask(uint8_t mask)** enables 0 or more channels simultaneously with a bit mask.
- **uint8_t getChannelMask()** reads back the bit mask of the channels enabled.
- **void setResetPin(uint8_t resetPin)** sets the pin to reset the chip. (Not tested)
- **void reset()** trigger the reset pin.
- **int getError()** returns the last I2C error.


### Forced IO

When forced IO is set all writes and read - **getChannelMask()** - will go to the device.
If the flag is set to false it will cache the value of the channels enabled.
This will result in more responsive / faster calls. 
Note that writes are only optimized if the channels are already set.

- **void setForced(bool forced = false)** set forced write, slower but more robust. Default off.
- **bool getForced()** returns set flag.


## Operation

See example


## Future

- improve error handling + documentation.
- add examples
- test test and test
- improve documentation
- write unit test
- set an "always enabled" mask  (have to investigate the consequences)



