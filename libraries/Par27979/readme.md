
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

The library is essentially a wrapper around the Stream used to connect the display.
This stream is typically Serial, Serial1 (2, 3, 4..) or newSoftSerial or equivalent.
The stream is a parameter of the constructor and cannot be changed runtime.

The library should work for the Parallax 27976 and Parallax 27977 display 
although these are not tested.

| Type    |   Size   |  Baudrate  |
|:-------:|:--------:|:----------:|
|  27976  |  2 x 16  |    19200   |
|  27977  |  2 x 16  |    19200   |
|  27979  |  4 x 20  |    19200   |

As always, feedback is welcome.

### Related

- https://github.com/RobTillaart/SWSerialOut
- https://github.com/RobTillaart/I2C_LDC


## Interface

```cpp
#include "PAR27979.h"
```

The library implements the **Print** interface to print integers
floats and strings and all printable types.

The library does not keep any state information, it only implements a few
methods to make working with the display easier.


### Base

- **PAR27979(Stream \* str)** constructor, used stream as parameter.
Before one can print anything the baud rate of the stream need to be 
set to 19200 baud (default).
- **void on()** switch display on.
- **void off()** switch display off.
- **void clearHome()** clear the display.
- **void backlightOn()** enable the backlight.
- **void backLightOff()** disable the backlight.


### Cursor Movement

- **void left()** move the cursor to the left.
- **void right()** move the cursor to the right.
- **void down()** move the cursor down.
- **void gotoXY(uint8_t x, uint8_t y)** move the cursor to position X, Y.


### Custom chars

See datasheet Page 5.

- **void defineCustomChar(uint8_t idx, uint8_t \* arr)** array will need to be at least 8 bytes.
- **void customChar(uint8_t idx)** print the custom character defined before.


### Sound support

These function do not check the range of the parameter.

- **void octave(uint8_t octave)** octave = 3 4 5 6 7
- **void duration(uint8_t duration)** duration = 1 2 4 8 16 32 64
- **void play(uint8_t note)** note = 0 1 2 3 4 5 6 7 8 9 10 11   0 = A 1 = A# etc.
- **void noSound()** switches the sound off.


## Support Parallax 27976 and Parallax 27977

Although not tested, the functions should work with the
Parallax 27976 and 27977 displays too.

Be aware that these have different sizes.


## Future

Only extend on a per request basis.

#### Must

#### Should

#### Could

- improve documentation
- test different baud rates.
- test SWSerialOut.
- test custom chars
- test 27976 and 27977 display 
  - https://forum.arduino.cc/t/2x16-lcd-troubleshoot/1311497/4
- extend unit test
- wrapper **play(note, octave, duration)** in one call?
- default parameters for some functions?

#### Won't


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

