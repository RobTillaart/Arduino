
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

**Experimental**

The MAX471 is an older current sensor which can handle up to 50 Watt, 
with a maximum of 25 Volts or a current of 3 Amperes.
It is officially not supported any more however there are still many
for sale.
The MAX471 is also in the market as the GY-471.

The MAX472 seems to be compatible with this library but it uses 
has some different wiring. Details see datasheet.

The library needs more testing.

Feedback, issues and improvements are welcome, 
Please open an issue on GitHub.


### Limits

**Warning** Use a voltage divider if you measure voltages above the
range that is supported by your processor! 
Always include a safety margin (>= 10%) in such voltage divider so
the peak is about 90% of the ADC range.

|  unit     |  limits    |  notes    |
|:---------:|:----------:|:----------|
|  Power    |  50 Watt   |  total
|  Voltage  |  25 Volt   |  at 2 A
|  Current  |  3 Ampere  |  at 16 V


### Related

- https://wolles-elektronikkiste.de/en/max471-current-sensor (excellent explanation)
- https://github.com/RobTillaart/ACS712
- https://github.com/RobTillaart/INA226


## Connection

There are at least two breakout board variants, I have seen a purple board and a red board.
The main difference is that the purple board has a sign pin. 
This pin indicate the direction of the current.

The library has two constructors, one with and one without the signPin parameter.


## Interface

```cpp
#include "MAX471.h"
```

### Constructor

The MAX471 needs two ADC pins. Current version of the library does not support 
sharing the same pin for both current and voltage. 
An external multiplexer could handle this.

- **MAX471(uint8_t currentPin, uint8_t voltagePin)** red + purple board
- **MAX471(uint8_t currentPin, uint8_t voltagePin, uint8_t signPin)** purple board.

MAX472 is just a wrapper for now

- **MAX472(uint8_t currentPin, uint8_t voltagePin)** red + purple board
- **MAX472(uint8_t currentPin, uint8_t voltagePin, uint8_t signPin)** purple board.


### Configure

- **void begin(float maxVoltage = 5.0, uint16_t maxSteps = 1023)**
Sets the parameters voltage and maxSteps of the internal ADC.
Note this allows to update the voltage runtime.
Steps must be larger than zero of course, typical 255 (8 bit), 1023 (10 bit), 
4095 (12 bit).

**begin()** can be called multiple times to adjust e.g. the voltage used.
Think of setting the analog reference (AREF) to 1V1.


### Read

Multiple reads averages over time, this stabilizes the measurements 
and might result a slightly higher resolution. Typical values are 2..16.
Drawback of multiple reads is that you do not get a "single point in time" measurement. 
So be aware if you want to measure fast changing currents.
Another drawback of multiple reads is it will block your code longer.

- **float readCurrent(uint8_t times = 1)** returns Ampere
- **float readCurrentMilliAmpere(uint8_t times = 1)** returns milliAmpere
- **float readVoltage(uint8_t times = 1)** returns Volts
- **float readVoltageMilliVolts(uint8_t times = 1)** returns milliVolts.

Read cached values

- **float getLastCurrent()** returns the last read current in Ampere
- **float getLastVoltage()** returns the last read voltage in Volts.


### Power

Not a feature of the MAX471 directly, however if both current and voltage are
measured, one can calculate the power = current x voltage easily.
If voltage is stable in your project it might be sufficient to only update 
the current measurement to calculate the power.

- **float calcPower()** returns power in Watt.
- **float calcPowerMilliWatt()** returns power in milliWatt.

### Experimental

By setting a fixed voltage one does not need to call **readVoltage()**.
Use getLastVoltage() to read back the value set..

- **void setFixedVoltage(float volts)** sets the internal voltage variable.



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

