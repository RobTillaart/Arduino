
[![Arduino CI](https://github.com/RobTillaart/MHZCO2/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MHZCO2/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MHZCO2/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MHZCO2/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MHZCO2/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MHZCO2.svg)](https://github.com/RobTillaart/MHZCO2/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MHZCO2/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MHZCO2.svg?maxAge=3600)](https://github.com/RobTillaart/MHZCO2/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MHZCO2.svg)](https://registry.platformio.org/libraries/robtillaart/MHZCO2)


# MHZCO2

Arduino Library for MHZ series CO2 sensors.


## Description

The MHZCO2 is an experimental library for the MHZ19B CO2 sensor
with a Serial (RS232-TTL) interface and compatibles.

The library offers a base class and derived classes to prepare for specific functionality.
The base class is based upon the MHZ19B specification. 
This might change in the future as compatibles might differ on detail.

Reference: user manual MHZ129B 2019-04-25 version 1.4


### Version 0.2.1

Minor breaking change as **Measure()** will only update lastMeasurement
in case the measurement was successful. See #11.


### Version 0.2.0

Version 0.2.0 fixes a bug in **setPPM()** which makes older versions obsolete.


### Compatibles

This list is not verified although these devices should be compatible based upon datasheet.

There exists different models of 400-2000 PPM and 400-5000 PPM and 400-10000 PPM. 
As far as known these have the same interface as there is very little information to be found.


|  type      | precision  |  notes  |
|:-----------|:----------:|:--------|
|  MHZ1311A  | 50ppm + 5% | energy saving version
|  MHZ19     | 50ppm + 5% | 
|  MHZ19B    | 50ppm + 3% | test device
|  MHZ19C    | 50ppm + 5% | (1)
|  MHZ19D    | 50ppm + 5% | 
|  MHZ19E    | 50ppm + 5% |

Note (1):
There exists different models of the MHZ19C and probably others. 
The range can go from 400-2000 PPM, 400-5000 PPM and 400-10000 PPM. 
As far as known these have the same interface as there is very little 
information to be found. See #9.

Note: The calibration of the MHZ1311A is different than MHZ19x series

If there are compatible devices missing in this list, please let me know.

In previous versions the MTP40F was incorrectly mentioned as compatible.


### Related

- https://emariete.com/en/sensor-co2-mh-z19b/
- https://emariete.com/en/sensor-co2-low-consumption-mh-z1311a-winsen/
- https://revspace.nl/MHZ19
- https://www.co2.earth/ - current outdoor CO2 level can be used for calibrating.
- https://keelingcurve.ucsd.edu/ - historical outdoor CO2 level.
- https://github.com/RobTillaart/MTP40C
- https://github.com/RobTillaart/MTP40F
- https://github.com/RobTillaart/Cozir


## Connection

- check datasheet of your sensor.


## Interface

```cpp
#include "MHZCO2.h"
```

### Constructor

- **MHZCO2()** base class constructor.
- **MHZ19()** constructor. Also 19B, C, D, E
- **void begin(Stream \* str)** set the Serial port to use, e.g Serial1,
or a softwareSerial port.
**begin()** also resets all internal variables.
- **uint32_t uptime()** returns milliseconds since 'instantiation'.


### Range

To set the max range of the actual sensor.

- **void setPPM(uint16_t PPM)** PPM = 2000, 5000, 10000. 
The value set is persistent over reboots (see issue #9).
- **uint16_t getPPM()** returns the cached PPM value.
Note: initially this function returns zero / 0 as the cache is not 
filled by **setPPM()** yet.


### Measure

- **int measure()** workhorse, send command to read the sensor and 
waits until an answer is received. Return values see below.
Will only update lastMeasurement if the measurement is successful (0.2.1)
- **uint32_t lastMeasurement()** timestamp in milliseconds of last measurement.
- **int getCO2()** returns CO2 PPM last measurement.
- **int getTemperature()** returns temperature last measurement.
Note that the temperature can be negative.
- **int getAccuracy()** returns accuracy last measurement.
Note: check datasheet.
- **int getMinCO2()** returns minCO2 last measurement.

The latter two might not be supported by all MH sensors.

#### Return values of **measure()**

|  value  |  Name              |  Description  |
|:-------:|:------------------:|:--------------|
|    0    |  MHZCO2_OK         | measurement succeeded.
|   -10   |  MHZCO2_TIMEOUT    | took too long to receive an answer.
|   -11   |  MHZCO2_ERROR_CRC  | Checksum error, handle answer with care.


#### CRC error

In case of an checksum error the values received may be corrupted.
Best strategy is to ignore the measurement. However this is not always
possible so a strategy might be to compare the values of the measurement 
with the previous ones. 
Often one can determine the failing ones but definitely not always.


### Calibration

**WARNING:** use with care, read the datasheet as these commands may disrupt your sensor.

- **void calibrateZero()** Only use when sensor is at least 30 minutes 
in a calibrated **400** PPM environment.
- **void calibrateSpan(uint16_t span)** Only use when sensor is at least 30 minutes 
in a calibrated **2000** PPM environment.
- **void calibrateAuto(bool mode = true)**

Note the outdoor calibration CO2 level differs per day and one should check 
a local airport or weather station for a good reference.

The University of San Diego keeps track of CO2 for a long time now.
See - https://keelingcurve.ucsd.edu/ 


### Timeout

These functions are used to set the default timeout in the receive function.
The faster the baud rate used, the smaller this value can be. As the **receive()** 
call has to read 9 bytes at (default) 9600 baud. This is max 1 character per 
millisecond. To receive 9 bytes one needs therefore at least 10 to 15 milliseconds
under ideal circumstances. So setting the timeout lower makes little sense.

If the timeout is set to zero / 0 there will be no time out checking. 

Use with care!

- **void setTimeOut(uint16_t timeout = 1000)** set the stream reading timeout, 
defaults to 1000 milliseconds.
- **uint16_t getTimeOut()** returns the set stream reading timeout.


## Future

#### Must

- improve documentation
- buy hardware MHZ19B / MHZ19C
- test with hardware
- verify timeout

#### Should

- check 5000 and 10000 PPM and possible others?
  - is there an effect on the PWM output.
- should the PPM be a parameter of the constructor?
  - default to 2000? or model based?

#### Could

- add type info for derived classes?
  - A .. E ?
- save RAM? possible?
  - all arrays start with 0xFF, 0x01
  - reduce data types?
- **uint16_t send()** could return bytes send?
  - would allow higher level functions to check.
- add **int maxCO2()** by keeping track myself?
- extend unit tests if needed.
- fix SoftwareSerial - https://github.com/Arduino-CI/arduino_ci/issues/346

#### Won't


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

