
[![Arduino CI](https://github.com/RobTillaart/AGS3871/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AGS3871/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AGS3871/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AGS3871/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AGS3871/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AGS3871.svg)](https://github.com/RobTillaart/AGS3871/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AGS3871/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AGS3871.svg?maxAge=3600)](https://github.com/RobTillaart/AGS3871/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AGS3871.svg)](https://registry.platformio.org/libraries/robtillaart/AGS3871)


# AGS3871

Arduino library for the AGS3871 - CarbonMonoxide CO sensor.


#### Description

**Experimental**

This library is experimental, so please use with care.

The library is based upon the limited datasheet and the code of the AGS02MA sensor,
which uses a very similar protocol.

**Warning:** This library is very limited tested with hardware.

Note this library is not meant to replace professional monitoring systems.


### Related

- https://github.com/RobTillaart/AGS02MA TVOC sensor
- https://github.com/RobTillaart/AGS3871 CO sensor
- https://www.renesas.com/us/en/document/whp/overview-tvoc-and-indoor-air-quality


## I2C

The device has a fixed address of 26 or 0x1A.

The device works at 100 kHz I2C bus speed (datasheet).


### PIN layout from left to right

|  Front L->R  |  Description  |
|:------------:|:--------------|
|   pin 1      |   VDD +5V     |
|   pin 2      |   SDA data    |
|   pin 3      |   GND         |
|   pin 4      |   SCL clock   |


### I2C multiplexing

Sometimes you need to control more devices than possible with the default
address range the device provides.
This is possible with an I2C multiplexer e.g. TCA9548 which creates up 
to eight channels (think of it as I2C subnets) which can use the complete 
address range of the device. 

Drawback of using a multiplexer is that it takes more administration in 
your code e.g. which device is on which channel. 
This will slow down the access, which must be taken into account when
deciding which devices are on which channel.
Also note that switching between channels will slow down other devices 
too if they are behind the multiplexer.

- https://github.com/RobTillaart/TCA9548


### Please report your experiences.

If you have a AGS3871 device, please let me know your experiences
with the sensor and this (or other) library.


## Interface

```cpp
#include "AGS3871.h"
```

### Constructor

- **AGS3871(TwoWire \*wire = &Wire)** constructor, with default I2C interface.
- **bool begin()** initialize the library.
- **bool isConnected()** returns true if device address can be seen on I2C.
- **void reset()** reset internal variables.


### Heating

- **bool isHeated()** returns true if 2 minutes have passed after startup (call of **begin()** ).
Otherwise the device is not optimal ready.
According to the datasheet the preheating will improve the quality of the measurements.
- **uint32_t lastRead()** last time the device is read, timestamp is in milliseconds since start.
Returns 0 if **readPPM()** is not called yet.


### Administration

- **uint8_t getAddress()** returns the fixed address, 26 or 0x1A.
- **uint8_t getVersion()** reads sensor version from device.
If the version cannot be read the function will return 255.


### Read

- **uint32_t readPPM()** reads PPM (parts per million 10^6) from device.
Typical value should be between 1 .. 1000.
Returns **lastPPM()** value if failed so one does not get sudden jumps in graphs.
Check **lastStatus()** and **lastError()** to get more info about success.
- **uint32_t lastPPM()** returns last readPPM (parts per million) value (cached).
- **uint32_t readResistance()** returns internal R of sensor. Meaning unknown.
- **uint8_t dataReady()** returns RDY bit from last read.
- **int lastError()** returns last error.


### Calibration

**NOT TESTED YET, use with care, feedback welcome**

- **bool zeroCalibration()** to be called after at least 5 minutes in fresh air.
See example sketch.
- **bool manualZeroCalibration(uint16_t value = 0)** Set the zero calibration value manually.
To be called after at least 5 minutes in fresh air.
- **bool getZeroCalibrationData(ZeroCalibrationData &data)** fills a data struct with the 
current zero calibration status and value. 
Returns true on success.


### Other

- **bool readRegister(uint8_t address, RegisterData &reg)** fills a data struct with the chip's 
register data at that address.
Primarily intended for troubleshooting and analysis of the sensor.
Not recommended to build applications on top of this method's raw data.
Returns true when the **RegisterData** is filled, false when the data could not be read.
Note: unlike other public methods, CRC errors don't return false or show up in `lastError()`, 
instead the CRC result is stored in `RegisterData.crcValid`.


### Status bits.

|  bit  |  description                        |  notes  |
|:-----:|:------------------------------------|:--------|
|  7-1  |  internal use                       |
|   0   |  RDY bit  0 = ready  1 = not ready  |  1 == busy


### Error Codes

|  ERROR_CODES                |  value  |
|:----------------------------|:-------:|
|  AGS3871_OK                 |     0   |
|  AGS3871_ERROR              |   -10   |
|  AGS3871_ERROR_CRC          |   -11   |
|  AGS3871_ERROR_READ         |   -12   |
|  AGS3871_ERROR_NOT_READY    |   -13   |



## Future

#### Must

- improve documentation
  - references?
- test with hardware

#### Should

- test with hardware
- test with different processors

#### Could

- elaborate error handling.
- move code to .cpp?

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

