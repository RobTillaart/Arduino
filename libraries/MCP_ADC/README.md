
[![Arduino CI](https://github.com/RobTillaart/MCP_ADC/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MCP_ADC/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MCP_ADC/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MCP_ADC/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MCP_ADC/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MCP_ADC.svg)](https://github.com/RobTillaart/MCP_ADC/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MCP_ADC/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MCP_ADC.svg?maxAge=3600)](https://github.com/RobTillaart/MCP_ADC/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MCP_ADC.svg)](https://registry.platformio.org/libraries/robtillaart/MCP_ADC)


# MCP_ADC

Arduino library for MCP3001 MCP3002 MCP3004 MCP3008 MCP3201 MCP3202 MCP3204 MCP3208 and compatibles.


## Description

This library reads the ADC ports of the MCP ADC convertors. 
The chips are 1 to 8 channels, 10 or 12 bit and communicates with SPI.
The library supports both hardware SPI and software SPI.


|  type     |  bits  |  channels  |  notes  |
|:----------|:------:|:----------:|:--------|
|  MCP3001  |   10   |      1     |  not tested yet.
|  MCP3002  |   10   |      2     |
|  MCP3004  |   10   |      4     |
|  MCP3008  |   10   |      8     |
|  MCP3201  |   12   |      1     |  test, see #13
|  MCP3202  |   12   |      2     |
|  MCP3204  |   12   |      4     |
|  MCP3208  |   12   |      8     |


Current version allows manual override of the hardware SPI clock as the speed is not
optimized per ADC type. 

The MCP ADC's allow a single mode read which compares voltage of a single channel against GND.
Furthermore they allow a differential mode which compares two channels **IN+** and **IN-** 
to each other. 
If the **IN+** is equal or below **IN-** the ADC will return 0.

Build into the library is a delta mode which is a software enhanced differential mode.
This delta mode can return negative values too. 


#### 0.5.0 Breaking change

Version 0.5.0 introduced a breaking change to improve handling the SPI dependency.
The user has to call **SPI.begin()** or equivalent before calling **MCP.begin()**.
Optionally the user can provide parameters to the **SPI.begin(...)**


#### 0.4.0 Breaking change

The version 0.4.0 has breaking changes in the interface. 
The rationale is that the programming environment of the **Arduino ESP32 S3** 
board uses a remapping by means of the include file **io_pin_remap.h**.
This file remaps the pins of several core Arduino functions. 
The remapping is implemented by #define macros and these implement "hard" text 
replacements without considering context. 
The effect is that methods from this class (and several others) which have the same 
name as those Arduino core functions will be remapped into something not working.

The following library functions have been renamed:

|  old name             |  new name        |  notes  |
|:----------------------|:-----------------|:--------|
|  analogRead()         |  read()          |  bugfix.
|  analogReadMultiple() |  readMultiple()  |  for consistency.


#### 0.3.0 Breaking change

The version 0.3.0 has breaking changes in the interface. 
The essence is removal of ESP32 specific code from the library. 
This makes it possible to support the ESP32-S3 and other processors in the future. 
Also it makes the library a bit simpler to maintain.


#### Related

- https://gammon.com.au/adc  tutorial about ADC's (UNO specific)
- https://github.com/RobTillaart/ADS1x15  (12 & 16 bit ADC, I2C, slow)
- https://github.com/RobTillaart/PCF8591  (8 bit ADC + 1 bit DAC)
- https://github.com/RobTillaart/MCP_DAC


## Interface

```cpp
#include "MCP_ADC.h"
```

#### Constructors

- **MCP_ADC(SPIClassRP2040 \* mySPI = &SPI)** hardware constructor RP2040
- **MCP_ADC(SPIClass \* mySPI = &SPI)** hardware constructor other
- **MCP_ADC(uint8_t dataIn, uint8_t dataOut, uint8_t clock)**

The derived classes have both constructors with same parameters.
- **MCP3001(...)** constructor 10 bit ADC 1 channel.
- **MCP3002(...)** constructor 10 bit ADC 2 channel.
- **MCP3004(...)** constructor 10 bit ADC 4 channel.
- **MCP3008(...)** constructor 10 bit ADC 8 channel.
- **MCP3201(...)** constructor 12 bit ADC 1 channel.
- **MCP3202(...)** constructor 12 bit ADC 2 channel.
- **MCP3204(...)** constructor 12 bit ADC 4 channel.
- **MCP3208(...)** constructor 12 bit ADC 8 channel.
- **void begin(uint8_t select)** set select pin.
- **uint8_t channels()** returns the number of channels.
- **int16_t maxValue()** returns maxReading of ADC, typical 1023 or 4095.
This makes it easy to calculate relative measurements.


#### Base

- **int16_t read(uint8_t channel)** reads the value of a single channel.
- **void readMultiple(uint8_t channels[], uint8_t numChannels, int16_t readings[])**
reads multiple channels in one call. See section below.
- **int16_t differentialRead(uint8_t channel)** reads differential between two channels.  
Check datasheet for details.  
Note if the **IN+** is equal or below **IN-** this function will return 0.
- **int16_t deltaRead(uint8_t channel)** reads differential like above however it
will return a negative value if **IN+** is below **IN-**.
- **void setSPIspeed(uint32_t speed)** sets SPI clock in **Hz**, please read datasheet
of the ADC first to get optimal speed.
- **uint32_t getSPIspeed()** gets current speed in **Hz**.


### Differential channel table:

| Channel | diff IN+ | diff IN- | 3x02 | 3x04 | 3x08 |
|:-------:|:--------:|:--------:|:----:|:----:|:----:|
|   0     |    0     |    1     |  V   |  V   |  V   |
|   1     |    1     |    0     |  V   |  V   |  V   |
|   2     |    2     |    3     |      |  V   |  V   |
|   3     |    3     |    2     |      |  V   |  V   |
|   4     |    4     |    5     |      |      |  V   |
|   5     |    5     |    4     |      |      |  V   |
|   6     |    6     |    7     |      |      |  V   |
|   7     |    7     |    6     |      |      |  V   |


Note: the MCP3x01 ADC's are not included in this table, not investigated yet.


### Debug

- **bool usesHWSPI()** returns true if hardware SPI is used.
- **uint32_t count()** returns number of channels reads since start.


## About SPI Speed

See https://github.com/RobTillaart/MCP_ADC/issues/3

The default SPI speed is reduced to 1 MHz. 
This is the value recommended in the datasheet for 2.7 Volt.

In a test with an ESP32 (3.3V) the library showed stable results 
at 4 MHz and at 6 MHz it was almost good.

The maximum value read at 6 MHz was 1020 instead of 1023 (MCP3008) 
which indicates that the last 2 bits got lost probably due to signal 
deformation.

|  Board  |  Voltage  |  safe   |   max   |
|:-------:|:---------:|:-------:|:-------:|
|  ESP32  |   2.7V    |  1 MHz  |  4 MHz  |
|  UNO    |   5.0V    |  2 MHz  |  4 MHz  |


For hardware SPI the ESP32 uses the VSPI pins. (see ESP examples).


## ReadMultiple()

Since version 0.2.0 the **readMultiple(channels[], numChannels, readings[])** 
is added to the interface.
(See https://github.com/RobTillaart/MCP_ADC/pull/11 - Thanks to Alex Uta).

This function allows to read multiple channels in one call, which improves 
the performance of fetching new readings from the MCP_ADC device.
The amount of gain differs per platform, so run your own performance test.

Besides fetching all ADC's in one call this function also allows to fetch
the data from a specific channel multiple times, e.g. to be averaged.
Other patterns are possible. 
These scenarios need still to be tested in practice.

Finally **readMultiple()** can be used to read only one channel too
by using numChannels = 1.


## MCP3001, MCP3201 experimental

Since 0.2.0 code for the MCP3201 has been added.
The first tests are done (see #13) which showed that the 0.2.0 implementation
was not correct. 
This has been fixed in the 0.2.1 version.

Note that not all function calls make sense for the MCP3201 and MCP3001 as these 
devices only have one channel. So use the library carefully with these ADC's.

Feedback is as always welcome. 


## Future

#### Must

- improve documentation
- test readMultiple() scenario's
- MCP3201 buy hardware and test

#### Should

- improve SWSPI for AVR 
  (code is under test for MCP23S17)


#### Could


#### Wont

- get / setF(float A, float B) => float readF(channel)   output = A\*value + B;
  it actually does float mapping. As it implies the same mapping for all it might 
  not be that useful => check multiMap library.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

