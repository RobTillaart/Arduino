
[![Arduino CI](https://github.com/RobTillaart/74HC154/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/74HC154/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/74HC154/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/74HC154/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/74HC154/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/74HC154.svg)](https://github.com/RobTillaart/74HC154/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/74HC154/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/74HC154.svg?maxAge=3600)](https://github.com/RobTillaart/74HC154/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/74HC154.svg)](https://registry.platformio.org/libraries/robtillaart/74HC154)


# 74HC154

Arduino library for the 74HC154 4-to-16 line decoder/demultiplexer.


## Description

This library controls the 74HC154 4 to 16 line decoder.
With 4 IO lines one can select one of 16 output lines to go LOW.
The other lines are HIGH.

The 74HC154 device has two input enable lines E0 and E1.
If one or both enable lines are HIGH all outputs are HIGH and there
is no line LOW.
If both enable lines are LOW, there is one line LOW (defined by the
address pins) and all others are HIGH.

The library supports only one ENABLE pin which is sufficient to control
the device. Set the other pin permanent LOW if not needed, however
never let the enable line(s) float.

One can use one of the enable inputs as the multiplexed data input.
Keep the other enable input LOW and the addressed output will follow
the state of the applied data.


### SetLine

When changing a line, not all address lines are set simultaneously as
individual digitalWrite()'s are used.
This might cause other lines be selected for a few microseconds which
might affect the working of your project.
To prevent this behaviour one can **disable()** the device before
**setLine()** and **enable()** the device afterwards.
This only works if the enablePin is set in the constructor.


### Related

- https://github.com/RobTillaart/74HC138  (3 to 8 selector)
- https://github.com/RobTillaart/74HC154  (4 to 16 selector)
- https://github.com/RobTillaart/HC4051  (1x8 mux)
- https://github.com/RobTillaart/HC4052  (2x4 mux)
- https://github.com/RobTillaart/HC4053  (3x2 mux)
- https://github.com/RobTillaart/HC4067  (1x16 mux)


## Interface

```cpp
#include "74HC154.h"
```

### Constructor

- **74HC154(uint8_t pin0, uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pinEnable = 255)**
set the 4 selection IO lines from pin numbers.
Optionally set the enable pin, connect to E1 or E2, see datasheet.
- **74HC154(uint8_t \* pins, uint8_t pinEnable = 255)**
set the 4 selection IO lines from an array.
The pins array should have at least 4 elements.
Optionally set the enable pin, connect to E1, see datasheet.


### Select line

- **bool setLine(uint8_t line)** set line 0 .. 15. Returns false if out of range.
- **uint8_t getLine()** returns 0 .. 15, default line selected = 0.
- **void nextLine()** selects the next line, wraps back to 0 if needed.
- **void prevLine()** selects the previous line, wraps to 15 if needed.


### Enable

Works only if enable line is set in constructor.

- **void enable()** enables output / selection.
- **void disable()** disables output / selection.
- **bool isEnabled()** checks if line is enabled.


## Future

#### Must

- improve documentation
- get hardware to test

#### Should


#### Could

- AVR optimize digitalWrite() as pins are known.
- investigate performance gain setLine by using a changed mask.
  - will decrease if all 4 lines change

```cpp
  void _setLine()
  {
    uint8_t changed = _oldLine ^ _line;
    for (int i = 0; i < 4; i++)
    {
      if (changed & 0x01) digitalWrite(_pin[i], (_line >> i) & 0x01);
      changed >>= 1;
    }
  }
```

- let next/prevLine() return the new line selected?
- optimize the enable functions by checking pin nr.?


#### Wont

- set default line in constructor?

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


