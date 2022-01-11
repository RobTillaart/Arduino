
[![Arduino CI](https://github.com/RobTillaart/DHT20/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DHT20/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DHT20/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DHT20/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DHT20/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DHT20/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DHT20.svg?maxAge=3600)](https://github.com/RobTillaart/DHT20/releases)


# DHT20

Arduino library for I2C DHT20 temperature and humidity sensor.


## Description

The library must be initiated by calling the **begin()** function, 
or **begin(dataPin, clockPin)** for **ESP32** and similar platforms.

Thereafter one has to call the **read()** function to do the actual reading,
and with **getTemperature()** and **getHumidity()** to get the measured values.
Calling these latter again will return the same values until a new **read()** is called.

The **read()** call of this sensor is blocking for 80+ milliseconds (datasheet 7.4)
so the library also has a asynchronous interface. See below.


## Interface


### Constructor

- **DHT20(TwoWire \*wire = &Wire)** constructor, using a specific Wire (I2C bus).
- **bool begin(uint8_t dataPin, uint8_t clockPin)** begin for ESP32 et al, to set I2C bus pins.
- **bool begin()** initializer for non ESP32. Returns true if connected.
- **bool isConnected()** returns true if the address of the DHT20 can be seen on the I2C bus.


### Core

- **int8_t read()** read the sensor and store the values internally. 
It returns the status of the read which should be 0.
- **float getHumidity()** returns last Humidity read.
- **float getTemperature()** returns last Temperature read.


### Offset

- **void setHumOffset(float offset)** set an offset to calibrate (1st order) the sensor.
- **float getHumOffset()** return current offset, default 0.
- **void setTempOffset(float offset)** set an offset to calibrate (1st order) the sensor.
- **float getTempOffset()** return current offset, default 0.


### Asynchronous interface

The async interface allows one to continue processing after a **requestData()** has been made.
One can check **readyData()** and if it returns true, enough time has 
passed to make the measurement and the sensor can be read with **readData()**.

- **int requestData()** signals the sensor to make a new measurement.
- **bool readyData()** returns true if 85 milliseconds have passed since the last **requestData()** call. 
The time of 85 ms is hard coded.
- **int readData()** does the actual reading of the data.


### Miscellaneous

- **uint32_t lastRead()** last time the sensor is read in milliseconds since start.
- **uint32_t lastRequest()** last time a request is made to make a measurement.
- **int internalStatus()** returns the internal status of the sensor. (debug ?).


### Return codes

TODO: fix incomplete list

| name                  |  value  |
|:----------------------|:-------:|
| DHT20_OK              |    00   |
| DHT20_ERROR_CHECKSUM  |   -10   |
| DHT20_ERROR_CONNECT   |   -11   |
| DHT20_MISSING_BYTES   |   -12   |


## Operation

See examples


## Future

- update documentation
  - add missing error codes
  - describe async interface
- test more in detail
  - test on ESP32
- improve unit tests.
- improve the code (check return codes etc.)
- investigate 
  - status register bits 
  - sensor calibration (website aosong?)
- check for optimizations.
  - mainly for asynchronous
  - test at different I2C speeds 400 KHz should be possible.
  - 85 ms wait time?
- add examples
  - asynchronous
  - 


#### won't

- **void setIgnoreChecksum(bool = false)** ignore checksum flag speeds up communication a bit
- **bool getIgnoreChecksum()** get status. for completeness.
- 


