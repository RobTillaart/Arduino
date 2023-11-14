
[![Arduino CI](https://github.com/RobTillaart/PAR27979/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PAR27979/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PAR27979/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PAR27979/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PAR27979/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/PAR27979.svg)](https://github.com/RobTillaart/PAR27979/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PAR27979/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PAR27979.svg?maxAge=3600)](https://github.com/RobTillaart/PAR27979/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/PAR27979.svg)](https://registry.platformio.org/libraries/robtillaart/PAR27979)


# PAR27979

Arduino library for the Parallax 27979 serial display.


## Description

The library is essentially a wrapper around a Stream, typically Serial, 
Serial2 (3,4..) or newSoftSerial or equivalent.
This stream is given as parameter in the constructor.

Should work for 27976 and 27977 display although not tested.


## Interface

```cpp
#include "PAR27979.h"
```

The library implements the **Print** interface to print integers
floats and strings and all printable types.

The library does not keep any state information, it only implements a few
methods to make working with it easier.

### Base

- **PAR27979(Stream \* str)** constructor, used stream as parameter.
- **void on()** switch display on.
- **void off()** switch display off.
- **void clearHome()** clear the display.
- **void backlightOn()** enable the backlight.
- **void backLightOff()** disable the backlight.


### Cursor Movement

- **void left()** move cursor.
- **void right()** move cursor.
- **void down()** move cursor.
- **void gotoXY(uint8_t x, uint8_t y)** idem.


### Custom chars

see datasheet.

- **void defineCustomChar(uint8_t idx, uint8_t \* arr)** array will need to be 8 bytes.
- **void customChar(uint8_t idx)** idem.


### Sound support

- **void octave(uint8_t octave)**  octave =  3 4 5 6 7
- **void duration(uint8_t duration)** duration = 1 2 4 8 16 32 64
- **void play(uint8_t note)** note = 0 1 2 3 4 5 6 7 8 9 10 11   0=A 1=A# etc.
- **void noSound()** idem.


## Support Parallax 27976 & 27977

Although not tested, the functions should work with the
Parallax 27976 and 27977 displays too.


## Operation

See examples.

## Future

only extend on a per request basis

- documentation
- different baud rates?
- test custom chars
- more testing.
- test 27976 and 27977 display 
- extend unit test


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

