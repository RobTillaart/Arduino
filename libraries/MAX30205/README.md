
[![Arduino CI](https://github.com/RobTillaart/MAX30205/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MAX30205/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MAX30205/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MAX30205/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MAX30205/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MAX30205.svg)](https://github.com/RobTillaart/MAX30205/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MAX30205/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MAX30205.svg?maxAge=3600)](https://github.com/RobTillaart/MAX30205/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MAX30205.svg)](https://registry.platformio.org/libraries/robtillaart/MAX30205)


# MAX30205

Arduino library for the MAX30205, I2C, high accuracy temperature sensor.


## Description

**Experimental**

This library is to use MAX30205 high accuracy (16 bits) temperature sensor.

This library is work in progress and needs testing with actual hardware.
So feedback is welcome!

The MAX30205 temperature sensor is especially meant for skin contact measurements. It has a high accuracy in the human temperature range

|   range °C       |  accuracy  |  notes  |
|:----------------:|:----------:|:-------:|
|  0°C to 15°C     |    ±0.5°C  |
|  15°C to 35.8°C  |    ±0.3°C  |
|  35.8°C to 37°C  |    ±0.2°C  |
|  37°C to 39°C    |    ±0.1°C  |
|  39°C to 41°C    |    ±0.2°C  |
|  41°C to 45°C    |    ±0.3°C  |
|  45°C to 50°C    |    ±0.5°C  |

The MAX30205 is a 3.3V device so so not connect it to a 5V as this can 
or will harm the sensor. If needed use a voltage convertor or an appropriate 
board that supports the 5V.

The conversion time is about 50 ms or a bit less.

The MAX30205 has an OS pin that can be used for thresholds and more.
This needs more investigation how this works.


Feedback as always is welcome.

### Special characters

ALT241 = ±
ALT0176 = °

### Warning

_Do not apply this product to safety protection devices or emergency stop equipment, 
and any other applications that may cause personal injury due to the product's failure._


### Hardware


```
             TOPVIEW MAX30205
         +--------------------+
         |                    |
   pin 1 | o                o |  pin 8
   pin 2 | o                o |  pin 7
   pin 3 | o                o |  pin 6
   pin 4 | o                o |  pin 5
         |                    |
         +--------------------+
```

|  pin  |  name  |  description          |  notes  |
|:-----:|:--------:|:--------------------|:-------:|
|   1   |  SDA     |  I2C data           |  3-5V
|   2   |  SCL     |  I2C clock          |  3-5V
|   3   |   OS     |  Overtemp Shutdown  |
|   4   |  GND     |  Ground             |
|   5   |   A2     |  address pins       |  see datasheet
|   6   |   A1     |  address pins       |
|   7   |   A0     |  address pins       |
|   8   |  VDD     |  +3.3V              |  Bypass GND with 0.1μF cap


### Related

- https://github.com/RobTillaart/MAX30205
- https://github.com/RobTillaart/DS18B20_RT - well known temperature sensor
- https://github.com/RobTillaart/PCT2075 11 bit I2C temperature sensor with thermal watchdog.
- https://github.com/RobTillaart/SHT85 Sensirion humidity / temperature sensor


### Tested

TODO: Test on Arduino UNO and ESP32


## I2C

### I2C Address

The device has three address lines and depending on connection a different 
address can be chosen.

0x40..0x5F = 32 addresses

See datasheet for full range of connections.

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

See example **TCA9548_demo_MAX30205.ino**


### I2C Performance

Only test **read()** as that is the main function.


|  Clock     |  time (us)  |  Notes  |
|:----------:|:-----------:|:--------|
|   100 KHz  |             |  default 
|   200 KHz  |             |
|   300 KHz  |             |
|   400 KHz  |             |  max per datasheet


TODO: run performance sketch on hardware.


## Interface

```cpp
#include "MAX30205.h"
```

### Constructor

- **MAX30205(uint8_t address, TwoWire \*wire = &Wire)** optional select I2C bus.
- **bool begin()** checks if device is visible on the I2C bus.
- **bool isConnected()** Checks if device address can be found on I2C bus.
- **uint8_t getAddress()** Returns the fixed address 0x2A (42).


### Read

- **bool read()** returns true after a successful read of the temperature.
- **float getTemperature()** returns the last read temperature.


### Configuration mask

See datasheet page 12, 13

- **void setConfig(uint8_t mask = 0x00)**
- **uint8_t getConfig()**

### Configuration field

See datasheet page 12, 13

- **void shutDown()**
- **void wakeUp()**
- **void setModeComparator()**
- **void setModeInterrupt()**
- **void setPolarity(uint8_t polarity = LOW)** polarity = LOW HIGH
- **void setFaultQueLevel(uint8_t level = 0)** level = 0..3
- **void setDataFormat(uint8_t range = 0)** range = 0 => 0..50; 
range = 1 => extended (slower)
- **void setTimeout(uint8_t timeout = 0)** timeout = 0, 1
- **void setModeContinuous()** Continuous implies wakeup
- **void setModeOneShot()** OneShot implies shutdown.


### Hysteresis and OverTemperature

See datasheet page 8

- **bool setHysteresis(float Celsius = 75)**
- **float getHysteresis()**
- **bool setOverTemperature(float Celsius = 80)**
- **float getOverTemperature()**

Describe OS pin behaviour.


### Debug

- **uint32_t getLastRead()**
- **uint16_t getLastError()** returns last error of low level communication.


## Future

#### Must

- improve documentation (a lot)
- get hardware to test

#### Should

- add examples 
  - configuration
  - interrupt
  - fan using OS pin

#### Could

- create unit tests if possible
- improve error handling

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


