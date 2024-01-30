
[![Arduino CI](https://github.com/RobTillaart/MAX471_RT/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MAX471_RT/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MAX471_RT/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MAX471_RT/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MAX471_RT/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MAX471_RT.svg)](https://github.com/RobTillaart/MAX471_RT/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MAX471_RT/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MAX471_RT.svg?maxAge=3600)](https://github.com/RobTillaart/MAX471_RT/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MAX471.svg)](https://registry.platformio.org/libraries/robtillaart/MAX471)


# MAX471

Arduino library for MAX471 current sensor.


## Description

The MAX471 is an older current sensor which can handle up to 50 Watt, 
with a maximum of 25 Volts or a current of 3 Amperes.
It is officially not supported anymore however there are still many
for sale.
The MAX471 is also in the market as the GY-471.

The MAX472 seems to be compatible with this library but it uses 
has some different wiring. Details see datasheet.

The library is **experimental** and needs testing.

Feedback, issues and improvements are welcome, 
Please open an issue on GitHub.


#### Limits

**Warning** Use a voltage divider if you measure voltages above the
range that is supported by your processor! 
Always include some safety margin (10%) in such voltage divider so
the peak is about 90% of the ADC range.

|  unit     |  limits    |  notes    |
|:---------:|:----------:|:----------|
|  Power    |  50 Watt   |  total
|  Voltage  |  25 Volt   |  at 2 A
|  Current  |  3 Ampere  |  at 16 V


#### Related

- https://wolles-elektronikkiste.de/en/max471-current-sensor (excellent explanation)


## Connection

There are two breakout board variants, a purple board and a red board.
The main difference is that the purple board has a sign pin. 
This pin indicate the direction of the current.

The library has two constructors, one with and one without the signPin parameter.


## Interface

```cpp
#include "MAX471.h"
```

#### Constructor

The MAX471 needs two ADC pins. Current version does not support sharing 
the same pin for both current and voltage. 
An external multiplexer could handle this.

- **MAX471(uint8_t currentPin, uint8_t voltagePin)** red + purple board
- **MAX471(uint8_t currentPin, uint8_t voltagePin, uint8_t signPin)** purple board.


#### Configure

- **void begin(float maxVoltage = 5, uint16_t maxSteps = 1023)**
Sets the parameters voltage and maxSteps of the internal ADC.
Note this allows to update the voltage runtime.
Steps must be larger than zero of course, typical 255 (8 bit), 1023 (10 bit), 
4095 (12 bit).

**begin()** can be called multiple times to adjust e.g. the voltage used.
Think of setting the analog reference (AREF) to 1V1.


#### Read

- **float readCurrent(uint8_t times = 1)** returns Ampere
- **float readCurrentMA(uint8_t times = 1)** wrapper, returns milliAmpere
- **float readVoltage(uint8_t times = 1)** returns Volts
- **float calcPower()** returns Watt, but only after current and voltage 
has been read as it uses the cached values.


## Future

#### Must

- improve documentation
- buy hardware MAX471
- test with hardware

#### Should 

- examples
  - integrate current over time.
  - performance
  - AREF for UNO?

#### Could

- support shutDown pin. LOW/GND = ON, HIGH = OFF. 
  - not on breakout boards.
- investigate AREF 1V1 to improve resolution.
- multiplex the ADC
- external ADC (ADS1115) for higher resolution.

#### Ideas

- add derivative of current + voltage (raising falling indicator)
- percentage interface
- warning limits reached.

#### Won't


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

