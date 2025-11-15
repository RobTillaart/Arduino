
[![Arduino CI](https://github.com/RobTillaart/MS5611/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MS5611/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MS5611/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MS5611/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MS5611/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MS5611.svg)](https://github.com/RobTillaart/MS5611/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MS5611/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MS5611.svg?maxAge=3600)](https://github.com/RobTillaart/MS5611/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MS5611.svg)](https://registry.platformio.org/libraries/robtillaart/MS5611)


# MS5611

Arduino library (I2C) for MS5611 temperature and pressure sensor.


## Description

The MS5611-01BA03 is a high resolution pressure and temperature sensor a.k.a GY-63.
The high resolution is made possible by oversampling many times.

The device address is 0x76 or 0x77 depending on the CSB/CSO pin.

This library only implements the I2C interface. 
An experimental SPI version of the library can be found here 
- https://github.com/RobTillaart/MS5611_SPI

A derived I2C library for the STM32 can be found here
- https://github.com/Zakrzewiaczek/ms5611-stm32

Feedback as always is welcome.


### Compatibility

The library should be compatible with MS56XX, MS57xx and MS58xx devices (to be tested). 

Note: Some device types will return only 50% of the pressure value. 
This is solved by calling **reset(1)** to select the math method used.


### Self heating problem

In some configurations especially when using SPI the sensor showed a self heating effect. 
First this was approached as a problem, so investigations were done to understand the 
cause and how to solve it. During this process the view changed of seeing the higher 
temperature as a problem to being the solution. 

The sensor is primary a pressure sensor and if it is heated by a cause (don't care) 
it needs compensation. For that the temperature sensor is build in the device. 
Depending on the configuration self heating can be as low as 0.1 °C to as high as 10++ °C.

**WARNING** One should **NOT** use 5V to control I2C address line, SPI select, or 
the protocol select line. This causes extreme heat build up > 10 °C. 

**One should only use 3V3 lines for these "selection lines".**

See also - https://github.com/RobTillaart/MS5611_SPI/issues/3

Note: the self heating offset can be compensated with **setTemperatureOffset(offset)**
which allows you to match the temperature with the ambient temperature again.
As the self heating effect is not expected to be linear over the full range of the
temperature sensor the offset might work only in a smaller range.
To have a reliable ambient temperature it is advised to use an dedicated temperature 
sensor for this (e.g. DS18B20).


### Breakout GY-63

```cpp
//
//  BREAKOUT  MS5611  aka  GY63 - see datasheet
//
//  SPI    I2C
//              +--------+
//  VCC    VCC  | o      |
//  GND    GND  | o      |
//         SCL  | o      |
//  SDI    SDA  | o      |
//  CSO         | o      |
//  SDO         | o L    |   L = led
//          PS  | o    O |   O = opening  PS = protocol select
//              +--------+
//
//  PS to VCC  ==>  I2C  (GY-63 board has internal pull up, so not needed)
//  PS to GND  ==>  SPI
//  CS to VCC  ==>  0x76
//  CS to GND  ==>  0x77
//
```

## I2C

The device address is 0x76 or 0x77 depending on the CSB/CSO pin.


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


### Related libraries

- https://github.com/RobTillaart/pressure - pressure conversions
- https://github.com/RobTillaart/Temperature - temperature conversions 
- https://github.com/RobTillaart/MS5837 - temperature pressure sensor 
- https://github.com/RobTillaart/MS5611
- https://github.com/RobTillaart/MS5611_SPI
- https://github.com/RobTillaart/MSP300 - industrial pressure transducer
- https://swharden.com/blog/2017-04-29-precision-pressure-meter-project/
- https://github.com/Zakrzewiaczek/ms5611-stm32 - derived library for STM32 boards.


## Release Notes (major)

### 0.3.0 breaking change

- fixed math error so previous versions are **obsolete**.
- temperature is a float expressed in degrees Celsius.
- pressure is a float expressed in mBar.


### 0.3.5 NANO 33 BLE

The I2C/Wire library of the NANO 33 BLE does not see the device on the I2C bus. 
After hours of testing it looks like that the I2C/Wire library of the NANO 33 BLE 
does not handle **isConnected()** like other platforms do. 
Adding a **wire->write(0x00)** in **isConnected()** fixes the problem, 
however more investigation is needed to understand the root cause.


### 0.3.9 pressure math 

There are MS5611 compatibles for which the math for the pressure is different.
See **AN520__004: C-code example for MS56xx, MS57xx (except analog sensor), and MS58xx series pressure sensors**
The difference is in the constants (powers of 2) used to calculate the pressure.

The library implements **reset(uint8_t mathMode = 0)** to select the mathMode.
- mathMode = 0 ==> datasheet type math  (default)
- mathMode = 1 ==> Application notes type math.
- other values will act as 0

See issue #33.


### 0.4.0 breaking change

refactored the Wire dependency. Affected are:
- constructor
- begin()

User has to call **Wire.begin()** (or equivalent) and optional set the I2C pins
before calling **ms5611.begin()** to initialize the library.


### 0.5.0 Breaking change

As the getAltitude() function had a bug it is advised to use version 0.5.0 or up.
Older versions are considered obsolete.


## Interface MS5611

```cpp
#include "MS5611.h"
```

### Base

- **MS5611(uint8_t deviceAddress = MS5611_DEFAULT_ADDRESS, TwoWire \*wire = &Wire)** constructor.
Since 0.3.7 a default address 0x77 is added. Optionally one can set the Wire interface.
- **bool begin()** Initializes internals, by calling reset().
Return false indicates either isConnected() error or reset() error.  
One must call **Wire.begin()** (or equivalent) before calling **begin()**.
- **bool isConnected()** checks availability of the device address set in the constructor 
on the I2C bus. 
(see note above NANO 33 BLE).
- **bool reset(uint8_t mathMode = 0)** resets the MS5611 device and loads the internal constants 
from its ROM. 
Returns false if ROM could not be read.
  - mathMode = 0 follows the datasheet math (default).
  - mathMode = 1 will adjust for a factor 2 in the pressure math.


### Read

- **int read(uint8_t bits)** does the actual reading of the sensor. 
Number of bits determines the oversampling factor. Returns MS5611_READ_OK upon success.
- **int read()** wraps the **read()** above, uses the preset oversampling (see below). 
Returns MS5611_READ_OK upon success.
- **float getTemperature()** returns temperature in degrees °C. 
Subsequent calls will return the same value until **read()** is called again.
- **float getPressure()** returns pressure in mBar. 
Subsequent calls will return the same value until **read()** is called again.
- **float getPressurePascal()** returns pressure in Pascal (SI-unit).
(1 pascal = 1 newton per square metre, 1 N/m2)
Subsequent calls will return the same value until **read()** is called again.

Return values of -9.99 or -999 indicate read error.


### Oversampling

- **void setOversampling(osr_t samplingRate)** sets the amount of oversampling. 
See table below and test example how to use.
- **osr_t getOversampling()** returns amount of oversampling.


Some numbers from datasheet, page 3 MAX column rounded up. (see #23)
(actual read time differs - see performance sketch)

| definition     | value | oversampling ratio | resolution (mbar) | time (us) | notes  |
|:--------------:|:-----:|:------------------:|:-----------------:|:---------:|:------:|
| OSR_ULTRA_HIGH |  12   |        4096        |      0.012        |   9100    |
| OSR_HIGH       |  11   |        2048        |      0.018        |   4600    |
| OSR_STANDARD   |  10   |        1024        |      0.027        |   2300    |
| OSR_LOW        |  9    |        512         |      0.042        |   1200    |
| OSR_ULTRA_LOW  |  8    |        256         |      0.065        |    600    | Default = backwards compatible


### Offset 

The offset functions are added (0.3.6) to calibrate the sensor against e.g. a local weather station. 
This calibration can only be done runtime.

- **void setPressureOffset(float offset = 0)** Set an offset in mBar to calibrate the pressure. 
Can be used to get the pressure relative to e.g. 1 Atm. 
Set the offset to -1013 HPa/mBar and you get a sort of relative pressure.
Default the offset is set to 0.
- **float getPressureOffset()** returns the current pressure offset in mBar.
- **void setTemperatureOffset(float offset = 0)** Set an offset in degrees C to calibrate the temperature. 
Can be used to get the temperature in degrees Kelvin, just set the offset to +273.15.
Default the offset is set to 0.
- **float getTemperatureOffset()** returns the current temperature offset in degrees C..


### Altitude

- **float getAltitude(float airPressure = 1013.25)** calculates the altitude,
based upon actual pressure measured and the current pressure at sea level (parameter airPressure).
Returns the altitude in meters.
Multiple calls will return the same altitude until a new pressure is **read()**.
- **float getAltitudeFeet(float airPressure)** idem but returns altitude in feet.
- **float getSeaLevelPressure(float pressure, float altitude)** inverse function of **getAltitude()**.
This function can be used to determine a reference air pressure for the getAltitude() function when
you are at a defined altitude and you measured the local pressure with **getPressure()**.
So think of it as calibration-tool for the reference pressure in getAltitude().


### Misc

- **int getLastResult()** checks last I2C communication. Replace with more informative error handling?
- **uint32_t lastRead()** last time when **read()** was called in milliseconds since startup.


### DeviceID

- **uint32_t getDeviceID()** returns the hashed values of the calibration PROM. 
As these calibration are set in the factory and differ (enough) per sensor these can serve as an unique deviceID.

Having a device-ID can be used in many ways:
- use known offsets for each sensor automatically, 
- work as an identification of that specific copy of the project (customer specific tracking).
- ID in a mesh network
- etc.

Note: this is not an official ID from the device / datasheet, it is made up from calibration data.
Expected to be random enough if you have to "track" multiple devices.


### getManufacturer

The meaning of the manufacturer and serialCode value is unclear. 
No reference found to these PROM fields. 

- **uint16_t getManufacturer()** returns manufacturer private info.
- **uint16_t getSerialCode()** returns serialCode from the PROM\[7] minus the CRC.


### Develop functions

- **uint16_t getProm(uint8_t index)** returns PROM\[index].
- **uint16_t getCRC()** returns CRC code from the PROM\[7].


### 2nd order pressure compensation

- **setCompensation(bool flag = true)** to enable/disable the 2nd order compensation. 
The default = true. 
Disabling the compensation will be slightly faster but you loose precision.
- **getCompensation()** returns flag set above.

----

## Interface MS5607

Interface is very identical to the MS5611.

- **MS5607(uint8_t deviceAddress, TwoWire \*wire = &Wire)** constructor.
Address = 0x76 or 0x77, it has no default. Optionally one can set the Wire interface.
- **bool begin()**
Initializes internals by calling reset() to set correct mathMode.
Return false indicates either isConnected() error or reset() error.  


## Future

#### Must

- update documentation
- sync with MS5611_SPI library

#### Should

- add / improve error handling.

#### Could

- define derived classes per device type
  - MS56XX, MS57xx and MS58xx?
  - add correct math
- redo lower level functions?
- handle the read + math of temperature first?
- find meaning PROM values, esp. 0 and 7
- add function to verify the CRC of the PROM


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

