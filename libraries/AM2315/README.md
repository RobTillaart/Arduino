
[![Arduino CI](https://github.com/RobTillaart/AM2315/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AM2315/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AM2315/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AM2315/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AM2315/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AM2315.svg)](https://github.com/RobTillaart/AM2315/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AM2315/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AM2315.svg?maxAge=3600)](https://github.com/RobTillaart/AM2315/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AM2315.svg)](https://registry.platformio.org/libraries/robtillaart/AM2315)


# AM2315

Arduino library for an AM2315 I2C temperature and humidity sensor.


## Description

The AM2315 is a sensor similar to the DHT12 with an I2C interface.

Although in theory this could enable multiple sensors on one bus
the AM2315 has a fixed address **0x5C** so one need to implement a 
multiplexing strategy to have multiple sensors in practice. 
See multiplexing below.

The AM2315 can also be read with the https://github.com/RobTillaart/AM232X library as it uses the same protocol. 
The AM232X library allows to read some internal registers.


#### 0.2.0 Breaking change

Version 0.2.0 introduced a breaking change.
You cannot set the pins in **begin()** any more.
This reduces the dependency of processor dependent Wire implementations.
The user has to call **Wire.begin()** and can optionally set the Wire pins
before calling **begin()**.


#### AM2315C

The AM2315C ( note the C ) is a different sensor with a different protocol.
Check - https://github.com/RobTillaart/AM2315C
The C-version has a fixed address of **0x38** so easy to detect.


#### Typical parameters

|             |  range     | accuracy | repeatability |
|:------------|:----------:|:--------:|:-------------:|
| Temperature | -40 - 125  | 0.5°C    |  ±0.2         |
| Humidity    | 0.0 - 99.9 | ±2%      |  ±0.1         |
| Sample time | 2 seconds  |          |               |


#### Hardware connection

```
//  AM232X PIN layout             AM2315 COLOR
//  ============================================
//   bottom view  DESCRIPTION     COLOR
//       +---+
//       |o  |       VDD          RED
//       |o  |       SDA          YELLOW
//       |o  |       GND          BLACK
//       |o  |       SCL          GREY
//       +---+
//
// do not forget pull up resistors between SDA, SCL and VDD.
```

## I2C

The AM2315 has a fixed address **0x5C** (92).


#### Multiplexing 

Multiplexing the **AM2315** can be done in several ways.
This is not a complete list or tutorial but should get you started.

1. Control the power line by means of an extra pin (+ transistor). 
Only switch on the sensor you want to use. Drawback might be time 
the sensor takes to boot and to be ready for the first measurement.
2. Use an AND gate between the I2C SCL (clock) line and the I2C SCL 
pin of the sensors. This way one can enable / disable communication 
per sensor. This will still need an IO pin per sensor but does not 
have the "boot time" constraint mentioned above.
You may use a **PCF8574** to control the AND gates.
https://github.com/RobTillaart/PCF8574
3. Use a **TCA9548A** I2C Multiplexer, or similar.

- https://github.com/RobTillaart/TCA9548

Drawback of using a multiplexer is that it takes more administration in 
your code e.g. which device is on which channel. 
This will slow down the access, which must be taken into account when
deciding which devices are on which channel.
Also note that switching between channels will slow down other devices 
too if they are behind the multiplexer.

Which method fit your application depends on your requirements and constraints.


#### I2C clock speed

The datasheet states the AM2315 should be used on 100 KHz I2C only. 
When overclocking I got good readings up to 190 KHz in a test with 
- Arduino UNO
- very short wires ( < 1 meter)
- not using pull ups.
- version 0.1.1 of this library


| I2C clock | timing us | Notes                 |
|:---------:|:---------:|:----------------------|
|   50 KHz  |    4570   | under-clocking works (e.g. long wires)
|  100 KHz  |    3276   | specs default, robust
|  150 KHz  |    2836   |
|  160 KHz  |    2792   |
|  170 KHz  |    2750   | 0.5 ms off, interesting for performance.
|  180 KHz  |    2700   | near critical. DO NOT USE.
|  190 KHz  |    2672   | near critical. DO NOT USE.
|  200 KHz  |   crash   | sensor needs a power cycle reboot. DO NOT USE.


If robustness is mandatory stick to the default of 100 KHz.
If performance is mandatory do not go beyond 170 KHz.


## Interface

```cpp
#include "AM2315.h"
```


#### Constructor

- **AM2315(TwoWire \*wire = &Wire)** constructor, default using Wire (I2C bus), optionally set to Wire0 .. WireN.
- **bool begin()** initializer.
Returns true if device address 0x5C is connected.
Note the user has to call Wire.begin() before **AM.begin()**.
- **bool isConnected(uint16_t timeout = 3000)** returns true if the device address 0x5C is found on I2C bus.
As the device can be in sleep modus it will retry for the defined timeout (in micros) with a minimum of 1 try. 
minimum = 800 us and maximum = 3000 us according to datasheet.


#### Core

- **int8_t read()** read the sensor and store the values internally.
It returns the status of the read which should be **AM2315_OK** == 0.
- **float getHumidity()** returns last read humidity + optional offset, 
or **AM2315_INVALID_VALUE** == -999 in case of error. 
This error can be suppressed, see below.
- **float getTemperature()** returns last read temperature + optional offset,
or **AM2315_INVALID_VALUE** == -999 in case of error. 
This error can be suppressed, see below.
- **uint32_t lastRead()** returns the timestamp in milliseconds since startup of the last successful read.


#### Offset

- **void setHumOffset(float offset = 0)** set an offset for humidity to calibrate (1st order) the sensor.
Default offset = 0, so no parameter will reset the offset.
- **float getHumOffset()** return current humidity offset, default 0.
- **void setTempOffset(float offset = 0)** set an offset for temperature to calibrate (1st order) the sensor.
Default offset = 0, so no parameter will reset the offset.
- **float getTempOffset()** return current temperature offset, default 0.


#### Control

Functions to adjust the communication with the sensor.

- **void setWaitForReading(bool b )** flag to enforce a blocking wait (up to 2 seconds) when **read()** is called.
- **bool getWaitForReading()** returns the above setting.
- **bool wakeUp()** function that will try for 3 milliseconds to wake up the sensor.
This can be done before an actual read to minimize the **read()** call.
- **void setSuppressError(bool b)** suppress error values of **AM2315_INVALID_VALUE** == -999 
=> you need to check the return value of read() instead.  
This can be used to keep spikes out of your graphs / logs. 
- **bool getSuppressError()**  returns the above setting.


#### Error codes

| name                              | value | notes       |
|:----------------------------------|------:|:------------|
| AM2315_OK                         |  0    |
| AM2315_ERROR_CHECKSUM             |  -10  | I2C problem.
| AM2315_ERROR_CONNECT              |  -11  | I2C problem.
| AM2315_MISSING_BYTES              |  -12  | I2C problem.
| AM2315_WAITING_FOR_READ           |  -50  | called **read()** too fast, within 2 seconds.
| AM2315_HUMIDITY_OUT_OF_RANGE      |  -100 | not used by default.
| AM2315_TEMPERATURE_OUT_OF_RANGE   |  -101 | not used by default.
| AM2315_INVALID_VALUE              |  -999 | can be suppressed. 

Note: The OUT_OT_RANGE errors are tested on the "raw" readings, excluding the offset.
So if the "raw" humidity is 99% and you use an offset of 3% you will get 102%
without the error. 


## Operation

See examples

In **setup()** you have to call the **begin()** to initialize 
the Wire library and do an initial **read()** to fill the variables temperature and humidity. 
To access these values one must use **getTemperature()** and **getHumidity()**. 
Multiple calls will give the same values until **read()** is called again.

Note that the AM2315 can go into sleep mode after 3 seconds after last read, 
so one might need to call **wakeUp()** before the **read()**.


## Future

#### Must

- update documentation
- test more (other platforms)

#### Should

- keep in sync with AM232X class
  - merge in a far future.


#### Could

- move code from .h to .cpp

#### Wont

- add calls for meta information (no description yet)
  - 0x07 status register
  - 0x08-0x0B user register HIGH LOW HIGH2 LOW2
  (use AM232x library to access those)


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

