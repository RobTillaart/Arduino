
[![Arduino CI](https://github.com/RobTillaart/AMT25/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AMT25/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AMT25/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AMT25/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AMT25/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AMT25.svg)](https://github.com/RobTillaart/AMT25/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AMT25/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AMT25.svg?maxAge=3600)](https://github.com/RobTillaart/AMT25/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AMT25.svg)](https://registry.platformio.org/libraries/robtillaart/AMT25)


# AMT25

Arduino library for SPI based AMT25 series rotary encoder.


### Description

**Experimental**

**Warning:** This library is not tested with hardware yet.
So use with care, feedback welcome.

AMT25 is a library for the **AMT253D-V** and compatible rotation encoders.
This devices decodes 360.0° in 4096 (12 bits) or 16384 steps (14 bits)
which implies an accuracy of about 0.088° or even 0.022°.

TODO elaborate.



### Compatibles

Families of AMT2x series rotary encoder devices with other interfaces.

|  device  |  protocol  |  compat  |  notes  |
|:--------:|:----------:|:--------:|:--------|
|  AMT21   |   RS485    |    x     |
|  AMT22   |    SPI     |   YYY    |
|  AMT23   |  3-Wire    |    ?     |  Simpler, SPI alike, investigate
|  AMT24   |   RS485    |    x     |
|  AMT25   |    SPI     |   YYY    |

So far the AMT22 family looks compatible and the AMT23 family might.
TODO investigate.

Please note that from the **AMT25xy-V** there are 8 variations.
See [datasheet](https://www.sameskydevices.com/product/resource/amt25.pdf)
for all details:
- x = Orientation: 2 = Radial (right angle), 3 = Axial (straight)
- y = Absolute Resolution:
  - A = 12-bit single-turn, B = 14-bit single-turn
  - C = 12-bit multi-turn,  D = 14-bit multi-turn

Not all variations are tested.


### Hardware

Hardware SPI connections UNO
[based upon AMT22](https://www.sameskydevices.com/product/resource/sample-code/amt22)

|  PIN   |  Uno Pin  |  AMT  |  color1  |  color2  |  Notes  |
|:------:|:---------:|:-----:|:---------|:---------|:-------:|
|  +5V   |    5V     |   1   |  White   |  Green   |
|  SCLK  |    13     |   2   |  Blue    |  White   |
|  MOSI  |    11     |   3   |  White   |  Blue    |
|  GND   |    GND    |   4   |  Green   |  White   |
|  MISO  |    12     |   5   |  Orange  |  White   |
|  CS    |     2     |   6   |  White   |  Orange  |  Chip Select can be any free pin.


### Related

Angle math

- https://github.com/RobTillaart/Angle
- https://github.com/RobTillaart/AngleConvertor
- https://github.com/RobTillaart/AverageAngle
- https://github.com/RobTillaart/runningAngle

Decoders

- https://www.sameskydevices.com/product/resource/amt25.pdf - datasheet
- https://github.com/RobTillaart/AMT25 this library
- https://github.com/RobTillaart/AS5600 magnetic rotation meter.
- https://github.com/RobTillaart/ERCFS SPI based rotary encoder.


### Please report your experiences.

If you have a AMT25 device, please let me know your experiences
with the sensor and this (or other) library.


## Interface

```cpp
#include "AMT25.h"
```

### Constructor

- **AMT25(uint8_t select, __SPI_CLASS__ \* mySPI = &SPI)** HARDWARE SPI
- **AMT25(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock)** SOFTWARE SPI
- **bool begin(uint8_t bits = 14)** initializes the communication, set number of bits.

AMT22 and AMT23 derived classes have same constructors.


### Read

- **uint16_t getRawValue()** returns a value from 0..16383
- **float getAngle()** returns an absolute angle from 0..360.0°, optional
with offset correction.
- **void setOffset(float offset = 0)** set an offset in degrees for the angle.
- **float getOffset()** returns the current offset in degrees.
- **uint16_t setZero()** set current position as zero.
- **uint16_t getTurns()** get number of turns.
- **uint32_t lastRead()** timestamp in microseconds since start.
Note this wraps every ~70 minutes however for RPM measurements one
need to read the device far more often.


### SPI

- **void setSPIspeed(uint32_t speed)** idem, clipped to max 2 MHz.
- **uint32_t getSPIspeed()** idem.
- **bool usesHWSPI()** idem.


## Future

#### Must

- improve documentation
- test with hardware

#### Should

- test compatibility ANT22 / AMT23

#### Could

- add examples
- add convenience getter for steps / bits

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

