
[![Arduino CI](https://github.com/RobTillaart/I2CKeyPad/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/I2CKeyPad/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/I2CKeyPad/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/I2CKeyPad/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/I2CKeyPad/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/I2CKeyPad.svg)](https://github.com/RobTillaart/I2CKeyPad/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/I2CKeyPad/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/I2CKeyPad.svg?maxAge=3600)](https://github.com/RobTillaart/I2CKeyPad/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/I2CKeyPad.svg)](https://registry.platformio.org/libraries/robtillaart/I2CKeyPad)


# I2CKeyPad

Arduino library for 4x4 (or smaller) keypad connected to an I2C PCF8574.


## Description

The I2CKeyPad library implements the reading of a 4x4 keypad by means of a PCF8574.
Smaller keypads, meaning less columns or rows (4x3) can be read with it too.

Since 0.3.2 the library allows a 5x3, 6x2 or 8x1 or smaller keypad to be connected too.

### Breaking change

Since 0.5.0 the library can set a debounce threshold. 
If this is set (> 0) the **getKey()** and **getChar()** functions 
can return **I2C_KEYPAD_THRESHOLD** (255).


### Related

Relates strongly to https://github.com/RobTillaart/I2CKeyPad8x8. which is an 8x8 version using **PCF8575**.

- https://github.com/RobTillaart/PCF8574
- https://github.com/RobTillaart/AnalogKeypad
- https://github.com/RobTillaart/I2CKeyPad4x4
- https://github.com/RobTillaart/I2CKeyPad8x8
- https://github.com/WK-Software56/AdvKeyPad (derived work with keyboard alike interface)


## Connection

The PCF8574 is connected between the processor and the (default) 4x4 keypad.
See the conceptual schema below. 
It might take some trying to get the correct pins connected.

```
          PROC             PCF8574               KEYPAD
        +--------+        +---------+          +---------+
        |        |        |       0 |<-------->| R       |
        |    SDA |<------>|       1 |<-------->| O       |
        |    SCL |------->|       2 |<-------->| W       |
        |        |        |       3 |<-------->| S       |
        |        |        |         |          |         |
        |        |        |       4 |<-------->| C       |
        |        |        |       5 |<-------->| O       |
        |        |        |       6 |<-------->| L       |
        |        |        |       7 |<-------->| S       |
        +--------+        +---------+          +---------+ 
```


## I2C

### I2C addresses

This library uses a PCF8574 or a PCF8574A chip.
These devices are identical in behaviour although there are two distinct address ranges.

|  Type      |  Address-range  |  Notes                    |
|:-----------|:---------------:|:-------------------------:|
|  PCF8574   |  0x20 to 0x27   |  same range as PCF8575 !  |
|  PCF8574A  |  0x38 to 0x3F   |

Be careful to select an unique I2C address for every device on the bus.


### I2C multiplexing

Sometimes you need to control more devices than possible with the default
address range the device provides.
This is possible with an I2C multiplexer e.g. TCA9548 which creates up
to eight channels (think of it as I2C subnets) which can use the complete
address range of the device.

Drawback of using a multiplexer is that it takes more administration in
your code e.g. which device is on which channel.
This will slow down the access, which must be taken into account when
deciding which devices are on which channel.
Also note that switching between channels will slow down other devices
too if they are behind the multiplexer.

- https://github.com/RobTillaart/TCA9548


## Interface

```cpp
#include "I2CKeyPad.h"
```

### Base

- **I2CKeyPad(const uint8_t deviceAddress, TwoWire \*wire = &Wire)** 
The constructor sets the device address and optionally 
allows to selects the I2C bus to use.
- **bool begin()** The return value shows if the PCF8574 with the given address is connected properly.
Call wire.begin() first!
- **bool isConnected()** returns false if the PCF8574 cannot be connected to.
- **uint8_t getKey()** Returns default 0..15 for regular keys, 
Returns **I2C_KEYPAD_NOKEY** (16) if no key is pressed and **I2C_KEYPAD_FAIL**
(17) in case of an error, e.g. multiple keys pressed.
If a debounce delay is set, it might return **I2C_KEYPAD_THRESHOLD** if called too fast.
- **uint8_t getLastKey()** Returns the last **valid** key pressed 0..15, 
or **I2C_KEYPAD_NOKEY** (16) which is also the initial value.
- **bool isPressed()** Returns true if one or more keys of the keyPad are pressed, 
however there is no check if multiple keys are pressed.


### Mode functions

**Experimental**

- **void setKeyPadMode(uint8_t mode = I2C_KEYPAD_4x4)** sets the mode, default 4x4.
This mode can also be used for 4x3 or 4x2 or 3x3 etc. 
Invalid values for mode are mapped to 4x4.
- **uint8_t getKeyPadMode()** returns the current mode.

**Supported modi**

There are 4 modi supported, and every mode will also support smaller keypads.
E.g. a 4x3 keypad can be read in mode 4x4 or in mode 5x3.

|  modi  |  value  |  definition      |  notes    |
|:------:|:-------:|:-----------------|:----------|
|  4x4   |    44   |  I2C_KEYPAD_4x4  |  default, also for 4x3 4x2 4x1 3x3 3x2 3x1 etc.
|  5x3   |    53   |  I2C_KEYPAD_5x3  |  also for 5x2 or 5x1 etc.
|  6x2   |    62   |  I2C_KEYPAD_6x2  |  also for 6x1 etc.
|  8x1   |    81   |  I2C_KEYPAD_8x1  |  not real matrix, connect pins to switch to GND.


### KeyMap functions

Note: **loadKeyMap()** must be called before **getChar()** and **getLastChar()**!

- **char getChar()** returns the char corresponding to mapped key pressed.
It returns **I2C_KEYPAD_THRESHOLD** if called too fast.
- **char getLastChar()** returns the last char pressed.
This function is not affected by the debounce threshold.
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

Note: The 5x3, 6x2 and the 8x1 modi also uses a key map of length 18.


### Debouncing threshold

**Experimental**

Since version 0.5.0, the library implements an experimental debounce threshold
which is non-blocking.

If a key bounces, it can trigger multiple interrupts, while the purpose is to
act like only one keypress. The debounce threshold results in a fast return 
of **getKey()** (with **I2C_KEYPAD_THRESHOLD**) if called too fast.

The default value of the debounce threshold is zero to be backwards compatible.
The value is set in milliseconds, with a maximum of 65535 ==> about 65 seconds or 1 minute.
A value of 1 still allows ~1000 **getKey()** calls per second (in theory).
A value of 65535 can be used e.g. for a delay after entering a wrong key code / password.
Setting a high value might result in missed keypresses so use with care.

The default value of the debounce threshold is zero to be backwards compatible.

- **void setDebounceThreshold(uint16_t value = 0)** set the debounce threshold,
value in milliseconds, max 65535.
The default value is zero, to reset its value.
- **uint16_t getDebounceThreshold()** returns the set debounce threshold.
- **uint32_t getLastTimeRead()** returns the time stamp of the last valid read key
(or NOKEY). This variable is used for the debounce, and may be used for other
purposes too. E.g. track time between keypresses.

If a debounce threshold is set, and **getKey()** or **getChar()** is called too fast,
these functions will return **I2C_KEYPAD_THRESHOLD** (255).

Feedback welcome!


### Basic working

After the **keypad.begin()** the sketch calls the **keyPad.getKey()** to read values from the keypad. 
- If no key is pressed **I2C_KEYPAD_NOKEY** code (16) is returned.
- If the read value is not valid, e.g. two keys pressed, **I2C_KEYPAD_FAIL** code (17) is returned.
- If a debounce threshold is set, **I2C_KEYPAD_THRESHOLD** might be returned.
See section above.
- Otherwise a number 0..15 is returned.

Note NOKEY and FAIL both have bit 4 set, all valid keys don't.
This allows fast checking for valid keys.

Only if a key map is loaded, the user can call **getChar()** and **getLastChar()** to get mapped keys.


## Interrupts

The library enables the PCF8574 to generate interrupts on the PCF8574 when a key is pressed. 
This makes checking the keypad far more efficient as one does not need to poll the device over I2C.
See examples.


## Future

#### Must

- update documentation

#### Should

- test extensively
  - basic working (OK)
  - interrupts
  - keymapping
  - performance
- improve error handling?
  - **I2C_KEYPAD_ERR_MODE**

#### Could

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

