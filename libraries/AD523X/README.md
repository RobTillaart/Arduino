
[![Arduino CI](https://github.com/RobTillaart/AD523X/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AD523X/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AD523X/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AD523X/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AD523X/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AD523X.svg)](https://github.com/RobTillaart/AD523X/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AD523X/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AD523X.svg?maxAge=3600)](https://github.com/RobTillaart/AD523X/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AD523X.svg)](https://registry.platformio.org/libraries/robtillaart/AD523X)


# AD523X

Arduino library for SPI AD5231 and AD5235 10 bit digital potentiometers.

## Description

**Experimental**

The library is experimental as the functionality is not tested with hardware yet.

The **AD5231** is a single channel, 10 bit = 1024 step, SPI based potentiometer, 
the **AD5235** is a dual channel version.

There are 10 kΩ, 50 kΩ, and 100 kΩ versions.

This library is written as it is the first 10 bit potentiometer encountered.
When used as a voltage divider one could set 5V in steps of 5 mV which is great.

The interface is straightforward, one can set a value per channels between 0..1023
or by means of a percentage. This value can be fetched from cache.

Furthermore the power on reset start value can be set in EEMEM (EEPROM), either by 
copying the current position or by writing an explicit value to the EEMEM address.

Finally there are 14 or so free addresses in EEMEM to store some 16 bit values.

The library does not support the **WP = writeProtect pin** or the **RDY = ready pin**.
This might change in the future.

The library does not implement the increment/decrement interface yet.
This might change in the future.

Feedback is as always welcome! please open an issue on GitHub.

#### Related

Mostly digipots:

- https://github.com/RobTillaart/AD520X
- https://github.com/RobTillaart/AD523X
- https://github.com/RobTillaart/AD524X
- https://github.com/RobTillaart/AD5245
- https://github.com/RobTillaart/AD5144A
- https://github.com/RobTillaart/AD5245
- https://github.com/RobTillaart/AD5263
- https://github.com/RobTillaart/X9C10X


## Interface

```cpp
#include "AD523X.h"
```

### Constructors

- **AD5231(uint8_t select, uint8_t reset, SPIClassRP2040 \* mySPI = &SPI)** constructor HW SPI (RP2040 specific)
- **AD5231(uint8_t select, uint8_t reset, SPIClass \* mySPI = &SPI)** constructor HW SPI
- **AD5231(uint8_t select, uint8_t reset, uint8_t dataIn, uint8_t dataOut, uint8_t clock)** constructor SW SPI


- **AD5235(uint8_t select, uint8_t reset, SPIClassRP2040 \* mySPI = &SPI)** constructor HW SPI (RP2040 specific)
- **AD5235(uint8_t select, uint8_t reset, SPIClass \* mySPI = &SPI)** constructor HW SPI
- **AD5235(uint8_t select, uint8_t reset, uint8_t dataIn, uint8_t dataOut, uint8_t clock)** constructor SW SPI

Note: 
- hardware SPI is about 10+ times faster on an UNO as software SPI.
- software SPI on ESP32 is about equally fast as hardware SPI.

### Base

- **void begin(uint8_t value = AD523X_MIDDLE_VALUE)** value is the initial value of all potentiometer.
- **void reset(uint8_t value = AD523X_MIDDLE_VALUE)** resets the device and sets all potentiometers 
to value, default is 512.
- **void resetDevice()** execute a power on reset.  
WARNING: This will probably corrupt the internal cache for getValue.
- **uint8_t pmCount()** returns the number of internal potentiometers.

### Value

- **bool setValue(uint8_t value)** set a potentiometer to a value.
Returns true if successful, false if not.
- **bool setValue(uint8_t pm, uint8_t value)** set a potentiometer to a value. 
Returns true if successful, false if not.
- **uint8_t getValue(uint8_t pm)** returns the last set value of a specific potentiometer
from cache. This will probably change in the future.
- **void setAll(uint8_t value)** set all potentiometers to the same value 
e.g. 0 or max or middle value.
Can typically be used for **mute** or stereo setting.

The library has defined **#define AD520X_MIDDLE_VALUE  512**
The library has defined **#define AD520X_MAX_VALUE  1023**

In the future **getValue()** might be reading from the device instead of from cache.


### Percentage

- **bool setPercentage(uint8_t pm, float percentage)** similar to setValue, 
percentage from 0..100%.
Returns true when successful, false if not.
- **bool setPercentageAll(float percentage)** similar to setValue, 
percentage from 0..100%, 
Returns true when successful, false if not.
- **float getPercentage(uint8_t pm)** return the value of potentiometer pm as percentage.

### Increment / decrement

Commented in the code as effect on the cached values is to be investigated.

- **void decrement6DB(uint8_t pm = 0)** not implemented yet.
- **void decrementOne(uint8_t pm = 0)** not implemented yet.
- **void increment6DB(uint8_t pm = 0)** not implemented yet.
- **void incrementOne(uint8_t pm = 0)** not implemented yet.

### EEMEM

- **uint32_t rawRead()** needed by commands to read a value from the device.
Returns normally the last command.
- **void loadWiperEEMEM(uint8_t pm = 0)** load wiper position from eemem
- **void storeWiperEEMEM(uint8_t pm = 0)** store current wiper position as power on reset.
- **uint16_t loadEEMEM(uint8_t address)** load previous stored value from eemem
- **void storeEEMEM(uint8_t address, uint16_t value)** store value at address.
  - store address 0 from value iso wiper position (AD5231/5)
  - store address 1 from value iso wiper position (AD5235)
  - store address 1 from value to write O1, O2    (AD5231) Page 8, datasheet

Note: address should be 0..15 (code does not check).
Note: the WP pin allows to write protect EEMEM  
Note: Writing to EEMEM can block up to **25 milliseconds**.  
More see page 14 datasheet.

### Hardware SPI

To be used only if one needs a specific speed for hardware SPI.  
Has no effect on software SPI.

- **void setSPIspeed(uint32_t speed)** set SPI transfer rate.
- **uint32_t getSPIspeed()** returns SPI transfer rate.
- **bool usesHWSPI()** returns true / false depending on constructor.

### AD5231 specific

The O1 en O2 outputs can be set by writing to EEMEM at address 0x01.

```cpp
storeEEMEM(1, 0);  //  01 = 0,  02 = 0
storeEEMEM(1, 1);  //  01 = 1,  02 = 0
storeEEMEM(1, 2);  //  01 = 0,  02 = 1
storeEEMEM(1, 3);  //  01 = 1,  02 = 1
```

To be verified with hardware.

### AD5235 specific

- dual channel functions.


## Future

#### Must

- improve documentation
- get hardware to test

#### Should

- TODO's in code and documentation.
- fix the getValue() => remove cache?
- move specific functions to AD5231/5 classes.
- redo class hierarchy.
- magic numbers (e.g. commands 0..15)

#### Could

- optimize code
- add error code
- add parameter checking
- extend unit tests
- extent examples
  - AD5235 as single potmeter with 2048 steps (series) TasO (two as one)
  - AD5235 as single potmeter with 2x 1024 steps (parallel)
- stereo functions for the AD5235

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

