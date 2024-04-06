
[![Arduino CI](https://github.com/RobTillaart/AnalogKeypad/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AnalogKeypad/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AnalogKeypad/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AnalogKeypad/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AnalogKeypad/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AnalogKeypad.svg)](https://github.com/RobTillaart/AnalogKeypad/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AnalogKeypad/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AnalogKeypad.svg?maxAge=3600)](https://github.com/RobTillaart/AnalogKeypad/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AnalogKeypad.svg)](https://registry.platformio.org/libraries/robtillaart/AnalogKeypad)


# AnalogKeypad

Library for (Robotdyn) 4x4 and 4x3 analog keypad.


## Description

AnalogKeypad is a simple library to read the keys from a (Robotdyn) 4x4 or 4x3 keypad.
No other keypads are tested, but they should work with this library after adjusting
the **MAGIC NUMBERS** in the function **rawRead()**.


#### Related

- https://github.com/RobTillaart/I2CKeyPad
- https://github.com/RobTillaart/I2CKeyPad8x8


## Interface

```cpp
#include "AnalogKeypad.h"
```


#### Constructor

- **AnalogKeypad(const uint8_t analogPin, const uint8_t bitsADC = 10)** constructor, 
analogPin is typical A0 etc. BitsADC has a default of 10, but need to be set to match the platform.
If bits < 8 then the internal shift would be too large causing all reads to return 0 or so.


#### polling interface

- **uint8_t pressed()** returns 0 if no key pressed, otherwise returns key pressed (may fluctuate).
- **uint8_t read()** read the key pressed returns 0 .. 16 where 0 means NOKEY.


#### event interface

- **uint8_t event()** checks if a change has occurred since last time.
- **uint8_t key()** returns the key involved with last event.

```cpp
  uint8_t e = AKP.event();
  switch (e)
  {
    case PRESSED:
      Serial.print("press\t");
      Serial.println(AKP.key());
      break;
    case RELEASED:
      Serial.print("release\t");
      Serial.println(AKP.key());
      break;
    case REPEATED:
      Serial.print("repeat\t");
      Serial.println(AKP.key());
      break;
    case CHANGED:
      Serial.print("change\t");
      Serial.println(AKP.key());
      break;
    default:  //  NOKEY
      break;
  }
```

|  Event     |  value  |
|:----------:|:-------:|
|  PRESSED   |   0x80  |
|  RELEASED  |   0x40  |
|  REPEATED  |   0x20  |
|  CHANGED   |   0x10  |
|  NOKEY     |   0x00  |


## Operation

The simplest usage is to use the **read()** function.
This will return a 0 (NOKEY) when no key is pressed and
a number 1 to 16 for the keys pressed. Note the return value may
fluctuate randomly when multiple keys are pressed.

The **pressed()** function is a bit more robust.
It returns the key pressed first, so multiple key presses simultaneously
are less likely to disturb your program.

See Examples


## Future

#### Must

#### Should

- more examples
  - self-learning example?

#### Could

- make internal mapping array runtime adaptable?
  - store in RAM, accessor functions
- version for external ADC
  - see ADC712
- derive class for 4x3, 4x2 and 4x1 analog keypads?

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


