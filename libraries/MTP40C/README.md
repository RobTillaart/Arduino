
[![Arduino CI](https://github.com/RobTillaart/MTP40C/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MTP40C/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MTP40C/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MTP40C/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MTP40C/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MTP40C.svg)](https://github.com/RobTillaart/MTP40C/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MTP40C/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MTP40C.svg?maxAge=3600)](https://github.com/RobTillaart/MTP40C/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MTP40C.svg)](https://registry.platformio.org/libraries/robtillaart/MTP40C)


# MTP40C / MTP40D

Arduino library for MTP40C and MTP40D CO2 sensor.

(include image)


## Description

The library for the MTP40C / MTP40D CO2 sensor is experimental as not all functionality is tested.

Both the MTP40C and MTP40D sensor is an NDIR (Non Dispersive InfraRed) CO2 sensor.

The sensor communicates over a 19200 baud serial (TTL) interface with a microprocessor or PC. 
This implies that calls which can take up to 25 bytes can take as much as about 20 milliseconds.

On the other hand this low baud rate implies it will work over relative long distances.
This signal quality over longer distances is not investigated. 

The MTP40D has more interface options, I2C, PWM and ALARM. 
This library does not support these other interfaces for now.
However minimal examples are added to have a starter but these 
need to be tested if and how well these work.


### Hardware interface


#### MTP40-C

Has no I2C, only TTL level RS232.

```
               TOPVIEW MTP40-C
              +-------------+---+
              |             | O |
    Vin   1 --|             +---+
    GND   2 --|             |
    TX    3 --|             |
    RX    4 --|             |
    NC    5 --|             +---+
              |             | O |
              +-------------+---+
```

| Pin  | Name  | Description         |
|:----:|:------|:--------------------|
|  1   | Vin   | 4.2V--5.5V          |
|  2   | GND   | idem                |
|  3   | TX    | Transmit 19200 baud |
|  4   | RX    | Receive 19200 baud  |
|  5   | NC    | Not Connected       |


#### MTP40-D

Has TTL level RS232, I2C and PWM IO.

```
               TOPVIEW MTP40-D
              +-------------+
              |             | 
    VCC   5 --|             |-- 1 Vin
    TX    6 --|             |-- 2 GND
    RX    7 --|             |-- 3 ALARM
    NC    8 --|             |-- 4 PWM / I2C
    GND   9 --|             |
              |             |
              +-------------+
```

| Pin  | Name    | Description                 |
|:----:|:--------|:----------------------------|
|  1   | Vin     | 4.2V--5.5V                  |
|  2   | GND     | idem                        |
|  3   | ALARM   | HIGH above 2000 PPM, LOW below 1800 PPM (hysteresis) |
|  4   | PWM/I2C | PWM out or I2C select       |
|  5   | VCC_O   | 3V3 out for serial          |
|  6   | TX      | Transmit 19200 baud or SDA  |
|  7   | RX      | Receive 19200 baud or SCL   |
|  8   | NC      | Not Connected               |
|  9   | GND     | idem                        |


#### Related

- https://www.co2.earth/ - current outdoor CO2 level can be used for calibrating.
- https://keelingcurve.ucsd.edu/ - historical outdoor CO2 level.
- https://github.com/RobTillaart/MTP40F
- https://github.com/RobTillaart/MHZCO2  MHZ19 series
- https://github.com/RobTillaart/Cozir


## Interface

```cpp
#include "MTP40C.h"
```

#### Warnings

During tests with an UNO the communication over Software Serial did fail sometimes.
Therefore it is important to **always check return values** to make your project more robust.

During tests it became clear that the sensor needs time to process 
commands e.g. **setSelfCalibration()**. By having a delay(100) between the calls
everything ran far more stable (within my test). Todo seek optimum delay(), added in Future section below.

The CRC of the sensor responses are not verified by the library.


#### Constructors

- **MTP40(Stream \* str)** constructor. should get a Serial port as parameter e.g. \&Serial, \&Serial1. This is the base class.
- **MTP40C(Stream \* str)** constructor. should get a Serial port as parameter e.g. \&Serial, \&Serial1 
or a software Serial port. That Serial port must connect to the sensor. 
- **MTP40D(Stream \* str)** constructor. should get a Serial port as parameter e.g. \&Serial, \&Serial1 
or a software Serial port. That Serial port must connect to the sensor. 
- **bool begin(uint8_t address = 0x64)** initialize the device.
Sets the address to communicate to the sensor. Address values allowed 0 .. 247.
Uses the factory default value of 0x64 when no parameter is given.
Also resets internal settings.
- **bool isConnected()** returns true if the address as set by **begin()** 
or the default address of 0x64 (decimal 100) can be found on the Serial 'bus'.
- **uint8_t getType()** returns type, see below.
Return 255 for the MTP40 base class.

|  Type  |  Model   |  Notes   |
|:------:|:--------:|:--------:|
|   2    |  MTP40C  |
|   3    |  MTP40D  |
|  255   |  MTP40   |  base class


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
Reading resets internal error to MTP40_OK;


#### Configuration

- **uint8_t getAddress()** request the address from the device.
Expect a value from 0 .. 247.
Returns **MTP40_INVALID_ADDRESS** (0xFF) if the request fails.
- **bool setAddress(uint8_t address = 0x64)** set a new address for the device. 
0x64 as default. Returns false if not successful. 
If **setSpecificAddress()** is called, this specific address will be used for further commands.

These address functions are only needed if handling multiple devices. (to be tested)
- **void setGenericAddress()** uses the broadcast address 0xFE in all requests. 
This is the default behaviour of the library.
- **void setSpecificAddress()** uses the address specified in **begin()** or 
**setAddress()** or the default 0x64 in all requests.
- **bool useSpecificAddress()** returns true if the specific address is used.
Returns false if the generic / broadcast address is used.

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
Returns **MTP40_INVALID_AIR_PRESSURE** in case request fails.
Default is 1013.0.
- **bool setAirPressureReference(float apr)** to calibrate the air pressure.
One can calibrate the sensor with an external device.
Value for air pressure should between 700.0 and 1100.0. 
The function returns **false** if the parameter is out of range or if the request fails.


#### SPC calibration

This takes a relative short time (few minutes) to calibrate the sensor in a known 
gas concentration. 

- **bool setSinglePointCorrection(float spc)** takes several minutes. see datasheet.
spc should be between 400 and 5000.
The function returns **false** if the parameter is out of range or if the request fails.
- **bool getSinglePointCorrectionReady()** To see if SPC is finished or not. The call also fails if the request fails.

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

- documentation

#### Should

- CRC verify responses from sensor
- improve readability code (e.g. parameter names)
- move code from .h to .cpp file

#### Could

- performance measurements
- optimize performance
  - caching? what?
  - seek optimum delay() between calls.
- reuse cmd buffer as response buffer?
- investigate wire length
- investigate serial bus with multiple devices? 
  - diodes
  - multiplexer
- investigate commands in PROGMEM?

#### Wont (unless on request)


## Sponsor 

The development of this MTP40C library is sponsored by [TinyTronics, Netherlands](https://www.tinytronics.nl/shop/nl).


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

