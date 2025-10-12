
[![Arduino CI](https://github.com/RobTillaart/CHT8305/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/CHT8305/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/CHT8305/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/CHT8305/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/CHT8305/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/CHT8305.svg)](https://github.com/RobTillaart/CHT8305/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/CHT8305/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/CHT8305.svg?maxAge=3600)](https://github.com/RobTillaart/CHT8305/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/CHT8305.svg)](https://registry.platformio.org/libraries/robtillaart/CHT8305)


# CHT8305

Arduino library for CHT8305 temperature and humidity sensor.

**EXPERIMENTAL** minimal tested.

If you are able to test this library, please let me know
your experiences.


## Description

**Experimental**

The CHT8305 is a temperature and humidity sensor.

|  sensor       |  range       |  accuracy\*  |  resolution  |
|:-------------:|:------------:|:------------:|:------------:|
|  temperature  |  -40°..125°  |  max 2°C     |  0.1° C      |
|  humidity     |  0%..100% RH |  max 5% RH   |  0.1% RH     |

\* Accuracy for full range.
More exact details for smaller ranges, see datasheet (page 8).

One of the interesting functions is the support of an ALERT function.
This prevents the need for continuous polling of the sensor.


### 0.2.0 Breaking change

Version 0.2.0 introduced a breaking change.
You cannot set the pins in **begin()** any more.
This reduces the dependency of processor dependent Wire implementations.
The user has to call **Wire.begin()** and can optionally set the Wire pins
before calling **begin()**.

Moved the address parameter from **begin()** to constructor.


### Tests

- Temperature and humidity functions works on AVR.
  - default about 14 milliseconds at 14 bit resolution.
- offset functions work.
- getVoltage() function works on AVR but meaning unclear.
- getManufacturer(), getVersionID() works on AVR.
-

The ALERT functions are not tested.
The reason is that the sensor I have does not expose the ALERT pin.

If you are able to test the ALERT functions, please let me know your experiences.


## Hardware

Always check datasheet for connections.

```cpp
//
//             +---------------+
//     VCC ----| VCC           |
//     SDA ----| SDA  CHT8305  |
//     GND ----| GND           |
//     SCL ----| SCL           |
//      ?  ----| AD0           |   ? depends on address see table below.
//             |               |
//     IRQ ----| ALERT         |   only if enabled.
//             +---------------+
//
//  check datasheet
//  VCC     RED
//  GND     BLACK
//  SDA     YELLOW
//  SCL     WHITE
```

Pull ups are needed on SDA, SCL and optional to ALERT.


### Alert

The CHT8305 has an ALERT logic output pin with an open drain structure.
This output is active low. (if the breakout supports this.)


## I2C

### performance

I2C bus speeds is supported up to 400 kHz.
In practice the sensor seems to work even at 800 kHz.
However not clear if the higher speed brings extra wear?

As the sensor / library blocks on reading the temperature
using high I2C speeds does not make a difference, except
for reading Humidity.

So a higher I2C speed does not help to read this sensor.

See - HT8305_performance.ino


|  SPEED   |  READ   |  READ_T  |  READ_H  |
|:--------:|:-------:|:--------:|:--------:|
|  100000  |  14824  |   14604  |    376   |
|  200000  |  14476  |   14360  |    224   |
|  300000  |  14368  |   14276  |    172   |
|  400000  |  14324  |   14244  |    148   |
|  500000  |  14300  |   14224  |    140   |
|  600000  |  14276  |   14212  |    132   |
|  700000  |  14272  |   14204  |    124   |
|  800000  |  14268  |   14196  |    120   |


in 0.2.3 readHumidity() has become slightly faster (no measurement done yet).


### Addresses

|  AD0  |   Address  |  Notes  |
|:-----:|:----------:|:--------|
|  GND  |    0x40    |  CHT8305_DEFAULT_ADDRESS
|  VCC  |    0x41    |
|  SDA  |    0x42    |
|  SCL  |    0x43    |

Pull ups are needed on SDA, SCL and optional to ALERT.


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


## Interface

```cpp
#include "CHT8305.h"
```

### Constructor

- **CHT8305(const uint8_t address = CHT8305_DEFAULT_ADDRESS, TwoWire \*wire = &Wire)**
Constructor with default address (0x40) and I2C bus.
- **int begin()** initializes internals.
Returns error status.
- **bool isConnected()** checks if address (default 0x40) can be seen on the I2C bus.


### Core

- **int read()** reads both the temperature and humidity.
Can be called once per second.
- **int readTemperature()** read only temperature (slightly faster than read)
- **int readHumidity()** read only humidity (slightly faster than read)
- **uint32_t lastRead()** returns lastRead in MilliSeconds since start sketch.
Useful to check when it is time to call **read()** again, or for logging.
- **float getHumidity()** returns last humidity read.
Will return the same value until **read()** or **readHumidity()** is called again.
- **float getTemperature()** returns last temperature read.
Will return the same value until **read()** or **readTemperature()** is called again.

Note: **read()**, **readTemperature()** and **readHumidity()** block each other,
so you can call only one of them every second.


### Conversion delay

- **void setConversionDelay(uint8_t cd = 14)** default is 14 milliseconds
(from the datasheet). 7 milliseconds failed and 8 milliseconds worked.
So values below 8 milliseconds are mapped to 8 in the library.
Expect that 10 milliseconds is a pretty save value to work with.
Adjust this setting at your own risk.
It might be that lower resolutions allow shorter delays. This is not tested.
- **uint8_t getConversionDelay()** returns the default (14) or last set value.


### Offset

Adding offsets works well in the "normal range" but might introduce
under- or overflow at the ends of the sensor range.
These are not handled for temperature by the library (humidity since 0.1.7).

- **void setHumidityOffset(float offset = 0.0)** idem. Default is set to
zero, for an easy reset off the offset.
There is no range check in this function, however, **read()** will
keep the value between 0 and 100%.
- **void setTemperatureOffset(float offset = 0.0)** idem. Default is set to
zero, for an easy reset off the offset.
There is no range check in this function.
- **float getHumidityOffset()** idem.
- **float getTemperatureOffset()** idem.

If the offset is not the same over the operational range,
consider a mapping function for temperature and humidity.
e.g. https://github.com/RobTillaart/MultiMap


### Configuration register

Check the datasheet for details of the register bits.

- **bool setConfigRegister(uint16_t bitmask)** See table below.
Default value 0x1004.
Returns false if write to the config register fails.
Check **getLastError()** for possible cause.
- **uint16_t getConfigRegister()** idem.
If 0x0000 is returned it may indicate an error.
Check **getLastError()** for possible cause.

Bits of configRegister, check datasheet for details.

|  bit  |  mask  |  name           |  description  |
|:-----:|:------:|:----------------|:--------------|
|  15   | 0x8000 |  soft reset     |  1 = reboot the sensor to default
|  14   | 0x4000 |  clock stretch  |  1 = ON, 0 = OFF (default)
|  13   | 0x2000 |  heater         |  1 = ON, 0 = OFF (default)
|  12   | 0x1000 |  mode           |  1 = read both (default), 0 = read T or RH
|  11   | 0x0800 |  vccs           |  1 = >2.8V,  0 = <2.8V
|  10   | 0x0400 |  T-RES          |  1 = 11 bit, 0 = 14 bit (default)
|  9-8  | 0x0300 |  H-RES          |  10 = 8 bit, 01 = 11 bit, 00 = 14 bit (default)
|  7-6  | 0x00C0 |  ALTM           |  Alert Mode (datasheet)
|  5    | 0x0020 |  APS            |  Alert pending status
|  4    | 0x0010 |  H-ALT          |  Humidity Alert status
|  3    | 0x0008 |  T-ALT          |  Temperature Alert status
|  2    | 0x0004 |  VCC enable     |  1 = enable VCC measurement (default), 0 = disable
|  1-0  | 0x0003 |  reserved.      |  do not change.


### Getters / setters configuration register

Note: setting **setConfigRegister(bitmask)** can be faster.

Wrapper functions for easy configuration. Read the datasheet for the details.

- **void softReset()** sets the soft reset bit in the configuration,
causing the sensor to reset.
- **void setI2CClockStretch(bool on = false)** check datasheet.
- **bool getI2CClockStretch()** check datasheet.
- **void setHeaterOn(bool on = false)** switch on internal heater.
Can improve humidity readings.
See datasheet for (limited) details.
  - **WARNING** User is responsible for timing as library does not support timing.
- **bool getHeater()** Returns status of the heater.
- **void setMeasurementMode(bool both = true)** both T and H or single value.
- **bool getMeasurementMode()** returns mode set above.
- **bool getVCCstatus()** 1 ==  > 2.8V  0 == < 2.8V  Useful when battery operated?
- **void setTemperatureResolution(uint8_t res = 0)** 1 = 11 bit, 0 = 14 bit (default).
- **uint8_t getTemperatureResolution()** idem.
- **void setHumidityResolution(uint8_t res = 0)** 2 = 8 bit, 1 = 11 bit, 0 = 14 bit (default).
- **uint8_t getHumidityResolution()** idem.
- **void setVCCenable(bool enable = false)** enable VCC measurement of the power supply.
- **bool getVCCenable()** return current status of enable bit.


### Alert

See register 3 datasheet page 12 for details.

- **void setAlertTriggerMode(uint8_t mode = 0)** see table below.
- **uint8_t getAlertTriggerMode()** returns 0, 1, 2 or 3.

|  mode  |  trigger  |  notes    |
|:------:|:---------:|:----------|
|   0    |  T or H   |  default  |
|   1    |  T        |
|   2    |  H        |
|   3    |  T and H  |

- **bool getAlertPendingStatus()** idem.
- **bool getAlertHumidityStatus()** idem.
- **bool getAlertTemperatureStatus()** idem.
- **bool setAlertLevels(float temperature, float humidity)**
  - the values will be truncated to the nearest value possible.
  - the ALERT supports HIGH limit only ==> there is no LOW limit ALERT.
  - note: the datasheet is ambiguous with respect to the formula used.
- **float getAlertLevelTemperature()** returns the truncated value set.
- **float getAlertLevelHumidity()** returns the truncated value set.


The ALERT pin triggers with a falling edge (from HIGH to LOW).


### Supply voltage

(datasheet 1.1.5)
The chip has a feature to measure supply voltage (VCC) with 16 bit output data.
VCC measurement should be enabled by means of **void setVCCenable(true)**.

- **float getVoltage()** unclear what unit is used.

Best guess for now: 16 bit data implies ```voltage = 5.0V * value / 32767.0;```
Varied slightly 5.000 - 4.999 also for 3V3 power supply.

Conclusion: it is not 100 % clear how to interpret this register.


### Meta data

- **uint16_t getManufacturer()** returns 0x5959.
- **uint16_t getVersionID()** return value may differ.
Test returned 0x8305.


### Error handling

Since 0.2.2 some error handling has been added.
This need to be improved in the future.

- **getLastError()** returns 0 if all is OK.
If it doesn't return 0 an error occurred during **read()** et al.
The table gives some information where the problem occurred.
A call to **getLastError()** resets the internal error flag.

Note: in case of e.g. an I2C error, the last values of Temperature
and Humidity do not change.

|  Error constant          |   value  |  Notes  |
|:-------------------------|:--------:|:--------|
|  CHT8305_OK              |      0   |
|  CHT8305_ERROR_ADDR      |    -10   |
|  CHT8305_ERROR_I2C       |    -11   |
|  CHT8305_ERROR_CONNECT   |    -12   |
|  CHT8305_ERROR_BUFSIZE   |    -13   |
|  CHT8305_ERROR_LASTREAD  |    -20   |
|  CHT8305_ERROR_GENERIC   |    -999  |
|                          |  0xFFFF  |  patch  |


### Register map

See datasheet page 10 for details

|  Address  |  Register name             |
|:---------:|:---------------------------|
|   0x00    |  CHT8305_REG_TEMPERATURE   |
|   0x01    |  CHT8305_REG_HUMIDITY      |
|   0x02    |  CHT8305_REG_CONFIG        |
|   0x03    |  CHT8305_REG_ALERT         |
|   0x04    |  CHT8305_REG_VOLTAGE       |
|   0xFE    |  CHT8305_REG_MANUFACTURER  |
|   0xFF    |  CHT8305_REG_VERSION       |


## Future

#### Must

- elaborate documentation.

#### Should

- test other platforms
  - ESP32,
- test resolution bits.
  - delay ?
- test configuration functions.
- test ALERT functions.
- test write / readRegister with a single uint16_t to simplify code.
- test error handling.

#### Could

- parameter testing
- parameter defaults?
- investigate asynchronous reading
  - request, ready (after 15 millis), fetch
  - needs lastRequest timestamp
- configRegister => force bit 0 and 1 to 0

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


