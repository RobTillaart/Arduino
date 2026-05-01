
[![Arduino CI](https://github.com/RobTillaart/US500/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/US500/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/US500/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/US500/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/US500/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/US500.svg)](https://github.com/RobTillaart/US500/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/US500/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/US500.svg?maxAge=3600)](https://github.com/RobTillaart/US500/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/US500.svg)](https://registry.platformio.org/libraries/robtillaart/US500)


# US500

Arduino library for US500 and US4000 underwater distance sensor.


## Description

**Experimental**

This library is to use the US500 and US4000 underwater distance sensors.
The sensor communicates over Serial at 9600 baud.
The MCU sends a command and depending on the command the device answers.

The devices can read the distance and the temperature.
Furthermore the device has a start and stop function. 
These functions are pretty straight forward.

Check latest data-sheets for the details:

|  Feature         |  US500             |  US4000              |
|:-----------------|:-------------------|:---------------------|
|  DISTANCE        |                    |                      |
|  range           |  -50 cm            |  -400 cm = ~13 feet  |
|  accuracy        |  ±2mm = ~0.1 inch  |  ±4cm = ~1.6 inch    |
|  field of view   |  90±5°             |  90±4°               |
|  frequency       |  3 MHz             |  1 MHz               |
|                  |                    |                      |
|  TEMPERATURE     |                    |                      |
|  range           |  -10..70° Celsius  |  -10..60° Celsius    |
|                  |                    |                      |
|  MISCELANEOUS    |                    |                      |
|  waterproof      |  IP67              |  IP68                |
|  voltage         |  5-12 V            |  5V                  |
|  Serial          |  9600,N,8,1 TTL    |  9600,N,8,1 TTL      |


The library is not tested with hardware yet (order pending).

It is unknown how the device behaves in other liquids.
Assumption is that the distance measurements incorrect as most liquids
have an other speed of sound.

The devices might need a separate power supply.

Feedback, as always is welcome.


### Connections US500

The US500 device is connected to a **controller board** (which is NOT waterproof).
This controller board is connected over Serial with the MCU.

|  Colour       |  Controller  |  Notes  |
|:--------------|:-------------|:--------|
|  Gray core    |  D signal +  |  polarity !!
|  Gray shield  |  D signal -  |  polarity !!
|  Black        |  Temp NTC    |
|  Black        |  Temp NTC    |

The temperature sensor has no preferred orientation, however the GRAY
distance cable can only be connected in one way.

Multiple devices can be connected to an MCU with multiple (hardware) 
Serial ports, or by means of a multiplexer e.g. MAX14661.


### Connections US4000

The US4000 device is connected directly to TTL Serial of the MCU.

|  Colour       |  Connection  |  Notes  |
|:--------------|:-------------|:--------|
|  Red          |  Power +12V  |
|  White        |  UART TX     |  TTL
|  Yellow       |  UART RX     |  TTL
|  Black        |  Power GND   |

Multiple devices can be connected to an MCU with multiple (hardware) 
Serial ports, or by means of a multiplexer e.g. MAX14661.


### Compatible

The US4000 (up to 4 meter, IP68) is almost compatible with the US500.
Main difference is the address and the setDistance() call is not supported.
A separate class in this library exists for the US4000.


### About hardware

It is not know what the resistance of the NTC is, otherwise it might be connected
with voltage divider to an analog port (possible improve resolution?).

It is also not clear what the protocol of the distance sensor is.
The transducer operates with a 3.3 MHz frequency.
Assumption is it will send a short pulse and waits for the echo.


### Speed of sound in water

It is unknown if the US500 compensates for the temperature of the water.
The assumption is it does.
The US4000 does compensate for temperature drift (datasheet page 2).

From - https://www.engineeringtoolbox.com/sound-speed-water-d_598.html
(has also a Fahrenheit => feet/sec table)

|  temp °C  |  Speed  m/s  |  Speed  m/s  |  Diff %  |
|:---------:|:------------:|:------------:|:--------:|
|           |     WATER    |   SEAWATER   |          |
|    0      |     1403     |     1449     |   3.28   |
|    5      |     1427     |              |          |
|    10     |     1447     |     1490     |   2.97   |
|    20     |     1481     |     1522     |   2.77   |
|    30     |     1507     |     1546     |   2.59   |
|    40     |     1526     |     1563     |   2.63   |
|    50     |     1541     |              |          |
|    60     |     1552     |              |          |
|    70     |     1555     |              |          |
|    80     |     1555     |              |          |
|    90     |     1550     |              |          |
|    100    |     1543     |              |          |

Values in between can be interpolated.
Note the graph is not linear and maxes out around 75°C.

Assumption is that the distance can be adjusted to other liquids
by using the right formula, or by using multiMap.


### Warnings from datasheet

1. Please make sure the Ultrasonic sensor probe unite perpendicular to the object( around 90°±5°)
When the ultrasonic sensor measure the object. If the angle bigger than 90°±5°,the signal will lose.
2. Please keep the sensor probe fixed for the test and do not hold it with your hand.That would affect
the signal.
3. The controller is not waterproof. Please do not submerge the controller in water.
4. This sensor is calibrated based on underwater measurement scenarios.
Cannot be use in air measurement scenarios.


### Related

Supplier
- https://www.positive-inno.com - supplier of the US500 (US4000 and more).
- https://positive-inno.com/wp-content/uploads/2026/04/US500-Manual.pdf - datasheet
- https://positive-inno.com/wp-content/uploads/2026/04/US4000LSG-M20-TTL-Manual.pdf - datasheet
- https://www.tinytronics.nl/nl/sensoren/afstand/pono-us500-hx-onderwater-ultrasone-afstandssensor-uart-50cm

Libraries:
- https://github.com/RobTillaart/US500 - this library
- https://github.com/RobTillaart/SRF05 - library for SRF05 distance sensor with temperature and humidity compensation.
- https://github.com/RobTillaart/MultiMap - library for non linear mapping
- https://github.com/RobTillaart/printHelpers - scientific notation / printInch() / printFeet()
- https://github.com/RobTillaart/MAX14661 - 16x2 channel multiplexer


### Tested

TODO test with hardware.


## Interface

```cpp
#include "US500.h"
```

### Constructors

- **US500(Stream \* str)** Typical Serial1 or Serial2.
Should be initialized at 9600,N,8,1.
- **US4000(Stream \* str)** idem
It is not known if software serial will work (not tested).
- **uint16_t getAddress()** Convenience function.
  - returns 0x0005 for US500
  - returns 0x000A for US4000

### Core

If the functions return a value < 0, it is an error code.

- **float getDistance()** returns the distance in cm (or error code).
- **int setMaxDistance(uint16_t distance)** set the maximum range in 0.1 mm
Must be between 1500 and 5000.
returns 0 = false or 1 = true (or error code).
This function is not supported by the US40000.
- **float getTemperature()** returns the temperature in degrees Celsius.
(or error code).
The resolution is in steps of 0.1 degree, supports negative values.
- **void startMeasurement()** idem.
- **void stopMeasurement()** idem.


### Error codes

|  name                  |  value  |
|:-----------------------|:-------:|
|  US500_CMD_ERROR       |    -1   |
|  US500_CRC_ERROR       |    -2   |
|  US500_TIMEOUT_ERROR   |    -3   |
|                        |         |
|  US4000_CMD_ERROR      |    -1   |
|  US4000_CRC_ERROR      |    -2   |
|  US4000_TIMEOUT_ERROR  |    -3   |


### Helper

- **void flush()** if communication is out of sync, 
one can flush int input buffer.


## Future

#### Must

- improve documentation
- get hardware
- test, test, test

#### Should

- verify Software Serial works / not.

#### Could

- improve error handling
- add range check for setMaxDistance or constrain.
- test temperature range (water is typical > 0).
- test other liquids (?)
  - water with sugar / oil / ...
- do we need to compensate distance for temperature?
  or is this done in the factory / device. (US4000 is for sure)
- time for measurement after start.
- performance indication. per function.
- create unit tests if possible

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


