
[![Arduino CI](https://github.com/RobTillaart/LTC2991/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/LTC2991/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/LTC2991/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/LTC2991/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/LTC2991/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/LTC2991.svg)](https://github.com/RobTillaart/LTC2991/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/LTC2991/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/LTC2991.svg?maxAge=3600)](https://github.com/RobTillaart/LTC2991/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/LTC2991.svg)](https://registry.platformio.org/libraries/robtillaart/LTC2991)


# LTC2991

Arduino library for an LTC2991 temperature and voltage control IC.


## Description

Experimental - not tested myself, (no hardware)

LTC2991 is an experimental library for the LTC2991 IC which is typically used
to monitor temperature and voltage. It also has a PWM out to control e.g. a fan.

The IC supports normal voltage measurement (8 lines), differential voltage
measurements (4 pairs) and temperature measurements (4 pairs).
These can be combined in a mix.
As the IC has only 8 inputs available one has to choose what.

Read the datasheet for the details.


#### Address

From datasheet - table 1

The address template is   0  1  0  0  - 1 A2 A1 A0  ==>  0x48 if all address pins are grounded,

|  ADR0  |  ADR1  |  ADR2  |  address  |
|:------:|:------:|:------:|:---------:|
|   0    |    0   |    0   |    0x48   |
|   1    |    0   |    0   |    0x49   |
|   0    |    1   |    0   |    0x4A   |
|   1    |    1   |    0   |    0x4B   |
|   0    |    0   |    1   |    0x4C   |
|   1    |    0   |    1   |    0x4D   |
|   0    |    1   |    1   |    0x4E   |
|   1    |    1   |    1   |    0x4F   |


#### Related

- https://github.com/RobTillaart/LTC2991
- https://github.com/RobTillaart/temperature converters


## Interface

```cpp
#include "LTC2991.h"
```

#### Constructor and setup

- **LTC2991(const uint8_t address, TwoWire \*wire = Wire)**
The address is 0x48..0x4F depending on the address pins.
The library does not check the range.
- **bool begin()** UNO ea. initializes the class.
Returns true if the LTC2991 address is on the I2C bus.  
Note: do call **Wire.begin()** before **begin()**
- **bool isConnected()** Returns true if the LTC2991 address is on the I2C bus.
- **uint8_t getAddress()** Returns the address set in the constructor.


#### Status functions

- **bool new_data(uint8_t channel)** true if there is a new **external** measurement available.
This can be a voltage or a temperature measurement.
- **bool new_temperature()** true if there is a new **internal** temperature measurement available.
- **bool new_voltage()** true, if there is a new **internal** voltage measurement available.
- **bool is_busy()** true if the sensor is converting...


#### External measurements

The following functions work on pairs:

|  n  |   selected   |
|:---:|:------------:|
|  1  |  V1  V2  T1  |
|  2  |  V3  V4  T2  |
|  3  |  V5  V6  T3  |
|  4  |  V7  V8  T4  |


- **void trigger_conversion(uint8_t n)** wrapper around enable(n, true), better naming.
- **void trigger_conversion_all()** triggers conversions for all 4 channels/pairs.
- **void enable(uint8_t n, bool enable)** enable or disable an external line.
disable can be used to stop the repeat mode.
- **bool is_enabled(uint8_t n)** idem
- **void enable_filter(uint8_t n, bool enable)** enable filter - not investigated.
- **bool is_enabled_filter(uint8_t n)** idem.
- **void set_Kelvin(uint8_t n)** sets temperature mode to Kelvin,
implicit set_mode_temperature().
- **void set_Celsius(uint8_t n)** sets temperature mode to Celsius,
implicit set_mode_temperature.
- **void set_temp_scale(uint8_t n, bool Kelvin = true)** used to switch between Kelvin and Celsius.
- **char get_temp_scale(uint8_t n)** returns 'K' or 'C'.
- **void set_mode_temperature(uint8_t n)** sets operational mode.
- **void set_mode_voltage_differential(uint8_t n)** sets operational mode.
- **void set_mode_voltage_normal(uint8_t n)** sets operational mode.
- **uint8_t get_operational_mode(uint8_t n)** returns operational mode.
- **uint8_t get_differential_mode(uint8_t n)** returns differential flag.
- **float get_value(uint8_t channel)** channel = 1..8;
depending on the operational mode it returns the temperature or the
(differential) voltage.


#### Internal measurements

- **void enable_Tintern_Vcc(bool enable)** enable internal temperature measurements.
- **bool is_enabled_Tintern_Vcc()** idem.
- **void enable_filter_Tintern(bool enable)** enable filter - not investigated
- **bool is_enabled_filter_Tintern()**
- **void set_Kelvin_Tintern()** use Kelvin.
- **void set_Celsius_Tintern()** use Celsius.
- **void set_temp_scale_Tintern(bool Kelvin = true)** Obsolete?.
- **char get_temp_scale_Tintern()** returns 'K' or 'C'.
- **float get_Tintern()** returns the internal temperature.
- **float get_VCC()** returns the internal voltage.


#### Configuration

- **void set_acquisition_repeat()** set continuous measurement mode.
- **void set_acquisition_single()** set single shot mode.
Note that before a measurement is made one needs to call **trigger_conversion(n)**
or **trigger_conversion_all()**.
- **uint8_t get_acquisition_mode()** return mode set (0,1).
  - 1 = repeat
  - 0 = single


#### PWM functions

- **void set_PWM(uint16_t value = 0)** value is 0..511.
- **void set_PWM_fast(uint16_t value = 0)** value is 0..511, less resolution (256 steps).
- **uint16_t get_PWM()** returns the value from the PWM register, when using PWM_fast this can differ 1.
- **void invert_PWM(bool invert)** idem.
- **bool is_inverted_PWM()** idem.
- **void enable_PWM(bool enable)** idem.
- **bool is_enabled_PWM()** idem.


#### Performance

No data available yet.
To be measured when hardware is available...
if you happen to have performance figures, please share them in an issue.


## Future

#### Must

- get hardware to test
- improve documentation (a lot)


#### Should

- error handling
- unit tests if possible?
- remove magic numbers / masks from code
  - some defines prepared in CPP file => to .h


#### Could

- cache registers (which) or ?
- cache a number of flags to speed up retrieving data
- optimizations
  - code / math
  - optimize multi-byte read / write
- **void disable_PWM()** convenience, 
- **enable_PWM(bool)** default true flag
- **void LTC2991::enable(uint8_t mask)** faster to set multiple.


#### Wont

- redo naming of some functions?
  - first get hands on experience.
- add Fahrenheit
  - do low level in Kelvin and convert to KFC as needed.
  - would simplify get_value
  - need an enum
  - would interface # functions increase too much?
  - == > Users can do this conversion.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

