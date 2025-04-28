
[![Arduino CI](https://github.com/RobTillaart/SHT31_SWW/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/SHT31_SWW/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/SHT31_SWW/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/SHT31_SWW/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/SHT31_SWW/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/SHT31_SWW.svg)](https://github.com/RobTillaart/SHT31_SWW/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/SHT31_SWW/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/SHT31_SWW.svg?maxAge=3600)](https://github.com/RobTillaart/SHT31_SWW/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/SHT31_SWW.svg)](https://registry.platformio.org/libraries/robtillaart/SHT31_SWW)


# SHT31_SWW

Arduino library for the SHT31 temperature and humidity sensor - using **SoftwareWire**.


## Description

This **experimental**  library features the class SHT31_SWW derived from - https://github.com/RobTillaart/SHT31
It has the same interface as the SHT31 class so please use that documentation 
as it will be the "leading class".

The main difference is that the SHT31_SWW class uses the **SoftwareWire** 
library for communication instead of the **TwoWire** based **Wire** class.
See SHT31 PR #35.

**SoftwareWire** is a software I2C bus library to be able to select other pins 
than the default (AVR) hardware I2C pins (SDA and SCL).
An important reason to use this version is when you want more than two 
devices on one Arduino.

Note: this library is AVR specific.


### SoftWire vs SoftwareWire

The **SoftWire** library is portable, however it could not read (on AVR)
the SHT85 sensor which is command compatible with the SHT3x.
The cause is not found yet.
Therefore a separate repo is created based upon the AVR specific **SoftwareWire**
see links below. 
If you know a solution to get softWire working on AVR, please let me know.

The **SoftwareWire** library is an AVR specific and worked for the SHT85.
See https://github.com/RobTillaart/SHT31_SW/issues/5


### SHT3x SHT85 sensors

The SHT3x family of sensors should work up to 1 MHz I2C.

This library should also work for SHT30, SHT35 and SHT85 but these are
not tested yet.

Accuracy table

|  Sensor  |  Temperature  |  Humidity  |  Verified  }
|:--------:|:-------------:|:----------:|:----------:|
|   SHT30  |      ~0.3°    |     2.0%   |     N      |
|   SHT31  |      ~0.3°    |     1.5%   |     Y      |
|   SHT35  |      ~0.2°    |     1.5%   |     N      |
|   SHT85  |      ~0.2°    |     1.5%   |     Y      |


An elaborated library for the SHT31 sensor can be found here
- https://github.com/hawesg/SHT31D_Particle_Photon_ClosedCube

A derived class for using the SHT31 sensor with SoftWire (soft I2C) can be found here
- https://github.com/RobTillaart/SHT31_SW


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


### 0.2.0 Breaking change

Version 0.2.0 introduced a breaking change.
You cannot set the pins in **begin()** any more.
This reduces the dependency of processor dependent Wire implementations.
The user has to call **Wire.begin()** and can optionally set the Wire pins 
before calling **begin()**.


### Related

These libraries need to be installed to get SHT31_SW working:

- https://github.com/RobTillaart/SHT31
- https://github.com/Testato/SoftwareWire      //   AVR only

Related
- https://github.com/stevemarple/AsyncDelay
- https://github.com/stevemarple/SoftWire

An elaborated library for the SHT31 sensor can be found here
- https://github.com/hawesg/SHT31D_Particle_Photon_ClosedCube

Other, including Dewpoint, heatindex, related functions and conversions.

- https://www.kandrsmith.org/RJS/Misc/Hygrometers/calib_many.html (interesting)
- https://github.com/RobTillaart/Temperature (conversions, dewPoint, heat index etc.)


## Interface

```cpp
#include "SHT31_SWW.h"
```

Note: The interface is mostly inherited from SHT31 and presented here for completeness.


### Constructor

- **SHT31_SWW(uint8_t address, SoftwareWire \*wire = &Wire)** constructor. 
Select address and the (software) I2C bus.
- **bool begin()** 
Returns false if device address is incorrect or device cannot be reset.
- **bool isConnected()** check sensor is reachable over I2C. Returns false if not connected.
- **uint8_t getAddress()** returns address set in the constructor.


### Read

- **bool read(bool fast = true)** blocks 4 (fast) or 15 (slow) milliseconds + actual read + math.
Does read both the temperature and humidity.

Meta information about the sensor.

- **uint16_t readStatus()** returns bit mask, details see **Status fields** below (and datasheet).
- **bool clearStatus()** clear status register, see **Status fields** below.
- **uint32_t lastRead()** in milliSeconds since start of program.
- **bool reset(bool hard = false)** resets the sensor, soft reset by default. Returns false if call fails.

The following functions will return the same value until a new **read()** call (or async) is made.

- **float getHumidity()** computes the relative humidity in % based on the latest raw reading, and returns it.
- **float getTemperature()** computes the temperature in °C based on the latest raw reading, and returns it.
- **float getFahrenheit()** computes the temperature in °F based on the latest raw reading, and returns it..


The **getRawHumidity()** and **getRawTemperature()** can be used to minimize storage or communication as the data type is 50% smaller.
Another application is faster comparison with a previous value or threshold.
However comparisons are quite fast.

- **uint16_t getRawHumidity()** returns the raw two-byte representation of humidity directly from the sensor.
- **uint16_t getRawTemperature()** returns the raw two-byte representation of temperature directly from the sensor.

Note that the temperature and humidity values are recalculated on every call to getHumidity() and getTemperature(). 
If you're worried about the extra cycles, you should make sure to cache these values or only request them after 
you've performed a new reading.


### Error interface

- **int getError()** returns last set error flag and clear it. 
Be sure to clear the error flag by calling **getError()** before calling 
any command as the error flag could be from a previous command.

|  Error  |  Symbolic                   |  Description                   |
|:-------:|:----------------------------|:-------------------------------|
|  0x00   |  SHT31_OK                   |  no error                      |
|  0x81   |  SHT31_ERR_WRITECMD         |  I2C write failed              |
|  0x82   |  SHT31_ERR_READBYTES        |  I2C read failed               |
|  0x83   |  SHT31_ERR_HEATER_OFF       |  Could not switch off heater   |
|  0x84   |  SHT31_ERR_NOT_CONNECT      |  Could not connect             |
|  0x85   |  SHT31_ERR_CRC_TEMP         |  CRC error in temperature      |
|  0x86   |  SHT31_ERR_CRC_HUM          |  CRC error in humidity         |
|  0x87   |  SHT31_ERR_CRC_STATUS       |  CRC error in status field     |
|  0x88   |  SHT31_ERR_HEATER_COOLDOWN  |  Heater need to cool down      |
|  0x89   |  SHT31_ERR_HEATER_ON        |  Could not switch on heater    |


### Heater interface

**WARNING:** Do not use heater for long periods. 

Use the heater for max **180** seconds, and let it cool down **180** seconds = 3 minutes. 
SHT31 version 0.3.3 and up guards the cool down time by preventing switching the heater on 
within **180** seconds of the last switch off. Note: this guarding is not reboot persistent. 

**WARNING:** The user is responsible to switch the heater off manually!

The class does **NOT** do this automatically.
Switch off the heater by explicitly calling **heatOff()** or indirectly by calling **isHeaterOn()**.

- **void setHeatTimeout(uint8_t seconds)** Set the time out of the heat cycle.
This value is truncated to max 180 seconds. 
- **uint8_t getHeatTimeout()** returns the value set.
- **bool heatOn()** switches the heat cycle on if not already on.
Returns false if the call fails, setting error to **SHT31_ERR_HEATER_COOLDOWN** 
or to **SHT31_ERR_HEATER_ON**. 
- **bool heatOff()** switches the heat cycle off. 
Returns false if fails, setting error to **SHT31_ERR_HEATER_OFF**.
- **bool isHeaterOn()** is the sensor still in a heating cycle? Replaces **heatUp()**.
Will switch the heater off if maximum heating time has passed.


### Async interface

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
|  9-5  |  Reserved                    |  00000  | reserved
|   4   |  System reset detected       |  0      | no reset since last ‘clear status register’ command
|       |                              |  1      | reset detected (hard or soft reset command or supply fail) - default
|  3-2  |  Reserved                    |  00     |
|   1   |  Command status              |  0      | last command executed successfully
|       |                              |  1      | last command not processed. Invalid or failed checksum
|   0   |  Write data checksum status  |  0      | checksum of last write correct
|       |                              |  1      | checksum of last write transfer failed

**bool clearStatus()** clears 15, 11, 10 and 4.


## Future

#### Must

- keep in sync with (leading) SHT31 and SHT31_SW library.

#### Should

#### Could

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


