
[![Arduino CI](https://github.com/RobTillaart/MTP40C/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![JSON check](https://github.com/RobTillaart/MTP40C/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MTP40C/actions/workflows/jsoncheck.yml)
[![Arduino-lint](https://github.com/RobTillaart/MTP40C/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MTP40C/actions/workflows/arduino-lint.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MTP40C/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MTP40C.svg?maxAge=3600)](https://github.com/RobTillaart/MTP40C/releases)

# MTP40C

Arduino library for MTP40C CO2 + air pressure sensor.

(include image)

## Description

The library for the MTP40C CO2 sensor is experimental as not all functionality is tested.

The MTP40C is an NDIR (Non Dispersive InfraRed) CO2 sensor.

The sensor communicates over a 19200 baud serial (TTL) interface with a microprocessor or PC. 
This implies that calls which can take up to 25 bytes can take as much as about 20 milliseconds.

Detailed performance measurements are planned for the future.


### Hardware interface

```
               // TOPVIEW
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

| Pin   | Description         |
|:------|:--------------------|
| Vin   | 4.2V--5.5V          |
| GND   | idem                |
| TX    | Transmit 19200 baud |
| RX    | Receive 19200 baud  |
| NC    | Not Connected       |



## Interface


### Constructors

- **MTP40C(Stream \* str)** constructor. should get a Serial port as parameter e.g. \&Serial, \&Serial1 
or a software Serial port. That Serial port must connect to the sensor. 
- **bool begin(uint8_t address = 0x64)** initialize the device.
Sets the address to communicate to the sensor. Address values allowed 0..247.
Uses the factory default value of 0x64 when no parameter is given.
Also resets internal settings.
- **bool isConnected()** returns true if the address as set by **begin()** or the default address of 0x64
(decimal 100) can be found on the Serial 'bus'.


### Configuration

- **uint8_t getAddress()** request the address from the device.
Expect a value from 0 .. 247.
Returns **MTP40C_INVALID_ADDRESS** (0xFF) if the request fails.
- **bool setAddress(uint8_t address)** set a new address for the device. 
Returns false if not successful. If set this specific address will be used for the commands.

These address functions are only needed if handling multiple devices. (to be tested)
- **void setGenericAddress()** uses the broadcast address 0xFE in all requests. This is the default behaviour of the library.
- **void setSpecificAddress()** uses the address specified in **begin()** or **setAddress()** or the default 0x64 
in all requests.
- **bool useSpecificAddress()** returns true if the specific address is used.
Returns false if the generic / broadcast address is used.

The MTP40C library can set a maximum timeout in the communication with the sensor.
Normally this is not needed to set as the default of 100 milliseconds is long enough.
- **void setTimeout(uint32_t to = 100)** sets the timeout. If no parameter is given a default timeout of 100 milliseconds is set.
- **uint32_t getTimeout()** get the value set above or the default. Value returned is time in milliseconds.


### Measurements

- **float getAirPressure()** returns the air pressure from the device.
Returns **MTP40C_INVALID_AIR_PRESSURE** (0) in case request fails.
- **bool setAirPressureReference(float apr)** to calibrate the air pressure one can calibrate 
the sensor with an external device.
Value should between 700.0 and 1100.0. 
The function returns **false** if the parameter is out of range or if the request fails.
- **uint16_t getGasConcentration()** returns the CO2 concentration in PPM (parts per million).
The function returns **MTP40C_INVALID_GAS_LEVEL** (0) if the request fails.

Note: there is no **getAirPressureReference()** command documented.


### Calibration

Please read datasheet before using these functions to understand the process of calibration.


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
between 24 - 720 hours as the reference for minimum outdoor values. (CHECK).
Note that 720 hours is 30 days / 1 month.

- **bool openSelfCalibration()** start the self calibration cycle. CHECK
- **bool closeSelfCalibration()** stop the self calibration cycle. CHECK
- **uint8_t getSelfCalibrationStatus()** CHECK.
- **bool setSelfCalibrationHours(uint16_t hrs)** Sets the number of hours between self calibration
moments. Valid values are 24 - 720 .
- **uint16_t getSelfCalibrationHours()** returns the value set above.


## Future

- test test test test
- CRC in PROGMEM
- performance measurements
- optimize performance
- optimize memory usage  (buffer)
- caching? what?
- serial bus with multiple devices? => diodes
- add improved error handling. e.g. **MTP40C_REQUEST_FAILS**


## Operations

See examples.


## Sponsor 

The development of this MTP40C library is sponsored by [TinyTronics, Netherlands](https://www.tinytronics.nl/shop/en).
