
[![Arduino CI](https://github.com/RobTillaart/DS18B20_INT/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DS18B20_INT/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DS18B20_INT/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DS18B20_INT/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DS18B20_INT/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DS18B20_INT.svg)](https://github.com/RobTillaart/DS18B20_INT/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DS18B20_INT/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DS18B20_INT.svg?maxAge=3600)](https://github.com/RobTillaart/DS18B20_INT/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DS18B20_INT.svg)](https://registry.platformio.org/libraries/robtillaart/DS18B20_INT)


# DS18B20_INT

Minimalistic library for the DS18B20 temperature sensor - restricted to one sensor per pin.


## Arduino Temperature Control Library (ATCL)

This DS18B20 library is a minimalistic library for a DS18B20 sensor.
It will give only temperatures in whole degrees C.
Goal is to minimize footprint.

If you need more functions or control over the DS18B20 family I refer to the library
of Miles Burton - https://github.com/milesburton/Arduino-Temperature-Control-Library

I'm a great fan of the above library however some time ago I needed to strip it down 
to save a few dozen bytes. I reworked that minimalistic version into a library and I 
added a number of Arduino examples to help you get started.


#### Related

This library is related to 
- https://github.com/RobTillaart/DS18B20_INT
- https://github.com/RobTillaart/DS18B20_RT
- https://github.com/milesburton/Arduino-Temperature-Control-Library


## Interface

```cpp
#include "DS18B20_INT.h"
```


#### Core

This DS18B20_INT library supports only the DS18B20, only one sensor per pin, no parasite 
mode, no Fahrenheit and no alarm functions. The only feature the class supports is 
the asynchronous reading of the temperature by means of three core functions:

- **DS18B20_INT(OneWire \*)** constructor needs a reference to OneWire object.
- **bool begin(uint8_t retries = 3)** resets oneWire and set resolution default to 9 bit.  
Returns true if address / device is found and all is OK. 
There will be a number of retries to connect, default 3.
- **bool isConnected(uint8_t retries = 3)** Returns true if address / device is found.
There will be a number of retries to connect, default 3.
- **void requestTemperatures()** trigger temperature conversion.
- **bool isConversionComplete()** check if conversion is complete.
- **int16_t getTempC(bool connectCheck = true)** returns temperature in whole degrees only. 
-55..125  or  -127 = DEVICE_DISCONNECTED
Is faster when connectCheck is set to false. Default true = backwards compatible.
- **bool getAddress()** returns true if the sensor is configured (available).


#### CentiC part

The following functions are experimental since 0.2.0 and not tested a lot by me.
They allow to use a higher resolution while **not using floats**. 
Goal is to keep the footprint of the library small.

- **bool setResolution(uint8_t resolution = 9)** sets the internal resolution to 9, 10, 11 or 12 bits. 
Other numbers will be mapped on 9. 
This will affect the conversion time for a measurement.
Internally it will call **begin()** to set the new resolution.
Returns false if no address / device can be found.
- **void getResolution()** returns the resolution set, default 9.
Convenience function.
- **getTempCentiC(void)** returns the measured temperature times 100. -5500..12500
So 10.62°C will be returned as 1062.
Note one might need to set the resolution to get more "decimals".


## Operation

This library supports only one DS18B20 per Arduino/ MCU pin.

```
    //  BOTTOM VIEW
    //
    //          PIN  MEANING
    //   /---+
    //  /  o |  1    GND
    //  |  o |  2    DATA
    //  \  o |  3    VCC
    //   \---+
```
(always check datasheet)

Connect a pull-up resistor 4.7 KOhm between pin3 and pin2. 
When the wires are longer this resistor needs to be smaller.


#### -127 and 85

Two specific return values from reading the sensor:

- minus 127 == DEVICE_DISCONNECTED
- plus 85 is the power on default. 
If you get this unexpected it may indicate a power problem


#### Pull up resistor

An **indicative** table for pull up resistors, (E12 series), to get started.

Note: thicker wires require smaller resistors (typically 1 step in E12 series) 


|  Length         |   5.0 Volt  |  3.3 Volt  |  Notes  |
|----------------:|------------:|-----------:|:--------|
|  10cm (4")      |    10K0     |    6K8     |  might work without  |
|  20cm (8")      |     8K2     |    4K7     |
|  50cm (20")     |     4K7     |    3K3     | 
|  100cm (3'4")   |     3K3     |    2K2     | 
|  200cm (6'8")   |     2K2     |    1K0     | 
|  500cm (16'8")  |     1K0     |    \*      |  
|  longer         |     \*      |    \*      |

\* = no info, smaller?


## Performance

To elaborate connected state.

Tested on UNO, 16 MHz, time in microseconds.
Measured with DS18B20_performance.ino

|  function              |  not connected  |  connected  |
|:-----------------------|:---------------:|:-----------:|
|  begin                 |            920  |      -      |
|  getAddress            |              4  |      -      |
|  requestTemperatures   |           1276  |      -      |
|  isConversionComplete  |             72  |      -      |
|  getTempC              |            912  |      -      |


## Credits

Miles Burton who originally developed the Arduino Temperature Control Library.
and all people who contributed to that library.


## Future

#### Must

- elaborate performance connected state.

#### Should

- better error handling
  - DS18B20_ERR_DISCONNECT
  - DS18B20_OK
  - DS18B20_ERR_POWER_ON.
  - DS18B20_ERR_TIMEOUT ?

#### Could

- example 85 device power on (reread if 85).
- #define DEVICE_POWER_ON       85
- add rounding for **getTempC()**.
  - now it truncates, so it can be 0.5°C off.
  - add "0.5" to raw and truncate improves only for 10 bits and higher.
  - ==> in conflict with minimalistic goal?

#### Wont

- unit tests
  - get it working is too time consuming.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

