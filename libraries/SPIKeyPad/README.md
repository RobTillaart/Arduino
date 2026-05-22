
[![Arduino CI](https://github.com/RobTillaart/SPIKeyPad/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/SPIKeyPad/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/SPIKeyPad/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/SPIKeyPad/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/SPIKeyPad/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/SPIKeyPad.svg)](https://github.com/RobTillaart/SPIKeyPad/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/SPIKeyPad/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/SPIKeyPad.svg?maxAge=3600)](https://github.com/RobTillaart/SPIKeyPad/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/SPIKeyPad.svg)](https://registry.platformio.org/libraries/robtillaart/SPIKeyPad)


# SPIKeyPad

Arduino library for 4x4 (or smaller) keypad connected to an SPI MCP23S08.


## Description

**Experimental**

The SPIKeyPad library implements the reading of a 4x4 keypad by means of a MCP23S08.
Smaller keypads, meaning less columns or rows (4x3) can be read with this library too.
The library allows a 5x3, 6x2 or 8x1 or smaller keypad to be connected too.

The library is based upon the I2CKeypad library which uses a PCF8574 to read the 
device. The interface is kept as equal as possible to minimize the effort when  switching between different libraries.

The idea behind this library is to read 4 pins at once for rows and 4 pins at once
for the columns. In both cases only zero (NoKey) or one bit should be set. 

The MCP23S08 has two address pins, so one could create 4 unique keypads on the SPI
bus with the same CS (chip select) pin.

Not all functionality has been tested on all different boards, so if problems 
occur open an issue (or PR) on GitHub.

Feedback as always is welcome.


### Related

Relates strongly to https://github.com/RobTillaart/I2CKeyPad. which is an 4x4 version using **PCF8574**.

- https://github.com/RobTillaart/MCP23S08 - device used
- https://github.com/RobTillaart/AnalogKeypad - uses resistor ladder
- https://github.com/RobTillaart/I2CKeyPad - PCF8574 based keyPad
- https://github.com/RobTillaart/I2CKeyPad8x8 - PCF8575 based keyPad
- https://github.com/RobTillaart/SPIKeyPad - this library
- https://github.com/WK-Software56/AdvKeyPad (derived work with keyboard alike interface)
- https://www.gammon.com.au/forum/?id=14175


## Connection

The MCP23S08 is connected between the processor and the (default) 4x4 keypad.
See the conceptual schema below.
It might take some experimenting to get the pins connected correctly.

```
          MCU              MCP23S08              KEYPAD
        +--------+        +---------+          +---------+
        |        |        |       0 |<-------->| ROW     |
        |     IN |<------>|       1 |<-------->| ROW     |
        |    OUT |------->|       2 |<-------->| ROW     |
        |    CLK |------->|       3 |<-------->| ROW     |
        |        |        |         |          |         |
        |        |        |       4 |<-------->| COL     |
        |        |        |       5 |<-------->| COL     |
        |        |        |       6 |<-------->| COL     |
        |        |        |       7 |<-------->| COL     |
        +--------+        +---------+          +---------+
```


## Performance

Indicative performance measurements UNO R3, IDE 1.8.19,
measured with - I2CKeyPad_demo03.ino

|  SPI (MHz)  |  no key pressed |  key pressed  |
|:-----------:|:---------------:|:-------------:|
|    1 MHz    |    100 us       |    180 us     |
|    2 MHz    |     76 us       |    136 us     |
|    4 MHz    |     64 us       |    112 us     |
|    8 MHz    |     60 us       |    100 us     |
|   SW SPI    |    908 us       |   1808 us     |

Note: SW SPI could be optimized for AVR by using low level IO,
however it can still do ~500 reads per second.
 

## Interface

```cpp
#include "SPIKeyPad.h"
```

### Constructor

The MCP23S08 has two **address** pins, so one could create 4 unique keypads on the SPI
bus with the same CS (chip select) pin.
This address needs to be set in the constructor, or defalt address 0x00 is used.

- **SPIKeyPad(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock, uint8_t address = 0x00)** Software SPI constructor.
- **SPIKeyPad(int select, \__SPI_CLASS\__\* spi)** Hardware SPI constructor
- **SPIKeyPad(int select, int address = 0x00,\__SPI_CLASS\__\* spi = &SPI)** Hardware SPI constructor
- **bool begin()** initializes the internal parameters. If hardware SPI is used,
one need to call SPI.begin (or equivalent) before this function.
- **uint8_t getAddress()** returns the set device address (from constructor).


### getKey

- **uint8_t getKey()** Returns default 0..15 for regular keys,
Returns **SPI_KEYPAD_NOKEY** (16) if no key is pressed and **SPI_KEYPAD_FAIL**
(17) in case of an error, e.g. multiple keys pressed.
If a debounce delay is set, it might return **SPI_KEYPAD_THRESHOLD** if called too fast.
- **uint8_t getLastKey()** Returns the last **valid** key pressed 0..15,
or **SPI_KEYPAD_NOKEY** (16) which is also the initial value.
- **bool isPressed()** Returns true if one or more keys of the keyPad are pressed,
however there is no check if multiple keys are pressed.


|  getKey()  |  HEX code    |  Meaning               |  Notes  |
|:----------:|:------------:|:-----------------------|:--------|
|  0..15     |  0x00..0x0F  |  valid key pressed     |
|  16        |  0x10        |  SPI_KEYPAD_NOKEY      |
|  17        |  0x11        |  SPI_KEYPAD_FAIL       |  multi key or communication error.
|  255       |  0xFF        |  SPI_KEYPAD_THRESHOLD  |


### Mode functions

- **void setKeyPadMode(uint8_t mode = SPI_KEYPAD_4x4)** sets the mode, default 4x4.
This mode can also be used for 4x3 or 4x2 or 3x3 etc.
Invalid values for mode are mapped to 4x4.
- **uint8_t getKeyPadMode()** returns the current mode.

**Supported modi**

There are 4 modi supported, and every mode will also support smaller keypads.
E.g. a 4x3 keypad can be read in mode 4x4 or in mode 5x3.

|  modi  |  value  |  definition      |  notes    |
|:------:|:-------:|:-----------------|:----------|
|  4x4   |    44   |  SPI_KEYPAD_4x4  |  default, also for 4x3 4x2 4x1 3x3 3x2 3x1 etc.
|  5x3   |    53   |  SPI_KEYPAD_5x3  |  also for 5x2 or 5x1 etc.
|  6x2   |    62   |  SPI_KEYPAD_6x2  |  also for 6x1.
|  8x1   |    81   |  SPI_KEYPAD_8x1  |  not real matrix, connect pins to switch to GND.


### KeyMap functions

Note: **loadKeyMap()** must be called before **getChar()** and **getLastChar()**!

- **char getChar()** returns the char corresponding to mapped key pressed.
It returns **SPI_KEYPAD_THRESHOLD** if called too fast.
Returns zero if no keyMap is loaded.
- **char getLastChar()** returns the last char pressed.
This function is not affected by the debounce threshold.
Returns zero if no keyMap is loaded.
- **bool loadKeyMap(char \* keyMap)** keyMap should point to a (global) char array of length 19.
This array maps index 0..15 on a char and index \[16\] maps to **SPI_KEYPAD_NOKEY** (typical 'N')
and index \[17\] maps **SPI_KEYPAD_FAIL** (typical 'F'). index 18 is the null char.

**WARNING**

If there is no key map loaded the user should **NOT** call **getChar()** or
**getLastChar()** as these would return 0.


```cpp
char normal_keymap[19]  = "123A456B789C*0#DNF";   // typical normal key map (phone layout)
char repeat_keymap[19]  = "1234123412341234NF";   // effectively 4 identical columns
char partial_keymap[19] = "1234            NF";   // top row
char diag_keymap[19]    = "1    2    3    4NF";   // diagonal keys only
```

In the examples above a 'space' key might be just meant to ignore.
However functional there is no limit how one wants to use the key mapping.
It is even possible to change the mapping runtime after each key press.

Note: a keyMap char array may be longer than 18 characters, 
but only the first 18 are used.
The length is **NOT** checked upon loading.

Note: The 5x3, 6x2 and the 8x1 modi also use a key map of length 18.


### Debouncing threshold

**Experimental**

The library implements an experimental debounce threshold
which is non-blocking.

If a key bounces, it can trigger multiple interrupts, while the purpose is to
act like only one key press. The debounce threshold results in a fast return
of **getKey()** (with **SPI_KEYPAD_THRESHOLD**) if called too fast.

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
these functions will return **SPI_KEYPAD_THRESHOLD** (255).

Feedback welcome!


### SPI

- **void setSPIspeed(uint32_t speed)** set hardware speed (8Mb default).
- **uint32_t getSPIspeed()** returns set speed.
- **bool usesHWSPI()** returns true = hardware SPI, false = software SPI.


### Basic working

After the **keypad.begin()** the sketch calls the **keyPad.getKey()** to read values from the keypad.
- If no key is pressed **SPI_KEYPAD_NOKEY** code (16) is returned.
- If the read value is not valid, e.g. two keys pressed, **SPI_KEYPAD_FAIL** code (17) is returned.
- If a debounce threshold is set, **SPI_KEYPAD_THRESHOLD** might be returned.
See section above.
- Otherwise a number 0..15 is returned.

Note NOKEY and FAIL both have bit 4 set, all valid keys don't.
This allows fast checking for valid keys by masking.

```
if ((key & 0xF0) == 0x00)  //  handle invalid
```

Only if a key map is loaded, the user can call **getChar()** and **getLastChar()** to get mapped keys.


## Interrupts

(not tested yet)

The library enables the MCP23S08 to generate interrupts on the MCP23S08 when a key is pressed.
This makes checking the keypad far more efficient as one does not need to poll the device over SPI.
See examples.


## Future

#### Must

- update documentation
- keep in sync with I2CKeypad / I2CKeypad8x8
- support interrupt example

#### Should

- test more


#### Could

- improve **SPIkeypad_readKeyUntil.ino** => no blocking readUntil(...) function.


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

