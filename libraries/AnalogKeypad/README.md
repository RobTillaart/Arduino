
[![Arduino CI](https://github.com/RobTillaart/AnalogKeypad/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AnalogKeypad/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AnalogKeypad.svg?maxAge=3600)](https://github.com/RobTillaart/AnalogKeypad/releases)

# AnalogKeypad

Library for (Robotdyn) 4x4 and 4x3 analog keypad

## Description

AnalogKeypad is a simple library to read the keys from a (robotdyn) 4x4 or 4x3 keypad.
No other keypads are tested, but they should work with this library after adjusting
the **MAGIC NUMBERS** in the function **rawRead()**.

## Interface

### Constructor

- **AnalogKeypad(pin)** constructor, pin is typical A0 etc

### polling interface

- **pressed()** returns 0 if no key pressed, otherwise returns key pressed (may fluctuate)
- **read()** read the key pressed returns 0..16

### event interface

- **event()** checks if a change has occurred since last time.
- **key()** returns the key involved with last event

Switch(int e = event()) 
  
| Event | value |
|:----:|:----:|
| PRESSED  | 0x80 |
| RELEASED | 0x40 |
| REPEATED | 0x20 |
| CHANGED  | 0x10 |
| NOKEY    | 0x00 |


## Operation

The simplest usage is to use the **read()** function. 
This will return a 0 (NOKEY) when no key is pressed and
a number 1 to 16 for the keys pressed. Note the return value may
fluctuate randomly when multiple keys are pressed.

The **pressed()** function is a bit more robust.
It returns the key pressed first, so multiple key presses simultaniously 
are less likely to disturbe your program.

See Examples

