
[![Arduino CI](https://github.com/RobTillaart/AD568X/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AD568X/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AD568X/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AD568X/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AD568X/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AD568X.svg)](https://github.com/RobTillaart/AD568X/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AD568X/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AD568X.svg?maxAge=3600)](https://github.com/RobTillaart/AD568X/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AD568X.svg)](https://registry.platformio.org/libraries/robtillaart/AD568X)


# AD568X

Arduino library for the AD568X series digital analog convertor.


## Description

**Experimental**

The AD568X library implements a base class and four derived classes.
The derived classed only differ on the resolution set. 

|  Type     |  bits  |  supported  |  Notes  |
|:---------:|:------:|:-----------:|:--------|
|  AD5681R  |   12   |     Y       |
|  AD5682R  |   14   |     Y       |
|  AD5683   |   16   |     Y       |
|  AD5683R  |   16   |     Y       |

The AD568X uses SPI to communicate to the device and supports both
hardware SPI as software SPI (bit bang).

The library is not tested with hardware yet so it is labelled as 
**experimental** and should be used with care.

Although the library has a function to set the Daisy Chain ENable bit,
the library does not support this mode. 
It is added for completeness and possibly to be used in the future.
So for now the library only supports stand alone mode. 

Note: the AD5691, AD5692, AD5693 are equivalent devices with I2C (no library yet).

Feedback, issues, improvements are welcome. 
Please file an issue on GitHub.


#### 0.3.0 Breaking change

Version 0.3.0 introduced a breaking change to improve handling the SPI dependency.
The user has to call **SPI.begin()** or equivalent before calling **AD.begin()**.
Optionally the user can provide parameters to the **SPI.begin(...)**


#### 0.2.0 breaking change

The version 0.2.0 has breaking changes in the interface. 
The essence is removal of ESP32 specific code from the library. 
This makes it possible to support the ESP32-S3 and other processors in the future. 
Also it makes the library a bit simpler to maintain.

Note the order of the parameters of the software SPI constructor has changed in 0.2.0.


## Related

- https://github.com/RobTillaart/AD56x8 (multi channel DAC's)
- https://github.com/RobTillaart/AD5680 (18 bit version)
- https://github.com/RobTillaart/MCP_DAC (SPI interface)


## Interface

```cpp
#include "AD568X.h"
```

### Base class

Should not be used to instantiate a device as the derived types have 
set the correct number of bits. 

- **AD568X(uint8_t slaveSelect, SPIClassRP2040 \* mySPI = &SPI)** constructor HW SPI (RP2040 specific). Sets internal value to zero.
- **AD568X(uint8_t slaveSelect, SPIClass \* mySPI = &SPI)** constructor HW SPI.
Sets internal value to zero.
- **AD568X(uint8_t spiData, uint8_t spiClock, uint8_t slaveSelect)** constructor, 
sets SW SPI.
Sets internal values to zero.
- **begin()** initializes the SPI and sets internal state.
- **uint8_t getType()** returns bit depth (see below).

#### Derived classes (preferred use)

The parameters for the specific constructors are identical to the base class.
One should use these, as these set the bit resolution!

- **AD5681R(uint8_t slaveSelect, ..)** constructor, 12 bit.
- **AD5682R(uint8_t slaveSelect, ..)** constructor, 14 bit.
- **AD5683R(uint8_t slaveSelect, ..)** constructor, 16 bit.
- **AD5683(uint8_t slaveSelect, ..)** constructor,  16 bit.


### LDAC

The use of the LDAC interface is optional.
It allows a prepared value to be set in in the DAC register.
See **prepareValue()**.
If you control multiple devices the hardware LDAC allows you to 
set a new value on all devices simultaneously.

- void **setLDACPin(uint8_t ldac)** set the LDAC pin.
- void **triggerLDAC()** give a pulse over the LDAC line.


### Set DAC

- **bool setValue(uint16_t value)** set value to the output immediately, 
effectively a prepare + update in one call.
Returns false if value out of range.
- **uint16_t getValue()** returns set OR prepared value.
At power up the DAC's will be reset to 0 Volt.
- **bool setPercentage(float percentage)** sets the output as a percentage 0..100.
If percentage is out of range, it is not set and the function returns false.
- **float getPercentage()** returns percentage, wrapper around **getValue()**.
Might return a slightly different value than **setPercentage()** due to 
rounding errors.
- **bool prepareValue(uint16_t value)** prepares the value.
Returns false if value out of range.
- **bool updateValue()** writes the prepared value to ADC.
Returns false if value out of range.
This function is also known as the software LDAC.


### Control Register

Check datasheet for details.

- **bool setControlRegister(uint16_t value)** set register in one call.
- **uint16_t getControlRegister()** return the set / current value.
- **bool reset()** reset the AD568X device.
Also resets all flags in control register.
- **bool setPowerDownMode(uint8_t mode = AD568X_PWR_NORMAL)** 
set one of three power down modes, see table below, or to normal mode.
Default is AD568X_PWR_NORMAL.
- **bool disableReference(bool b)** false = reference enabled.
true = reference disabled (uses less power). 
Default is enabled.
- **bool enableGain(bool enable = false)** false = 0..Vref  true = 0..2x Vref.
Default is false.
- **bool enableDaisyChain(bool enable = false)** enables daisy chain mode.
**WARNING** Daisy Chain is not supported in current library.
Default is false.

Control register bits: (see datasheet)

|  bits  |  meaning             |  Notes  |
|:------:|:---------------------|:--------|
|   15   |  RESET               |
|   14   |  PowerDown 1         |
|   13   |  PowerDown 2         |
|   12   |  REFerence selection |
|   11   |  GAIN                |
|   10   |  DCEN, Daisy Chain   |  not supported in the library.


Power down modi: (see datasheet)

|  mode  |  define             |
|:------:|:--------------------|
|  0x00  |  AD568X_PWR_NORMAL  |
|  0x01  |  AD568X_PWR_1K      |
|  0x02  |  AD568X_PWR_100K    |
|  0x03  |  AD568X_PWR_TRI     |


#### SPI 

- **void setSPIspeed(uint32_t speed)** sets SPI clock in **Hz**,
please read datasheet of the ADC first to get optimal speed.
- **uint32_t getSPIspeed()** gets current speed in **Hz**.
- **bool usesHWSPI()** returns true if HW SPI is used.


#### SPI ESP32 specific

Note: earlier experiments shows that on a ESP32 SW-SPI is equally fast as 
HW-SPI and in fact a bit more stable. 
The SW pulses are a bit slower than the HW pulses and therefore more square. 
The HW-SPI has some overhead SW-SPI hasn't. 


## Future

#### Must

- improve documentation
- get hardware for testing
- test the library

#### Should

- write examples
  - performance
  - LDAC pin
  - multi device ( array)
  - multi device (LDAC sync)
- Clean up / improve code.
  - move conditional code to variable. (setValue etc).
- sync with AD5680

#### Could

- write unit test


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

