
[![Arduino CI](https://github.com/RobTillaart/LTC2991/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/LTC2991/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/LTC2991.svg?maxAge=3600)](https://github.com/RobTillaart/LTC2991/releases)


# LTC2991

Arduino library for an LTC2991 temperature and voltage control IC


## Description

Experimental - not tested yet

LTC2991 is an experimental library for the LTC2991 IC which is typically used to control temperature and voltage lines.

The IC supports normal voltage measurement (8 lines), differential voltage measurements (4 pairs) and temperature measurements (4 pairs). These can be combined in a mix. As the IC has only 8 inputs available one has to choose what. 

Read the datasheet for the details.


## Interface


### Constructor and setup

- **LTC2991(const int8_t address, TwoWire \*wire = Wire);**
- **bool begin(uint8_t sda, uint8_t scl)** ESP32 ea initializes the class.
sets I2C pins.
returns true if the LTC2991 is on the I2C bus.
- **bool begin()** UNO ea. initializes the class. 
returns true if the LTC2991 is on the I2C bus.
- **bool isConnected()** returns true if the LTC2991 is on the I2C bus.


### Status functions

- **bool new_data(uint8_t channel)** true if there is a new **external** measurement (temperature or voltage) available.
- **new_temperature()** true if there is a new **internal** temperature measurement available.
- **new_voltage()** true, if ther is a new **internal** voltage measurement available.
- **is_busy()** true if converting...


### External measurements

The following functions work on pairs

|   n  | selected  |
|:----:|:---------:|
|   1  | V1 V2  T1 |
|   2  | V3 V4  T2 |
|   3  | V5 V6  T3 |
|   4  | V7 V8  T4 |

- **void enable(uint8_t n, bool enable)** enable or disable an external line. 
- **bool is_enabled(uint8_t n)** idem
- **void enable_filter(uint8_t n, bool enable)** not investigated 
- **bool is_enabled_filter(uint8_t n)** idem
- **void set_Kelvin(uint8_t n)** sets temperature mode to Kelvin, 
implicit set_mode_temperature(), 
- **void set_Celsius(uint8_t n)** sets temperature mode to Celsius,
implicit set_mode_temperature
- **void set_temp_scale(uint8_t n, bool Kelvin = true)** obsolete?
- **char get_temp_scale(uint8_t n)** returns 'K' or 'C'
- **void set_mode_temperature(uint8_t n)** sets operational mode
- **void set_mode_voltage_differential(uint8_t n)** sets operational mode
- **void set_mode_voltage_normal(uint8_t n)** sets operational mode
- **uint8_t get_operational_mode(uint8_t n)** returns operational mode
- **uint8_t get_differential_mode(uint8_t n)** returns differential flag
- **float get_value(uint8_t channel)** channel = 1..8;
depending on the operational mode it returns the temperature or the
(differential) voltage.


### Internal measurements

- **void enable_Tintern_Vcc(bool enable)** enable internal temperature sensor
- **bool is_enabled_Tintern_Vcc()** idem
- **void enable_filter_Tintern(bool enable)** enable filter - not investigated
- **bool is_enabled_filter_Tintern()**
- **void set_Kelvin_Tintern()** use Kelvin
- **void set_Celsius_Tintern()** use Celsius
- **void set_temp_scale_Tintern(bool Kelvin = true)** Obsolete?
- **char get_temp_scale_Tintern()** returns 'K' or 'C'
- **float get_Tintern()** returns internal temperature
- **float get_VCC()** returns the internal voltage.


### Configuration
- **void set_acquisition_repeat()** set continuous measurement mode
- **void set_acquisition_single()** set single shot mode
- **uint8_t get_acquisition_mode()** return mode set (0,1)


### PWM functions

- **void set_PWM(uint16_t value)** value is 0..511
- **uint16_t get_PWM()** idem
- **void invert_PWM(bool invert)** idem
- **bool is_inverted_PWM()** idem
- **void enable_PWM(bool enable)** idem
- **bool is_enabled_PWM()** idem


### Performance

No data available yet.
To be measured when hardware is available...


## Operational

See examples..


### TODO

- get hardware to 
- test test test
- elaborate on the documentation
- more examples

COULD
- cache all registers or
- cache a number of flags to speed up retrieving data
- optimize multibyte read / write
- look for code optimizations
- 
