
[![Arduino CI](https://github.com/RobTillaart/DHTstable/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DHTstable/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DHTstable/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DHTstable/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DHTstable/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DHTstable.svg)](https://github.com/RobTillaart/DHTstable/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DHTstable/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DHTstable.svg?maxAge=3600)](https://github.com/RobTillaart/DHTstable/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DHTstable.svg)](https://registry.platformio.org/libraries/robtillaart/DHTstable)


# DHTStable

Arduino Library for the DHT11 and DHT22 temperature and humidity sensor. 


## Description

The DHTStable library is a "frozen" version of the DHTlib.
This version is stable for both ARM and AVR.

0.2.5 is a migration to its own repository.
0.2.6 fixed URL to new repository
0.2.7 getTemperature() and getHumidity() added
      added Arduino-CI + unit test.
0.2.8 fix negative temperature
0.2.9 fix URL in JSON file

**breaking name**

1.0.0 renamed the dht.h file to DHTStable.h to fix the incompatible flag 
See issue https://github.com/RobTillaart/DHTstable/issues/8
Also made temperature and humidity private


The latest developments for the DHT sensors are done in https://github.com/RobTillaart/DHTNEW
which is also tested on an ESP32.
There are some interface differences, these are relative small but can be time critical.

It is advised to upgrade to the DHTNEW library if one needs the new functionality.


## Interface

```cpp
#include "DHTStable.h"
```



#### Constructor

- **dht()** Constructor


#### Read functions per type

- **int read11(uint8_t pin)**
- **int read(uint8_t pin)**


- **int read12(uint8_t pin)**
- **int read21(uint8_t pin)**
- **int read22(uint8_t pin)**
- **int read33(uint8_t pin)**
- **int read44(uint8_t pin)**
- **int read2301(uint8_t pin)**
- **int read2302(uint8_t pin)**
- **int read2303(uint8_t pin)**
- **int read2320(uint8_t pin)**
- **int read2322(uint8_t pin)**


- **float getHumidity()**
- **float getTemperature()**


#### Enable / disable interrupts

- **bool getDisableIRQ()**
- **void setDisableIRQ(bool b )**




## Operational

See examples.

#### Voltage AM2301 

In a test an AM2301 had problems giving no humidity (99.9% overflow) when this
DHTStable library was used with an ESP8266. (Reported by mail, no GH issue)
After days of testing and thinking and more testing the cause was found. 
The AM2301 was powered by a 5V3 power supply which was apparently too high while having the
data handshakes at 3V3. 
When the VCC voltage was lowered to 5V1 it appeared to work as it should. 
(Kudos to Viktor for finding the cause)


## Future

- no active development 
  - follow bug fixes from DHTnew
  - on request.

#### Must

#### Should

#### Could

#### Wont

- move some const int to .cpp file
- improve unit test
  - add constants test


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


