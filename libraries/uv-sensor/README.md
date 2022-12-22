
[![Arduino CI](https://github.com/RobTillaart/uv-sensor/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/uv-sensor/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/uv-sensor/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/uv-sensor/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/uv-sensor/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/uv-sensor/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/uv-sensor.svg?maxAge=3600)](https://github.com/RobTillaart/uv-sensor/releases)


# uv-sensor

Arduino sketch for analog UV sensor.


## Description

![Foo](https://www.tinytronics.nl/shop/image/cache/catalog/products/product-003601/uv-light-sensor-module-200-370nm-80x80w.jpg)
Image courtesy Tinytronics

This small (type-less) UV-sensor is powered by 3.3 .. 5 V so it can be used by almost any microprocessor.

The sensor has an analogue output that is roughly linear with the UV-index (sunlight assumed, see notes)


| Voltage | UV index |
|:-------:|:--------:|
| <0.050  |     0    |
|  0.227  |     1    |
|  0.318  |     2    |
|  0.408  |     3    |
|  0.503  |     4    |
|  0.606  |     5    |
|  0.696  |     6    |
|  0.795  |     7    |
|  0.881  |     8    |
|  0.976  |     9    |
|  1.079  |    10    |
|  1.170> |    11    |

From this table the formula is derived (spreadsheet) which is pretty linear between UV 1 and 11.

Related to: https://github.com/RobTillaart/AnalogUVSensor


### Notes

Note: The sensor is not calibrated and the table is indicative for sunlight (assumption!) and therefore not suitable for e.g. medical or industrial usage. 

Note: UV radiation will not go through glass, so inside you will most likely always read  zero. This may help to calibrate the zero level of the sensor.

Note: depending on the light source used, the table above is incorrect.



### Sensitivity

The sensor is sensitive for wavelengths from 200 - 370 nm, so mostly in UVB and UVA region and less in the UVC. 

https://en.wikipedia.org/wiki/Ultraviolet


### Future

- verify vs calibrated sensor.
- investigate angle sensitivity (if the UV light comes from an angle).
- investigate response time to stabilize (e.g. does it react fast on clouds).
- investigate with different light sources (UVled, TL, sunlight).
- allow use of internal / external ADC.
- add a pin to control the power of the sensor (low energy applications).
- 

