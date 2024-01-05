
[![Arduino CI](https://github.com/RobTillaart/MAX31850/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MAX31850/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MAX31850/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MAX31850/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MAX31850/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MAX31850.svg)](https://github.com/RobTillaart/MAX31850/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MAX31850/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MAX31850.svg?maxAge=3600)](https://github.com/RobTillaart/MAX31850/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MAX31850.svg)](https://registry.platformio.org/libraries/robtillaart/MAX31850)


# MAX31850

Arduino library for the MAX31850 / MAX31851 thermocouple sensor.


## Description

**WARNING EXPERIMENTAL** needs more testing (no hardware yet).
(feedback welcome)

his MAX31850 library is not a full featured library for the MAX31850 family.

The MAX31850/1 is a Cold-Junction Compensated, 1-Wire Thermocouple-to-Digital Converter.

The MAX31850/1 supports K-, J-, N-, T-, S-, R-, and E-type thermocouples. (to be tested).

The library supports both the MAX31850 and MAX31851 but is limited to one sensor per pin.
The only feature the class supports is the asynchronous reading of the temperature.

This allowed the class to be both minimal in size and non-blocking.
In fact the class has no support for a synchronous read in one call.
This choice will teach people how to work in a non-blocking way from the start.

Finally this library will probably make it easier to use a MAX31850 with processing
boards or IC's with small memory footprint.

The MAX31851 is (for now) functional identical to MAX31850.


#### Related

- https://github.com/RobTillaart/MAX6675
- https://github.com/RobTillaart/MAX31850
- https://github.com/RobTillaart/MAX31855_RT


## Hardware connection

```
//  PROCESSOR        MAX31850       THERMOCOUPLE
//              +---------------+
//   GND   1    | o           o |   T+
//   DATA  2    | o             |
//   VCC   3    | o           o |   T-
//              |               |
//              |     oooo      |
//              +---------------+
//               4 address pins.
```

This library supports only one MAX31850 per Arduino/ MCU IO pin.


#### Pull up resistor

Connect a pull-up resistor 4.7 KOhm between DATA (pin 3) and VCC (pin 2).
When the wires are longer this resistor needs to be smaller.

An **indicative** table for pull up resistors, (E12 series), to get started.

Note: thicker wires require smaller resistors (typically 1 step in E12 series)

|  Length         |  5.0 Volt  |  3.3 Volt  |
|----------------:|-----------:|-----------:|
|  10cm (4")      |    10K0    |     6K8    |
|  20cm (8")      |     8K2    |     4K7    |
|  50cm (20")     |     4K7    |     3K3    |
|  100cm (3'4")   |     3K3    |     2K2    |
|  200cm (6'8")   |     2K2    |     1K0    |
|  500cm (16'8")  |     1K0    |     \*     |
|  longer         |     \*     |     \*     |

\* = no info, smaller


## Interface

```cpp
#include "MAX31850.h"
```


#### Constructor

- **explicit MAX31850(OneWire \* oneWire)** constructor.
- **bool begin(uint8_t retries = 3)** initialize the library.
Returns true if addresses are found.
Nr of retries can be adjusted if needed, default 3.
- **bool getAddress(uint8_t \* buffer)** get the address if found.


#### Read the sensor

- **void requestTemperatures(void)** Asynchronous request to start conversion.
- **bool isConversionComplete(void)** CHeck if requested conversion is done.
- **float read(void)** read the data from the sensor.
Returns the temperature of the thermoCouple as this is most often needed.
- **float getTempTC(void)** returns temperature of the ThermoCouple from cache.
One must call **read()** again to get new measurements.
- **float getTempInternal(void)** returns internal temperature from cache.
One must call **read()** again to get new measurements.


#### Other

- **uint8_t getAddressPins()** binary form of the 4 address bits. 0x00..0x0F.
- **uint8_t getErrorCode()** get the internal error code. See below.
- **bool setTypeTC(char typeTC)** typeTC is one char from E J K N R S T
- **uint8_t getTypeTC()** returns the current TC type.


## Types of thermocouples

The MAX31850 comes in MAX31850E.. MAX31850T types reflecting the version of TC to use.


|  Sensor type  |  SC in µV/°C  |  Temp Range in °C  |  Material                   |  notes      |
|:-------------:|:--------------|:-------------------|:----------------------------|:------------|
|     E_TC      |     76.373    |   -270 to +1000    |  Constantan Chromel         |
|     J_TC      |     57.953    |   -210 to +1200    |  Constantan Iron            |
|     K_TC      |     41.276    |   -270 to +1372    |  Alumel Chromel             |  most used  |
|     N_TC      |     36.256    |   -270 to +1300    |  Nisil Nicrosil             |
|     R_TC      |     10.506    |    -50 to +1768    |  Platinum Platinum/Rhodium  |
|     S_TC      |      9.587    |    +50 to +1768    |  Platinum Platinum/Rhodium  |
|     T_TC      |     52.18     |   -270 to +400     |  Constantan Copper          |

(MAX31851 idem)


## Error codes

|  name                     |  value  |
|:--------------------------|:-------:|
|  MAX31850_OK              |    0    |
|  MAX31850_ERR_SHORT_OPEN  |    1    |
|  MAX31850_ERR_SHORT_GND   |    2    |
|  MAX31850_ERR_SHORT_VDD   |    4    |


## Future

#### Must

- improve documentation
- get hardware to test (sponsors welcome)
- test on different platforms


#### Should

- investigate different thermocouples
- test with different platforms
- has the MAX31851 special features to implement?


#### could

- extend error handling
- expand to multi sensor per pin.
  - first get one sensor working
- investigate range checking on type TC
  - need setType() and more.
  - need lower upper range = int16_t will do.
- add CRC check
  - + error code


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


