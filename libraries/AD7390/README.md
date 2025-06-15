
[![Arduino CI](https://github.com/RobTillaart/AD7390/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AD7390/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AD7390/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AD7390/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AD7390/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AD7390.svg)](https://github.com/RobTillaart/AD7390/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AD7390/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AD7390.svg?maxAge=3600)](https://github.com/RobTillaart/AD7390/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AD7390.svg)](https://registry.platformio.org/libraries/robtillaart/AD7390)


# AD7390

Arduino library for AD7390 / AD7391 12/10 bit SPI DAC.


## Description

**Experimental**

The library is experimental as not all functionality is tested with hardware.

|  type      |  bits  |  maxValue  |  range °C   |  notes    |
|:-----------|:------:|:----------:|:------------|:----------|
|  AD7390    |   12   |    4095    |  -40..+85   |
|  AD7391    |   10   |    1023    |  -40..+85   |
|  AD7391IAR |   10   |    1023    |  -40..+125  |

Check datasheet for all details.

The AD7390 has a Vref input which can be set to any voltage between 0 and Vdd (2.7 .. 5.5 Volt.
This allows the output to vary between 0 volt and approx. Vref -1 LSB. 
See datasheet page 8.

The device does not support reading the set value, so the library caches the 
last value set to provide this.
Furthermore the library provides a "percentage" functions to set and get the output
in a range from 0 to 100.0 %.

As always feedback is welcome.


### Hardware

See datasheet page 4.

```
        top view
       +--------+
   LD  | 1    8 |  Vref
  CLK  | 2    7 |  Vdd
  SDI  | 3    6 |  Vout
  CLR  | 4    5 |  GND
       +--------+

```

### Related

Mainly other DAC libraries.

- https://github.com/RobTillaart/AD7390 1 channel 12/10 bit SPI
- https://github.com/RobTillaart/DAC8550 1 channel, 16 bit
- https://github.com/RobTillaart/DAC8551 1 channel, 16 bit
- https://github.com/RobTillaart/DAC8552 2 channel, 16 bit
- https://github.com/RobTillaart/DAC8554 4 channel, 16 bit
- https://github.com/RobTillaart/MCP_DAC 1, 2 channel, 8,10,12 bit
- https://github.com/RobTillaart/AD5680  (18 bit DAC)
- https://github.com/RobTillaart/MAX520 I2C, 4, 8 channel, 8 bit
- https://github.com/RobTillaart/MCP4725 I2C, 1 channel, 12 bit


## Performance

TODO


## Interface

```cpp
#include "AD7390.h"
```

### Constructors

- **AD7390(uint8_t select, uint8_t clear, SPIClassRP2040 \* mySPI = &SPI)** constructor HW SPI (RP2040 specific)
- **AD7390(uint8_t select, uint8_t clear, SPIClass \* mySPI = &SPI)** constructor HW SPI
- **AD7390(uint8_t select, uint8_t clear, uint8_t dataOut, uint8_t clock)** constructor SW SPI
- **AD7391(uint8_t select, uint8_t clear, SPIClassRP2040 \* mySPI = &SPI)** constructor HW SPI (RP2040 specific)
- **AD7391(uint8_t select, uint8_t clear, SPIClass \* mySPI = &SPI)** constructor HW SPI
- **AD7391(uint8_t select, uint8_t clear, uint8_t dataOut, uint8_t clock)** constructor SW SPI

Note: 
- hardware SPI is 10+ times faster on an UNO than software SPI.
- software SPI on ESP32 is about equally fast as hardware SPI.

### Base

- **void begin(uint16_t value)** value is the initial value.
- **void clear()** resets the device to 0.

### Value

- **bool setValue(uint16_t value)** sets the value of the DAC. 
Returns false if value > maxValue. 
- **uint16_t getValue()** returns the current value (from cache).
- **uint16_t getMaxValue()** returns 4095 for AD7390 and 1023 for AD7391.

### Percentage

- **bool setPercentage(float percentage)** sets the value of the DAC as percentage 0..100.
Note the actual value set gets rounded.
Returns false if percentage < 0 or > 100. 
- **float getPercentage()** returns the percentage set, calculated from the value.
The percentage can differ a small bit from the percentage set. 

### Hardware SPI

To be used only if one needs a specific speed for hardware SPI.  
Has no effect on software SPI.

- **void setSPIspeed(uint32_t speed)** set SPI transfer rate.
- **uint32_t getSPIspeed()** returns SPI transfer rate.

### Debugging

- **bool usesHWSPI()** returns true / false depending on constructor used.


## Future


#### Must

- improve documentation
- test with hardware

#### Should

- add reference voltage functions. (See .h)
- extend unit tests
- add examples

#### Could


#### Wont



## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

