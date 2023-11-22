
[![Arduino CI](https://github.com/RobTillaart/SHT31_SW/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/SHT31_SW/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/SHT31_SW/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/SHT31_SW/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/SHT31_SW/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/SHT31_SW.svg)](https://github.com/RobTillaart/SHT31_SW/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/SHT31_SW/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/SHT31_SW.svg?maxAge=3600)](https://github.com/RobTillaart/SHT31_SW/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/SHT31_SW.svg)](https://registry.platformio.org/libraries/robtillaart/SHT31_SW)


# SHT31_SW

Arduino library for the SHT31 temperature and humidity sensor - using **SoftWire**.


## Description

This **experimental** library features the class SHT31_SW derived from - https://github.com/RobTillaart/SHT31.
It has the same interface as the SHT31 class so please use that documentation 
as it will be the "leading class".

The main difference is that the SHT31_SW class uses the **SoftWire** library 
for communication instead of the **TwoWire** based **Wire** class.
See SHT31 PR #35.

**SoftWire** is a software I2C bus library to be able to select other pins 
than the default (AVR) hardware I2C pins (SDA and SCL).
An important reason to use this version is when you want more than two 
devices on one Arduino.


#### SoftWire vs SoftwareWire

The **SoftWire** library is portable, however it could not read (on AVR)
the SHT85 sensor which is command compatible with the SHT3x.
The cause is not found yet.
Therefore a separate repo is created based upon the AVR specific **SoftwareWire**
see links below. 
If you know a solution to get softWire working on AVR, please let me know.

The **SoftwareWire** library is an AVR specific and worked for the SHT85.
See https://github.com/RobTillaart/SHT31_SW/issues/5


#### SHT3x SHT85 sensors

The SHT3x family of sensors should work up to 1 MHz I2C although not tested above 400 MHz.

This library should also work for SHT30/35/85 but these are not tested yet.

Test on UNO

|  SENSOR  |  Temperature  |  Humidity  |  works         |
|:--------:|:-------------:|:----------:|:---------------|
|  SHT30   |  ~0.3         |  2.0       |  (not tested)  |
|  SHT31   |  ~0.3         |  1.5       |  yes           |
|  SHT35   |  ~0.2         |  1.5       |  (not tested)  |
|  SHT85   |  ~0.2         |  1.5       |  no            |  See SHT31_SWW


#### Related

These libraries need to be installed to get SHT31_SW working:

- https://github.com/RobTillaart/SHT31
- https://github.com/stevemarple/AsyncDelay
- https://github.com/stevemarple/SoftWire

Related
- https://github.com/Testato/SoftwareWire      //   AVR only


## Interface

```cpp
#include "SHT31_SW.h"
```

Note: The interface is mostly inherited from SHT31 but presented here for completeness.


#### Base interface

- **SHT31_SW()** constructor.
- **bool begin(uint8_t address, SoftWire \*wire = &Wire)** for platforms with multiple I2C buses.
- **bool begin(SoftWire \*wire = &Wire)** same as above. With default SHT_DEFAULT_ADDRESS.
- **bool read(bool fast = true)** blocks 4 (fast) or 15 (slow) milliseconds + actual read + math.
Does read both the temperature and humidity.
- **bool isConnected()** check sensor is reachable over I2C. Returns false if not connected.
- **uint16_t readStatus()** details see datasheet and **Status fields** below.
- **uint32_t lastRead()** in milliSeconds since start of program.
- **bool reset(bool hard = false)** resets the sensor, soft reset by default. Returns false if it fails.
- **float getHumidity()** computes the relative humidity in % based on the latest raw reading, and returns it.
- **float getTemperature()** computes the temperature in °C based on the latest raw reading, and returns it.
- **float getFahrenheit()** computes the temperature in °F based on the latest raw reading, and returns it.
- **uint16_t getRawHumidity()** returns the raw two-byte representation of humidity directly from the sensor.
- **uint16_t getRawTemperature()** returns the raw two-byte representation of temperature directly from the sensor.

Note that the temperature and humidity values are recalculated on every call to **getHumidity()** and **getTemperature()**. 
If you're worried about the extra cycles, you should make sure to cache these values or only request them after 
you've performed a new reading.


#### Error interface

- **int getError()** returns last set error flag and clear it. 
Be sure to clear the error flag by calling **getError()** before calling 
any command as the error flag could be from a previous command.

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
SHT31 version 0.3.3 and up guards the cool down time by preventing switching the heater on 
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


## Future

#### Must

- keep in sync with (leading) SHT31 and SHT31_SWW library.

#### Should

- remove script for atomic if not needed any more.
- investigate why SHT85 does not work with SoftWire.

#### Could

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

