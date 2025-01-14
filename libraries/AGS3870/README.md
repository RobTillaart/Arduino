
[![Arduino CI](https://github.com/RobTillaart/AGS3870/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AGS3870/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AGS3870/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AGS3870/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AGS3870/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AGS3870.svg)](https://github.com/RobTillaart/AGS3870/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AGS3870/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AGS3870.svg?maxAge=3600)](https://github.com/RobTillaart/AGS3870/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AGS3870.svg)](https://registry.platformio.org/libraries/robtillaart/AGS3870)


# AGS3870

Arduino library for AGS3870 - Methane CH4 sensor.


### Description

**Experimental**

**Warning:** CH4 is an explosive gas, so handle it with necessary precautions.
See also license.

This library is experimental, so please use with care.

The library is based upon the limited datasheet and the code of the AGS02MA sensor,
which uses a very similar protocol.

The AGS3870 is a Methane or CH4 sensor which has a working range of 30-3000 PPM.
The sensor needs a warm up time of 2 minutes before readings are stabilized.
Readings during warm up must be considered with care.
The time between reads should be at least 2 seconds.

|  function   |  value           |  notes  |
|:------------|:----------------:|:--------|
|  CH4 range  |  30 - 50000 PPM  |
|  read freq  |  once per 2 sec  |
|  warm up    |  120 sec         |
|  current    |  20-30 mA        |  prefers own power supply.
|  temprange  |  -25..60 C       |


**Warning:** This library is not tested with hardware yet. So use with care.

Feedback as always, is welcome. Please open an issue.

**Warning:** This library is **not** meant to replace professional monitoring systems.


### Related

- https://github.com/RobTillaart/AGS02MA TVOC sensor
- https://github.com/RobTillaart/AGS2616 H2 sensor
- https://github.com/RobTillaart/AGS3870 CH4 sensor
- https://github.com/RobTillaart/AGS3871 CO sensor
- https://www.renesas.com/us/en/document/whp/overview-tvoc-and-indoor-air-quality


## I2C

### PIN layout from left to right

|  Front L->R  |  Description  |
|:------------:|:--------------|
|   pin 1      |   VDD +5V     |
|   pin 2      |   SDA data    |
|   pin 3      |   GND         |
|   pin 4      |   SCL clock   |


### Address

The device has a fixed address of 26 or 0x1A.

The device works at 100 kHz I2C bus speed (datasheet).

Note: several AGS devices use the same I2C address 0x1A.
Known are the AGS2616 (H2), AGS3870 (CH4), AGS3871 (CO), AGS02MA (TVOC).
If you want to use them on one I2C bus, you need multiplexing.
See section below.


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

If you have a AGS3870 device, please let me know your experiences
with the sensor and this (or other) library.


## Interface

```cpp
#include "AGS3870.h"
```

### Constructor

- **AGS3870(TwoWire \*wire = &Wire)** constructor, with default I2C interface.
- **bool begin()** initialize the library.
- **bool isConnected()** returns true if device address can be seen on I2C.
- **void reset()** reset internal variables.


### Heating

- **bool isHeated()** returns true if 120 seconds have passed after startup (call of **begin()** ).
Otherwise the device is not optimal ready.

According to the datasheet the preheating will improve the quality of the measurements.
If heating is ongoing the **dataReady()** returns 1


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


### Status

- **uint32_t lastRead()** timestamp of last time the device is read,
timestamp is in milliseconds since start.
Returns 0 if **readPPM()** is not called yet.
- **uint8_t lastStatus()** returns status byte.
- **bool dataReady()** returns true if data has been updated.
Returns false if not updated or heating in progress.
- **int lastError()** returns last error.


### Calibration

**NOT TESTED YET, use with care, feedback welcome**

Calibration functions should be called after at least 5 minutes in fresh air.
See example sketch.

- **bool zeroCalibration()** wrapper, for fast zero calibration.
- **bool manualZeroCalibration(uint16_t value = 0)** Set the zero calibration
value manually. See table below.
- **bool getZeroCalibrationData(ZeroCalibrationData &data)** fills a data
struct with the current zero calibration status and value.
Returns true on success.
- **uint32_t readResistance()** returns internal R of sensor. To be used for
calibration. (Alt-234 = Ω)


|  value   |  meaning  |
|:--------:|:----------|
|  0xFFFF  |  Factory reset
|  0x0000  |  set current resistance as zero
|  other   |  set value as zero


### Other

- **bool readRegister(uint8_t address, RegisterData &reg)** fills a data struct
with the sensors register data at that address.
Primarily intended for troubleshooting and analysis of the sensor.
Not recommended to build applications on top of this method's raw data.
Returns true if the **RegisterData** is filled, false if data could not be read.
Note: unlike other public methods, CRC errors don't return false or show up in
`lastError()`, instead the CRC result is stored in `RegisterData.crcValid`.


### Status bits.

|  bit  |  description                        |  notes  |
|:-----:|:------------------------------------|:--------|
|  7-1  |  reserved                           |
|   0   |  RDY bit  0 = ready  1 = not ready  |  1 == busy


### Error Codes

|  ERROR_CODES                |  value  |
|:----------------------------|:-------:|
|  AGS3870_OK                 |     0   |
|  AGS3870_ERROR              |   -10   |
|  AGS3870_ERROR_CRC          |   -11   |
|  AGS3870_ERROR_READ         |   -12   |
|  AGS3870_ERROR_NOT_READY    |   -13   |


## Future

#### Must

- improve documentation
- test with hardware

#### Should

- investigate and test calibration
- keep in sync with AGS3871 / AGS02MA lib

#### Could

- test with different processors
- elaborate error handling.
- move code to .cpp?
- investigate other registers
- check MAGIC numbers.
- examples
  - use dataReady() to optimize number of reads.

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

