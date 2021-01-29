
[![Arduino CI](https://github.com/RobTillaart/DHTstable/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DHTstable/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DHTstable.svg?maxAge=3600)](https://github.com/RobTillaart/DHTstable/releases)

# DHTstable

Arduino Library for the DHT11 and DHT22 temperature and humidity sensor. 

## Description

The DHTstable library is a "frozen" version of the DHTlib.
This version is stable for both ARM and AVR.

0.2.5 is a migration to its own repository.
0.2.6 fixed URL to new repro
0.2.7 getTemperature() and getHumidity() added
      added arduino-ci + unit test.

The latest developments for the DHT sensors are done in https://github.com/RobTillaart/DHTNEW
which is also tested on an ESP32.
There are some interface differences but these are relative small.

It is adviced to upgrade to the DHTNEW library if one needs new functionality.

## Multiple dht.h includes

Note that the include file is called dht.h (for compatibily reasons)
this might need a rename in sketch and library if there is a conflict.

## TODO (optional)

- rename files to dhtstable.h + dhtstable.cpp  ( 0.3.0 version some day )

## Operational

See examples.
