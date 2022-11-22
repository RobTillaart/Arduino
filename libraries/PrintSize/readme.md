
[![Arduino CI](https://github.com/RobTillaart/PrintSize/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PrintSize/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PrintSize/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PrintSize/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PrintSize/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PrintSize/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PrintSize.svg?maxAge=3600)](https://github.com/RobTillaart/PrintSize/releases)


# PrintSize

Arduino library to determine the length of print statements.


## Description

PrintSize is a minimal library to determine the length of a variable when printed.
This includes printing of floats, integers in decimal or hex notation.

Works for **print()**, **println()** and if supported **printf()** e.g. ESP32.

Finally since **0.2.0** it has a total counter to add up the characters "printed" since
the last **reset()** call. (see example)

This library is related to
- https://github.com/RobTillaart/PrintCharArray (captures data in a buffer)
- https://github.com/RobTillaart/PrintSize. (captures data in a String)


## Operational

Example shows the right alignment of 10 random numbers.

Example shows (elementary) line fitting.


## Applications

Can be used to calculate the needed space.
- to properly do a right alignment e.g. for numbers or variable text.
- do left alignment and overwrite previous output with just enough spaces.
- centring of numbers.
- see if output will fit into a line / display.
- see if a string fits in EEPROM or any other storage medium.
- see if a string fits in a communication buffer.


## Future

- add examples
- add a function to handle **tab** char correctly e.g. 
  could add more than one char. Interferes with the **write(str, length)**.
  - setTabSize(2,4,6, 8...);
  - getTabSize();
  - uint8_t \_tabSize = 4;
- 

