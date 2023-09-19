
[![Arduino CI](https://github.com/RobTillaart/AD5680/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AD5680/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AD5680/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AD5680/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AD5680/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AD5680.svg)](https://github.com/RobTillaart/AD5680/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AD5680/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AD5680.svg?maxAge=3600)](https://github.com/RobTillaart/AD5680/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AD5680.svg)](https://registry.platformio.org/libraries/robtillaart/AD5680)


# AD5680

Arduino library for the AD5680 series digital analog convertor (18 bit).


## Description

**Experimental**

The AD5680 is a 18 bit DAC on paper but in fact it is a 16 bit DAC.
To get the 18 bits a 2 bit duty cycle is used to implement the last two bits.
This means that the output voltage will be fluctuating unless the two
least significant bits are 0 (zero). To dampen this fluctuation the datasheet
advises to add a LOW pass filter after the output.

Feedback, issues, improvements are welcome. 
Please file an issue on GitHub.

#### Related

- https://github.com/RobTillaart/AD56x8 (multi channel)
- https://github.com/RobTillaart/AD568X (single channel lower resolution)
- https://github.com/RobTillaart/MCP_DAC (SPI interface)


## Interface

```cpp
#include "AD5680.h"
```

### Base class

- **AD5680(uint8_t slaveSelect)** constructor base class, sets HW SPI.
Sets internal values to zero.
- **AD5680(uint8_t spiData, uint8_t spiClock, uint8_t slaveSelect)** constructor, 
sets SW SPI.
Sets internal values to zero.
- **begin()** initializes the SPI and sets internal state.


### Set DAC

- **bool setValue(uint16_t value)** set value to the output immediately, 
effectively a prepare + update in one call.
Returns false if value out of range.
- **uint16_t getValue()** returns set OR prepared value.
At power up the DAC's will be reset to 0 Volt.
- **bool setPercentage(float percentage)** idem.
- **float getPercentage()** idem.


#### SPI 

- **void setSPIspeed(uint32_t speed)** sets SPI clock in **Hz**,
please read datasheet of the ADC first to get optimal speed.
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
overrule GPIO pins of ESP32 for hardware SPI. Needs to be called AFTER the **begin()** function.

Note: earlier experiments shows that on a ESP32 SW-SPI is equally fast as 
HW-SPI and in fact a bit more stable. 
The SW pulses are a bit slower than the HW pulses and therefore more square. 
The HW-SPI has some overhead SW-SPI hasn't. 


## Future

#### Must

- improve documentation
- get test hardware
- test the library


#### Should

- add examples
  - performance


#### Could

- make a 16 bit interface?

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,



