
[![Arduino CI](https://github.com/RobTillaart/MCP23017_RT/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MCP23017_RT/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MCP23017_RT/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MCP23017_RT/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MCP23017_RT/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MCP23017_RT/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MCP23017_RT.svg?maxAge=3600)](https://github.com/RobTillaart/MCP23017_RT/releases)


# MCP23017_RT

Arduino library for MCP23017 16 channel I2C port expander.


## Description

This library gives easy control over the 16 pins of a (I2C) MCP23017 chip.

This IC is strongly related tot the MCP23S17 SPI port expander - https://github.com/RobTillaart/MCP23S17
Programming Interface is kept the same as much as possible.


## Interface

### Constructor

- **MCP23017(uint8_t address, TwoWire \*wire = &Wire)** constructor, with default Wire interface.  
Can be overruled with Wire0..WireN.
- **bool begin()** for UNO, returns true if successful.
- **bool begin(uint8_t sda, uint8_t scl)** for ESP32, returns true if successful.
- **bool isConnected()** returns true if connected, false otherwise.


### Single pin interface

- **bool pinMode(uint8_t pin, uint8_t mode)** pin = 0..15, mode = INPUT, OUTPUT, returns true if successful.
- **bool digitalWrite(uint8_t pin, uint8_t value)** pin = 0..15, value = LOW(0) HIGH (!0), returns true if successful.
- **uint8_t digitalRead(uint8_t pin)** pin = 0..15, returns LOW or HIGH, might set the lastError();
- **bool setPolarity(uint8_t pin, bool reversed)** pin = 0..15, set reversed flag, returns true if successful.
- **bool getPolarity(uint8_t pin, bool &reversed)** pin = 0..15, reads reversed flag, returns true if successful.
- **bool setPullup(uint8_t pin, bool pullup)** pin = 0..15, set pull-up flag, returns true if successful.
- **bool getPullup(uint8_t pin, bool &pullup)** pin = 0..15, reads pull-up flag, returns true if successful.


### 8 pins interface

- **bool pinMode8(uint8_t port, uint8_t value)** port = 0..1, value = 0..255, returns true if successful.
- **bool write8(uint8_t port, uint8_t value)** port = 0..1, value = 0..255, returns true if successful.
- **uint8_t read8(uint8_t port)** port = 0..1, reads 8 pins into one byte.
- **bool setPolarity8(uint8_t port, uint8_t mask)** port = 0..1, sets polarity for 8 channels at once.
- **bool getPolarity8(uint8_t port, uint8_t &mask)** port = 0..1, reads polarity of 8 channels at once.
- **bool setPullup8(uint8_t port, uint8_t mask)** port = 0..1, sets pull-up for 8 channels at once.
- **bool getPullup8(uint8_t port, uint8_t &mask)** port = 0..1, reads pull-up for 8 channels at once.


### 16 pins interface

- **bool pinMode16(uint16_t value)** value = 0..0xFFFF, returns true if successful.
- **bool write16(uint16_t value)** value = 0..0xFFFF, returns true if successful.
- **uint16_t read16()** reads 16 pins into an uint16_t.
- **bool setPolarity16(uint16_t mask)** sets polarity for 16 channels.
- **bool getPolarity16(uint16_t &mask)** reads polarity of 16 channels.
- **bool setPullup16(uint16_t mask)** sets pull-up for 16 channels.
- **bool getPullup16(uint16_t &mask)** reads pull-up for 16 channels.


### Error codes

- **int lastError()** Above functions set an error flag that can be read with this function.  
Reading it will reset the flag to **MCP23017_OK**.

| DESCRIPTION           | VALUE |
|:----------------------|:-----:|
| MCP23017_OK           |  0x00 |
| MCP23017_PIN_ERROR    |  0x81 |
| MCP23017_I2C_ERROR    |  0x82 |
| MCP23017_VALUE_ERROR  |  0x83 |
| MCP23017_PORT_ERROR   |  0x84 |


## Operation

See examples.


## Future


#### Must

- Improve and extend documentation
- add examples


#### Should

- extend error codes
- optimize code - squeeze footprint
- optimize code - do not write if pin does not chance (~25%)


#### Could

- initial value (16 bit?) as begin parameter (breaking change)
  - depends on input output pull-up etc?
- investigate auto address increment?

