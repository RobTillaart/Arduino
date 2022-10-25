
[![Arduino CI](https://github.com/RobTillaart/AD5245/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AD5245/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AD5245/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AD5245/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AD5245/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AD5245/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AD5245.svg?maxAge=3600)](https://github.com/RobTillaart/AD5245/releases)


# AD5245

Arduino library for I2C digital potentiometer AD5245.

The library is experimental and not tested yet. 


## Description

The AD5245 is a digital potentiometer which comes in 10K, 100K and 1M
and can be set in 256 steps.

An important property of the device is that it defaults
to the mid position at startup.


#### Related libraries

This library is based upon the AD524X library, and triggered by this issue:
- https://github.com/RobTillaart/AD524X/issues/11
 

## I2C address

The AD5245 has one address line to configure the I2C address.

| Addr(dec)| Addr(Hex) | AD0  |
|:--------:|:---------:|:----:|
|  44      |  0x2C     | GND  |
|  45      |  0x2D     | +5V  |


## Interface

The library has a number of functions which are all quite straightforward.
One can get / set the value of the potentiometer.

- **AD5245(uint8_t address, TwoWire \*wire = &Wire)** constructor
- **bool begin(uint8_t sda, uint8_t scl)** ESP32 a.o initializing of Wire.
- **bool begin()** for UNO.
- **bool isConnected()** See if address set in constructor is on the bus.
- **uint8_t reset()** sets potentiometer to midpoint = 128. (startup default)
- **uint8_t write(uint8_t value)** set to value 0 .. 255.
- **uint8_t read(uint8_t rdac)** read value from cache.
- **uint8_t readDevice(uint8_t rdac)** read value from device.
- **uint8_t shutDown()** check datasheet, not tested yet, use at own risk.


## Error codes

|  define        |  value  |
|:---------------|:-------:|
|  AD5245_OK     |   0     |
|  AD5245_ERROR  |  100    |


## Operation

The examples show the basic working of the functions.


## Future

- sync with AD520X library
- sync with AD524X library
  - reset ==> midScaleReset() ?  AD524X alike

