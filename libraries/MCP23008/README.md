
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


## I2C

Supports 100kHz, 400kHz and 1.7MHz 

TODO - add performance data


#### I2C multiplexing

Sometimes you need to control more devices than possible with the default
address range the device provides.
This is possible with an I2C multiplexer e.g. TCA9548 which creates up
to eight channels (think of it as I2C subnets) which can use the complete
address range of the device.

Drawback of using a multiplexer is that it takes more administration in
your code e.g. which device is on which channel.
This will slow down the access, which must be taken into account when
deciding which devices are on which channel.
Also note that switching between channels will slow down other devices
too if they are behind the multiplexer.

- https://github.com/RobTillaart/TCA9548


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

- **bool pinMode1(uint8_t pin, uint8_t mode)** pin = 0..7, mode = INPUT, OUTPUT or INPUT_PULLUP.
Do NOT use 0, 1 for mode as the 3 constants are (possibly) defined differently.
Returns true if successful.
- **bool write1(uint8_t pin, uint8_t value)** pin = 0..7, value = LOW(0) HIGH (!0). Returns true if successful.
- **uint8_t read1(uint8_t pin)** pin = 0..7, returns LOW or HIGH, might set the lastError();
- **bool setPolarity(uint8_t pin, bool reversed)** pin = 0..7, set reversed flag. Returns true if successful.
- **bool getPolarity(uint8_t pin, bool &reversed)** pin = 0..7, reads reversed flag. Returns true if successful.
- **bool setPullup(uint8_t pin, bool pullup)** pin = 0..7, set pull-up flag. Returns true if successful.
- **bool getPullup(uint8_t pin, bool &pullup)** pin = 0..7, reads pull-up flag. Returns true if successful.


### 8 pins interface

- **bool pinMode8(uint8_t mask)** mask = 0..255. Returns true if successful.
- **bool write8(uint8_t value)** value = 0..255. Returns true if successful.
- **uint8_t read8()** reads 8 pins into one byte.
- **bool setPolarity8(uint8_t mask)** sets polarity for 8 channels at once. Returns true if successful.
- **bool getPolarity8(uint8_t &mask)** reads polarity of 8 channels at once. Returns true if successful.
- **bool setPullup8(uint8_t mask)** sets pull-up for 8 channels at once. Returns true if successful.
- **bool getPullup8(uint8_t &mask)** reads pull-up for 8 channels at once. Returns true if successful.


### Interrupts (experimental 0.3.3)

Read the datasheet for the details. Page 21.  
Note: Error handling is limited.

pin = 0..7  
mode = { RISING, FALLING, CHANGE }  
- **bool enableInterrupt(uint8_t pin, uint8_t mode)** 
Returns true if successful.
Returns MCP23017_PIN_ERROR if pin > 7.
- **bool disableInterrupt(uint8_t pin)**
Returns true if successful.
Returns MCP23017_PIN_ERROR if pin > 7.


Determine which pins caused the Interrupt. (datasheet).
- **uint8_t getInterruptFlagRegister()** Reads all 8 pins.
- **uint8_t getInterruptCaptureRegister()** Reads all 8 pins.
Is used to detect if multiple pins triggered an interrupt.


- **bool setInterruptPolarity(uint8_t ipol)** polarity: 0 = LOW, 1 = HIGH, 2 = NONE/ODR
- **uint8_t getInterruptPolarity()** return set value.


### IO Control Register

The library supports setting bit fields in the IO control register.
Read the datasheet carefully!

- **bool enableControlRegister(uint8_t mask)** set IOCR bit fields
- **bool disableControlRegister(uint8_t mask)** clear IOCR bit fields


|  constant              |  mask  |  description  |
|:-----------------------|:------:|:--------------|
|  MCP23x17_IOCR_BANK    |  0x80  |  Controls how the registers are addressed.
|  MCP23x17_IOCR_MIRROR  |  0x40  |  INT Pins Mirror bit.
|  MCP23x17_IOCR_SEQOP   |  0x20  |  Sequential Operation mode bit.
|  MCP23x17_IOCR_DISSLW  |  0x10  |  Slew Rate control bit for SDA output.
|  MCP23x17_IOCR_HAEN    |  0x08  |  Hardware Address Enable bit (MCP23S17 only).
|  MCP23x17_IOCR_ODR     |  0x04  |  Configures the INT pin as an open-drain output.
|  MCP23x17_IOCR_INTPOL  |  0x02  |  This bit sets the polarity of the INT output pin.
|  MCP23x17_IOCR_NI      |  0x01  |  Not implemented. 


Two dedicated functions are added: (MCP23S17 only)

- **bool enableHardwareAddress()** set IOCR_HAEN  bit.
- **bool disableHardwareAddress()** clear IOCR_HAEN bit.


### Error codes

If one of the above functions return false, there might be an error.

- **int lastError()** Above functions set an error flag that can be read with this function.  
Reading it will reset the flag to **MCP23008_OK**.

|  name                     |  value  |  description  |
|:--------------------------|:-------:|:--------------|
|  MCP23008_OK              |  0x00   |  No error     |
|  MCP23008_PIN_ERROR       |  0x81   |
|  MCP23008_I2C_ERROR       |  0x82   |  (compatibility)
|  MCP23008_VALUE_ERROR     |  0x83   |
|  MCP23008_PORT_ERROR      |  0x84   |
|  MCP23008_REGISTER_ERROR  |  0xFF   |  low level.
|  MCP23008_INVALID_READ    |  0xFF   |  low level.


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

