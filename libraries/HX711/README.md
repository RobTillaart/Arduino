
[![Arduino CI](https://github.com/RobTillaart/HX711/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/HX711/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/HX711.svg?maxAge=3600)](https://github.com/RobTillaart/HX711/releases)


# HX711

Arduino library for HX711 24 bit ADC  used for load cells and scales.


## Description

This HX711 library has an interface which is a superset of a library made by bogde.
Some missing functions were added to get more info from the lib. 

Another important difference is that this library uses floats. The 23 bits mantisse 
of the IEE754 float matches the 24 bit ADC very well. Furthermore it gave a smaller
footprint.


## Main flow

First action is to call **begin(dataPin, clockPin)** to make connection to the **HX711**.

Second step is calibration for which a number of functions exist.
- **tare()** measures zero point
- **set_scale(factor)** set a known conversion factor e.g. from EEPROM.
- **calibrate_scale(WEIGHT, TIMES)** determines the scale factor based upon a known weight e.g. 1 Kg.

Steps to take for calibration
1. clear the scale
1. call tare() to set the zero offset
1. put a known weight on the scale 
1. call calibrate_scale(weight) 
1. scale is calculated.
1. save the offset and scale for later use e.g. EEPROM.


## Pricing

Some price functions were added to make it easy to use this library
for pricing goods or for educational purposes. These functions are under discussion
if they will stay. Another set of function to add weights together didn't make it in 
the 0.2.0 release, it is on a todo list.

For weight conversion functions see https://github.com/RobTillaart/weight


## Notes


### Scale values for loadcells

These scale values worked pretty well with a set of loadcells, 
Use calibrate to find your values.

- 5 KG loadcell   scale.set_scale(420.52); 
- 20 KG loadcell  scale.set_scale(127.15); 


### Connections HX711

- A+/A-  uses gain of 128 or 64
- B+/B-  uses gain of 32


### Connections

| HX711 Pin | Color |
|:----:|:----:|
|  E+  |  red           |
|  E-  |  black         |
|  A-  |  white         |
|  A+  |  green         |
|  B-  |  not connected |
|  B+  |  not connected |


| HX711 Pin | Color |
|:----:|:----:|
|  E+  | red           |
|  E-  | black         |
|  A-  | blue          |
|  A+  | white         |
|  B-  | not connected |
|  B+  | not connected |


### Temperature

Loadcells do have a temperature related error.
This can be reduced by doing the calibration and take the tare 
at the temperature one also does the measurements.

Another way to handle this is to add a good temperature sensor
(e.g. DS18B20, SHT85) and compensate for the temperature
differences in your code. 


## Operation

See examples
