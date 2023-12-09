
[![Arduino CI](https://github.com/RobTillaart/SHT31/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/SHT31/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/SHT31/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/SHT31/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/SHT31/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/SHT31.svg)](https://github.com/RobTillaart/SHT31/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/SHT31/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/SHT31.svg?maxAge=3600)](https://github.com/RobTillaart/SHT31/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/SHT31.svg)](https://registry.platformio.org/libraries/robtillaart/SHT31)


# SHT31

Arduino library for the SHT31 temperature and humidity sensor.

Relates to the SHT85 library - https://github.com/RobTillaart/SHT85


## Description

The SHT3x family of sensors should work up to 1 MHz I2C

This library should also work for SHT30 and SHT35 but these are 
not tested yet.

Accuracy table

|  SENSOR  |  Temperature  |  Humidity  |
|:--------:|:-------------:|:----------:|
|  SHT30   |  ~0.3         |  2.0       |
|  SHT31   |  ~0.3         |  1.5       |
|  SHT35   |  ~0.2         |  1.5       |
|  SHT85   |  ~0.2         |  1.5       |


An elaborated library for the SHT31 sensor can be found here
- https://github.com/hawesg/SHT31D_Particle_Photon_ClosedCube

A derived class for using the SHT31 sensor with SoftWire (soft I2C) can be found here
- https://github.com/RobTillaart/SHT31_SW


#### 0.5.0 Breaking change

Version 0.5.0 introduced a breaking change.
You cannot set the pins in **begin()** any more.
This reduces the dependency of processor dependent Wire implementations.
The user has to call **Wire.begin()** and can optionally set the Wire pins 
before calling **begin()**.


#### Related

- https://github.com/RobTillaart/SHT31
- https://github.com/RobTillaart/SHT31_SW
- https://github.com/RobTillaart/SHT31_SWW
- https://github.com/RobTillaart/SHT85


## Interface

```cpp
#include "SHT31.h"
```

#### Constructor

- **SHT31(uint8_t address = SHT_DEFAULT_ADDRESS, TwoWire \*wire = &Wire)** constructor. 
Optional select address and the I2C bus (Wire, Wire1 etc).
- **bool begin()** 
Returns false if device address is incorrect or device cannot be reset.
- **bool isConnected()** check sensor is reachable over I2C. Returns false if not connected.
- **uint8_t getAddress()** returns address set in the constructor.


#### Read

- **bool read(bool fast = true)** blocks 4 (fast) or 15 (slow) milliseconds + actual read + math.
Does read both the temperature and humidity.
- **uint16_t readStatus()** details see datasheet and **Status fields** below.
- **uint32_t lastRead()** in milliSeconds since start of program.
- **bool reset(bool hard = false)** resets the sensor, soft reset by default. Returns false if it fails.
- **float getHumidity()** computes the relative humidity in % based on the latest raw reading, and returns it.
- **float getTemperature()** computes the temperature in °C based on the latest raw reading, and returns it.
- **float getFahrenheit()** computes the temperature in °F based on the latest raw reading, and returns it..
- **uint16_t getRawHumidity()** returns the raw two-byte representation of humidity directly from the sensor.
- **uint16_t getRawTemperature()** returns the raw two-byte representation of temperature directly from the sensor.

Note that the temperature and humidity values are recalculated on every call to getHumidity() and getTemperature(). 
If you're worried about the extra cycles, you should make sure to cache these values or only request them after 
you've performed a new reading.


#### Error interface

- **int getError()** returns last set error flag and clear it. 
Be sure to clear the error flag by calling **getError()** before calling any command as the error flag could be from a previous command.

|  Error  |  Symbolic                   |  Description                  |
|:-------:|:----------------------------|:------------------------------|
|  0x00   |  SHT31_OK                   |  no error                     |
|  0x81   |  SHT31_ERR_WRITECMD         |  I2C write failed             |
|  0x82   |  SHT31_ERR_READBYTES        |  I2C read failed              |
|  0x83   |  SHT31_ERR_HEATER_OFF       |  Could not switch off heater  |
|  0x84   |  SHT31_ERR_NOT_CONNECT      |  Could not connect            |
|  0x85   |  SHT31_ERR_CRC_TEMP         |  CRC error in temperature     |
|  0x86   |  SHT31_ERR_CRC_HUM          |  CRC error in humidity        |
|  0x87   |  SHT31_ERR_CRC_STATUS       |  CRC error in status field    |
|  0x88   |  SHT31_ERR_HEATER_COOLDOWN  |  Heater need to cool down     |
|  0x88   |  SHT31_ERR_HEATER_ON        |  Could not switch on heater   |


#### Heater interface

**WARNING:** Do not use heater for long periods. 

Use the heater for max **180** seconds, and let it cool down **180** seconds = 3 minutes. 
Version 0.3.3 and up guards the cool down time by preventing switching the heater on 
within **180** seconds of the last switch off. Note: this guarding is not reboot persistent. 

**WARNING:** The user is responsible to switch the heater off manually!

The class does **NOT** do this automatically.
Switch off the heater by directly calling **heatOff()** or indirectly by calling **isHeaterOn()**.

- **void setHeatTimeout(uint8_t seconds)** Set the time out of the heat cycle.
This value is truncated to max 180 seconds. 
- **uint8_t getHeatTimeout
- **bool heatOn()** switches heat cycle on if not already on.
Returns false if fails, setting error to **SHT31_ERR_HEATER_COOLDOWN** 
or to **SHT31_ERR_HEATER_ON**. 
- **bool heatOff()** switches heat cycle off. 
Returns false if fails, setting error to **SHT31_ERR_HEATER_OFF**.
- **bool isHeaterOn()** is the sensor still in heating cycle? replaces **heatUp()**.
Will switch the heater off if max heating time has passed. 
- **bool heatUp()** will be obsolete in the future. replaced by **isHeaterOn()**


#### Async interface

See async example for usage

- **bool requestData()** requests a new measurement. Returns false if this fails.
- **bool dataReady()** checks if enough time has passed to read the data. (15 milliseconds)
- **bool readData(bool fast = true)** fast = true skips the CRC check. 
Returns false if reading fails or in case of a CRC failure. 


## Status fields

|  BIT  |  Description                 |  value  |  notes  |
|:------|:-----------------------------|:--------|:--------|
|  15   |  Alert pending status        |  0      | no pending alerts
|       |                              |  1      | at least one pending alert - default
|  14   |  Reserved                    |  0      |
|  13   |  Heater status               |  0      | Heater OFF - default
|       |                              |  1      | Heater ON 
|  12   |  Reserved                    |  0      |
|  11   |  Humidity tracking alert     |  0      | no alert - default
|       |                              |  1      | alert
|  10   |  Temperature tracking alert  |  0      | no alert - default
|       |                              |  1      | alert
|  9-5  |  Reserved                    |  00000  |
|   4   |  System reset detected       |  0      | no reset since last ‘clear status register’ command
|       |                              |  1      | reset detected (hard or soft reset command or supply fail) - default
|  3-2  |  Reserved                    |  00     |
|   1   |  Command status              |  0      | last command executed successfully
|       |                              |  1      | last command not processed. Invalid or failed checksum
|   0   |  Write data checksum status  |  0      | checksum of last write correct
|       |                              |  1      | checksum of last write transfer failed



## Operation

See examples.


## Future

#### Must

- keep in sync with SHT85 library.
- keep derived SHT31_SW builds green

#### Should

- check TODO in code.
- rename MAGIC numbers.  e.g. in dataReady()

#### Could

- move code from .h to .cpp

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


