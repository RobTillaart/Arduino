
[![Arduino CI](https://github.com/RobTillaart/AD5370/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AD5370/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AD5370/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AD5370/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AD5370/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AD5370.svg)](https://github.com/RobTillaart/AD5370/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AD5370/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AD5370.svg?maxAge=3600)](https://github.com/RobTillaart/AD5370/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AD5370.svg)](https://registry.platformio.org/libraries/robtillaart/AD5370)


# AD5370

Arduino library for the AD5370 40 channel 16 bit DAC over SPI.

## Description

**Experimental**

This library is to use the AD5370 device from a microcontroller.
This AD5370 device is quite unique as it controls **40 channels** of 16 bit DACs.
To set the DAC's fast it uses SPI and not I2C.
The 40 channels are split up in 5 groups of 8, and group 0 is special.
See datasheet for details.

Besides the DAC value per channel, the AD5370 supports a GAIN and OFFSET for every channel.

There are GROUP functions to set multiple channels in one call.

The device has two VREFs, VREF0 for group 0, and VREF1 for group 1,2,3,4.


The library is **NOT** tested with hardware yet. Feedback welcome.

**Read datasheet before use**

Readme.md to be elaborated (but time is up for now)

Feedback as always is welcome.


### Performance

Timing based upon dry run of the performance sketch (Arduino UNO).
It tests the duration of **setDAC()** as that is the most used. 
Times are for 1000 calls in microseconds.

|    SPI     |  TIME (us)  |  notes  |
|:----------:|:-----------:|:-------:|
|  250000    |    111708   |  very slow, think long distance.
|  500000    |     63708   |
|  1000000   |     39692   |
|  2000000   |     27660   |
|  4000000   |     21624   |  
|  8000000   |     18612   |
|  16000000  |     18612   |


### Related

Mainly other DAC devices.

- https://github.com/robtillaart/AD5370  this repo.
- https://github.com/RobTillaart/DAC8550 1 channel, 16 bit
- https://github.com/RobTillaart/DAC8551 1 channel, 16 bit
- https://github.com/RobTillaart/DAC8552 2 channel, 16 bit
- https://github.com/RobTillaart/DAC8554 4 channel, 16 bit
- https://github.com/RobTillaart/MCP_DAC 1, 2 channel, 8,10,12 bit
- https://github.com/RobTillaart/AD5680  (18 bit DAC)
- https://github.com/RobTillaart/MAX520 I2C, 4, 8 channel, 8 bit
- https://github.com/RobTillaart/MCP4725 I2C, 1 channel, 12 bit


## Interface

```cpp
#include "AD5370.h"
```

### Constructor

- **AD5370(uint8_t select, uint8_t reset, uint8_t clear, \__SPI_CLASS__ \* mySPI = &SPI)** Hardware SPI
- **AD5370(uint8_t select, uint8_t reset, uint8_t clear, uint8_t dataIn, uint8_t dataOut, uint8_t clock)** Software SPI
- **void begin()** initialize internals.
- **setBusyPin(uint8_t busyPin)** idem.
- **setLDACPin(uint8_t ldacPin)** idem.


### Base commands

```
  channel = 0..39
  DAC value = 0..65535
```

- **bool setDAC(uint8_t channel, uint16_t value)**     //  AB register
- **bool setGain(uint8_t channel, uint16_t value)**    //  M  register
- **bool setOffset(uint8_t channel, uint16_t value)**  //  C  register


### Group Commands

Datasheet Table 11 - column 000 + column 110 + column 111

- **bool setAllAllDAC(uint16_t value)** Sets all channels to the same value.
Value = 0..65535.
- **bool setGroupAllChannelDAC(uint8_t group, uint16_t value)** Set all channels 
within a group to the same value. Group = 0..4, value = 0..65535.
- **bool setAllGroupChannelDAC(uint8_t channel, uint16_t value)** Set a channel
for all groups to the same value. channel = 0..7, value = 0..65535.
- **bool set1234GroupChannelDAC(uint8_t channel, uint16_t value)** Set a channel
for groups 1-4 to the same value. channel = 0..7, value = 0..65535.


### Special Functions

See datasheet + Table 12 + 13 + 14 + 15

Read datasheet for appropriate values and bit masks to use.
The functions do not all work as they should yet.
Need hardware to verify and test. Feedback welcome.

- **uint32_t NOP()**  //  used to read back, does not work yet
- **bool writeControlRegister(uint8_t mask)**
- **bool writeOffset0Register(uint16_t value)**   //  14 bit 0..16383
- **bool writeOffset1Register(uint16_t value)**   //  14 bit 0..16383
- **bool selectReadBackRegister(uint16_t selection)**
- **bool writeABSelectRegister(uint8_t reg, uint8_t value)**
- **bool blockABSelectRegister(uint8_t value)**


### SPI

- **void setSPIspeed(uint32_t speed)** set speed in Hz
- **uint32_t getSPIspeed()** returns set speed.


### Control Signals

Read datasheet for details.

- **bool isBusy()** returns LOW if device is busy.
Needs **setBusyPin()** to be called first.
- **void pulseLDAC()** sends a LATCH pulse to the device.
Needs **setLDACPin()** to be called first.
- **void reset()** idem.
- **void clear()** idem.


## Future

#### Must

- improve documentation
- get hardware to test

#### Should

- read back registers
- improve the special functions (also doc)
  - add defines for mask etc
  - add detailed links to datasheet
- find better name group commands - set1234GroupChannelDAC()

#### Could

- add examples
- create unit tests if possible
- move reset and clear pin to separate initializer?
  - like busy and reset?

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


