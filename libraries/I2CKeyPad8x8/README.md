
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

**Experimental** (first tests ==> OK)

The I2CKeyPad8x8 library implements the reading of a 8x8 keypad by means 
of a PCF8575. Smaller keypads, meaning less columns or rows (e.g. 5x4) 
can be read with it too.


### Breaking change

Since 0.3.0 the library can set a debounce threshold. 
If this is set (> 0) the **getKey()** and **getChar()** functions 
can return **I2C_KEYPAD_THRESHOLD** (255).


### Related

Relates strongly to https://github.com/RobTillaart/I2CKeyPad which is 
an 4x4 version using **PCF8574**.

- https://github.com/RobTillaart/PCF8575
- https://github.com/RobTillaart/AnalogKeypad
- https://github.com/RobTillaart/I2CKeyPad
- https://github.com/RobTillaart/I2CKeyPad8x8


## Connection

The PCF8575 is connected between the processor and the (default) 8x8 keypad.
See the conceptual schema below. 
It might take some trying to get the correct pins connected.

```
          PROC              PCF8575              KEYPAD
        +--------+        +---------+          +---------+
        |        |        |       0 |<-------->| R       |
        |    SDA |<------>|       . |<-------->| O       |
        |    SCL |<------>|       . |<-------->| W       |
        |        |        |       7 |<-------->| S       |
        |        |        |         |          |         |
        |        |        |       8 |<-------->| C       |
        |        |        |       . |<-------->| O       |
        |        |        |       . |<-------->| L       |
        |        |        |      15 |<-------->| S       |
        +--------+        +---------+          +---------+ 
```


## I2C

### I2C addresses

This library uses a PCF8575 chip.

|  Type      |  Address-range  |  Notes                    |
|:-----------|:---------------:|:-------------------------:|
|  PCF8575   |  0x20 to 0x27   |  same range as PCF8574 !  |

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
#include "I2CKeyPad8x8.h"
```

### Constructor

- **I2CKeyPad8x8(const uint8_t deviceAddress, TwoWire \*wire = &Wire)** 
The constructor sets the device address and optionally 
allows to selects the I2C bus to use.
- **bool begin()** The return value shows if the PCF8575 with the given 
device address is connected properly. 
Call wire.begin() first!
- **bool isConnected()** returns false if the PCF8575 cannot be connected to.
- **bool isConnected()** returns false if the device address of the PCF8574 cannot be seen on the I2C bus.
- **uint8_t getAddress()** returns the set device address.


### getKey

- **uint8_t getKey()** Returns default 0..63 for regular keys, 
Returns **I2C_KEYPAD8X8_NOKEY** (64) if no key is pressed and and **I2C_KEYPAD8X8_FAIL**
(65) in case of an error, e.g. multiple keys pressed.
If a debounce delay is set (see below), it will return **I2C_KEYPAD8X8_THRESHOLD** (255) 
if the function is called too fast.
- **uint8_t getLastKey()** Returns the last **valid** key pressed 0..63, or **I2C_KEYPAD8X8_NOKEY** 
(64) which is also the initial value.
This function does not "cache" failed keys.
- **bool isPressed()** Returns true if one or more keys of the keyPad are pressed.
Note there is no check if multiple keys are pressed or just one.
Returns false if no key is pressed or when there is a communication error.
So checking **getKey()** yourself will give more information, but is slightly slower.


|  getKey()  |  HEX code    |  Meaning                  |  Notes  |
|:----------:|:------------:|:--------------------------|:--------|
|  0..63     |  0x00..0x3F  |  valid key pressed        |
|  64        |  0x40        |  I2C_KEYPAD8X8_NOKEY      |
|  65        |  0x41        |  I2C_KEYPAD8X8_FAIL       |  multi key or I2C communication error.
|  255       |  0xFF        |  I2C_KEYPAD8X8_THRESHOLD  |


### KeyMap functions

Note: **loadKeyMap()** must be called before **getChar()** and **getLastChar()**
can be used!

- **char getChar()** returns the char corresponding to mapped key pressed.
The function returns **I2C_KEYPAD_THRESHOLD** (255) if called too fast and a debounce threshold is set.
- **char getLastChar()** returns the last char pressed.
This function is not affected by the debounce threshold.
- **bool loadKeyMap(char \* keyMap)** keyMap should point to a (global) char array of length 67.
This array maps index 0..63 on a character and index \[64\] maps to **I2CKeyPad8x8_NOKEY** (typical 'N') 
and index \[65\] maps **I2CKeyPad8x8_FAIL** (typical 'F'). Index 66 is the null char.
This allows to define a keymap as a null terminated char array, e.g. 

```cpp
char keymap = "1234567890...NF";  //  ... stands for 50+ more chars.

kp8.loadKeyMap(keymap);
```

**WARNING**

If there is no key map loaded the user should **NOT** call **getChar()** or 
**getLastChar()** as these would return meaningless bytes.


Note: a keyMap char array may be longer than 66 characters, but only the first 66 are used.
The length is **NOT** checked upon loading (as it may contain a NULL char).

See also future section below.


### Debouncing threshold

**Experimental**

Since version 0.3.0, the library implements an experimental debounce threshold
which is non-blocking.

If a key bounces, it can trigger multiple interrupts, while the purpose is to
act like only one keypress. The debounce threshold results in a fast return 
of **getKey()** (with **I2C_KEYPAD8x8_THRESHOLD**) if called too fast.

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
these functions will return **I2C_KEYPAD8x8_THRESHOLD** (255).

Feedback welcome!


### Basic working

After the **keypad.begin()** the sketch calls the **keyPad.getKey()** to read values from the keypad. 
- If no key is pressed **I2C_KEYPAD8x8_NOKEY** code (64) is returned.
- If the read value is not valid, e.g. two keys pressed, **I2C_KEYPAD8x8_FAIL** code (65) is returned.
- If a debounce threshold is set, **I2C_KEYPAD8x8_THRESHOLD** (255) might be returned.
See section above.
- Otherwise a number 0..63 is returned.

Note **I2C_KEYPAD8x8_NOKEY**, **I2C_KEYPAD8x8_FAIL** and **I2C_KEYPAD8x8_THRESHOLD**, all are 64 or
beyond, all valid keys are below 64.
This allows easy and fast checking for validity of keys.

Only if a key map is loaded, the user can call **getChar()** and **getLastChar()** to get mapped keys.


## Interrupts

The library enables the PCF8575 to generate interrupts on the PCF8575 when a key is pressed. 
This makes checking the keypad far more efficient as one does not need to poll the device over I2C.
See examples (TODO).


## Smaller keypads

If one wants to connect a smaller keyPad e.g. a 4x4 to the PCF8575, one need to be
sure to have the rows on P00..P07 and the columns on P10..P17 (or P08..P15).

This library does not support the usage of the "not used" pins, when connecting a
smaller keypad than 8x8. 

In issue #7 an idea is proposed to use the https://github.com/RobTillaart/I2CKeyPad
with a PCF8575. It proposes to connect a 4x4 keypad to the P00..P07 pins.
Warning: this idea is not confirmed to work yet, feedback is welcome.


## Future

#### Must

- update documentation
- keep in sync with **I2CKeyPad** as much as possible.

#### Should

- test extensively
  - interrupts
  - key-mapping
  - performance
- improve error handling
  - **I2C_KEYPAD_ERR_MODE**
  - **I2C_KEYPAD_ERR_COMM** (66?) or map to **I2C_KEYPAD_FAIL**?

#### Could

- add examples
  - from https://github.com/RobTillaart/I2CKeyPad?
- KeyMap
  - checking if NULL?  ==>  FAIL, how?
  - checking length of keymap during load.
  - default ASCII map (32..96?)
  - in PROGMEM?

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

