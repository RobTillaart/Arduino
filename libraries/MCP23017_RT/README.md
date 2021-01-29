
[![Arduino CI](https://github.com/RobTillaart/MCP23017_RT/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MCP23017_RT/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MCP23017_RT.svg?maxAge=3600)](https://github.com/RobTillaart/MCP23017_RT/releases)

# MCP23017_RT

Arduino library for MCP23017 16 channel I2C port expander


## Description

This library gives easy control over the 16 pins of a MCP23017 chip.


## Interface

### Constructor

- **MCP23017(address, TwoWire \*wire = &Wire)** constructor, with default Wire interface. Can be overruled with Wire0..WireN
- **bool begin()** for UNO, returns true if successful
- **bool begin(sda, scl)** for ESP32, returns true if successful
- **bool isConnected()** returns true if connected, false otherwise


### single pin interface

- **bool pinMode(pin, value)** pin = 0..15, value = INPUT, OUTPUT, returns true if successful.
- **bool digitalWrite(pin, value)** pin = 0..15, value = LOW(0) HIGH (!0), returns true if successful.
- **uint8_t digitalRead(pin)** pin = 0..15


### 8 pins interface

- **bool pinMode8(port, value)** port = 0, 1  value = 0..255, returns true if successful.
- **bool write8(port, value)** port = 0, 1  value = 0..255, returns true if successful.
- **uint8_t read8(port)** port = 0, 1


### Error codes

- **int lastError()** Above functions set an error flag that can be read withthis function. Reading it will reset the flag to **MCP23017_OK**.

| DESCRIPTION           | VALUE |
|:----------------------|:-----:|
| MCP23017_OK           |  0x00 |
| MCP23017_PIN_ERROR    |  0x81 |
| MCP23017_I2C_ERROR    |  0x82 |
| MCP23017_VALUE_ERROR  |  0x83 |
| MCP23017_PORT_ERROR   |  0x84 |


## Operation

See examples

