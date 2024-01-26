
[![Arduino CI](https://github.com/RobTillaart/DHT20/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DHT20/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DHT20/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DHT20/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DHT20/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DHT20.svg)](https://github.com/RobTillaart/DHT20/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DHT20/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DHT20.svg?maxAge=3600)](https://github.com/RobTillaart/DHT20/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DHT20.svg)](https://registry.platformio.org/libraries/robtillaart/DHT20)


# DHT20

Arduino library for I2C DHT20 temperature and humidity sensor.


## Description

The DHT20 is a humidity and temperature sensor. 

The sensor has a fixed address of **0x38**.
It is not known if the address can be changed.

The library must be initiated by calling the **begin()** function.

Thereafter one has to call the **read()** function to do the actual reading,
and call **getTemperature()** and **getHumidity()** to get the measured values.
Calling these latter again will return the same values until a new **read()** is done.

The **read()** call of this sensor is blocking for 80+ milliseconds (datasheet 7.4)
so the library also has a asynchronous interface. See below.

Since 0.1.3 and 0.1.4 the performance of **read()** has been optimized, 
still blocking but less long for about 45 milliseconds.


### 0.2.0

In #8 a bug is described that the sensor "freezes".
Cause is not well understood.

Two solutions / workarounds are found:
- call **resetSensor()** before EVERY **read()**. 
This is the preferred solution.
- use **Wire.setClock(200000)** 100 K and lower speeds freezes the sensor.
With clock set to 200 K and above the sensor seems to work for longer periods.
Tested several speeds on UNO, no pull ups, < 10 cm wire.

Note: setting the I2C clock possibly interferes with other devices on the I2C bus,
so it is not a solution in the end.

The 0.2.0 version embeds the **resetSensor()** into **requestData()** to 
reset the sensor if needed in both synchronous and asynchronous calls.
This keeps the API simple. The reads are 1-2 ms slower than 0.1.4. (< 50 ms).
Still far below the 80 ms mentioned in the datasheet. 


#### 0.3.0 Breaking change

Version 0.3.0 introduced a breaking change.
You cannot set the pins in **begin()** any more.
This reduces the dependency of processor dependent Wire implementations.
The user has to call **Wire.begin()** and can optionally set the Wire pins
before calling **begin()**.


#### Tested

Verified to work with Arduino UNO and ESP32 and ESP8266 (see #8)
Please let me know if other platforms work (or not).


## I2C

#### Address

The sensor has a fixed address of **0x38**.
It is not known if the address can be changed.


#### I2C multiplexing

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


#### Connection

Always check datasheet!

Front view
```
          +--------------+
  VDD ----| 1            |
  SDA ----| 2    DHT20   |
  GND ----| 3            |
  SCL ----| 4            |
          +--------------+
```

#### Performance

The datasheet states 400 KHz as the maximum speed.
Below the results of a small test that works well up to 800 KHz.

 - Arduino UNO + 10 cm wires + no pull up + DHT20_I2C_speed.ino

Speed in KHz, Time in microseconds. 


**read()**

|  Speed  |  Time   |  notes  |
|:-------:|:-------:|:--------|
|   100   |  44588  |  default I2C speed  |
|   200   |  43988  |
|   400   |  44040  |  datasheet maximum  |
|   600   |  43224  |
|   800   |  43988  |


**ASYNC: requestData()**

|  Speed  |  Time   |  notes  |
|:-------:|:-------:|:--------|
|   100   |  1676   |  default I2C speed  |
|   200   |  1384   |
|   400   |  1240   |  datasheet maximum  |
|   600   |  1188   |
|   800   |  1168   |


**ASYNC: readData()**

|  Speed  |  Time   |  notes  |
|:-------:|:-------:|:--------|
|   100   |   832   |  default I2C speed  |
|   200   |   464   |
|   400   |   284   |  datasheet maximum  |
|   600   |   212   |
|   800   |   188   |

The numbers indicate that the conversion takes > 40 milliseconds.
Requesting the measurement and fetching the data < 2.5 milliseconds.

Using the asynchronous interface frees up a lot of clock cycles.
Going beyond 400 KHz (datasheet max) does not save much extra time,
and should only be used if you are in a need for speed.


## Interface

```cpp
#include "DHT20.h"
```

#### Constructor

- **DHT20(TwoWire \*wire = &Wire)** constructor, using a specific Wire (I2C bus).
- **bool begin()** initializer. Returns true if connected.
The user must call **Wire.begin()** before calling this function.
- **bool isConnected()** returns true if the address of the DHT20 can be seen on the I2C bus.
- **uint8_t getAddress()** returns the (fixed) address - convenience.

#### Core

- **int8_t read()** read the sensor and store the values internally. 
Returns the status of the read which should be 0 == **DHT20_OK**.
- **float getHumidity()** returns last Humidity read.
Multiple calls will return same value until a new **read()** is made.
- **float getTemperature()** returns last Temperature read.
Multiple calls will return same value until a new **read()** is made.


#### Offset

- **void setHumOffset(float offset = 0)** set an offset to calibrate the sensor (1st order).
Default offset is 0.
- **float getHumOffset()** return current humidity offset, default 0.
- **void setTempOffset(float offset = 0)** set an offset to calibrate the sensor (1st order).
Default offset is 0.
- **float getTempOffset()** return current temperature offset, default 0.


#### Asynchronous interface

There are two timings that need to be considered (from datasheet):
- time between requests = 1000 ms.
- time between request and data ready = 80 ms.

The async interface allows one to continue processing after a **requestData()** has been made. 
Note there should be at least **1000 milliseconds** between subsequent requests.

With **bool isMeasuring()** one can check if a new measurement is ready.
Alternative is to delay for up to 80 ms.
If so the sensor can be read with **readData()**.

To interpret the read bits to temperature, humidity and status one needs to call **convert()** as last step.


- **int requestData()** signals the sensor to make a new measurement.
Note there must be at least 1000 milliseconds between requests!
- **int readData()** does the actual reading of the data.
- **int convert()** converts the read bits to temperature and humidity.

See the example **DHT20_async.ino**


#### Status

- **uint8_t readStatus()** forced read of the status only.
This function blocks a few milliseconds to optimize communication.
- **bool isCalibrated()** idem, wrapper around **readStatus()**
- **bool isMeasuring()** idem, wrapper around **readStatus()**
- **bool isIdle()** idem, wrapper around **readStatus()**
- **int internalStatus()** returns the internal status of the sensor. (for debug).

|  status bit  |  meaning                   |
|:------------:|:---------------------------|
|    7         |  1 = measurement, 0 = idle |
|  6 - 4       |  unknown                   |
|    3         |  1 = calibrated, 0 = not   |
|  2 - 0       |  unknown                   |


#### Experimental 0.1.4 resetSensor

Use with care!

- **uint8_t resetSensor()** if at startup the sensor does not return a status of 0x18, 
three registers 0x1B, 0x1C and 0x1E need to be reset. 
See datasheet 7.4 Sensor Reading Process, point 1.
There is no documentation about the meaning of these registers.
The code is based upon example code for the AHT20 (from manufacturer).

The call is needed to get the **read()** working well so it has been embedded into
the read calls. (0.2.0)


#### Timing

- **uint32_t lastRead()** last time the sensor is read in milliseconds since start.
- **uint32_t lastRequest()** last time a request is made to make a measurement.


#### Return codes

|  name                        |  value  |  notes  |
|:-----------------------------|:-------:|:--------|
|  DHT20_OK                    |    00   |  OK
|  DHT20_ERROR_CHECKSUM        |   -10   |  values might be OK if they are like recent previous ones.
|  DHT20_ERROR_CONNECT         |   -11   |  check connection
|  DHT20_MISSING_BYTES         |   -12   |  check connection
|  DHT20_ERROR_BYTES_ALL_ZERO  |   -13   |  check connection
|  DHT20_ERROR_READ_TIMEOUT    |   -14   |
|  DHT20_ERROR_LASTREAD        |   -15   |  wait 1 second between reads


## Future

#### Must

- improve documentation.
- sync AM2315C developments
  - see https://github.com/RobTillaart/AM2315C
- investigate the bug from #8 further
  (is done in 0.2.1 see issue #8)


#### Should


#### Could

- improve unit tests.
- investigate 
  - sensor calibration (website aosong?)
  - can sensor address be changed?
- investigate optimizing timing in readStatus()
  - delay(1) ==> microSeconds(???).
- connected flag?
- keep in sync DHT12 ?


#### Wont

- **void setIgnoreChecksum(bool = false)** ignore checksum flag speeds up communication a bit
- **bool getIgnoreChecksum()** get checksum flag. for completeness.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

