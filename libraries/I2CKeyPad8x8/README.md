
[![Arduino CI](https://github.com/RobTillaart/I2CKeyPad8x8/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/I2CKeyPad8x8/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/I2CKeyPad8x8/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/I2CKeyPad8x8/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/I2CKeyPad8x8/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/I2CKeyPad8x8.svg)](https://github.com/RobTillaart/I2CKeyPad8x8/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/I2CKeyPad8x8/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/I2CKeyPad8x8.svg?maxAge=3600)](https://github.com/RobTillaart/I2CKeyPad8x8/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/I2CKeyPad8x8.svg)](https://registry.platformio.org/libraries/robtillaart/I2CKeyPad8x8)


# I2CKeyPad8x8

Arduino library for 8x8 or smaller KeyPad connected to an I2C PCF8575.


## Description

EXPERIMENTAL (first tests ==> OK)

The I2CKeyPad8x8 library implements the reading of a 8x8 keypad by means of a PCF8575.
Smaller keypads, meaning less columns or rows (e.g. 5x4) can be read with it too.

#### Related

Relates strongly to https://github.com/RobTillaart/I2CKeyPad. which is an 8x8 version using **PCF8574**.

- https://github.com/RobTillaart/AnalogKeypad
- https://github.com/RobTillaart/I2CKeyPad8x8


## Connection

The PCF8575 is connected between the processor and the (default) 8x8 keypad.
See the conceptual schema below. 
It might take some trying to get the correct pins connected.

```
          PROC             PCF8575              KEYPAD
        +--------+        +--------+          +--------+
        |        |        |       0|----------|R       |
        |    SDA |--------|       .|----------|O       |
        |    SCL |--------|       .|----------|W       |
        |        |        |       7|----------|S       |
        |        |        |       .|          |        |
        |        |        |       .|          |        |
        |        |        |       8|----------|C       |
        |        |        |       .|----------|O       |
        |        |        |       .|----------|L       |
        |        |        |      15|----------|S       |
        +--------+        +--------+          +--------+ 
```


## Interface

```cpp
#include "I2CKeyPad8x8.h"
```


#### Base

- **I2CKeyPad8x8(const uint8_t deviceAddress, TwoWire \*wire = &Wire)** 
The constructor sets the device address and optionally 
allows to selects the I2C bus to use.
- **bool begin()** The return value shows if the PCF8575 with the given address is connected properly.
Call wire.begin() first!
- **bool isConnected()** returns false if the PCF8575 cannot be connected to.
- **uint8_t getKey()** Returns default 0..63 for regular keys, 
Returns 64 if no key is pressed and 65 in case of an error.
- **uint8_t getLastKey()** Returns the last **valid** key pressed 0..63. Initially it will return 64 (NOKEY).
- **bool isPressed()** Returns true if one or more keys of the keyPad is pressed, 
however it is not checked if multiple keys are pressed.


#### KeyMap functions

**loadKeyMap()** must be called before **getChar()** and **getLastChar()**!

- **char getChar()** returns the char corresponding to mapped key pressed.
- **char getLastChar()** returns the last char pressed.
- **bool loadKeyMap(char \* keyMap)** keyMap should point to a (global) char array of length 66.
This array maps index 0..63 on a char and index \[64\] maps to **I2CKeyPad8x8_NOKEY** (typical 'N') 
and index \[65\] maps **I2CKeyPad8x8_FAIL** (typical 'F'). index 66 is the null char.

**WARNING**
If there is no key map loaded the user should **NOT** call **getChar()** or 
**getLastChar()** as these would return meaningless bytes.


Note: a keyMap char array may be longer than 66 characters, but only the first 66 are used.
The length is **NOT** checked upon loading (as it may contain a NULL char).


#### Basic working

After the **keypad.begin()** the sketch calls the **keyPad.getKey()** to read values from the keypad. 
- If no key is pressed **I2C_KEYPAD8x8_NOKEY** code (16) is returned.
- If the read value is not valid, e.g. two keys pressed, **I2CKeyPad8x8_FAIL** code (17) is returned.
- Otherwise a number 0..63 is returned.

Note NOKEY and FAIL bot have bit 8 set, all valid keys don't.
This allows fast checking for valid keys.

Only if a key map is loaded, the user can call **getChar()** and **getLastChar()** to get mapped keys.


## Interrupts

The library enables the PCF8575 to generate interrupts on the PCF8575 when a key is pressed. 
This makes checking the keypad far more efficient as one does not need to poll over I2C.

See examples. (TODO)


## Operation

See examples


## Future


#### Must

- update documentation
- keep in sync with **I2CKeyPad** as much as possible.

#### Should

- test extensively
  - basic working (OK)
  - interrupts
  - keymapping
  - performance

#### Could

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

