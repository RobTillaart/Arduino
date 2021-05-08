
[![Arduino CI](https://github.com/RobTillaart/I2CKeyPad/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/I2CKeyPad/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/I2CKeyPad.svg?maxAge=3600)](https://github.com/RobTillaart/I2CKeyPad/releases)

# I2CKeyPad

Arduino libray for 4x4 KeyPad connected to an I2C PCF8574 

## Description

The I2CKeyPad library implements the reading of a 4x4 keypad by means of a PCF8574.
Smaller keypads, meaning less columns or rows (4x3) can be read with it too.
A 5x3 keypad would require modification

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

**I2CKEYPAD keypad(const uint8_t deviceAddress, TwoWire \*wire = &Wire)**

The constructor sets the device address and optionally 
allows to selects the I2C bus to use.

**keyPad.begin()**

First call that needs to be done is **keyPad.begin()**. 
For the ESP32 **begin(sda, scl)** is provided.
The return value shows if the PCF8574 with the given address is connected properly.

**keyPad.getKey()**

Then the user can use the **keyPad.getKey()** to read values from the keypad.
The read is done in the following way:
First it scans all rows at once by setting all rows to input and all columns to output.
If no row is pressed **I2CKEYPAD_NOKEY** code is returned.

If a row is pressed the row is determined by checking the read value against valid values.
If the read value is not valid a **I2CKEYPAD_FAIL** code is returned. 
(e.g. double key pressed)

Then all columns are scanned at once by setting the columns to input and rows to output.
The column is determined by checking the read value against valid values.
If the read value is not valid a **I2CKEYPAD_FAIL** code is returned.

Given the row and column, a number 0..15 is returned.

**keyPad.getLastKey()**

returns the last valid key pressed 0..15 or **I2C_KEYPAD_NOKEY** = 16.

**keyPad.isPressed()**

returns true if one or more keys of the keyPad is pressed, 
however it is not checked if multiple keys are pressed.

**keyPad.isConnected()**

returns false if the PCF8574 cannot be connected to.


## Interrupts

(Note not tested yet)

Since version 0.2.1 the library should be able to generate interrupts 
on the PCF8574 when a key is pressed. This could make checking the keypad
far more efficient. 


## Char mapping

The code does not map the index on a character or digit as that depends on the application.
It returns 0..15 if one key is pressed, 16 for **I2CKEYPAD_NOKEY** and 17 for **I2CKEYPAD_FAIL**.


## Operation

See examples

