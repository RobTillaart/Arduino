
[![Arduino CI](https://github.com/RobTillaart/MCP23017_RT/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MCP23017_RT/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MCP23017_RT/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MCP23017_RT/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MCP23017_RT/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MCP23017_RT.svg)](https://github.com/RobTillaart/MCP23017_RT/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MCP23017_RT/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MCP23017_RT.svg?maxAge=3600)](https://github.com/RobTillaart/MCP23017_RT/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MCP23017.svg)](https://registry.platformio.org/libraries/robtillaart/MCP23017)


# MCP23017_RT

Arduino library for MCP23017 16 channel I2C port expander.


## Description

This library gives easy control over the 16 pins of a (I2C) MCP23017 chip.

This IC is strongly related tot the MCP23S17 SPI port expander - https://github.com/RobTillaart/MCP23S17
Programming Interface is kept the same as much as possible.

Since 0.3.1 the **digitalWrite(pin, value)** is optimized. 
If a pin is not changed it will not be written again to save time.

#### REV D - June 2022

The I2C IO expander MCP23017 has changed according to the new data sheet. It is now a 14/16-bit IO expander.
The pins GPA7 and GPB7 have lost their input mode, output mode still works.
The chips look the same and did not change names.
This implies it not possible to read 8 bits in parallel at the exact same moment any more.
The REV D version now need reading both A and B register to get 8 bits parallel (with a minor delay).

Details see:

- https://hackaday.com/2023/02/03/mcp23017-went-through-shortage-hell-lost-two-inputs/
- https://ww1.microchip.com/downloads/aemDocuments/documents/APID/ProductDocuments/DataSheets/MCP23017-Data-Sheet-DS20001952.pdf

Note: the library has no provisions (yet) for detecting DEV D chips or handle them in a special way.


#### Related

16 bit port expanders

- https://github.com/RobTillaart/MCP23017_RT
- https://github.com/RobTillaart/MCP23S17
- https://github.com/RobTillaart/PCF8575


8 bit port expanders

- https://github.com/RobTillaart/MCP23008
- https://github.com/RobTillaart/MCP23S08
- https://github.com/RobTillaart/PCF8574


## Interface

```cpp
#include "MCP23017.h"
```


### Constructor

- **MCP23017(uint8_t address, TwoWire \*wire = &Wire)** constructor, with default Wire interface.  
Can be overruled with Wire0..WireN.
- **bool begin()** for UNO, returns true if successful.
- **bool begin(uint8_t sda, uint8_t scl)** for ESP32, returns true if successful.
- **bool isConnected()** returns true if connected, false otherwise.


### Single pin interface

- **bool pinMode(uint8_t pin, uint8_t mode)** pin = 0..15, mode = INPUT, OUTPUT. Returns true if successful.
- **bool digitalWrite(uint8_t pin, uint8_t value)** pin = 0..15, value = LOW(0) HIGH (!0). Returns true if successful.
- **uint8_t digitalRead(uint8_t pin)** pin = 0..15, returns LOW or HIGH, might set the lastError();
- **bool setPolarity(uint8_t pin, bool reversed)** pin = 0..15, set reversed flag. Returns true if successful.
- **bool getPolarity(uint8_t pin, bool &reversed)** pin = 0..15, reads reversed flag. Returns true if successful.
- **bool setPullup(uint8_t pin, bool pullup)** pin = 0..15, set pull-up flag. Returns true if successful.
- **bool getPullup(uint8_t pin, bool &pullup)** pin = 0..15, reads pull-up flag. Returns true if successful.


### 8 pins interface

- **bool pinMode8(uint8_t port, uint8_t value)** port = 0..1, value = 0..255. Returns true if successful.
- **bool write8(uint8_t port, uint8_t value)** port = 0..1, value = 0..255. Returns true if successful.
- **uint8_t read8(uint8_t port)** port = 0..1, reads 8 pins into one byte.
- **bool setPolarity8(uint8_t port, uint8_t mask)** port = 0..1, sets polarity 
for 8 channels at once.
Returns true if successful.
- **bool getPolarity8(uint8_t port, uint8_t &mask)** port = 0..1, reads polarity of 8 channels at once.
Returns true if successful.
- **bool setPullup8(uint8_t port, uint8_t mask)** port = 0..1, sets pull-up for 8 channels at once.
Returns true if successful.
- **bool getPullup8(uint8_t port, uint8_t &mask)** port = 0..1, reads pull-up for 8 channels at once.
Returns true if successful.


### 16 pins interface

- **bool pinMode16(uint16_t value)** value = 0..0xFFFF. Returns true if successful.
- **bool write16(uint16_t value)** value = 0..0xFFFF. Returns true if successful.
- **uint16_t read16()** reads 16 pins into an uint16_t.
- **bool setPolarity16(uint16_t mask)** sets polarity for 16 channels.
Returns true if successful.
- **bool getPolarity16(uint16_t &mask)** reads polarity of 16 channels.
Returns true if successful.
- **bool setPullup16(uint16_t mask)** sets pull-up for 16 channels.
Returns true if successful.
- **bool getPullup16(uint16_t &mask)** reads pull-up for 16 channels.
Returns true if successful.


### Error codes

If one of the above functions return false, there might be an error.

- **int lastError()** Above functions set an error flag that can be read with this function.  
Reading it will reset the flag to **MCP23017_OK**.

|  Description           |  Value  |
|:-----------------------|:-------:|
|  MCP23017_OK           |  0x00   |
|  MCP23017_PIN_ERROR    |  0x81   |
|  MCP23017_I2C_ERROR    |  0x82   |
|  MCP23017_VALUE_ERROR  |  0x83   |
|  MCP23017_PORT_ERROR   |  0x84   |


## Future


#### Must

- Improve and extend documentation
- add examples

#### Should

- extend error codes
- optimize code - squeeze footprint
- investigate if REV D chips can be detected.

#### Could

- initial value (16 bit?) as begin parameter (breaking change)
  - depends on input output pull-up etc
- investigate auto address increment

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

