
[![Arduino CI](https://github.com/RobTillaart/M5ROTATE8/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/M5ROTATE8/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/M5ROTATE8/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/M5ROTATE8/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/M5ROTATE8/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/M5ROTATE8.svg)](https://github.com/RobTillaart/M5ROTATE8/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/M5ROTATE8/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/M5ROTATE8.svg?maxAge=3600)](https://github.com/RobTillaart/M5ROTATE8/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/M5ROTATE8.svg)](https://registry.platformio.org/libraries/robtillaart/M5ROTATE8)


# M5ROTATE8

Arduino library for M5 8ROTATE 8x rotary encoders.


## Description

**Experimental**

M5ROTATE8 is an Arduino library to read the 8 rotary encoders of the
M5 8ENCODER device.
It also provides means to write RGB values to the 9 LED's in the same module.

The rotary encoders can be read as an absolute counter, since start or reset, 
or as a relative counter since last time read. 
These values can be both positive and negative depending on the direction of the turns.
The absolute counters can be given an initial value e.g. to match some value in your project.
These counters can be reset per channel.

Furthermore the library can read the key pressed status of every rotary encoder.
These can be used e.g. to switch mode from fine to coarse and back.

The library can set the RGB value of the 9 LEDS.
The RotaryEncoder module has no brightness, like the 8ANGLe unit does.

Finally the library can read the state of the mini switch.

First tests with hardware have been done. 
**Warning:** One strange observation, the RE makes steps of size 2 and occasionally step size 1.
This needs further investigation, so use with care.

Feedback is welcome!

#### Missing in V1

The device has no interrupt signal e.g. on change. However since firmware version V2
the device allows to read one register to see changes on all rotary encoders and one 
registers to see all the button states. These enhancements improve interaction most
of the time.

Note: V2 is not tested with hardware yet.


#### Breaking change

Version 0.4.0 added support for Firmware V2 functions. See below.
If your hardware has firmware V1 these functions won't work.


#### Breaking change

Version 0.3.0 introduced a breaking change.
You cannot set the pins in **begin()** any more.
This reduces the dependency of processor dependent Wire implementations.
The user has to call **Wire.begin()** and can optionally set the Wire pins 
before calling **begin()**.


#### I2C

The address range is in theory from 0..127, however the I2C specification
states it should be between 8 and 119 as some addresses are reserved,
or have special meaning.

The default address is **0x41** or **65**.

|  clock  |  works  |  notes  |
|:-------:|:-------:|:-------:|
| 100 KHz |   yes   |
| 200 KHz |   yes   |
| 400 KHz |   yes   |  max speed advised.
| 600 KHz |    no   |

See log file performance sketch.


#### Accuracy

The overall behaviour looks not too bad, there are 30 steps per rotation.
The rotary encoders show a step size of 2 and sometimes a step size of 1.
So normally one rotation gives +60 or -60.
The step size needs investigation as I would expect step size 1, always.


#### Related

Manufacturer
- https://github.com/m5stack/M5Unit-8Encoder
- https://github.com/m5stack/M5Unit-8Encoder/issues/1 (V2 extensions)
- https://github.com/m5stack/M5Unit-8Encoder-Internal-FW  (firmware)

Libraries
- https://github.com/RobTillaart/M5ANGLE8
- https://github.com/RobTillaart/M5ROTATE8
- https://github.com/RobTillaart/rotaryDecoder
- https://github.com/RobTillaart/rotaryDecoderSwitch


## Interface

```cpp
#include "M5ROTATE8.h"
```

#### Constructor part

- **M5ROTATE8(uint8_t address = M5ROTATE8_DEFAULT_ADDRESS, TwoWire \*wire = &Wire)** constructor.
Default address = 0x41, default Wire.
- **bool begin()** checks if address is on the I2C bus.
User must call wire.begin() before this one.
- **bool isConnected()** checks if the address given in the constructor, or by setAddress(), 
can be found on the I2C bus.
- **bool setAddress(uint8_t address = M5ROTATE8_DEFAULT_ADDRESS)** set a new address for the device.
Default address = 0x41.
Returns false if address below 8 or above 119.
- **uint8_t getAddress()** convenience function to get the set address.
- **uint8_t getVersion()** get the firmware version from device.


#### Rotary encoder part

- **int32_t getAbsCounter(uint8_t channel)**
Read the absolute or cumulative position of the rotary encoder since reset or start.
Note this can be positive or negative or zero.
- **void setAbsCounter(uint8_t channel, int32_t value)** allows to set an initial value
e.g. so it matches a setting or value in your application.
- **int32_t getRelCounter(uint8_t channel)**
Read a relative position of the rotary encoder since reset.
Note this can be positive or negative or zero.
Note: this counter will reset after each read.
- **bool getKeyPressed(uint8_t channel)** get the status of the key of the rotary encoder.
True (1) is pressed, False (0) is not pressed.
- **bool resetCounter(uint8_t channel)** reset a rotary encoder.
- **void resetAll()** reset all rotary encoder counters to 0.


#### Input switch part

- **uint8_t inputSwitch()** read the status of the micro switch.


#### LED part

- **bool writeRGB(uint8_t channel, uint8_t R, uint8_t G, uint8_t B)** Set the RGB value of a specific LED.  
channel = 0..8 as there is one more LED than rotary encoders.
- **uint32_t readRGB(uint8_t channel)** read back the RGB value of specified LED as an 32 bits integer.
The value is 0x00RRGGBB.
- **bool setAll(uint8_t R, uint8_t G, uint8_t B)** set all LEDs to the specified RGB value.
- **bool allOff()** switches all LEDs off, RGB = (0,0,0).


#### Firmware V2 functions

New content in registers 0x58 - 0x5F, 0x61, 0x62.  
Needs testing with hardware.

- **void setButtonToggleCount(uint8_t channel, uint8_t value = 0)**
Write a starting value to the toggle counters.
- **uint8_t getButtonToggleCount(uint8_t channel)** Button toggle counting.
To be used to see if button has been pressed and released, optionally multiple times.
Reset to zero after reading.
- **uint8_t getButtonChangeMask()** returns a bit mask for all 8 buttons, 
bit 0 = not pressed, bit 1 = pressed.
To be used to check all 8 buttons in just one call. 
This is much faster than reading them separately one by one.
Note that this function inverts the datasheetV2 specification as it seems more logical.
- **uint8_t getEncoderChangeMask()** returns a bit mask for all 8 rotary encoders.
Bit 0 = no change, bit 1 = changed.
To be used to check all 8 encoders in one call. 
This is much faster than reading them separately one by one.
Resets the whole mask (register) to zero after reading. 


## Future

#### Must

- improve documentation
- keep in sync with **M5ANGLE8** where possible.
- investigate step size 2 / 1.
  - An easy patch: divide by 2 resulting in step size 1 or 0

#### Should

- test firmware V2 functions with hardware.
- error handling
- optimize low level calls
  - merge into two functions => read/write array + length.
  - resetAll() could be "one call"
  - does this affect performance?
- improve performance (how?)
- extend performance example with V2 functions

#### Could

- add examples
  - digital lock
- add unit tests

#### Wont (unless)

- **bool readRGB(channel, &R, &G, &B)**

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


