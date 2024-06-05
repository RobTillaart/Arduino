# Change Log MCP_POT

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.2.2] - 2024-06-05
- add support for ARDUINO_ARCH_MBED

## [0.2.1] - 2024-04-25
- add examples
  - **MCP_POT_performance.ino** measure setValue() at various SPI speeds
  - **MCP_POT_serial.ino** control device ove Serial
  - **MCP_POT_triangle.ino** test sketch
- add **setSWSPIdelay()** to reduce SW SPI maximum speed.
- reduced default HW SPI speed to 1 MHz.
- add experimental Ohm wrappers (need testing)
- update readme.md
- update keywords.txt


## [0.2.0] - 2024-01-19
- Fix #2, improve SPI dependency.

----

## [0.1.0] - 2023-12-21
- initial version.

