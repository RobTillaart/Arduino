
[![Arduino CI](https://github.com/RobTillaart/DHT_Simulator/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DHT_Simulator/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DHT_Simulator/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DHT_Simulator/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DHT_Simulator/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DHT_Simulator/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DHT_Simulator.svg?maxAge=3600)](https://github.com/RobTillaart/DHT_Simulator/releases)


# DHT_Simulator

Arduino sketch to simulate a DHT22 temperature and humidity sensor.


## Description

The DHT22 is an often used sensor and many libraries are written for it
including my own https://github.com/RobTillaart/DHTNew library. 
To better understand the protocol and to be able to debug my library 
I wrote a simulator for the DHT sensors in 2014.

The simulator can be used to test applications to that use a DHT sensor,
e.g. to get high alarm temp or whatever.

Currently the code uses two analogue ports to get a value for temperature 
and humidity. Just connect two potentiometers to play and simulate increase and 
decrease of the temperature and humidity.


## 2022-11-01
- add RP2040 to build-CI
- update license

## 0.2.1

- added pin to trigger CRC errors
- added temp and hum pin for input for CI
- added pins for CRC error, pulse length error and timeout error 
(to be tested in detail)


## 0.2.0 version

- added flag for random generation of data
- added flag for debug
- explicit support ESP32 & ESP8266
- added counter # samples generated per second ==> so one sees it still runs
- added error and debug messages // some commented

The simulator is not tested extensively so please report bugs.


## Future

1) use the simulator-core as a bridge to other sensors.
Idea is to use the code of the simulator in combination with a 
Sensirion or two separate sensors (DS18B20 + ? ) to provide an 
accurate temperature and humidity. These could then be readable 
with any DHT library with the performance of a DHT (~ 5ms).
(when time permits)

2) implement a recorder mode, to be able to replay a certain
behaviour time after time. 


## Operation

- adjust the pins in the head of the program to meet your setup
- compile, connect, run

And have fun.
