
[![Arduino CI](https://github.com/RobTillaart/I2CKeyPad/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/I2CKeyPad/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/I2CKeyPad/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/I2CKeyPad/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/I2CKeyPad/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/I2CKeyPad/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/I2CKeyPad.svg?maxAge=3600)](https://github.com/RobTillaart/I2CKeyPad/releases)


# I2CKeyPad

Arduino library for 4x4 KeyPad connected to an I2C PCF8574.


## Description

The I2CKeyPad library implements the reading of a 4x4 keypad by means of a PCF8574.
Smaller keypads, meaning less columns or rows (4x3) can be read with it too.
A 5x3 keypad would require modification (issue pending to support this).


## Connection

The PCF8574 is connected between the processor and the 4x4 keypad, see the conceptual
below. It might take some trying to get the correct pins connected.

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

- **I2CKEYPAD keypad(const uint8_t deviceAddress, TwoWire \*wire = &Wire)** 
The constructor sets the device address and optionally 
allows to selects the I2C bus to use.
- **bool keyPad.begin()** The return value shows if the PCF8574 with the given address is connected properly.
- **bool begin(uint8_t sda, uint8_t scl)** for ESP32.
The return value shows if the PCF8574 with the given address is connected properly.
- **keyPad.isConnected()** returns false if the PCF8574 cannot be connected to.
- **uint8_t keyPad.getKey()** Returns 0..15 for regular keys, 16 if no key is pressed 
and 17 in case of an error.
- **keyPad.getLastKey()** Returns the last **valid** key pressed 0..15. Initially it will return 16 (noKey).
- **keyPad.isPressed()** Returns true if one or more keys of the keyPad is pressed, 
however it is not checked if multiple keys are pressed.


#### KeyMap functions

**loadKeyMap()** must be called first!

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
It is even possible to change the mapping runtime.

Note: a keyMap char array may be longer than 18 characters, but only the first 18 are used.
The length is **NOT** checked upon loading.


#### Basic working

After the **keypad.begin()** the sketch calls the **keyPad.getKey()** to read values from the keypad. 
- If no key is pressed **I2CKEYPAD_NOKEY** code (16) is returned.
- If the read value is not valid, e.g. two keys pressed, **I2CKEYPAD_FAIL** code (17) is returned.
- Otherwise a number 0..15 is returned.

Only if a key map is loaded, the user can call **getChar()** and **getLastChar()** to get mapped keys.


## Interrupts

Since version 0.2.1 the library enables the PCF8574 to generate interrupts 
on the PCF8574 when a key is pressed. 
This makes checking the keypad far more efficient as one does not need to poll over I2C.
See examples.


## Operation

See examples


## Future

- update documentation
- investigate 5x3 keypad and other 'formats'
- test key mapping functions.
