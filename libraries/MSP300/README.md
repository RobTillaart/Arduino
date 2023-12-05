
[![Arduino CI](https://github.com/RobTillaart/MSP300/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MSP300/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MSP300/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MSP300/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MSP300/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MSP300.svg)](https://github.com/RobTillaart/MSP300/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MSP300/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MSP300.svg?maxAge=3600)](https://github.com/RobTillaart/MSP300/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MSP300.svg)](https://registry.platformio.org/libraries/robtillaart/MSP300)


# MSP300

Arduino library for I2C MSP300 pressure transducer.

The library is experimental and not tested yet (no hardware). 


## Description

The MSP300 is an industrial digital pressure transducer. 
This library implements the I2C version (J) of the sensor.
It is written based upon the datasheet.

The library does not implement the SPI or analog version.

Note: be aware to buy the right sensor: PSI/BAR, SPI/I2C/analog and I2C address as these are hardcoded.
(OK pressure output can be converted)

As the sensor is industrial quality, many applications can be realized with it.

Issues, remarks, experience and improvements are welcome, 
please open an issue on https://github.com/RobTillaart/MSP300.


#### 0.2.0 Breaking change

Version 0.2.0 introduced a breaking change.
You cannot set the pins in **begin()** any more.
This reduces the dependency of processor dependent Wire implementations.
The user has to call **Wire.begin()** and can optionally set the Wire pins 
before calling **begin()**.


#### Available pressure ranges

- PSI := 100, 200, 300, 500, 1K, 3K, 5K, 10K, 15K
- BAR := 7, 10, 20, 35, 70, 200, 350, 700, 1000


#### I2C connection

|  colour  |  description  |
|:--------:|:-------------:|
|  RED     |  2.7 – 5.0V   |
|  BLACK   |  GND          |
|  GREEN   |  SCL          |
|  WHITE   |  SDA          |
|  YELLOW  |  NC           |


#### Analog version

For Arduino analog output version 3 is also interesting.
It provide 0.5-4.5 volt output which matches many ADC ranges.

White wire is the output (page 4 datasheet).

This version is not supported in the library.


#### Related libraries

This library is related to:
- https://github.com/RobTillaart/I2C_ASDX Honeywell pressure sensors
- https://github.com/RobTillaart/MS5611 (I2C) air pressure & temperature sensor
- https://github.com/RobTillaart/MS5611_SPI air pressure & temperature sensor
- https://github.com/RobTillaart/Pressure to convert PSI to BAR and back.
 

## I2C 

#### Address

The MSP300 has a fixed address, however there a five different supported.
So without a multiplexer you can have up to 5 transducers on one I2C bus.
The address is in the product number of the sensor you buy. (check datasheet Page 7).

|  code  |  address  |
|:------:|:---------:|
|    0   |   0x28    |
|    1   |   0x36    |
|    2   |   0x46    |
|    3   |   0x48    |
|    4   |   0x51    |


#### Speed

The sensor should work at 100 - 400 KHz I2C.


## Interface

```cpp
#include "MSP300.h"
```

#### Constructor

The library has a number of functions which are all quite straightforward.

- **MSP300(uint8_t address = 0x20, TwoWire \*wire = &Wire)** constructor, 
default address and I2C bus.
- **bool begin(int maxValue)** initialize internals.
maxValue is the maximum the sensor can read.
- **bool isConnected()** See if address set in constructor is on the bus.
- **bool setAddress(const uint8_t deviceAddress)** set address for e.g. second sensor.
- **uint8_t getAddress()** returns address set.


#### Read

- **uint32_t readPT()** must be called before pressure or temperature can be read.
Returns the raw value which is useful for debugging.
- **float getPressure()** returns the pressure in PSI or BAR (whatever sensor you have).
- **float getTemperature()** returns the temperature in degrees Celsius. 
Range 0..55° Celsius


#### Calibration

- **void setPressureCounts(uint16_t Pmin = 1000, uint16_t Pmax = 15000)** set the count rates.
Use with care. Check datasheet for details.


#### Error handling

- **int lastError()** returns the last error set. Note: will reset the error!


## Error codes

|  define        |  value  |
|:---------------|:-------:|
|  MSP300_OK     |   0     |
|  MSP300_ERROR  |  100    |


## Operation

The examples show the basic working of the functions.


## Future

#### Must

- improve documentation
- get hardware
- test 


#### Should

- add examples
- elaborate error handling.


#### Could

- test I2C performance.
- add **setTemperatureOffset(float offset = 0)**
- add **setPressureOffset(float offset = 0)**
- unit tests
- add simple class for the analog version
  - MSP300A


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

