
[![Arduino CI](https://github.com/RobTillaart/MCP23008/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MCP23008/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MCP23008/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MCP23008/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MCP23008/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MCP23008.svg)](https://github.com/RobTillaart/MCP23008/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MCP23008/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MCP23008.svg?maxAge=3600)](https://github.com/RobTillaart/MCP23008/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MCP23008.svg)](https://registry.platformio.org/libraries/robtillaart/MCP23008)


# MCP23008

Arduino library for MCP23008 8 channel I2C port expander.


## Description

This library gives easy control over the 8 pins of a (I2C) MCP23008 chip.

This IC is strongly related tot the MCP23017 I2C port expander - https://github.com/RobTillaart/MCP23017_RT
Programming Interface is kept the same as much as possible.

Since 0.1.1 the **digitalWrite(pin, value)** is optimized. 
If a pin is not changed it will not be written again to save time.


#### 0.3.0 Breaking change

The version 0.3.0 has breaking changes in the interface. 
The rationale is that the programming environment of the **Arduino ESP32 S3** 
board uses a remapping by means of the include file **io_pin_remap.h**.
This file remaps the pins of several core Arduino functions. 
The remapping is implemented by #define macros and these implement "hard" text 
replacements without considering context. 
The effect is that methods from this class (and several others) which have the same 
name as those Arduino core functions will be remapped into something not working.

The following library functions have been renamed:

|  old name        |  new name    |  notes  |
|:-----------------|:-------------|:--------|
|  analogRead()    |  read()      |
|  analogWrite()   |  write()     |
|  pinMode()       |  pinMode1()  |
|  digitalRead()   |  read1()     |
|  digitalWrite()  |  write1()    |


#### 0.2.0 Breaking change

Version 0.2.0 introduced a breaking change.
You cannot set the pins in **begin()** any more.
This reduces the dependency of processor dependent Wire implementations.
The user has to call **Wire.begin()** and can optionally set the Wire pins 
before calling **begin()**.


#### Related

16 bit port expanders

- https://github.com/RobTillaart/MCP23017_RT
- https://github.com/RobTillaart/MCP23S17
- https://github.com/RobTillaart/PCF8575
- https://github.com/RobTillaart/TCA9555


8 bit port expanders

- https://github.com/RobTillaart/MCP23008
- https://github.com/RobTillaart/MCP23S08
- https://github.com/RobTillaart/PCF8574


## Interface

```cpp
#include "MCP23008.h"
```

### Constructor

- **MCP23008(uint8_t address, TwoWire \*wire = &Wire)** constructor, with default Wire interface.  
Can be overruled with Wire0..WireN.
- **bool begin(bool pullup = true)** initializes library, returns true if successful. 
Default sets the pins to INPUT PULLUP.
Returns false if not connected or a register could not be set.
- **bool isConnected()** returns true if connected, false otherwise.
- **uint8_t getAddress()** returns address set in the constructor.


### Single pin interface

- **bool pinMode1(uint8_t pin, uint8_t mode)** pin = 0..7, mode = INPUT, OUTPUT.
0xFF is all pins are input, 0x1F are 5 inputs and 3 outputs.
Returns true if successful.
- **bool write1(uint8_t pin, uint8_t value)** pin = 0..7, value = LOW(0) HIGH (!0). Returns true if successful.
- **uint8_t read1(uint8_t pin)** pin = 0..7, returns LOW or HIGH, might set the lastError();
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

|  DESCRIPTION           |  VALUE  |
|:-----------------------|:-------:|
|  MCP23008_OK           |  0x00   |
|  MCP23008_PIN_ERROR    |  0x81   |
|  MCP23008_I2C_ERROR    |  0x82   |
|  MCP23008_VALUE_ERROR  |  0x83   |
|  MCP23008_PORT_ERROR   |  0x84   |


## Operation

See examples.


## Future

#### Must

- improve documentation

#### Should

- keep in sync with MCP23017

#### Could


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

