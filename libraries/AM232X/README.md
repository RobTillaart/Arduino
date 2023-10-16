
[![Arduino CI](https://github.com/RobTillaart/AM232X/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AM232X/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AM232X/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AM232X/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AM232X/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AM232X.svg)](https://github.com/RobTillaart/AM232X/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AM232X/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AM232X.svg?maxAge=3600)](https://github.com/RobTillaart/AM232X/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AM232X.svg)](https://registry.platformio.org/libraries/robtillaart/AM232X)


# AM232X

Arduino library for AM2320 AM2321 and AM2322 I2C temperature and humidity sensor.


## Description

AM232X is a sensor similar to the DHT12 with an I2C interface. 
Although in theory this could enable multiple sensors on one bus
the AM232X has a fixed address **0x5C** so one need to implement a 
multiplexing strategy to have multiple sensors in practice. 
See multiplexing below.

This library works also for the **AM2315** which has a library of its own - https://github.com/RobTillaart/AM2315


#### Typical parameters

|             |  range     | accuracy | repeatability |
|:------------|:----------:|:--------:|:-------------:|
| Temperature | -40 - 80   | 0.5°C    |  ±0.1         |
| Humidity    | 0.0 - 99.9 | ±3%      |  ±0.1         |
| Sample time | 2 seconds  |          |               |


#### Hardware connection

```
//  AM232X PIN layout             AM2315 COLOR
//  ============================================
//   bottom view  DESCRIPTION     COLOR
//       +---+
//       |o  |       VDD          RED
//       |o  |       SDA          YELLOW
//       |o  |       GND          BLACK
//       |o  |       SCL          GREY
//       +---+
//
// do not forget pull up resistors between SDA, SCL and VDD.
```


#### I2C clock speed

The datasheet states the AM2320 should be used on 100 KHz I2C only.

TODO measure and verify (see AM2315)


## One Wire Protocol

The AM2320, AM2321 and AM2322 can also be read by using a "OneWire" protocol.
This protocol is identical to the DHT22 and will only provide temperature,
humidity and a CRC. See issue #26.

If one wants to use this protocol, one can use https://github.com/RobTillaart/DHTNew
and optionally force the type to 22.

If problems arise with the "OneWire" protocol, please let me know and 
file the issues under DHTNew.


## Interface

```cpp
#include "AM232X.h"
```

Since 0.4.2 the library provides specific classes for the AM2320, AM2321 and AM2322 which have the same interface.


#### Constructor

- **AM232X(TwoWire \*wire = &Wire)** constructor, default using Wire (I2C bus), 
optionally set to Wire0 .. WireN.
- **bool begin()** initializer for class.
Returns true if fixed device address 0x5C is connected.
- **bool isConnected(uint16_t timeout = 3000)** returns true if the fixed device address 0x5C is found on I2C bus.
As the device can be in sleep modus it will retry for the defined timeout (in micros) with a minimum of 1 try. 
minimum = 800 us and maximum = 3000 us according to datasheet.


#### Core

- **int read()** read the sensor and store the values internally.
Returns the status of the read which should be **AM232X_OK** == 0.
- **float getHumidity()** returns the last read humidity + optional offset, 
or **AM232X_INVALID_VALUE** == -999 in case of error. 
This error can be suppressed, see below.
- **float getTemperature()** returns the last read temperature + optional offset,
or **AM232X_INVALID_VALUE** == -999 in case of error. 
This error can be suppressed, see below.
- **uint32_t lastRead()** returns the timestamp in milliseconds since startup of the last successful read.


#### Offset

- **void setHumOffset(float offset = 0)** set an offset for humidity to calibrate (1st order) the sensor.
Default offset = 0, so no parameter will reset the offset to 0.
- **float getHumOffset()** return the current humidity offset, default 0.
- **void setTempOffset(float offset = 0)** set an offset for temperature to calibrate (1st order) the sensor.
Default offset = 0, so no parameter will reset the offset to 0.
- **float getTempOffset()** return the current temperature offset, default 0.


#### Control

Functions to adjust the communication with the sensor.

- **void setReadDelay(uint16_t readDelay = 0)** Tunes the time it waits before actual read can be done.
Set readDelay to 0 will reset it to 2000 ms effective the next **read()**.
- **uint16_t getReadDelay()** returns the current readDelay in milliseconds. 
Note that a value of zero (reset) will return 0 before the call and 2000 after the call to **read()**.
- **bool wakeUp()** function that will try for 3 milliseconds to wake up the sensor.
This can be done before an actual read to minimize the **read()** call.
- **void setSuppressError(bool b)** suppress error values of **AM232X_INVALID_VALUE** == -999.
=> you need to check the return value of read() instead.  
This can be used to keep spikes out of your graphs / logs. 
- **bool getSuppressError()**  returns the current suppression setting.


#### Metadata

Check datasheet for details.

- **int getModel()** idem
- **int getVersion()** idem
- **uint32_t getDeviceID()** idem
- **int setStatus(uint8_t value)**
- **int getStatus()**


#### User registers

Check datasheet for details.

- **int setUserRegisterA(int value)**
- **int setUserRegisterB(int value)**
- **int getUserRegisterA()**
- **int getUserRegisterB()**


#### Error codes

| name                              | value | notes       |
|:----------------------------------|------:|:------------|
| AM232X_OK                         |  0    |
| AM232X_ERROR_UNKNOWN              |  -10  |
| AM232X_ERROR_CONNECT              |  -11  |
| AM232X_ERROR_FUNCTION             |  -12  |
| AM232X_ERROR_ADDRESS              |  -13  |
| AM232X_ERROR_REGISTER             |  -14  |
| AM232X_ERROR_CRC_1                |  -15  |
| AM232X_ERROR_CRC_2                |  -16  |
| AM232X_ERROR_WRITE_DISABLED       |  -17  |
| AM232X_ERROR_WRITE_COUNT          |  -18  |
| AM232X_MISSING_BYTES              |  -19  |
| AM232X_READ_TOO_FAST              |  -20  |
| AM232X_HUMIDITY_OUT_OF_RANGE      |  -100 | not used by default.
| AM232X_TEMPERATURE_OUT_OF_RANGE   |  -101 | not used by default.
| AM232X_INVALID_VALUE              |  -999 | can be suppressed. 


## Operation

See examples

In **setup()** you have to call the **begin()** to initialize 
the Wire library and do an initial **read()** to fill the variables temperature and humidity. 
To access these values one must use **getTemperature()** and **getHumidity()**. 
Multiple calls will give the same values until **read()** is called again.

Note that the sensor can go into sleep mode after 3 seconds after last read, 
so one might need to call **wakeUp()** before the **read()**.


## Multiplexing 

Multiplexing the **AM232X** can be done in several ways.
This is not a complete list or tutorial but should get you started.

1. Control the power line by means of an extra pin (+ transistor). 
Only switch on the sensor you want to use. Drawback might be time 
the sensor takes to boot and to be ready for the first measurement.
2. Use an AND gate between the I2C SCL (clock) line and the I2C SCL 
pin of the sensors. This way one can enable / disable communication 
per sensor. This will still need an IO pin per sensor but does not 
have the "boot time" constraint mentioned above.
you may use a **PCF8574** to control the AND gates.
https://github.com/RobTillaart/PCF8574
3. Use a **TCA9548A** I2C Multiplexer, or similar. https://github.com/RobTillaart/TCA9548

Which method fit your application depends on your requirements and constraints.


## Future

#### Must

- update documentation
- test more (other platforms)

#### Should

- keep in sync with AM2315 class
  - merge in a far future.
- update unit test
- add examples

#### Could

- I2C performance measurements
  - clock speed > 170 - see AM2315


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


