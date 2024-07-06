
[![Arduino CI](https://github.com/RobTillaart/MCP23S08/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MCP23S08/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MCP23S08/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MCP23S08/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MCP23S08/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MCP23S08.svg)](https://github.com/RobTillaart/MCP23S08/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MCP23S08/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MCP23S08.svg?maxAge=3600)](https://github.com/RobTillaart/MCP23S08/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MCP23S08.svg)](https://registry.platformio.org/libraries/robtillaart/MCP23S08)


# MCP23S08

Arduino library for MCP23S08 8 channel SPI port expander.


## Description

This library gives easy control over the 8 pins of a (SPI) MCP23S08 chip.

This IC is strongly related to the MCP23017 I2C port expander - https://github.com/RobTillaart/MCP23017_RT
Programming Interface is kept the same as much as possible.

The **write1(pin, value)** is optimized. 
If a pin is not changed it will not be written again to save time.


#### 0.5.0 Breaking change

Version 0.5.0 introduced a breaking change to improve handling the SPI dependency.
The user has to call **SPI.begin()** or equivalent before calling **MCP.begin()**.
Optionally the user can provide parameters to the **SPI.begin(...)**


#### 0.4.0 Breaking change

The version 0.4.0 has breaking changes in the interface. 
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


#### 0.3.0 Breaking change

The version 0.3.0 has breaking changes in the interface. 
The essence is removal of ESP32 specific code from the library. 
This makes it possible to support the ESP32-S3 and other processors in the future. 
Also it makes the library a bit simpler to maintain.


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
#include "MCP23S08.h"
```


### Constructor

- **MCP23S08(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock, uint8_t address = 0x00)** constructor SOFTWARE SPI.
- **MCP23S08(int select, SPIClassRP2040\* spi)** constructor HARDWARE SPI with explicit SPI interface selected.
- **MCP23S08(int select, SPIClass\* spi)** constructor HARDWARE SPI with explicit SPI interface selected.
- **MCP23S08(int select, int address = 0x00, SPIClassRP2040\* spi = &SPI)** constructor HARDWARE SPI with optional address pins and SPI interface.
- **MCP23S08(int select, int address = 0x00, SPIClass\* spi = &SPI)** constructor HARDWARE SPI with optional address pins and SPI interface.
- **bool begin(bool pullup = true)** initializes library, returns true if successful. 
Default sets the pins to INPUT PULLUP.
Returns false if not connected or a register could not be set.
- **bool isConnected()** returns true if connected, false otherwise. (dummy for compatibility reasons)
- **uint8_t getAddress()** returns the address set in the constructor. 
Default = 0, range = 0..3.


The two hardware constructors allow to call 4 different constructors.

```cpp
- MCP23S08(10);            //  select pin only
- MCP23S08(10, 7);         //  select pin + address pins
- MCP23S08(10, 7, &SPI2);  //  select pin + address pins + SPI port
- MCP23S08(10, &SPI2);     //  select pin + SPI port
```


#### Sharing SELECT lines

(verified in MCP23S17 issue 19)  
Technically two chips could use the same SELECT pin and a different address. 
Since 0.2.0 the constructors allow to setup such a configuration.
The added value is that one can use up to 4 devices (= 32 IO lines) with only 
four lines (MISO, MOSI, CLOCK, SELECT).

I assume that this configuration is less used and IMHO not recommended.
NB it is more difficult to detect which device is selected when debugging.

To use the hardware addresses the Hardware Address ENable register must be set.
See datasheet 1.6.6 ADDRESSING SPI DEVICES, need to set IOCON.HAEN.

The library supports two ways:
```cpp
MCP.enableControlRegister(MCP23S08_IOCR_HAEN);  //  or 0x08
or
MCP.enableHardwareAddress();  //  0.2.0 version and up
```

See also **IO Control Register** section below.


### Single pin interface

- **bool pinMode1(uint8_t pin, uint8_t mode)** pin = 0..7. 
mode = INPUT, OUTPUT or INPUT_PULLUP. 
Do NOT use 0, 1 for mode as the 3 constants are (possibly) defined differently.
Returns true if successful.
- **bool write1(uint8_t pin, uint8_t value)** pin = 0..7, value = LOW(0) HIGH (!0). Returns true if successful.
- **uint8_t read1(uint8_t pin)** pin = 0..7, returns LOW or HIGH, might set the lastError();
- **bool setPolarity(uint8_t pin, bool reversed)** pin = 0..7, set reversed flag. Returns true if successful.
- **bool getPolarity(uint8_t pin, bool &reversed)** pin = 0..7, reads reversed flag. Returns true if successful.
- **bool setPullup(uint8_t pin, bool pullup)** pin = 0..7, set pull-up flag. Returns true if successful.
- **bool getPullup(uint8_t pin, bool &pullup)** pin = 0..7, reads pull-up flag.Returns true if successful.


### 8 pins interface

- **bool pinMode8(uint8_t mask)** mask = 0..255. Returns true if successful.
Returns true if successful.
- **bool write8(uint8_t value)** value = 0..255. Returns true if successful.
Returns true if successful.
- **uint8_t read8()** reads 8 pins into one byte.
- **bool setPolarity8(uint8_t mask)** sets polarity for 8 channels at once.
Returns true if successful.
- **bool getPolarity8(uint8_t &mask)** reads polarity of 8 channels at once.
Returns true if successful.
- **bool setPullup8(uint8_t mask)** sets pull-up for 8 channels at once.
Returns true if successful.
- **bool getPullup8(uint8_t &mask)** reads pull-up for 8 channels at once.
Returns true if successful.


### Interrupts (experimental 0.5.2)

Read the datasheet for the details. Page 21.  
Note: Error handling is limited.

pin = 0..7  
mode = { RISING, FALLING, CHANGE }  
- **bool enableInterrupt(uint8_t pin, uint8_t mode)** 
Returns true if successful.
Returns MCP23S17_PIN_ERROR if pin > 7.
- **bool disableInterrupt(uint8_t pin)**
Returns true if successful.
Returns MCP23S17_PIN_ERROR if pin > 7.


Determine which pins caused the Interrupt. (datasheet).
- **uint8_t getInterruptFlagRegister()** Reads all 8 pins.
- **uint8_t getInterruptCaptureRegister()** Reads all 8 pins.
Is used to detect if multiple pins triggered an interrupt.


- **bool setInterruptPolarity(uint8_t ipol)** polarity: 0 = LOW, 1 = HIGH, 2 = NONE/ODR
- **uint8_t getInterruptPolarity()** return set value.


### SPI

- **void setSPIspeed(uint32_t speed)** set hardware speed (8Mb default).
- **uint32_t getSPIspeed()** returns set speed.


### Debugging

- **bool usesHWSPI()** returns true = hardware SPI, false = software SPI.
- **int lastError()** idem.


### IO Control Register

The library supports setting bit fields in the IO control register.
Read the datasheet carefully!

- **bool enableControlRegister(uint8_t mask)** set IOCR bit fields
- **bool disableControlRegister(uint8_t mask)** clear IOCR bit fields


|  constant              |  mask  |  description  |
|:-----------------------|:------:|:--------------|
|  MCP23S08_IOCR_BANK    |  0x80  |  Controls how the registers are addressed.
|  MCP23S08_IOCR_MIRROR  |  0x40  |  INT Pins Mirror bit.
|  MCP23S08_IOCR_SEQOP   |  0x20  |  Sequential Operation mode bit.
|  MCP23S08_IOCR_DISSLW  |  0x10  |  Slew Rate control bit for SDA output.
|  MCP23S08_IOCR_HAEN    |  0x08  |  Hardware Address Enable bit (MCP23S17 only).
|  MCP23S08_IOCR_ODR     |  0x04  |  Configures the INT pin as an open-drain output.
|  MCP23S08_IOCR_INTPOL  |  0x02  |  This bit sets the polarity of the INT output pin.
|  MCP23S08_IOCR_NI      |  0x01  |  Not implemented. 


Two dedicated functions are added: (MCP23S08 only)

- **bool enableHardwareAddress()** set IOCR_HAEN  bit.
- **bool disableHardwareAddress()** clear IOCR_HAEN bit.


### Error codes

If one of the above functions return false, there might be an error.

- **int lastError()** Above functions set an error flag that can be read with this function.  
Reading it will reset the flag to **MCP23S08_OK**.

|  name                     |  value  |  description  |
|:--------------------------|:-------:|:--------------|
|  MCP23S08_OK              |  0x00   |  No error     |
|  MCP23S08_PIN_ERROR       |  0x81   |
|  MCP23S08_SPI_ERROR       |  0x82   |
|  MCP23S08_VALUE_ERROR     |  0x83   |
|  MCP23S08_PORT_ERROR      |  0x84   |
|  MCP23S08_REGISTER_ERROR  |  0xFF   |  low level.
|  MCP23S08_INVALID_READ    |  0xFF   |  low level.


## Future

#### Must

- keep documentation in sync with MCP23S17

#### Should

- keep functional in sync with MCP23017_RT and MCP23S17

#### Could

- ESP32 example code

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


