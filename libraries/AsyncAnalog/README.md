
[![Arduino CI](https://github.com/RobTillaart/AsyncAnalog/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AsyncAnalog/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AsyncAnalog/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AsyncAnalog/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AsyncAnalog/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AsyncAnalog.svg)](https://github.com/RobTillaart/AsyncAnalog/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AsyncAnalog/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AsyncAnalog.svg?maxAge=3600)](https://github.com/RobTillaart/AsyncAnalog/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AsyncAnalog.svg)](https://registry.platformio.org/libraries/robtillaart/AsyncAnalog)


# AsyncAnalog

Arduino Library for async reading of an analogue pin. **\[AVR ONLY\]**.


## Description

AsyncAnalog is a library to read the analogue port of an **AVR** in an asynchronous way.
This means that the user must explicitly **start()** the ADC, check if it is **ready()**
and read its **value()**.

By using this class, the user prevents the (~112 uSec) blocking of the 
**analogRead()** call, and gives the user the ability to do some processing.

The library works only for AVR boards now, other platforms might be supported in the future.
(PR's are welcome).

**WARNING**
As the UNO has only one ADC that is multiplexed, one can only read one analog pin
in async way simultaneously. Still it offers to about 100 micros to do something!

**Use with care**


#### Related

- https://github.com/RobTillaart/AnalogPin


## Interface

```cpp
#include "AsynAnalog,h"
```

- **AsyncAnalog(uint8_t pin)** constructor, defines the analogue pin to use.
- **void start()** triggers a new ADC measurement.
- **bool ready()** Checks if the measurement is completed. 
If so the value is calculated and cached for **value()**.
As long as ready() is not called the old value will not change!
- **uint16_t value()** returns the value of the ADC from cache.
So it will return the same value even if the internal ADC is used to sample
another analog port.


## Operation

The example **asyncAnalogTest2.ino** shows a loop of 1000 analogReads and prints 
over Serial at 115200 baud. 


## Future

#### Must

- improve documentation.

#### Should

- create examples
  - real world examples preferred.
  - multi ADC, e.g. A0..A4


#### Could

- investigate the performance gain.
  - asyncAnalogTest2.ino is not a good test.
- investigate other platforms
- fall back to normal analogRead for non AVR platforms ?
  - start would be analogRead() and it would immediately be ready and the value is cached.
  - better have specific code per platform.

#### Wont

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

