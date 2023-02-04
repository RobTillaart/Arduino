
[![Arduino CI](https://github.com/RobTillaart/DS18B20_INT/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DS18B20_INT/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DS18B20_INT/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DS18B20_INT/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DS18B20_INT/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DS18B20_INT/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DS18B20_INT.svg?maxAge=3600)](https://github.com/RobTillaart/DS18B20_INT/releases)


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
- **bool isConnected()** Returns true if address / device is found.
- **void requestTemperatures()** trigger temperature conversion.
- **bool isConversionComplete()** check if conversion is complete.
- **int16_t getTempC()** returns temperature in whole degrees only. -55..125  
or  -127 = DEVICE_DISCONNECTED
- **bool getAddress()** returns true if the sensor is configured (available).


#### CentiC part

The following functions are experimental since 0.2.0
They allow to use a higher resolution while not using floats. 
This keeps the library small.

- **bool setResolution(uint8_t bits = 9)** sets the internal resolution to 9, 10, 11 or 12 bits. 
Other numbers will be mapped on 9. 
This will affect the conversion time for a measurement.
Internally it will call **begin()** to set the new resolution.
Returns false if no address / device can be found.
- **void getResolution()** returns the bits set, default 9.
Convenience function.
- **getTempCentiC(void)** returns the measured temperature times 100. -5500..12500
So 10.62°C will be returned as 1062.
Note one might need to set the resolution.

**Warning** The DEVICE_DISCONNECTED is not tested for, but is commented in the code. 
Use at own risk.


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
and all people who contributed to that lib.


## Future

#### Must

- elaborate performance connected state.

#### Should

- add examples
  - a multi sensor == multiple pins, no bus

#### Could

- add rounding for **getTempC()**.
  - now it truncates, so it can be 0.5°C off.
  - add "0.5" to raw and truncate improves only for 10 bits and higher.

#### Wont

- unit tests
  - get it working


