
[![Arduino CI](https://github.com/RobTillaart/US500/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/US500/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/US500/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/US500/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/US500/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/US500.svg)](https://github.com/RobTillaart/US500/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/US500/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/US500.svg?maxAge=3600)](https://github.com/RobTillaart/US500/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/US500.svg)](https://registry.platformio.org/libraries/robtillaart/US500)


# US500

Arduino library for US500 underwater distance sensor.


## Description

**Experimental**

This library is to use the US500 underwater (IP67) distance sensor.
The sensor communicates over Serial at 9600 baud.
The MCU sends a command and depending on the command the device answers.

The device can read a distance in the range from 0.5 to 50 centimetre (0.2 - 20 inch). 
The accuracy is ±2mm (~0.1 inch).
The field of view is ±5°.
The US500 can also read the temperature of the water typical 0-100°C.
Furthermore the device has a start and stop function. 
These functions are straight forward.

The library is not tested with hardware (order pending).

It is unknown how the device behaves in other liquids, at least the distance
measurements are expected to be incorrect (other speed of sound).

The device might need a separate power supply (75mW @ 5V).

Feedback, as always is welcome.


### Connections US500

The US500 device is connected to a controller board (which is NOT waterproof).

|  Colour       |  Connection  |  Notes  |
|:--------------|:-------------|:--------|
|  Gray core    |  D signal +  |  polarity !!
|  Gray shield  |  D signal -  |  polarity !!
|  Black        |  Temp NTC    |
|  Black        |  Temp NTC    |

The temperature sensor has no preferred orientation, however the GRAY
distance cable can only be connected in one way.


### Compatible

The US4000 (up to 4 meter, IP68) is almost compatible with the US500.
Main difference is the address and the setDistance() call is not supported.
A future update is planned to support the US4000.


### About hardware

It is not know what the resistance of the NTC is, otherwise it might be connected
with voltage divider to an analog port (possible improve resolution?).

It is also not clear what the protocol of the distance sensor is.
The transducer operates with a 3.3 MHz frequency.
Assumption is it will send a short pulse and waits for the echo.


### Speed of sound in water

It is unknown if the US500 compensates for the temperature of the water.
One may assume it does.

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

Assumption is that the distance can be adjusted to other liquids
by using right formula.


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

Libraries:
- https://github.com/RobTillaart/US500 - this library
- https://github.com/RobTillaart/SRF05 - library for SRF05 distance sensor with temperature and humidity compensation.
- https://www.tinytronics.nl/nl/sensoren/afstand/pono-us500-hx-onderwater-ultrasone-afstandssensor-uart-50cm


### Tested

TODO test with hardware.


## Interface

```cpp
#include "US500.h"
```

### Constructor

- **US500(Stream \* str)** Typical Serial1 or Serial2.
It is not known if software serial will work (not tested).
- **uint16_t getAddress()** returns 0x0005. Convenience function.


### Core

If the functions return a value < 0, it is an error code.

- **float getDistance()** returns the distance in cm (or error code).
- **int setMaxDistance(uint16_t distance)** set the maximum range in 0.1 mm
Must be between 1500 and 5000.
returns 0 = false or 1 = true (or error code).
- **float getTemperature()** returns the temperature in degrees Celsius.
(or error code).
The resolution is in steps of 0.1 degree, supports negative values.
- **void startMeasurement()** idem.
- **void stopMeasurement()** idem.


### Error codes

|  name                 |  value  |
|:----------------------|:-------:|
|  US500_CMD_ERROR      |    -1   |
|  US500_CRC_ERROR      |    -2   |
|  US500_TIMEOUT_ERROR  |    -3   |


### Helper

- **void flush()** if communication is out of sync, 
one can flush int input buffer.


## Future

#### Must

- improve documentation
- get hardware
- test, test, test

#### Should

- support US4000
- improve error handling
- add range check for setMaxDistance or constrain.
- verify software serial works / not.
- test temperature range (water is typical > 0).
- do we need to compensate distance for temperature?
  or is this done in the factory / device.
- time for measurement after start.
- performance indication. per function.

#### Could

- create unit tests if possible

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


