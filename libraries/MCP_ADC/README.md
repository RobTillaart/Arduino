
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
The chips are communicates with SPI and support both hardware SPI or optional software SPI.


|  type     |  bits  |  chan  |  notes  |
|:----------|:------:|:------:|:--------|
|  MCP3001  |   10   |    1   |  not tested yet.
|  MCP3002  |   10   |    2   |
|  MCP3004  |   10   |    4   |
|  MCP3008  |   10   |    8   |
|  MCP3201  |   12   |    1   |  test, see #13
|  MCP3202  |   12   |    2   |
|  MCP3204  |   12   |    4   |
|  MCP3208  |   12   |    8   |


Current version allows manual override of the hardware SPI clock as the speed is not
optimized per ADC type. 

The MCP ADC allow single mode which compares voltage of a single channel against GND.
Furthermore they allow a differential mode which compares two channels **IN+** and **IN-** 
to each other. if the **IN+** is equal or below **IN-** the ADC will return 0. 

Build into the library is a delta mode which is a software enhanced differential mode.
This delta mode can return negative values too. 


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

If the pins are not set in the constructor, the class will automatically
use the hardware SPI, otherwise it will use software SPI.

- **MCP3001(uint8_t dataIn, uint8_t dataOut, uint8_t clock)** constructor 10 bit ADC 1 channel.
- **MCP3002(uint8_t dataIn, uint8_t dataOut, uint8_t clock)** constructor 10 bit ADC 2 channel.
- **MCP3004(uint8_t dataIn, uint8_t dataOut, uint8_t clock)** constructor 10 bit ADC 4 channel.
- **MCP3008(uint8_t dataIn, uint8_t dataOut, uint8_t clock)** constructor 10 bit ADC 8 channel.
- **MCP3201(uint8_t dataIn, uint8_t dataOut, uint8_t clock)** constructor 12 bit ADC 1 channel.
- **MCP3202(uint8_t dataIn, uint8_t dataOut, uint8_t clock)** constructor 12 bit ADC 2 channel.
- **MCP3204(uint8_t dataIn, uint8_t dataOut, uint8_t clock)** constructor 12 bit ADC 4 channel.
- **MCP3208(uint8_t dataIn, uint8_t dataOut, uint8_t clock)** constructor 12 bit ADC 8 channel.
- **void begin(uint8_t select)** set select pin.
- **uint8_t channels()** returns the number of channels.
- **int16_t maxValue()** returns maxReading of ADC, typical 1023 or 4095.
This makes it easy to calculate relative measurements.


#### Base

- **int16_t analogRead(uint8_t channel)** reads the value of a single channel.
- **void analogReadMultiple(uint8_t channels[], uint8_t numChannels, int16_t readings[])**
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

| Channel | diff IN+ | diff IN- | MCP            |
|:-------:|:--------:|:--------:|---------------:|
|   0     |    0     |    1     | 3x02/3x04/3x08 |
|   1     |    1     |    0     | 3x02/3x04/3x08 |
|   2     |    2     |    3     |      3x04/3x08 |
|   3     |    3     |    2     |      3x04/3x08 |
|   4     |    4     |    5     |           3x08 |
|   5     |    5     |    4     |           3x08 |
|   6     |    6     |    7     |           3x08 |
|   7     |    7     |    6     |           3x08 |

Note: the MCP3x01 are not included in this table, not investigated yet.


### Debug

- **bool usesHWSPI()** returns true if HW SPI is used.
- **uint32_t count()** returns number of channels read since start.


### ESP32 specific

- **void selectHSPI()** in case hardware SPI, the ESP32 has two options HSPI and VSPI.
- **void selectVSPI()** see above.
- **bool usesHSPI()** returns true if HSPI is used.
- **bool usesVSPI()** returns true if VSPI is used.

The **selectVSPI()** or the **selectHSPI()** needs to be called 
BEFORE the **begin()** function.


#### setGPIOpins() experimental

- **void setGPIOpins(uint8_t clk, uint8_t miso, uint8_t mosi, uint8_t select)** 
overrule GPIO pins of ESP32 for hardware SPI. 
This function needs to be called AFTER the **begin()** function.

in code:
```cpp
void setup()
{
  MCP.selectVSPI();
  MCP.begin(15);
  MCP.setGPIOpins(CLK, MISO, MOSI, SELECT);  // SELECT should match the parameter of begin()
}
```

This implementation might change in the future, e.g. leave out the select pin as it is
already known in the code.


## About SPI Speed

See https://github.com/RobTillaart/MCP_ADC/issues/3

The default SPI speed is reduced to 1 MHz. 
This is the value recommended in the datasheet for 2.7V.

In a test with an ESP32 (3.3V) the library showed stable results 
at 4 MHz and at 6 MHz it was almost good.

The maximum value read at 6 MHz was 1020 instead of 1023  (MCP3008) 
which indicates that the last 2 bits got lost probably due to signal 
deformation.

|  Board  |  Voltage  |  safe   |   max   |
|:-------:|:---------:|:-------:|:-------:|
|  ESP32  |   2.7V    |  1 MHz  |  4 MHz  |
|  UNO    |   5.0V    |  2 MHz  |  4 MHz  |


For hardware SPI the ESP32 uses the VSPI pins. (see ESP examples).


## analogReadMultiple() 

Since version 0.2.0 the **analogReadMultiple(channels[], numChannels, readings[])** 
is added to the interface.
(See https://github.com/RobTillaart/MCP_ADC/pull/11 - Thanks to Alex Uta).

This function allows to read multiple channels in one call, which improves 
the performance of fetching new readings from the MCP_ADC device.
The amount of gain differs per platform, so run your own performance test.

Besides fetching all ADC's in one call this function also allows to fetch
the data from a specific channel multiple times, e.g. to be averaged.
Other patterns are possible. 
These scenarios need still to be tested in practice.

Finally **analogReadMultiple()** can be used to read only one channel too
by using numChannels = 1.


## MCP3001, MCP3201 experimental

Since 0.2.0 code for the MCP3201 has been added.
The first tests are done (see #13) which showed that the 0.2.0 implementation
was not correct. 
This has been fixed in the 0.2.1 version.

Note that not all function calls make sense for the MCP3201 and MCP3001 as these 
devices only have one channel. So use the library carefully.

Feedback is as always welcome. 


## Future

#### Must

- improve documentation
- test analogReadMultiple() scenario's
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

