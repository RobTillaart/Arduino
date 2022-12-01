
[![Arduino CI](https://github.com/RobTillaart/AD56X8/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AD56X8/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AD56X8/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AD56X8/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AD56X8/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AD56X8/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AD56X8.svg?maxAge=3600)](https://github.com/RobTillaart/AD56X8/releases)


# AD56X8

Experimental Library for the AD56X8 series digital analog convertor.

NOTE: not yet tested, TODO buy hardware.

Feedback, issues, improvements are welcome. 
Please file an issue on GitHub.


## Description

The AD56X8 is an 8 channel DAC convertor, that has 12, 14 or 16 bit accuracy. 
Furthermore it is available in 2.5 V and 5.0 V version, see table below.

The device allows to set the outputs directly, or prepare them and update them simultaneously (Latch DAC). 

|   type   |  output  | resolution | power up  |
|:---------|:--------:|:----------:|:---------:|
| AD5668-1 |   2.5 V  |   16 bit   |   0.0 V   |
| AD5648-1 |   2.5 V  |   14 bit   |   0.0 V   |
| AD5628-1 |   2.5 V  |   12 bit   |   0.0 V   |
| AD5668-3 |   5.0 V  |   16 bit   | **2.5 V** |
| AD5668-2 |   5.0 V  |   16 bit   |   0.0 V   |
| AD5648-2 |   5.0 V  |   14 bit   |   0.0 V   |
| AD5628-2 |   5.0 V  |   12 bit   |   0.0 V   |


The library is usable but not functional complete yet. 
At least it lacks support for:
- RESET pin,
- LDAC pin,
- VREF pin.
- other points mentioned in future section below.


## Links

This library is partly inspired by https://github.com/bobhart/AD5668-Library, kudo's to Bob!
Discussed here - https://forum.arduino.cc/t/new-library-for-the-ad5668-dac/340393

Furthermore it has the SPI part from https://github.com/RobTillaart/MCP_DAC a.o.

Some differences between this library and Bob Harts. This library
- caches the values of all channels, so they can be read back.
- has derived classes for every specific type DAC.
This allows value range checking in the future. Not Implemented Yet.
- caches the LDAC mask, so it can be read back and updated.
- has extended (ESP32) SPI interface (similar and tested with MCP_DAC)
- allows to set SPI-speed.
- has faster software SPI transfer, on ESP32 this rivals HW SPI.
- MIT license instead of GNU v3


## Interface

```cpp
#include "AD56X8.h"
```

#### Base class

Should not be used to instantiate a device as the derived types have correct number of bits. 

- **AD56X8(uint8_t slaveSelect)** constructor base class, sets HW SPI. 
Uses default a 16 bit interface.
Sets internal values to zero.
- **AD56X8(uint8_t spiData, uint8_t spiClock, uint8_t slaveSelect)** constructor, sets SW SPI.
Uses default a 16 bit interface.
Sets internal values to zero.
- **begin()** initializes the SPI and sets internal state.


#### Set DAC

- **bool setValue(uint8_t channel, uint16_t value)** set value to the output immediately, effectively a prepare + update in one call.
Returns false if channel out of range.
- **uint16_t getValue(uint8_t channel)** returns set OR prepared value.
At power up the DAC's will be reset to 0 V except the AD5668-3 (2.5V).
- **bool prepareChannel(uint8_t channel, uint16_t value)** prepares the value for a channel.
Returns false if channel out of range.
- **bool updateChannel(uint8_t channel)** writes the prepared value to ADC.
Returns false if channel out of range.
- **void updateAllChannels()** writes all prepared channels to their ADC simultaneously by applying a SW latch pulse (LDAC).

NOte: the valid range of **value** is not checked by the library. 


#### LDAC

The AD56X8 has an LDAC register with one bit per channel. 
This is to configure which channels are updated simultaneously.
Read datasheet for details.

- **void setLDACmask(uint8_t mask = 0x00)** sets 8 channels with one call by using a bit mask. Default value 0x00 clears all channels.
- **uint8_t getLDACmask()** return the current (cached) LDAC bit mask, default = 0x00.
- **bool inLDACmask(uint8_t channel)** returns true if a channel is in the current LDAC bit mask.
Returns also false if channel is out of range.


#### Powermode

- **bool setPowerMode(uint8_t powerDownMode, uint8_t mask = 0x00)** powerDownMode = 0..3. 
Default is setting the channels to **PWR_NORMAL**.
Returns false if powerDownMode is out of range.

|  mode  |  define            |
|:------:|:-------------------|
|  0x00  | AD56X8_PWR_NORMAL  |
|  0x01  | AD56X8_PWR_1K      |
|  0x02  | AD56X8_PWR_100K    |
|  0x03  | AD56X8_PWR_TRI     |


#### Misc

- **void reset()** software reset.
- **bool setClearCode(uint8_t CCmode)** Set the startup value.
CCmode = 0..3, see table below. 
Returns false if mode out of range.

|  mode  |  define            |  notes  |
|:------:|:-------------------|:--------|
|  0x00  |  AD56X8_CC_0000    |
|  0x01  |  AD56X8_CC_8000    |
|  0x02  |  AD56X8_CC_FFFF    |
|  0x03  |  AD56X8_CC_NOP     | do not use => Read datasheet.


#### SPI 

- **void setSPIspeed(uint32_t speed)** sets SPI clock in **Hz**, please read datasheet
of the ADC first to get optimal speed.
- **uint32_t getSPIspeed()** gets current speed in **Hz**.
- **bool usesHWSPI()** returns true if HW SPI is used.


#### SPI ESP32 specific

("inherited" from MPC_DAC library)

- **void selectHSPI()** in case hardware SPI, the ESP32 has two options HSPI and VSPI.
- **void selectVSPI()** see above.
- **bool usesHSPI()** returns true if HSPI is used.
- **bool usesVSPI()** returns true if VSPI is used.

The **selectVSPI()** or the **selectHSPI()** needs to be called 
BEFORE the **begin()** function.

(experimental)
- **void setGPIOpins(uint8_t clk, uint8_t miso, uint8_t mosi, uint8_t select)** 
overrule GPIO pins of ESP32 for hardware SPI. needs to be called AFTER the **begin()** function.

Note: earlier experiments shows that on a ESP32 SW-SPI is equally fast as HW-SPI and in fact a bit more stable. 
The SW pulses are a bit slower than the HW pulses and therefore more square. The HW-SPI has some overhead SW-SPI hasn't. 


### Derived classes (preferred use)

The parameters for the specific constructors are identical 
to the base class.

- **AD5668_3(..)** constructor, 16 bit. 
Starts up at **midscale = 32768**.
- **AD5668(..)** constructor, 16 bit.
- **AD5648(..)** constructor, 14 bit.
- **AD5628(..)** constructor, 12 bit.


## Operation

The examples (should) show the basic working of the functions.
Note that the library is not tested with hardware yet.
(based upon datasheet)


## Future

#### Must
- update and improve documentation
- get test hardware
- test the library
- write unit test
- check TODO's in code

#### Should
- write examples
  - get/setValue
  - LDAC
  - power mode
- support for RESET pin
- support for LDAC pin
- support for EXTERNAL VREF
- investigate value range checking for AD5648 and AD5628
  - now setValue() returns false if value > max, 
  - should value be clipped instead?
- voltage interface(?)
  - convenient.
- **bool loadLDAC()** TODO?
- investigate different type for AD5668_3 (as it does midscale)

#### Could
- CCmode + reset implies start value for getValue(ch)
  - is this implementable? costs?


