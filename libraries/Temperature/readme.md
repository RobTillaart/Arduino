
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

Note: pre-0.3.1 versions have incorrect heat-index.


## Interface


### Conversion

- **float Fahrenheit(float Celsius)** idem.
- **float Celsius(float Fahrenheit)** idem.
- **float Kelvin(float Celsius)** idem.

More converters are implemented in tne **temperatureConverter()** below.


### DewPoint, humidex

- **float dewPoint(float Celsius, float humidity)** idem.
- **float dewPointFast(float Celsius, float humidity)** idem.
- **float humidex(float Celsius, float dewPoint)** idem.


### heatIndex

- **float heatIndex(float Fahrenheit, float humidity)** idem.
- **float heatIndexC(float Celsius, float humidity)** idem.


#### 0.3.0

The formula for the **heatIndex()** was taken from https://en.wikipedia.org/wiki/Heat_index.
Since version 0.3.0 the more elaborated version of https://www.wpc.ncep.noaa.gov/html/heatindex_equation.shtml 
will be used. Note: there will be performance differences.

Indicative table

| Fahrenheit | Celsius | description | colour code |
|:----------:|:-------:|:------------|------------:|
|   70-79    |  21-26  | warm        |    green    |
|   80-89    |  26-32  | very warm   |    yellow   |
|   90-104   |  32-40  | hot         |    orange   |
|  105-129   |  40-54  | very hot    |       red   |
|  > 130     |  > 54   | extreme hot |    purple   |


#### 0.3.1

Fixed the adjustment which was incorrectly added.


### WindChill

Wind speed @ 10 meter, if **convert** is true => wind speed will be converted to 1.5 meter
else ==> formula assumes wind speed @ 1.5 meter

- **float WindChill_F_mph(float Fahrenheit, float milesPerHour, bool convert = true)**
- **float WindChill_C_kmph(float Celsius, float kilometerPerHour, bool convert = true)**
- **float WindChill_C_mps(float Celsius, float meterPerSecond, bool convert = true)**


Indicative table (subjective).

| wind chill °C | description          |
|:-------------:|:---------------------|
|  > -10        |  cold                |
|  -10 .. -25   |  very cold !         |
|  -25 .. -35   |  very very cold !    |
|  -35 .. -55   |  chance of frostbite |
|  < -55        |  serious dangerous   |


# temperatureConverter class

Since version 0.3.2 a temperature convertor class is added to convert to and from 
other (less known) temperature scales. 
The idea is to set a value in one scale and retrieve it in the other.
As the converter holds the last value set, multiple conversions are easy.
See example.

The scales are typically named after their inventor. 
Check Wikipedia for details about the scales.

| Name        | units | 1° in °K |    0°C  |   100°C | notes |
|:------------|:-----:|:--------:|--------:|--------:|:------|
| Celsius     |  °C   | 1.000000 |    0.00 |  100.00 |
| Delisle     |  °De  | 0.666666 | -100.00 |   50.00 |
| Fahrenheit  |  °F   | 0.555556 |   32.00 |  212.00 |
| Kelvin      |  °K   | 1.000000 |  273.15 |  373.15 |
| Newton      |  --   | 3.030303 |    0.00 |   33.00 | not the force.
| Rankine     |  °Ra  | 0.555556 |  491.76 |  671.67 | 0°Ra == 0°K, steps == Fahrenheit.
| Reamur      |  °Re  | 1.250000 |    0.00 |   80.00 |
| Romer       |  °Ro  | 1.904762 |    7.50 |   60.00 |

Note: units to be verified.

Note: this class is slightly slower than direct conversion, but it 
prevents to have 8 x 7 optimized functions.


#### Constructor

- **temperatureConverter()** Constructor sets the default to zero degrees C.


#### setters

- **void setKelvin(float value = 0)**
- **void setCelsius(float value = 0)**
- **void setFahrenheit(float value = 0)**
- **void setReamur(float value = 0)**
- **void setRankine(float value = 0)**
- **void setDelisle(float value = 0)**
- **void setNewton(float value = 0)**
- **void setRomer(float value = 0)**

#### getters

- **void getKelvin()**
- **void getCelsius()**
- **void getFahrenheit()**
- **void getReamur()**
- **void getRankine()**
- **void getDelisle()**
- **void getNewton()**
- **void getRomer()**


## Operations

The functions have a limited scope so one cannot use it for all input values possible.
The user should be aware of that. Check the references mentioned in the code and or
Wikipedia to confirm the applicability of the values generated.
The functions do not check the inputs.

See examples for typical usage.


# Future

- improve documentation
  - add short explanation?
- 
