
[![Arduino CI](https://github.com/RobTillaart/PCA9632/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PCA9632/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PCA9632/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PCA9632/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PCA9632/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/PCA9632.svg)](https://github.com/RobTillaart/PCA9632/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PCA9632/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PCA9632.svg?maxAge=3600)](https://github.com/RobTillaart/PCA9632/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/PCA9632.svg)](https://registry.platformio.org/libraries/robtillaart/PCA9632)


# PCA9632

Arduino library for PCA9632 and PCA9633 4 channel, I2C LED driver.


## Description

**Experimental**

Warning:

The library is **experimental** as not all functionality is implemented or tested with hardware.
By means of the generic ```setRegister()``` the user can configure the device.
This will be changed after a full public API is done (when time permits).
Do expect changes of existing functions during development.


The PCA9632/33 is a 4 channel PWM device, which is typically used to adjust the brightness of LEDs.
Being a 4 channel device it is ideal to drive an RGB or RGBW LED.

The library uses a fixed mapping of the pins to colours {0,1,2,3} <=> {R,G,B,W};
This might change in the future.

Feedback is welcome, please open an issue with your questions and remarks.


### Compatibility

The PCA9632 is a drop-in upgrade for the PCA9633.
This library consist of base PCA9632 and a derived PCA9633 class
which is identical (for now).


### Related

- https://github.com/RobTillaart/PCA9632 (4 channel)
- https://github.com/RobTillaart/PCA9634 (8 channel)
- https://github.com/RobTillaart/PCA9635 (16 channel)
- https://github.com/RobTillaart/PCA9685_RT (16 channel)
- https://github.com/RobTillaart/map2colour 


## Interface

```cpp
#include "PCA9632.h"
```

### Constructors

Default address = 0x60 for the version without address pins.

- **PCA9632(uint8_t deviceAddress, TwoWire \*wire = &Wire)** Constructor with I2C device address,
and optional the Wire interface as parameter.
- **PCA9633(uint8_t deviceAddress, TwoWire \*wire = &Wire)** Constructor with I2C device address,
and optional the Wire interface as parameter.
- **bool begin(uint8_t mode1_mask = PCA9632_MODE1_DEFAULT, uint8_t mode2_mask = PCA9632_MODE2_DEFAULT)**
initializes the library after startup.
- **bool isConnected()** checks if address is available on I2C bus.


### Write

Write single channel, note the fixed mapping of the pins.

- **uint8_t writeR(uint8_t R)** idem.
- **uint8_t writeG(uint8_t G)** idem.
- **uint8_t writeB(uint8_t B)** idem.
- **uint8_t writeW(uint8_t W)** idem.
- **uint8_t write(uint8_t channel, uint8_t value)** generic function to drive PWM channel 0..3.

Write all channels at once

- **uint8_t write(uint8_t R, uint8_t G, uint8_t B, uint8_t W = 0)** writes RGB values.
- **uint8_t write(uint8_t \* arr)** array of at least 4 elements.


### Mode registers

Check datasheet for details. 

- **uint8_t setMode1(uint8_t value)** bits see PCA9632.h
- **uint8_t setMode2(uint8_t value)** bits see PCA9632.h
- **uint8_t getMode1()**
- **uint8_t getMode2()**


### Led driver mode register

Check datasheet for details.

- **uint8_t setLedDriverModeAll(uint8_t mode)** set mode for all channels.
- **uint8_t setLedDriverMode(uint8_t channel, uint8_t mode)** set mode for one channel (0..3).
- **uint8_t getLedDriverMode(uint8_t channel)** get mode for one channel (0..3).

|  mode               |  meaning  |
|:-------------------:|:----------|
|  PCA9632_LEDOFF     |  idem
|  PCA9632_LEDON      |  idem
|  PCA9632_LEDPWM     |  write PWM per channel
|  PCA9632_LEDGRPPWM  |  


### Low level

Public for now. Check datasheet for details.

- **uint8_t writeReg(uint8_t reg, uint8_t mask)**
- **uint8_t readReg(uint8_t reg)**


## Future

#### Must

- improve documentation (e.g. tables, masks etc)
- get hardware to test.


#### Should

- default values for functions.
- implement all registers.
- align PCA9634 if possible
- examples
- derived class PCA9633

#### Could

- unit tests
- read back RGBW (cache?)


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

