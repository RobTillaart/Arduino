
[![Arduino CI](https://github.com/RobTillaart/PCA9632/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PCA9632/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PCA9632/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PCA9632/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PCA9632/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/PCA9632.svg)](https://github.com/RobTillaart/PCA9632/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PCA9632/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PCA9632.svg?maxAge=3600)](https://github.com/RobTillaart/PCA9632/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/PCA9632.svg)](https://registry.platformio.org/libraries/robtillaart/PCA9632)


# PCA9632

Arduino library for PCA9632 and PCA9633 I2C 8 bit PWM LED driver, 4 channel.


## Description

**Experimental**

Warning:

The library is **experimental** as not all functionality is implemented or tested with hardware.
By means of the generic ```setRegister()``` the user can configure the device.
This will be changed after a full public API is done (when time permits).
Do expect changes of existing functions during development.


The PCA9632/33 is a 4 channel PWM device, which is typically used to adjust the brightness of LEDs.
Being a 4 channel device it is ideal to drive an RGB or RGBW LED.
The 4 channels are independently configurable in steps of 1/256.
This allows for better than 1% fine tuning of the duty-cycle
of the PWM signal.

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


### Constructor

Default address = 0x60 for the version without address pins.

- **PCA9632(uint8_t deviceAddress, TwoWire \*wire = &Wire)** Constructor with I2C device address,
and optional the Wire interface as parameter.
- **PCA9633(uint8_t deviceAddress, TwoWire \*wire = &Wire)** Constructor with I2C device address,
and optional the Wire interface as parameter.
- **bool begin(uint8_t mode1_mask = PCA9632_MODE1_DEFAULT, uint8_t mode2_mask = PCA9632_MODE2_DEFAULT)**
initializes the library after startup. Optionally setting the MODE1 and MODE2 configuration registers.
See PCA9632.h and datasheet for settings possible.
- **bool isConnected()** checks if address is available on I2C bus.
- **uint8_t channelCount()** returns the number of channels = 4.


### LedDriverMode

Configure LED behaviour. Check datasheet for details.

- **uint8_t setLedDriverMode(uint8_t channel, uint8_t mode)** set mode for one channel (0..3).
  - returns error code, see below.
- **uint8_t setLedDriverModeAll(uint8_t mode)** set same mode for ALL channels.
- **uint8_t getLedDriverMode(uint8_t channel)** returns the current mode of the channel. (0..3).

|  LED mode           |  Value  |  Description                        |
|:--------------------|:-------:|:------------------------------------|
|  PCA9632_LEDOFF     |   0x00  |  led is 100% off, default @startup  |
|  PCA9632_LEDON      |   0x01  |  led is 100% on.                    |
|  PCA9632_LEDPWM     |   0x02  |  set LED in PWM mode, 0..255        |
|  PCA9632_LEDGRPPWM  |   0x03  |  add LED to the GRPPWM*             |


\* all LEDs in the group GRPPWM can be set to the same PWM value in one set.
This is ideal to trigger e.g. multiple LEDs (servo's) at same time.


### Read and write

Write single channel, note the fixed mapping of the pins.

- **uint8_t writeR(uint8_t R)** idem.
- **uint8_t writeG(uint8_t G)** idem.
- **uint8_t writeB(uint8_t B)** idem.
- **uint8_t writeW(uint8_t W)** idem.
- **uint8_t write(uint8_t channel, uint8_t value)** generic function to drive PWM channel 0..3.

Write all channels at once

- **uint8_t write(uint8_t R, uint8_t G, uint8_t B, uint8_t W = 0)** writes RGB values.
- **uint8_t write(uint8_t \* arr)** array of at least 4 elements.
- **uint8_t allOff()** shortcut, idem.


### Mode registers

Used to configure the PCA963x general behaviour. Check datasheet for details.

- **uint8_t setMode1(uint8_t value)** see table below
- **uint8_t setMode2(uint8_t value)** see table below
- **uint8_t getMode1()**
- **uint8_t getMode2()**


### Constants for mode registers

|  Name                     |  Value  |  Description                         |
|:--------------------------|:-------:|:-------------------------------------|
|  PCA9632_MODE1_AUTOINCR2  |  0x80   |  Read Only, 0 = disable  1 = enable  |
|  PCA9632_MODE1_AUTOINCR1  |  0x40   |  Read Only, bit1                     |
|  PCA9632_MODE1_AUTOINCR0  |  0x20   |  Read Only, bit0                     |
|  PCA9632_MODE1_SLEEP      |  0x10   |  0 = normal        1 = sleep         |
|  PCA9632_MODE1_SUB1       |  0x08   |  0 = disable       1 = enable        |
|  PCA9632_MODE1_SUB2       |  0x04   |  0 = disable       1 = enable        |
|  PCA9632_MODE1_SUB3       |  0x02   |  0 = disable       1 = enable        |
|  PCA9632_MODE1_ALLCALL    |  0x01   |  0 = disable       1 = enable        |
|  PCA9632_MODE1_NONE       |  0x00   |                                      |
|  PCA9632_MODE1_DEFAULT    |  0x81   |                                      |
|  ----                     |         |                                      |
|  PCA9632_MODE2_BLINK      |  0x20   |  0 = dim           1 = blink         |
|  PCA9632_MODE2_INVERT     |  0x10   |  0 = normal        1 = inverted      |
|  PCA9632_MODE2_STOP       |  0x08   |  0 = on STOP       1 = on ACK        |
|  PCA9632_MODE2_TOTEMPOLE  |  0x04   |  0 = open drain    1 = totem-pole    |
|  PCA9632_MODE2_NONE       |  0x00   |                                      |
|  PCA9632_MODE2_DEFAULT    |  0x02   |                                      |


These constants makes it easier to set modes without using a non descriptive
bit mask. The constants can be merged by OR-ing them together, see snippet:


### Group PWM and frequency

Check datasheet for the details.

- **uint8_t setGroupPWM(uint8_t value)** sets all channels that are part of the PWM group to value.
- **uint8_t getGroupPWM()** get the current PWM setting of the group.
- **uint8_t setGroupFREQ(uint8_t value)** is used for blinking the group of configured LED. 
Value goes from 0 to 255 with each step representing an increase of approx. 41 ms. 
So 0x00 results in 41 ms blinking period (on AND off) and 0xFF in approx. 10.5 s.
- **uint8_t getGroupFREQ()** returns the set frequency of the PWM group.


### Error

- **int lastError()** returns **PCA9632_OK** if all is OK, and other error codes otherwise.

|  Error code         |  Value  |  Description           |
|:--------------------|:-------:|:-----------------------|
|  PCA9632_OK         |   0x00  |  Everything went well
|  PCA9632_ERROR      |   0xFF  |  Generic error
|  PCA9632_ERR_WRITE  |   0xFE  |  Tries to write more elements than PWM channels
|  PCA9632_ERR_CHAN   |   0xFD  |  Channel out of range
|  PCA9632_ERR_MODE   |   0xFC  |  Invalid mode
|  PCA9632_ERR_REG    |   0xFB  |  Invalid register
|  PCA9632_ERR_I2C    |   0xFA  |  I2C communication error


## SUB CALL and ALL CALL

Please read the datasheet to understand the working of **SUB CALL** and **ALL CALL**.

There is (experimental) support for the **SUB CALL** and **ALL CALL** functions.
It needs more testing and if there are issues, please report.

AllCall is automatically activated for each device on startup.


### Description

**SUB CALL** allows one to make groups of PCA9632 devices and control them on group level.
The number of groups one can make depends on free I2C addresses on one I2C bus.
Using multiple I2C buses or multiplexers will even increase the possible number. 
Every PCA9632 device can be member of up to three of these groups.
To become member one needs to set the **setSubCallAddress(nr, address)** and enable 
it with **enableSubCall(nr)**.

In the same way one can become member of an **ALL CALL** group.
Typically there is only one such group but one can configure more of them by applying different addresses.


### Interface

The functions to enable all/sub-addresses are straightforward:

- **bool enableSubCall(uint8_t nr)** nr = 1,2,3
- **bool disableSubCall(uint8_t nr)** nr = 1,2,3
- **bool isEnabledSubCall(uint8_t nr)** nr = 1,2,3
- **bool setSubCallAddress(uint8_t nr, uint8_t address)**
- **uint8_t getSubCallAddress(uint8_t nr)**

- **bool enableAllCall()**
- **bool disableAllCall()**
- **bool isEnabledAllCall()**
- **bool setAllCallAddress(uint8_t address)**
- **uint8_t getAllCallAddress()**


## Future

#### Must

- improve documentation
  - restructure readme.md
- get hardware to test.


#### Should

- align with PCA9634 where possible
  - error codes
  - configure()?
- examples


#### Could

- default values for functions.
- unit tests
- read back RGBW (cache?)


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

