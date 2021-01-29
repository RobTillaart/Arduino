
[![Arduino CI](https://github.com/RobTillaart/Temperature/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Temperature/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Temperature.svg?maxAge=3600)](https://github.com/RobTillaart/Temperature/releases)


# Temperature

Arduino library with dewPoint, humidex, heatIndex and windchill functions.


## Description

This library contains weather related functions.
These functions are approximations based on work of NOAA a.o.

These functions can be used with temperature and humidity sensors e.g.
DHT22 or Sensirion, to make a weather station application.


## Interface

TO elaborate

### Conversion

- **float Fahrenheit(celsius)** idem
- **float Celsius(fahrenheit)** idem
- **float Kelvin(celsius)** idem


### DewPoint, humidex

- **float dewPoint(celsius, humidity)** idem
- **float dewPointFast(celsius, humidity)** idem
- **float humidex(celsius, dewpoint)** idem


### heatIndex

- **float heatIndex(fahrenheit, humidity)** idem
- **float heatIndexC(celsius, humidity)** idem


### WindChill

Windspeed @ 10 meter, if convert is true => windspeed will be converted to 1.5 meter
else ==> formula assumes windspeed @ 1.5 meter

- **float WindChill_F_mph(fahrenheit, milesPerHour, convert = true)**
- **float WindChill_C_kmph(celcius, kilometerPerHour, convert = true)**
- **float WindChill_C_mps(celsius, meterPerSecond, convert = true)**


## Operations

The functions have a limited scope so one cannot use it for all input values possible.
The user should be aware of that. Check the references mentioned in the code and or
wikipedia to confirm the applicability of the values generated.
The functions do not check the inputs.

See examples for typical usage.
