
[![Arduino CI](https://github.com/RobTillaart/CHT8310/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/CHT8310/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/CHT8310/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/CHT8310/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/CHT8310/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/CHT8310.svg)](https://github.com/RobTillaart/CHT8310/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/CHT8310/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/CHT8310.svg?maxAge=3600)](https://github.com/RobTillaart/CHT8310/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/CHT8310.svg)](https://registry.platformio.org/libraries/robtillaart/CHT8310)


# CHT8310

Arduino library for CHT8310 temperature and humidity sensor.


## Description

This library is **EXPERIMENTAL** and implements a minimal subset of the functionality of the sensor.
Version 0.1.0 includes reading the temperature and humidity register and the manufacturer-ID register.
Furthermore one can set an offset for temperature and humidity.

Version 0.1.0 does support reading or writing other registers by generic wrappers.
Read the datasheet for the register details.

|  sensor       |  range        |  accuracy\*  |  resolution  |
|:-------------:|:-------------:|:------------:|:------------:|
|  temperature  |  -40°..125°C  |  max 0.5°C   |  0.03125°C   |
|  humidity     |  0%..100% RH  |  max 2% RH   |  0.02% RH    |

\* Accuracy for full range.
More exact details for smaller ranges, see datasheet.

The library is based upon https://github.com/RobTillaart/CHT8305
which is a simpler and unfortunately not an compatible sensor.

If you are able to test this library, please share your experiences.


#### Tests

Many initial tests performed by YouCanNotBeSerious. Thanks.


#### Related

- https://github.com/RobTillaart/Temperature (e.g. heatIndex)
- https://github.com/RobTillaart/CHT8305


## Hardware

Always check datasheet for connections.

```cpp
//
//             +---------------+
//     VCC ----| VCC           |
//     SDA ----| SDA  CHT8310  |
//     GND ----| GND           |
//     SCL ----| SCL           |
//      ?  ----| AD0           |   ? depends on address see table below.
//             |               |
//      x  ----| ALERT         |   x not suppported yet
//             +---------------+
//
//  check datasheet
//  VCC     RED
//  GND     BLACK
//  SDA     YELLOW
//  SCL     WHITE
```

Pull ups are needed on SDA, SCL.


## I2C 

#### performance

I2C bus speeds is supported up to 1000 KHz (datasheet P4).

An indicative table of times in micros on an ESP32-C3 for various I2C clock speeds.
Note that the performance gain of higher clock speeds become less and less.
At the same time the robustness of the signal decreases (not visible in the table).

Times in micros on an ESP32-C3 (See #3 for more)

|  Version  |  Speed   |   READ   |  READ T  |  READ H  | getManufacturer  |
|:---------:|:--------:|:--------:|:--------:|:--------:|:----------------:|
|   0.2.0   |   50000  |   2165   |   1060   |   1058   |   1051           |
|   0.2.0   |  100000  |   1164   |    582   |    582   |    578           |
|   0.2.0   |  150000  |    855   |    427   |    427   |    424           |
|   0.2.0   |  200000  |    654   |    327   |    327   |    323           |
|   0.2.0   |  250000  |    561   |    281   |    281   |    277           |
|   0.2.0   |  300000  |    491   |    245   |    245   |    241           |
|   0.2.0   |  400000  |    417   |    209   |    209   |    204           |
|   0.2.0   |  500000  |    371   |    186   |    186   |    181           |
|   0.2.0   |  600000  |    344   |    172   |    172   |    169           |

The **read()** call uses two I2C calls so it makes sense that it takes twice
as long as **readTemperature()**, **readHumidity()** and **getManufacturer()** 
which only use one I2C call to the device.
**getManufacturer()** is a bit faster as **readTemperature()** as the latter 
needs to do conversion math.


#### Addresses

The CHT8310 supports up to 4 devices on the I2C bus.

|  AD0  |   Address  |  Notes  |
|:-----:|:----------:|:--------|
|  GND  |    0x40    |  CHT8310_DEFAULT_ADDRESS
|  VCC  |    0x44    |
|  SDA  |    0x48    |
|  SCL  |    0x4C    |

Pull ups are needed on SDA, SCL and optional to ALERT.


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


## Interface

```cpp
#include "CHT8310.h"
```

#### Constructor

- **CHT8310(const uint8_t address = CHT8310_DEFAULT_ADDRESS, TwoWire \*wire = &Wire)** Constructor 
with default address (0x40) and I2C bus.
- **int begin()** initializes internals.
Returns error status.
- **bool isConnected()** checks if address (default 0x40) can be seen on the I2C bus.
- **uint8_t getAddress()** returns address set in constructor.


#### Core

- **int read()** reads both the temperature and humidity from the sensor.
Can be called at most once per second, otherwise it will return **CHT8310_ERROR_LASTREAD**
Return should be tested and be **CHT8310_OK**.
- **int readTemperature()** read only temperature from the sensor, therefore faster than read().
This function does not check the lastRead flag, but does set it.
- **int readHumidity()** read only humidity from the sensor, therefore faster than read().
This function does not check the lastRead flag, but does set it.
- **uint32_t lastRead()** returns lastRead in MilliSeconds since start sketch.
Useful to check when it is time to call **read()** again, or for logging.
- **float getTemperature()** returns last temperature read.
Will return the same value until **read()** or **readTemperature()** is called again.
- **float getHumidity()** returns last humidity read.
Will return the same value until **read()** or **readHumidity()** is called again.

Note: read(), readTemperature() and readHumidity() blocks each other,
so you can call only one of them every second (see Convert Rate below).


#### Conversion delay

Not functional for now, need investigation.
Check datasheet for details.

- **void setConversionDelay(uint8_t cd = 11)** default is 11 milliseconds (datasheet P8).
Not tested what is the optimum.
- **uint8_t getConversionDelay()** returns set value.


#### Offset

Adding offsets works well in the "normal range" but might introduce 
under- or overflow at the ends of the sensor range.
These are not handled for temperature by the library, humidity is constrained.
  
- **void setHumidityOffset(float offset)** idem.
- **void setTemperatureOffset(float offset)** idem.
This function can be used to set return temperature in Kelvin!
- **float getHumidityOffset()** idem.
- **float getTemperatureOffset()** idem.

If the offset is not the same over the operational range, 
consider a mapping function for temperature and humidity.
e.g. https://github.com/RobTillaart/MultiMap


#### Configuration

To be elaborated (table / functions)

Check datasheet for details about the bit fields.

- **void setConfiguration(uint16_t mask)** set a bit mask
- **uint16_t getConfiguration()** returns current mask


#### Convert Rate

Check datasheet for details.

The idea is that longer conversion times stabilize the measurement.

- **void setConvertRate(uint8_t rate = 4)** set convert rate, see table below.
Default value = 4 meaning 
- **uint8_t getConvertRate()** returns the set rate.


|  value |  measurement  |  frequency  |  notes  |
|:------:|:-------------:|:-----------:|:-------:|
|   0    |     120 s     |  1/120 Hz   |
|   1    |      60 s     |   1/60 Hz   |
|   2    |      10 s     |    0.1 Hz   |
|   3    |       5 s     |    0.2 Hz   |
|   4    |       1 s     |      1 Hz   |  default
|   5    |     500 ms    |      2 Hz   |
|   6    |     250 ms    |      4 Hz   |
|   7    |     125 ms    |      8 Hz   |


#### ALERT

Check datasheet for details.

Minimal API to set thresholds to trigger the ALERT pin.
No range check (e.g. low < high) is made.

ALERT pin triggers default on both temperature and humidity.

- **void setTemperatureHighLimit(float temperature)**
- **void setTemperatureLowLimit(float temperature)**
- **void setHumidityHighLimit(float humidity)**
- **void setHumidityLowLimit(float humidity)**

See also **getStatusRegister()**


#### Status register

Check datasheet for details.

- ** uint16_t getStatusRegister()**

|  bit  |  name   | description  |
|:-----:|:-------:|:-------------|
|   15  |  Busy   |  idem
|   14  |  Thigh  |  temperature exceeded
|   13  |  Tlow   |  temperature exceeded
|   12  |  Hhigh  |  humidity exceeded
|   11  |  Hlow   |  humidity exceeded


#### OneShot conversion

Check datasheet for details.

- **void oneShotConversion()** idem.


#### SoftwareReset

- **void softwareReset()** idem.


#### Meta data

- **uint16_t getManufacturer()** Returns 0x5959 according to the datasheet,
However in #3 a value of 8215 is seen. Seems to be an other manufacturer.


#### Register Access

Temporary wrappers to access the registers.
Check datasheet for details.

- **uint16_t readRegister(uint8_t reg)**
- **int writeRegister(uint8_t reg, uint16_t value)**


## Error codes

|  value  |  define                  |  notes  |
|:-------:|:-------------------------|:--------|
|     0   |  CHT8310_OK              |
|   -10   |  CHT8310_ERROR_ADDR      |
|   -11   |  CHT8310_ERROR_I2C       |
|   -12   |  CHT8310_ERROR_CONNECT   |
|   -20   |  CHT8310_ERROR_LASTREAD  |
|   -30   |  CHT8310_ERROR_HUMIDITY  |


## Future

#### Must

- elaborate documentation.
- test with hardware
- implement configuration functions.

#### Should


#### Could

- test different platforms
  - AVR, ESP32, ESP8266, STM32, RP2040, ...
- improve error handling
  - **int lastError()**
  - forward return values

#### Could missing functionality

- Configuration register => 10 fields, see datasheet
  - EM flag for resolution
- OneShot

#### Wont

- getters for ALERT limits? (user can track these).


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


