
[![Arduino CI](https://github.com/RobTillaart/DHTstable/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DHTstable/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DHTstable.svg?maxAge=3600)](https://github.com/RobTillaart/DHTstable/releases)

# DHTStable

Arduino Library for the DHT11 and DHT22 temperature and humidity sensor. 

## Description

The DHTStable library is a "frozen" version of the DHTlib.
This version is stable for both ARM and AVR.

0.2.5 is a migration to its own repository.
0.2.6 fixed URL to new repro
0.2.7 getTemperature() and getHumidity() added
      added arduino-ci + unit test.
0.2.8 fix negative temperature
0.2.9 fix URL in JSON file

**breaking name**

1.0.0 renamed the dht.h file to DHTStable.h to fix the incompatible flag 
See issue https://github.com/RobTillaart/DHTstable/issues/8
Also made temperature and humidity private


The latest developments for the DHT sensors are done in https://github.com/RobTillaart/DHTNEW
which is also tested on an ESP32.
There are some interface differences, these are relative small but can be time critical.

It is adviced to upgrade to the DHTNEW library if one needs the new functionality.


## TODO (optional)



## Operational

See examples.
