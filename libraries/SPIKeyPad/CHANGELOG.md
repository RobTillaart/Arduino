# Change Log SPIKeyPad

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).

## [0.1.2] - 2026-05-17
- improved Doxygen documentation
- improved const correctness for getters and parameters
- replaced NULL with nullptr
- replaced if/else chains with switch statements
- added explicit SPI_KEYPAD_INVALID enum value
- improved constructor initialization using initializer lists
- improved const correctness for getters and parameters
- verified compatibility with C++11
- fix select and address parameter to uint8_t
- add setSPIspeed implementation
- fix examples to compile without warning
- minor edits


## [0.1.1] - 2026-05-16
- Merge PR #2, Kudos to Chris0xdeadbeef
- start doxygen documentation
- Add SPIKeyPad_4x4 example
- minor edits

## [0.1.0] - 2026-04-09
- initial version based upon I2CKeyPad and MCP23S08 library

