
[![Arduino CI](https://github.com/RobTillaart/MCP_POT/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MCP_POT/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MCP_POT/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MCP_POT/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MCP_POT/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MCP_POT.svg)](https://github.com/RobTillaart/MCP_POT/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MCP_POT/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MCP_POT.svg?maxAge=3600)](https://github.com/RobTillaart/MCP_POT/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MCP_POT.svg)](https://registry.platformio.org/libraries/robtillaart/MCP_POT)


# MCP_POT

Arduino library for MCP41xxx and MCP42xxx SPI based digital potentiometers.


## Description

**Experimental** to be tested on hardware.

The MCP_POT library implements digital potentiometers.
The chips have 1 or 2 potentiometers, 10 KΩ, 50 KΩ and 100 KΩ and communicates over SPI.
The library supports both hardware SPI and software SPI.


|  type      |   KΩ   |  potentiometers  |  notes  |
|:-----------|:------:|:----------------:|:--------|
|  MCP41010  |   10   |        1         |  not tested yet.
|  MCP41050  |   50   |        1         |
|  MCP41100  |  100   |        1         |
|  MCP42010  |   10   |        2         |  daisy chain allowed
|  MCP42050  |   50   |        2         |
|  MCP42100  |  100   |        2         |


Current version allows manual override of the hardware SPI clock. 

Alt-234 = Ω


#### 0.2.0 Breaking change

Version 0.2.0 introduced a breaking change to improve handling the SPI dependency.
The user has to call **SPI.begin()** or equivalent before calling **AD.begin()**.
Optionally the user can provide parameters to the **SPI.begin(...)**


#### Related

Mainly other digital potentiometers.

- https://github.com/RobTillaart/AD520x
- https://github.com/RobTillaart/AD524X
- https://github.com/RobTillaart/AD5245
- https://github.com/RobTillaart/AD5144A
- https://github.com/RobTillaart/AD5263
- https://github.com/RobTillaart/X9C10X


## Interface

```cpp
#include "MCP_POT.h"
```

#### Constructors

Base class.
- **MCP_POT(uint8_t select, uint8_t reset, uint8_t shutdown, SPIClassRP2040 \* mySPI = &SPI)** hardware constructor RP2040
- **MCP_POT(uint8_t select, uint8_t reset, uint8_t shutdown, SPIClass \* mySPI = &SPI)** hardware constructor other
- **MCP_POT(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut, uint8_t clock)**

The derived classes have same constructors with same parameters as the base class.
- **MCP41010(...)** constructor 1 potentiometer, 10 KΩ
- **MCP41050(...)** constructor 1 potentiometer, 50 KΩ
- **MCP41100(...)** constructor 1 potentiometer, 100 KΩ
- **MCP42010(...)** constructor 2 potentiometer, 10 KΩ
- **MCP42050(...)** constructor 2 potentiometer, 50 KΩ
- **MCP42100(...)** constructor 2 potentiometer, 100 KΩ
- **void begin(uint8_t value = MCP_POT_MIDDLE_VALUE)**
- **void reset(uint8_t value = MCP_POT_MIDDLE_VALUE)**
- **bool setValue(uint8_t value)** set both potmeters.
- **bool setValue(uint8_t pm, uint8_t value)**
- **uint8_t getValue(uint8_t pm = 0)**


#### SPI

- **void setSPIspeed(uint32_t speed)** sets SPI clock in **Hz**.
- **uint32_t getSPIspeed()** gets current speed in **Hz**.


#### Miscellaneous

- **uint8_t pmCount()** returns the number of potmeters.
- **void powerOn()** set SHUTDOWN pin HIGH (device enabled).
- **void powerOff()**  set SHUTDOWN pin LOW (device disabled).
- **bool isPowerOn()** idem.


#### Debug

- **bool usesHWSPI()** returns true if hardware SPI is used.


## About SPI Speed

SPI code is based upon MCP_ADC.

The default SPI speed is reduced to 1 MHz. 
This is the value recommended in the datasheet for 2.7 Volt.

|  Board  |  Voltage  |  safe   |   max   |
|:-------:|:---------:|:-------:|:-------:|
|  ESP32  |   2.7V    |  1 MHz  |  4 MHz  |
|  UNO    |   5.0V    |  2 MHz  |  4 MHz  |

For hardware SPI the ESP32 uses the VSPI pins. (see ESP examples).


## Daisy Chaining

Not supported yet. (need hardware)

The MCP42xxx series have a **dataout** pin which allows to daisy chain the devices.
The devices must share a CS signal, or at least all of them should have been 
selected to forward bytes.
WHen the CS signal goes HIGH again, all devices will simultaneously change to their
new values. However per device at most one potmeter can be set in a daisy chain, or both have the same value.


## Future

#### Must

- improve documentation
- buy hardware and test

#### Should

- investigate and implement daisy chaining of MCP42xxx


#### Could

- improve SWSPI for AVR 
  (code is under test for MCP23S17)


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

