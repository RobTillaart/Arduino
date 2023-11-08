
[![Arduino CI](https://github.com/RobTillaart/M5ANGLE8/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/M5ANGLE8/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/M5ANGLE8/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/M5ANGLE8/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/M5ANGLE8/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/M5ANGLE8.svg)](https://github.com/RobTillaart/M5ANGLES8/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/M5ANGLE8/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/M5ANGLE8.svg?maxAge=3600)](https://github.com/RobTillaart/M5ANGLE8/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/M5ANGLE8.svg)](https://registry.platformio.org/libraries/robtillaart/M5ANGLE8)


# M5ANGLE8

Arduino library for M5 8ANGLE 8x12 bit potentiometers.


## Description

**Experimental**

M5ANGLE8 is an Arduino class to read the potentiometers of the M5 8ANGLE module.
It also provides means to write RGB values to the 9 LED's in the same module.

The potentiometers can be read with 8 bit (faster) or 12 bit.
Derived from these two resolutions this library also supports resolutions from 1 to 12 bit.
So the range can be chosen to match your application.
Furthermore the library can reverse the range from 0..n => n..0.

The library has a wrapper function **selectionRead(channel, steps)** around the analogRead 
to make a selection between 0..steps-1. 

The library can read the state of the mini switch.

The library can set the RGB value and brightness of the 9 LEDS.

First tests are done and the library looks stable now. 
Missing is an interrupt signal e.g. on change. 
One has to poll all channels for changes which is not efficient. 
A single byte register that showed change since last read would allow to monitor 
all 8 potentiometers in one call.  

Feedback is welcome!


#### I2C

The address range is in theory from 0..127, however the I2C specification
states it should be between 8 and 119 as some addresses are reserved.
The default address is **0x43** or **67**.

|  clock  |  works  |  notes  |
|:-------:|:-------:|:--------|
| 100 KHz |   yes   |
| 200 KHz |   yes   |
| 400 KHz |   yes   |  max speed advised
| 600 KHz |    no   |

See log file performance sketch.


#### Accuracy

The potentiometers in my test setup were quite stable and have little noise. 
At 12 bit resolution I got most of the time 2 bits or less noise. 

The angle of 280° for 4095 values is 14~15 steps per degree,
that makes it pretty difficult to set a value exactly. 

The update performance of LEDs looks stable up to 40x per second in total.
Beyond that frequency some blocking effects occur. 
Roughly determined with led_demo.


#### Related

- https://github.com/RobTillaart/GAMMA
- https://github.com/RobTillaart/map2colour
- https://github.com/RobTillaart/M5Angle8
- https://github.com/RobTillaart/M5ROTATE8


## Interface

```cpp
#include "M5ANGLE8.h"
```

#### Constructor part

- **M5ANGLE8(uint8_t address = M5ANGLE8_DEFAULT_ADDRESS, TwoWire \*wire = &Wire)** constructor.
Default address = 0x43, default Wire.
- **bool begin()** check if device is connected. 
User must call wire.begin() before this one.
- **bool isConnected()** checks if address is on the I2C bus.
- **bool setAddress(uint8_t address = M5ANGLE8_DEFAULT_ADDRESS)** set a new address for the device.
Default 0x43.
- **uint8_t getAddress()** convenience function.
- **uint8_t getVersion()** get firmware version from device.


#### Analog part

- **uint16_t analogRead(uint8_t channel, uint8_t resolution = 12)**
Read a potentiometer, resolution can be set from 1..12 bit, constrained.
- **void setReverse(bool reverse)** reverse the range of the potentiometers. 
Default is false == 0..n  (true == n..0) - think right turn.
- **bool getReverse()** get the current setting.
- **uint16_t selectorRead(uint8_t channel, uint8_t steps)** maps the analogRead upon 0..steps-1 steps.


#### Input switch part

- **uint8_t inputSwitch()** read status of the switch.


#### LED part

- **bool writeRGB(uint8_t channel, uint8_t R, uint8_t G, uint8_t B, uint8_t brightness)**
Set the RGB value and brightness of a specific LED.  
channel = 0..8  
brightness - 0..100  
- **bool setAll(uint8_t R, uint8_t G, uint8_t B, uint8_t brightness)** set all LEDS.
- **bool allOff()** switch all LEDs off.
Returns true.
- **bool writeBrightness(channel, uint8_t brightness)** Set brightness only.


## Future

#### Must

- improve documentation
- keep in sync with **M5ROTATE8** where possible.

#### Should

- error handling
- **bool readRGB(channel, &R, &G, &B, &brightness)**
  - or **uint32_t readRGB(uint8_t channel)**
- improve on return values of functions.
- improve performance
  - faster **allOff()** writing 2x 16 bytes dedicated.
  - read all analog ports in one call. (array of values).
- investigate address changes


#### Could

- add examples
  - complex wave generator (freq, p0..p6 7 harmonics)
  - digital lock - 4096^8 possibilities in theory. 256^8 = 2^64 is enough...
    even 8^8 = 16 million.
    switch => verify trigger
  - dynamic "multi-mapping", set 8 points to match a curve.
  - equalizer 2x4 band (stereo)
  - LED colour mapping green -> yellow -> red.
- investigate pulsating LED, how much performance costs?
- investigate "optimal" polling frequency
- add unit tests

  
#### Wont (unless)

- write separate colour channels?
- caching?
  - version (not interesting), 
  - RGB values = 32 bytes


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

