
[![Arduino CI](https://github.com/RobTillaart/AD520X/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AD520X/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AD520X/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AD520X/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AD520X/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AD520X.svg)](https://github.com/RobTillaart/AD520X/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AD520X/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AD520X.svg?maxAge=3600)](https://github.com/RobTillaart/AD520X/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AD520X.svg)](https://registry.platformio.org/libraries/robtillaart/AD520X)


# AD520X

Arduino library for SPI AD5204 and AD5206 digital potentiometers.

Works with the AD840x series too (see PR #15)


## Description

The library is experimental as not all functionality is tested (enough).

The **AD5204** (4 channels) and **AD5206** (6 channels) are SPI based digital potentiometers.
This library consists of a base class **AD520X** that does the work.

The interface is straightforward, one can set a value per channels between 0..255.

|  type    |  channels  |  1 kΩ | 10 kΩ | 50 kΩ | 100 kΩ |  works    |
|:---------|:----------:|:-----:|:-----:|:-----:|:------:|:----------|
|  AD5204  |    4       |       |   V   |   V   |   V    | confirmed |
|  AD5206  |    6       |       |   V   |   V   |   V    | confirmed |
|  AD8400  |    1       |   V   |   V   |   V   |   V    | confirmed |
|  AD8402  |    2       |   V   |   V   |   V   |   V    |
|  AD8403  |    4       |   V   |   V   |   V   |   V    | confirmed |  see PR #15

The library is not yet confirmed to work for **AD8402** (2 channels).
This device has  a very similar interface (datasheet comparison) so it should work. If you can confirm the AD8402 works, please let me know.


#### 0.5.0 Breaking change

Version 0.5.0 introduced a breaking change to improve handling the SPI dependency.
The user has to call **SPI.begin()** or equivalent before calling **AD520X.begin()**.
Optionally the user can provide parameters to the **SPI.begin(...)**


#### 0.4.0 breaking change

The version 0.4.0 has breaking changes in the interface. 
The essence is removal of ESP32 specific code from the library. 
This makes it possible to support the ESP32-S3 and other processors in the future. 
Also it makes the library a bit simpler to maintain.


#### Related

- https://github.com/RobTillaart/AD520x
- https://github.com/RobTillaart/AD524X
- https://github.com/RobTillaart/AD5245
- https://github.com/RobTillaart/AD5144A
- https://github.com/RobTillaart/AD5245
- https://github.com/RobTillaart/AD5263
- https://github.com/RobTillaart/X9C10X


## Interface

```cpp
#include "AD520X.h"
```

### Constructors

- **AD520X(uint8_t select, uint8_t reset, uint8_t shutdown, SPIClassRP2040 \* mySPI = &SPI)** constructor HW SPI (RP2040 specific)
- **AD520X(uint8_t select, uint8_t reset, uint8_t shutdown, SPIClass \* mySPI = &SPI)** constructor HW SPI
- **AD520X(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut, uint8_t clock)** constructor SW SPI
Base class, not to be used directly.
- **AD5204(select, reset, shutdown, ...)** has 4 channels. As above.
- **AD5206(select, reset, shutdown, ...)** has 6 channels. As above.
- **AD8400(select, reset, shutdown, ...)** has 1 channel. As above.
- **AD8402(select, reset, shutdown, ...)** has 2 channels. As above.
- **AD8403(select, reset, shutdown, ...)** has 4 channels. As above.

Note: 
- hardware SPI is 10+ times faster on an UNO than software SPI.
- software SPI on ESP32 is about equally fast than hardware SPI.


### Base

Since 0.2.0 the functions have more default parameters. Potentiometer is default pot 0 
and value is default the **AD520X_MIDDLE_VALUE** of 128.

- **void begin(uint8_t value = 128)** value is the initial value of all potentiometer.
- **void reset(uint8_t value = 128)** resets the device and sets all potentiometers to value, default 128.

### Value

- **bool setValue(uint8_t pm = 0, uint8_t value = 128)** set a potentiometer to a value. 
Default value is middle value.  
Returns true if successful, false if not.
- **bool setValue(uint8_t pmA, uint8_t pmB, uint8_t value)** set two potentiometers to same value.
Note, no default value!
Returns true if successful, false if not.
- **void setAll(uint8_t value = 128)** set all potentiometers to the same value e.g. 0 or max or mid value.
Can typically be used for **mute**.
- **uint8_t getValue(uint8_t pm = 0)** returns the last set value of a specific potentiometer.
- **setGroupValue(mask, value)** bit mask to set 0..8 channels in one call.


The library has defined **#define AD520X_MIDDLE_VALUE  128**


### Percentage

- **bool setPercentage(uint8_t pm = 0, float percentage = 50)** similar to setValue, percentage from 0..100%, default potmeter 0 and 50%. 
Returns true when successful, false if not.
- **bool setPercentage(uint8_t pmA, uint8_t pmB, float percentage)** similar to setValue, percentage from 0..100%.
Note, no default value.
Returns true when successful, false if not.
- **float getPercentage(uint8_t pm = 0)** return the value of potentiometer pm as percentage.
- **setGroupPercentage(mask, value)** bit mask to set 0..8 channels in one call.


### Hardware SPI

To be used only if one needs a specific speed for hardware SPI.  
Has no effect on software SPI.

- **void setSPIspeed(uint32_t speed)** set SPI transfer rate.
- **uint32_t getSPIspeed()** returns SPI transfer rate.


### Misc

- **uint8_t pmCount()** returns the number of internal potentiometers.
- **void powerOn()** switches the module on.
- **void powerOff()** switches the module off.
- **bool isPowerOn()** returns true if on (default) or false if off.


### Debugging

- **bool usesHWSPI()** returns true / false depending on constructor.


## Future


#### Must

- improve documentation

#### Should

- extend unit tests
- extent examples

#### Could (only if requested.)

- **AD520X_MIDDLE_VALUE** 127 ?   (0.4.0?)
- **setSWSPIdelay(uint8_t del = 0)** to tune software SPI?
  - bit delay / not byte delay
  - unit microseconds
  - if (_del) delayMicroseconds(_del/2); // pre and post pulse.
- **void setInvert(uint8_t pm)** invert flag per potentiometer.
   - 0..255 -> 255..0
   - 1 uint8_t can hold 8 flags
   - **will slow performance**
   - how does this work with **stereo** functions.
   - at what level should invert work.
- **bool getInvert(uint8_t pm)**

#### Wont

- **void setGamma(uint8_t pm, float gamma)**
  - logarithmic effect? easier with setPercentage()
  - see https://github.com/RobTillaart/GAMMA library.
- **void follow(pm_B, pm_A, float percentage = 100)**
  - makes pm_B follow pm_A unless pm_B is addressed explicitly
  - e.g. to be used for **stereo** channels.
  - array cascade = 0xFF or pm_A.
  - It will follow pm_A for certain percentage default 100.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

