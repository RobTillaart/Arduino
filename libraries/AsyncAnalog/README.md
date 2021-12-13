
[![Arduino CI](https://github.com/RobTillaart/AsyncAnalog/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AsyncAnalog/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AsyncAnalog/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AsyncAnalog/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AsyncAnalog/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AsyncAnalog/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AsyncAnalog.svg?maxAge=3600)](https://github.com/RobTillaart/AsyncAnalog/releases)


# AsyncAnalog

Arduino Library for async reading of an analogue pin. **\[AVR ONLY\]**.


## Description

AsyncAnalog is a library to read the analogue port of an AVR in an asynchronous way.
This means that the user must explicitly **start** the ADC, check if it is **ready**
and read out its **value**.

By using this class, the user prevents the (~112 uSec) blocking of the 
**analogRead()** call, and gives the user the ability to do some processing.

The library works only for AVR boards now, other platforms might be supported in the future.

As the UNO has only one ADC that is multiplexed, one can only read one analogue pin
in async way simultaneously.

**Use with care**


## Interface 

- **AsyncAnalog(uint8_t pin)** constructor, defines the analogue pin to use.
- **void start()** triggers a new ADC reading.
- **bool ready()** returns true if sample is complete.
- **int value()** returns the value.


## Operation

The example **asyncAnalogTest2.ino** shows a loop of 1000 analogReads and prints 
over Serial at 115200 baud. 


## Future

- improve documentation.
- investigate the performance gain.
  - asyncAnalogTest2.ino is no good test.
- create examples
  - real world examples preferred.
- investigate other platforms
- fall back to normal analogRead for non AVR platforms ?
- 

