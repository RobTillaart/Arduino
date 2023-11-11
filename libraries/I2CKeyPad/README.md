
[![Arduino CI](https://github.com/RobTillaart/I2CKeyPad/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/I2CKeyPad/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/I2CKeyPad/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/I2CKeyPad/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/I2CKeyPad/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/I2CKeyPad.svg)](https://github.com/RobTillaart/I2CKeyPad/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/I2CKeyPad/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/I2CKeyPad.svg?maxAge=3600)](https://github.com/RobTillaart/I2CKeyPad/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/I2CKeyPad.svg)](https://registry.platformio.org/libraries/robtillaart/I2CKeyPad)


# I2CKeyPad

Arduino library for 4x4 KeyPad connected to an I2C PCF8574.


## Description

The I2CKeyPad library implements the reading of a 4x4 keypad by means of a PCF8574.
Smaller keypads, meaning less columns or rows (4x3) can be read with it too.

Since 0.3.2 the library allows a 5x3, 6x2 or 8x1 or smaller keypad to be connected too.

#### Related

Relates strongly to https://github.com/RobTillaart/I2CKeyPad8x8. which is an 8x8 version using **PCF8575**.

- https://github.com/RobTillaart/AnalogKeypad
- https://github.com/RobTillaart/I2CKeyPad8x8
- https://github.com/WK-Software56/AdvKeyPad (derived work with keyboard alike interface)


## Connection

The PCF8574 is connected between the processor and the (default) 4x4 keypad.
See the conceptual schema below. 
It might take some trying to get the correct pins connected.

```
          PROC             PCF8574              KEYPAD
        +--------+        +--------+          +--------+
        |        |        |       0|----------|R       |
        |    SDA |--------|       1|----------|O       |
        |    SCL |--------|       2|----------|W       |
        |        |        |       3|----------|S       |
        |        |        |        |          |        |
        |        |        |       4|----------|C       |
        |        |        |       5|----------|O       |
        |        |        |       6|----------|L       |
        |        |        |       7|----------|S       |
        +--------+        +--------+          +--------+ 
```


## Interface

```cpp
#include "I2CKeyPad.h"
```

#### Base

- **I2CKeyPad(const uint8_t deviceAddress, TwoWire \*wire = &Wire)** 
The constructor sets the device address and optionally 
allows to selects the I2C bus to use.
- **bool begin()** The return value shows if the PCF8574 with the given address is connected properly.
Call wire.begin() first!
- **bool isConnected()** returns false if the PCF8574 cannot be connected to.
- **uint8_t getKey()** Returns default 0..15 for regular keys, 
Returns 16 if no key is pressed and 17 in case of an error.
- **uint8_t getLastKey()** Returns the last **valid** key pressed 0..15. Initially it will return 16 (noKey).
- **bool isPressed()** Returns true if one or more keys of the keyPad is pressed, 
however it is not checked if multiple keys are pressed.


#### Mode functions

Note: experimental

- **void setKeyPadMode(uint8_t mode = I2C_KEYPAD_4x4)** sets the mode, default 4x4.
This mode can also be used for 4x3 or 4x2. 
Invalid values are mapped to 4x4.
- **uint8_t getKeyPadMode()** returns the current mode.

**Supported modi**

There are 4 modi supported, and every mode also supports smaller keypads.
E.g. a 4x3 keypad can be read in mode 4x4 or in mode 5x3.

|  modi  |  value  |  definition      |  notes    |
|:------:|:-------:|:-----------------|:----------|
|  4x4   |    44   |  I2C_KEYPAD_4x4  |  default  |
|  5x3   |    53   |  I2C_KEYPAD_5x3  |
|  6x2   |    62   |  I2C_KEYPAD_6x2  |
|  8x1   |    81   |  I2C_KEYPAD_8x1  |  not real matrix, connect pins to switch to GND.


#### KeyMap functions

**loadKeyMap()** must be called before **getChar()** and **getLastChar()**!

- **char getChar()** returns the char corresponding to mapped key pressed.
- **char getLastChar()** returns the last char pressed.
- **bool loadKeyMap(char \* keyMap)** keyMap should point to a (global) char array of length 19.
This array maps index 0..15 on a char and index \[16\] maps to **I2CKEYPAD_NOKEY** (typical 'N') 
and index \[17\] maps **I2CKEYPAD_FAIL** (typical 'F'). index 18 is the null char.

**WARNING**
If there is no key map loaded the user should **NOT** call **getChar()** or 
**getLastChar()** as these would return meaningless bytes.


```cpp
char normal_keymap[19]  = "123A456B789C*0#DNF";   // typical normal key map (phone layout)
char repeat_keymap[19]  = "1234123412341234NF";   // effectively 4 identical columns
char partial_keymap[19] = "1234            NF";   // top row
char diag_keymap[19]    = "1    2    3    4NF";   // diagonal keys only
```

In the examples above a 'space' key might be just meant to ignore.
However functionality there is no limit how one wants to use the key mapping.
It is even possible to change the mapping runtime after each key.

Note: a keyMap char array may be longer than 18 characters, but only the first 18 are used.
The length is **NOT** checked upon loading.

Note: The 5x3, 6x2 and the 8x1 modi also uses a keymap of length 18.


#### Basic working

After the **keypad.begin()** the sketch calls the **keyPad.getKey()** to read values from the keypad. 
- If no key is pressed **I2CKEYPAD_NOKEY** code (16) is returned.
- If the read value is not valid, e.g. two keys pressed, **I2CKEYPAD_FAIL** code (17) is returned.
- Otherwise a number 0..15 is returned.

Note NOKEY and FAIL bot have bit 4 set, all valid keys don't.
This allows fast checking for valid keys.

Only if a key map is loaded, the user can call **getChar()** and **getLastChar()** to get mapped keys.


## Interrupts

Since version 0.2.1 the library enables the PCF8574 to generate interrupts 
on the PCF8574 when a key is pressed. 
This makes checking the keypad far more efficient as one does not need to poll over I2C.
See examples.


## Operation

See examples


## Future

#### Must

- update documentation

#### Should

- test key mapping functions.

#### Could

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

