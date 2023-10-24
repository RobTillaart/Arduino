
[![Arduino CI](https://github.com/RobTillaart/DHT_Simulator/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DHT_Simulator/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DHT_Simulator/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DHT_Simulator/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DHT_Simulator/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DHT_Simulator.svg)](https://github.com/RobTillaart/DHT_Simulator/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DHT_Simulator/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DHT_Simulator.svg?maxAge=3600)](https://github.com/RobTillaart/DHT_Simulator/releases)

```
when converted to a simulation class
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DHT_Simulator.svg)](https://registry.platformio.org/libraries/robtillaart/DHT_Simulator)
```

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


The simulator is not tested extensively so please report bugs.

#### Related

- https://github.com/RobTillaart/DHTNew
- https://github.com/RobTillaart/DHTStable
- https://github.com/RobTillaart/DHT_Simulator


## Operation

- adjust the pins in the head of the program to meet your setup
- compile, connect, run

And have fun.


## Future

1) use the simulator-core as a bridge to other sensors.
Idea is to use the code of the simulator in combination with a 
Sensirion or two separate sensors (DS18B20 + ? ) to provide an 
accurate temperature and humidity. These could then be readable 
with any DHT library with the performance of a DHT (~ 5ms).
(when time permits)

2) implement a recorder mode, to be able to replay a certain
behaviour time after time. 

3) make a SHT Simulator class?


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

