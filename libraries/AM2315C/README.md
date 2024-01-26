
[![Arduino CI](https://github.com/RobTillaart/AM2315C/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AM2315C/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AM2315C/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AM2315C/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AM2315C/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AM2315C.svg)](https://github.com/RobTillaart/AM2315C/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AM2315C/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AM2315C.svg?maxAge=3600)](https://github.com/RobTillaart/AM2315C/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AM2315C.svg)](https://registry.platformio.org/libraries/robtillaart/AM2315C)


# AM2315C

Arduino library for I2C AM2315C temperature and humidity sensor.


## Description

The AM2315C is a humidity and temperature sensor. 

Warning: this sensor is not compatible with the AM2315.

The sensor has a fixed address of **0x38**.
It is not known if the address can be changed.

The library must be initiated by calling the **begin()** function.

Thereafter one has to call the **read()** function to do the actual reading,
and call **getTemperature()** and **getHumidity()** to get the measured values.
Calling these latter again will return the same values until a new **read()** is done.

The **read()** call of this sensor is blocking for 80+ milliseconds (datasheet 7.4)
so the library also has a asynchronous interface. See below.

This library is based upon the DHT20 library which is leading in development.
The DHT20 also provides a bit more documentation and issues from the past.
- https://github.com/RobTillaart/DHT20


#### 0.2.0 Breaking change

Version 0.2.0 introduced a breaking change.
You cannot set the pins in **begin()** any more.
This reduces the dependency of processor dependent Wire implementations.
The user has to call **Wire.begin()** and can optionally set the Wire pins
before calling **begin()**.


## I2C

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
                    +-----------------+
    RED    -------- | VDD             |
    YELLOW -------- | SDA    AM2315C  |
    BLACK  -------- | GND             |
    WHITE  -------- | SCL             |
                    +-----------------+
```


## Interface

```cpp
#include "AM2315C.h"
```

#### Constructor

- **AM2315C(TwoWire \*wire = &Wire)** constructor, using a specific Wire (I2C bus).
- **bool begin()** initializer. Returns true if connected.
The user must call **Wire.begin()** before calling this function.
- **bool isConnected()** returns true if the address of the AM2315C can be seen on the I2C bus.
- **uint8_t getAddress()** returns the (fixed) address - convenience.

#### Core

- **int8_t read()** read the sensor and store the values internally. 
Returns the status of the read which should be 0 == **AM2315C_OK**.
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

See the example **AM2315C_async.ino**


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


#### Experimental resetSensor

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

|  name                          |  value  |  notes  |
|:-------------------------------|:-------:|:--------|
|  AM2315C_OK                    |    00   |  OK
|  AM2315C_ERROR_CHECKSUM        |   -10   |  values might be OK if they are like recent previous ones.
|  AM2315C_ERROR_CONNECT         |   -11   |  check connection
|  AM2315C_MISSING_BYTES         |   -12   |  check connection
|  AM2315C_ERROR_BYTES_ALL_ZERO  |   -13   |  check connection
|  AM2315C_ERROR_READ_TIMEOUT    |   -14   |
|  AM2315C_ERROR_LASTREAD        |   -15   |  wait 1 second between reads


## Future

#### Must

- improve documentation.
- follow / sync DHT20 developments
  - see https://github.com/RobTillaart/DHT20
- get hardware / sensor to test library

#### Should

#### Could

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

