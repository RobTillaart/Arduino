
[![Arduino CI](https://github.com/RobTillaart/MS5611_SPI/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MS5611_SPI/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MS5611_SPI/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MS5611_SPI/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MS5611_SPI/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MS5611_SPI.svg)](https://github.com/RobTillaart/MS5611_SPI/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MS5611_SPI/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MS5611_SPI.svg?maxAge=3600)](https://github.com/RobTillaart/MS5611_SPI/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MS5611_SPI.svg)](https://registry.platformio.org/libraries/robtillaart/MS5611_SPI)


# MS5611_SPI

Arduino library (SPI) for MS5611 pressure and temperature sensor.


## Description

**WARNING: the MS5611 has problems with self heating when using SPI interface so use with care.**

The MS5611 is a high resolution pressure and temperature sensor a.k.a GY-63.
The high resolution is made possible by oversampling many times.

This library only implements the SPI interface.
It is based upon the 0.3.6 version of the I2C library, 
see - https://github.com/RobTillaart/MS5611

If you know a cause or better a solution to the self heating effect, 
please let me know (open an issue).


#### 0.3.0 Breaking change

Version 0.3.0 introduced a breaking change to improve handling the SPI dependency.
The user has to call **SPI.begin()** or equivalent before calling **AD.begin()**.
Optionally the user can provide parameters to the **SPI.begin(...)**


#### 0.2.0 Breaking change

The version 0.2.0 has breaking changes in the interface. 
The essence is removal of ESP32 specific code from the library. 
This makes it possible to support the ESP32-S3 and other processors in the future. 
Also it makes the library a bit simpler to maintain.


#### Compatibility

The library should be compatible with MS56XX, MS57xx and MS58xx devices (to be tested). 

Note: Some device types will return only 50% of the pressure value. 
This is solved by calling **reset(1)** to select the math used.


#### Self heating problem

In some configurations especially when using SPI the sensor showed a self heating effect. 
First this was approached as a problem, so investigations were done to understand the 
cause and how to solve it. During this process the view changed of seeing the higher 
temperature as a problem to being the solution. 

The sensor is primary a pressure sensor and if it is heated by a cause (don't care) 
it needs compensation. For that the temperature sensor is build in the device. 
Depending on the configuration self heating can be as low as 0.1°C to as high as 10++ °C.

**WARNING** One should **NOT** use 5V to control I2C address line, SPI select, or 
the protocol select line. This causes extreme heat build up > 10°C. 

**One should only use 3V3 lines for these "selection lines".**

See also - https://github.com/RobTillaart/MS5611_SPI/issues/3

Note: the self heating offset can be compensated with **setTemperatureOffset(offset)**
which allows you to match the temperature with the ambient temperature again.
As the self heating effect is not expected to be linear over the full range of the
temperature sensor the offset might work only in a smaller range.
To have a reliable ambient temperature it is advised to use an 
dedicated temperature sensor for this (e.g. DS18B20).


#### Breakout GY-63

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

#### Related libraries

- https://github.com/RobTillaart/MS5611 - I2C version - working OK.
- https://github.com/RobTillaart/pressure - conversions.
- https://github.com/RobTillaart/Temperature - conversions.


## WARNING EXPERIMENTAL

Note: This library is under development.

SPI communication works and reasonable values are read, at least for pressure.

All SPI tests so far gave too high temperatures, some were rising slowly, others faster.
Values are read correctly but somehow the selection of SPI as protocol seems to cause internal heating.

This self heating has been confirmed and is discussed - https://github.com/RobTillaart/MS5611_SPI/issues/3

Some results of experiments:

| Platform        | tested | time (us)| Notes   |
|:----------------|-------:|:--------:|--------:|
|  UNO SW SPI     |  fail  |          | temperature is rising very fast (stopped)  ==> DO NOT USE 5V 
|  UNO HW SPI     |  fail  |          | no data, 
|  ESP32 SW SPI V |   Y    |   1299   | VSPI pins; temperature is rising slowly
|  ESP32 SW SPI H |   Y    |   1298   | HSPI pins; temperature too high (+3) but stable
|  ESP32 HSPI     |   Y    |   1396   | temperature is rising slowly and stabilizes
|  ESP32 VSPI     |   Y    |   1395   | temperature is rising slowly and stabilizes
|  NANO 33 SW SPI |   -    |    -     | not tested yet
|  NANO 33 HW SPI |   -    |    -     | not tested yet


#### Note UNO

For VCC 3V3 was used as the other pins CLK and SDI have a voltage converter in the GY-63.
- Unclear why HW SPI blocks for UNO. 
- The 5V voltage is definitely too high for the sensor, but protocol wise it was expected to work.
- it might be a timing issue as the ESP32 showed some improvement when "fiddle the timing"


#### Note ESP32 

H-SPI pins: 
- not reliable at start, incorrect PROM reads, both HW and SW. 
- adjusting the timing improves this a bit.
- these pins also interfere with uploading sketches. 


#### Conclusion for now

There are a few open ends to investigate.
- investigate an UNO with a level converter (for selection pins)
- investigate timing (clock) of the SPI. (both ESP and UNO)

If you have experiences with this library please share them in the issues.


## Interface

```cpp
#include "MS5611_SPI.h"
```

#### Base

- **MS5611_SPI(uint8_t select, SPIClassRP2040 \* myspi = &SPI)** constructor, HW SPI RP2040.
- **MS5611_SPI(uint8_t select, SPIClass \* myspi = &SPI)** constructor, HW SPI other.
- **MS5611_SPI(uint8_t select, uint8_t dataOut, uint8_t dataIn, uint8_t clock)** constructor, SW SPI
- **bool begin()** initializes internals,
- **bool isConnected()** checks device by calling **read()**.
- **bool reset(uint8_t mathMode = 0)** resets the chip and loads constants from its ROM.
Returns false if ROM could not be read.
  - mathMode = 0 follows the datasheet math (default).
  - mathMode = 1 will adjust for a factor 2 in the pressure math.
- **int read(uint8_t bits)** the actual reading of the sensor. 
Number of bits determines the oversampling factor. Returns MS5611_READ_OK upon success.
- **int read()** wraps the **read()** above, uses the preset oversampling (see below). 
Returns MS5611_READ_OK upon success.
- **float getTemperature()** returns temperature in °C. 
Subsequent calls will return the same value until a new **read()** is called.
- **float getPressure()** pressure is in mBar. 
Subsequent calls will return the same value until a new **read()** is called.


#### Oversampling

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


#### Offset 

The offset functions are added (0.3.6) to calibrate the sensor against e.g. a local weather station. 
This calibration can only be done runtime.

- **void setPressureOffset(float offset = 0)** Set an offset to calibrate the pressure. 
Can be used to get the pressure relative to e.g. 1 Atm. 
Set the offset to -1013 HPa/mBar and you get a sort of relative pressure.
Default the offset is set to 0.
- **float getPressureOffset()** returns the current pressure offset.
- **void setTemperatureOffset(float offset = 0)** Set an offset to calibrate the temperature. 
Can be used to get the temperature in degrees Kelvin, just set the offset to +273.15.
Default the offset is set to 0.
- **float getTemperatureOffset()** returns the current temperature offset.


#### Misc

- **int getLastResult()** checks last I2C communication. Replace with more informative error handling?
- **uint32_t lastRead()** last time when **read()** was called in milliseconds since startup.


#### DeviceID

- **uint32_t getDeviceID()** returns the hashed values of the calibration PROM. 
As these calibration are set in the factory and differ (enough) per sensor these can serve as an unique deviceID.

Having a device-ID can be used in many ways:
- use known offsets for each sensor automatically, 
- work as an identification of that specific copy of the project (customer specific tracking).
- ID in a mesh network
- etc.

Note: this is not an official ID from the device / datasheet, it is made up from calibration data.


#### getManufacturer

The meaning of the manufacturer and serialCode value is unclear.
- **uint16_t getManufacturer()** returns manufacturer private info.
- **uint16_t getSerialCode()** returns serialCode from the PROM\[6].


#### 2nd order pressure compensation

- **setCompensation(bool flag = true)** to enable/disable the 2nd order compensation. 
The default = true. 
Disabling the compensation will be slightly faster but you loose precision.
- **getCompensation()** returns flag set above.


#### SPI functions

// to be tested.

- **void setSPIspeed(uint32_t speed)**
- **uint32_t getSPIspeed()**
- **bool usesHWSPI()**


#### SPI - ESP32 specific

// to be tested.

- **void selectHSPI()**
- **void selectVSPI()**
- **bool usesHSPI()**
- **bool usesVSPI()**
- **void setGPIOpins(uint8_t clk, uint8_t miso, uint8_t mosi, uint8_t select)**


## Operation

See examples


## Future

#### Must

- update documentation
- follow I2C library.
- investigate internal heating with SPI.

#### Should

- proper error handling.

#### Could

- redo lower level functions?
- handle the read + math of temperature first?

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


