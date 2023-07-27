
[![Arduino CI](https://github.com/RobTillaart/MTP40F/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![JSON check](https://github.com/RobTillaart/MTP40F/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MTP40F/actions/workflows/jsoncheck.yml)
[![Arduino-lint](https://github.com/RobTillaart/MTP40F/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MTP40F/actions/workflows/arduino-lint.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MTP40F/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MTP40F.svg?maxAge=3600)](https://github.com/RobTillaart/MTP40F/releases)


# MTP40F

Arduino library for MTP40F CO2 sensor.


## Description

The library for the MTP40F CO2 sensor is **experimental** as not all functionality is tested.
It is based upon my https://github.com/RobTillaart/MTP40C library.

The MTP40F sensor is an NDIR (Non Dispersive InfraRed) CO2 sensor.

The sensor communicates over a 9600 baud serial (TTL) interface with a microprocessor or PC. 
This implies that calls which can take up to 25 bytes can take as much as about 20 milliseconds.

On the other hand this low baud rate implies it will work over relative long distances.
This signal quality over longer distances is not investigated. 

The MTP40F has more interface options, I2C, PWM and ALARM. 
This library does not support these other interfaces for now.
However minimal examples are added to have a starter but these 
need to be tested if and how well these work.


### Hardware interface MTP40-F  

Has TTL level RS232, I2C and PWM IO.

```
                        TOPVIEW MTP40-F
                       +-------------+
                       |             | 
    VCC (3v3 out)  5 --|             |-- 1 Vin
    TX             6 --|             |-- 2 GND
    RX             7 --|             |-- 3 ALARM
    NC             8 --|             |-- 4 PWM / I2C
    GND            9 --|             |
                       |             |
                       +-------------+
```

|  Pin  |  Name     |  Description                 |
|:-----:|:----------|:-----------------------------|
|   1   |  Vin      |  4.2V - 5.5V                 |
|   2   |  GND      |  idem                        |
|   3   |  ALARM    |  HIGH above 1000 PPM, LOW below 800 PPM (hysteresis) |
|   4   |  PWM/I2C  |  PWM out                     |
|   5   |  VCC_O    |  3V3 out for serial          |
|   6   |  TX       |  Transmit 9600 baud or SDA   |
|   7   |  RX       |  Receive 9600 baud or SCL    |
|   8   |  R/T      |  select I2C / Serial         |
|   9   |  GND      |  idem                        |


#### Links

- https://www.co2.earth/ - current outdoor CO2 level can be used for calibrating.
- https://keelingcurve.ucsd.edu/ - historical outdoor CO2 level.
- https://github.com/RobTillaart/MTP40C


## Interface

```cpp
#include "MTP40F.h"
```

#### Warnings

During tests with an UNO the communication over Software Serial did 
fail a few times.
Therefore it is important to **always check return values** 
to make your project more robust.

During tests it became clear that the sensor needs time to process 
commands e.g. **setSelfCalibration()**.

The CRC of the sensor responses are not verified by the library.


#### Constructors

- **MTP40F(Stream \* str)** constructor. should get a Serial port as parameter e.g. \&Serial, \&Serial1 
or a software Serial port. That Serial port must connect to the sensor. 
- **bool begin()** initialize the device.
Resets internal settings.
- **uint8_t getType()** returns type, see below.
Return 255 for the MTP40 base class.

|  Type  |  Model   |  Notes   |
|:------:|:--------:|:--------:|
|   2    |  MTP40C  |  for ref only
|   3    |  MTP40D  |  for ref only
|   5    |  MTP40F  |  
|  255   |  MTP40   |  for ref only


#### CO2 Measurement

- **uint16_t getGasConcentration()** returns the CO2 concentration in PPM (parts per million).
The function returns **MTP40_INVALID_GAS_LEVEL** if the request fails.
- **void suppressError(bool se)** sets or clears a flag that replaces the error value with 
the last read value if the request fails.
This is useful when plotting the values and one do not want a sudden spike.
One can still check **lastError()** to see if the value was OK.
- **bool getSuppressError()** gets the value of the suppress flag. 
- **int lastError()** returns last error set by **getGasConcentration()** 
or by **getAirPressureReference()** 
Reading resets internal error to MTP40F_OK;


#### Configuration

The library can set a maximum timeout in the communication with the sensor.
Normally this is not needed to set as the default of 100 milliseconds is long enough
for even the longest command. This timeout is needed if the sensor did not read the 
command correctly, preventing the host to wait indefinitely.
- **void setTimeout(uint32_t to = 100)** sets the timeout. 
If no parameter is given a default timeout of 100 milliseconds is set.
- **uint32_t getTimeout()** get the value set above or the default. 
Value returned is time in milliseconds.


## Calibration

Please read datasheet before using these functions to understand the process of calibration.

Note the outdoor calibration CO2 level differs per day and one should check 
a local airport or weather station for a good reference.

The University of San Diego keeps track of CO2 for a long time now.
See - https://keelingcurve.ucsd.edu/ 


#### Air pressure calibration

- **float getAirPressureReference()** returns the air pressure reference from the device.
Returns **MTP40F_INVALID_AIR_PRESSURE** in case request fails.
Default is 1013.0.
- **bool setAirPressureReference(float apr)** to calibrate the air pressure.
One can calibrate the sensor with an external device.
Value for air pressure should between 700.0 and 1100.0. 
The function returns **false** if the parameter is out of range or if the request fails.


#### SPC calibration

This takes a relative short time (few minutes) to calibrate the sensor in a known 
gas concentration. 

- **bool setSinglePointCorrection(uint32_t spc)** takes several minutes. see datasheet.
The parameter spc should be between 400 and 2000.
The function returns **false** if the parameter is out of range or if the request fails.
- **bool getSinglePointCorrectionReady()** To see if SPC is finished or not. 
The call also fails if the request fails.

As far as known the SPC point can not be retrieved from the sensor.


#### Self calibration

Self calibration is a process in which the sensor takes the minimum values over a longer period
between 24 - 720 hours as the reference for minimum outdoor values.
Note that 720 hours is 30 days / 1 month.

- **bool openSelfCalibration()** start the self calibration cycle.
- **bool closeSelfCalibration()** stop the self calibration cycle.
- **uint8_t getSelfCalibrationStatus()** Returns if the selfCalibration is open or closed.
**WARNING**: in our test the values in the datasheet seems to be not in sync with the sensor used. 
The function returned **0x00 for CLOSED and 0xFF for OPEN**.
- **bool setSelfCalibrationHours(uint16_t hrs)** Sets the number of hours between self calibration
moments. Valid values are 24 - 720 .
- **uint16_t getSelfCalibrationHours()** returns the value set above.


## Future

#### Must
- update documentation
  - reorder

#### Should 
- TODO in code
- ERROR handling.


#### Could 
- Performance
  - performance measurements
  - optimize performance if possible
  - caching? what?
  - seek optimum delay() between calls.
  - investigate wire length
- serial bus with multiple devices? => diodes
  - separate document
- improve readability code 
  - e.g. parameter names
- move all code from .h to .cpp file
- reuse command buffer as return buffer?
  - saves a bit.
- getAirPressureReference could be smarter 
  - always same value
  - from cache
  - dirty flag (-1);
- investigate timing of calls 
  - do they all need timeout of 4 seconds?

#### Wont

- store SPC point in the class?

