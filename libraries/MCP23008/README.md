
[![Arduino CI](https://github.com/RobTillaart/MCP23008/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MCP23008/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MCP23008/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MCP23008/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MCP23008/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MCP23008/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MCP23008.svg?maxAge=3600)](https://github.com/RobTillaart/MCP23008/releases)


# MCP23008

Arduino library for MCP23008 8 channel I2C port expander.


## Description

This library gives easy control over the 8 pins of a (I2C) MCP23008 chip.

This IC is strongly related tot the MCP23017 I2C port expander - https://github.com/RobTillaart/MCP23017_RT
Programming Interface is kept the same as much as possible.

Since 0.1.1 the **digitalWrite(pin, value)** is optimized. 
If a pin is not changed it will not be written again to save time.


## Interface

### Constructor

- **MCP23008(uint8_t address, TwoWire \*wire = &Wire)** constructor, with default Wire interface.  
Can be overruled with Wire0..WireN.
- **bool begin()** for UNO, returns true if successful.
- **bool begin(uint8_t sda, uint8_t scl)** for ESP32, returns true if successful.
- **bool isConnected()** returns true if connected, false otherwise.


### Single pin interface

- **bool pinMode(uint8_t pin, uint8_t mode)** pin = 0..7, mode = INPUT, OUTPUT. Returns true if successful.
- **bool digitalWrite(uint8_t pin, uint8_t value)** pin = 0..7, value = LOW(0) HIGH (!0). Returns true if successful.
- **uint8_t digitalRead(uint8_t pin)** pin = 0..7, returns LOW or HIGH, might set the lastError();
- **bool setPolarity(uint8_t pin, bool reversed)** pin = 0..7, set reversed flag. Returns true if successful.
- **bool getPolarity(uint8_t pin, bool &reversed)** pin = 0..7, reads reversed flag. Returns true if successful.
- **bool setPullup(uint8_t pin, bool pullup)** pin = 0..7, set pull-up flag. Returns true if successful.
- **bool getPullup(uint8_t pin, bool &pullup)** pin = 0..7, reads pull-up flag. Returns true if successful.


### 8 pins interface

- **bool pinMode8(uint8_t value)** value = 0..255. Returns true if successful.
- **bool write8(uint8_t value)** value = 0..255. Returns true if successful.
- **uint8_t read8()** reads 8 pins into one byte.
- **bool setPolarity8(uint8_t mask)** sets polarity for 8 channels at once. Returns true if successful.
- **bool getPolarity8(uint8_t &mask)** reads polarity of 8 channels at once. Returns true if successful.
- **bool setPullup8(uint8_t mask)** sets pull-up for 8 channels at once. Returns true if successful.
- **bool getPullup8(uint8_t &mask)** reads pull-up for 8 channels at once. Returns true if successful.


### Error codes

If one of the above functions return false, there might be an error.

- **int lastError()** Above functions set an error flag that can be read with this function.  
Reading it will reset the flag to **MCP23008_OK**.

| DESCRIPTION           | VALUE |
|:----------------------|:-----:|
| MCP23008_OK           |  0x00 |
| MCP23008_PIN_ERROR    |  0x81 |
| MCP23008_I2C_ERROR    |  0x82 |
| MCP23008_VALUE_ERROR  |  0x83 |
| MCP23008_PORT_ERROR   |  0x84 |


## Operation

See examples.


## Future

- keep in sync with MCP23017

