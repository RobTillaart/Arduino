
[![Arduino CI](https://github.com/RobTillaart/Temperature/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/Temperature/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/Temperature/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/Temperature/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/Temperature/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Temperature/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Temperature.svg?maxAge=3600)](https://github.com/RobTillaart/Temperature/releases)


# Temperature

Arduino library with dewPoint, humidex, heatIndex and wind-chill functions.


## Description

This library contains weather related functions.
These functions are approximations based on work of NOAA a.o.

These functions can be used with temperature and humidity sensors e.g.
DHT22 or Sensirion, to make a weather station application.


## Interface


### Conversion

- **float Fahrenheit(float Celsius)** idem.
- **float Celsius(float Fahrenheit)** idem.
- **float Kelvin(float Celsius)** idem.


### DewPoint, humidex

- **float dewPoint(float Celsius, float humidity)** idem.
- **float dewPointFast(float Celsius, float humidity)** idem.
- **float humidex(float Celsius, float dewPoint)** idem.


### heatIndex

- **float heatIndex(float Fahrenheit, float humidity)** idem.
- **float heatIndexC(float Celsius, float humidity)** idem.


### WindChill

Wind speed @ 10 meter, if **convert** is true => wind speed will be converted to 1.5 meter
else ==> formula assumes wind speed @ 1.5 meter

- **float WindChill_F_mph(float Fahrenheit, float milesPerHour, bool convert = true)**
- **float WindChill_C_kmph(float Celsius, float kilometerPerHour, bool convert = true)**
- **float WindChill_C_mps(float Celsius, float meterPerSecond, bool convert = true)**


## Operations

The functions have a limited scope so one cannot use it for all input values possible.
The user should be aware of that. Check the references mentioned in the code and or
Wikipedia to confirm the applicability of the values generated.
The functions do not check the inputs.

See examples for typical usage.


# Future

- improve documentation
- expand number of formulas
- 

