
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

**Experimental**

The MHZCO2 is a library for the MHZ19B CO2 sensor and compatibles 
with a **Serial** (RS232-TTL) interface.
The library has examples for reading the **PWM** and **analog** signal,
however these are not supported from the classes.

The library offers a base class **MHZCO2** and derived classes for specific devices
to prepare for specific functionality.
The base class is based upon the MHZ19B specification. 
This might change in the future as compatibles might differ on detail.

Reference: user manual MHZ129B 2019-04-25 version 1.4


### Pins

Check the datasheet to connect the right pins. These might differ between types
and versions within a type.


### PWM

The MHZ19B and some compatibles support a **PWM** output pin to indicate the concentration.
Do not forget to connect GND lines between MCU and sensor.

The library does not support this PWM within the MHZxxx classes.
However examples are available how to measure the CO2 concentration by means 
of the PWM output **MHZCO2_PWM.ino** and **MHZCO2_PWM_highres.ino**.

The PWM has a fixed period and changes its duty cycle.
The ratio of the period HIGH (-2 ms) to total period T (-4 ms) is the indication 
of the percentage of the maximum PPM.
\
The small minus constants are needed for correct result, especially at the lower 
end of the spectrum near the 400 PPM.

Example:
If the max PPM is 5000 and the period HIGH = 432 ms and T = 1002 ms, the concentration
CO2 = 5000 x 432 x 0.001 = 2160 PPM. 


### Analog

The MHZ19B and some compatibles support an **analog** output to indicate the concentration.
The library does not support this analog signal within the MHZxxx classes.
However an example is available how to measure the CO2 concentration by means 
of the analog output **MHZCO2_analog.ino**.

The advantage of the analog output is that it is the fastest interface of all
(depending on ADC used of course).

The example is straightforward and can be improved e.g. by using an external
reference for the ADC and some calibrated values. 
This is not implemented in the example.


### Precision

The MHZ sensors can measure with an 1 ppm precision although the accuracy is 
about ±50 PPM.


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
- **MHZ19()** constructor. Also MHZ19B, MHZ19C, MHZ19D, MHZ19E and MHZ1311A.
- **void begin(Stream \* str)** resets all internal variables and 
sets the Serial port to use, e.g Serial1, or a softwareSerial port.
This stream has to be configured before the call to **begin()**.
- **uint32_t uptime()** returns milliseconds since 'instantiation'.


### Range

To set the maximum range of the actual sensor used.

- **void setPPM(uint16_t PPM)** PPM = 2000, 5000, 10000. 
The value set is persistent over reboots (see issue #9).
- **uint16_t getPPM()** returns the cached PPM value.
Note: initially this function returns zero / 0 as the cache is not 
filled by **setPPM()** yet.


### Measure

- **int measure()** the workhorse, sends a command to read the sensor and 
waits until an answer is received. Return values see below.
Will only update lastMeasurement if the measurement is successful (0.2.1)
- **uint32_t lastMeasurement()** timestamp in milliseconds of last 
successful measurement.
- **int getCO2()** returns the CO2 PPM concentration of the last measurement.
Multiple calls will return the same value until a new measurement is made.
- **int getTemperature()** returns the temperature of the last measurement.
Multiple calls will return the same value until a new measurement is made.
Note that the temperature can be negative.
- **int getAccuracy()** returns the accuracy of the last measurement.
Multiple calls will return the same value until a new measurement is made.
Note: check datasheet.
- **int getMinCO2()** returns the minimum CO2 of the last measurement.
Multiple calls will return the same value until a new measurement is made.
Note: check datasheet.

The latter two might not be supported by all MH sensors.

#### Return values of **measure()**

|  value  |  Name              |  Description  |
|:-------:|:------------------:|:--------------|
|    0    |  MHZCO2_OK         | measurement succeeded.
|   -10   |  MHZCO2_TIMEOUT    | took too long to receive an answer.
|   -11   |  MHZCO2_ERROR_CRC  | Checksum error, handle answer with care.


#### CRC error

In case of an checksum error the values received may be corrupted.
Best strategy is to ignore the measurement. 

However ignoring is not always possible so a strategy might be to
compare the values of the measurement with the previous ones to see 
if they are plausible (e.g. close to previous measurement).
This depends of course how large delta is considered acceptable.
Often one can determine the really faulty measurements but definitely not always.


### Calibration

**WARNING:** use with care, read the datasheet as these commands may disrupt 
your sensor.

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

The timeout functions are used to set the default timeout of a measurement.
The faster the baud rate used, the smaller this value can be. As the **receive()** 
call has to read 9 bytes at (default) 9600 baud. This is max 1 character per 
millisecond. To receive 9 bytes one needs therefore at least 10 to 15 milliseconds
under ideal circumstances. So setting the timeout lower makes little sense as 
one would miss bytes.

If the timeout is set to zero / 0 there will be no time out checking.
Note however this can cause blocking code. 

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

#### Could

- add type info for derived classes?
  - A .. E ?
  - only when there are real differences.
- save RAM? possible?
  - all arrays start with 0xFF, 0x01
  - reduce data types?
- **uint16_t send()** could return bytes send?
  - would allow higher level functions to check.
- add **int maxCO2()** by keeping track myself?
  - also need **void resetMaxCO2()**
- extend unit tests if needed.
- fix SoftwareSerial - https://github.com/Arduino-CI/arduino_ci/issues/346
- flush Serial occasionally?


#### Won't

- should the PPM be a parameter of the constructor?
  - default to 2000? or model based?
  - no, as now it can (in theory) be changed/calibrated runtime.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

