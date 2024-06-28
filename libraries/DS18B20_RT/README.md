
[![Arduino CI](https://github.com/RobTillaart/DS18B20_RT/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DS18B20_RT/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DS18B20_RT/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DS18B20_RT/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DS18B20_RT/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DS18B20_RT.svg)](https://github.com/RobTillaart/DS18B20_RT/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DS18B20_RT/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DS18B20_RT.svg?maxAge=3600)](https://github.com/RobTillaart/DS18B20_RT/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DS18B20.svg)](https://registry.platformio.org/libraries/robtillaart/DS18B20)


# DS18B20

Arduino library for the DS18B20 sensor - restricted to one sensor per pin.


## Arduino Temperature Control Library (ATCL)

This DS18B20 library is not a full featured library for the DS18B20 family.
This library supports only one DS18B20 per Arduino/ MCU pin.

If you need more functions or control over the DS18B20 family I refer to the library
of Miles Burton - https://github.com/milesburton/Arduino-Temperature-Control-Library

I'm a great fan of the above library however some time ago I needed to strip it down 
to save a few dozen bytes. I reworked that minimalistic version into a library and I 
added a number of Arduino examples to help you get started.


#### Footprint OneWire

This library depends (is build) upon the **OneWire** library of Paul Stoffregen.
- https://github.com/PaulStoffregen/OneWire - the reference imho.

In issue [#31](https://github.com/RobTillaart/DS18B20_RT/issues/31) the footprint of 
the OneWireNG seems to be smaller when build on platformIO.

So if you are in need to save some more bytes, you might try [OneWireNG]
(https://github.com/pstolarz/OneWireNg).


#### Related

This library is related to 
- https://github.com/RobTillaart/DS18B20_INT
- https://github.com/RobTillaart/DS18B20_RT
- https://github.com/milesburton/Arduino-Temperature-Control-Library
- https://github.com/milesburton/Arduino-Temperature-Control-Library/issues/244#event-9253126638


## Interface

```cpp
#include "DS18B20.h"
```

#### Core

The DS18B20 library supports only the DS18B20, only one sensor per pin, no parasite 
mode, no Fahrenheit and no alarm functions. The only feature the class supports is 
the asynchronous reading of the temperature by means of three core functions:

- **DS18B20(OneWire \* ow, uint8_t resolution = 9)** constructor needs a reference to OneWire object.
Also sets the resolution, default to 9 bits.
- **bool begin(uint8_t retries = 3)** resets oneWire and set resolution default to 9 bit.  
Returns true if all is OK.
There will be a number of retries to connect, default 3.
- **bool isConnected(uint8_t retries = 3)** resets oneWire checks if a device can be found.  
Returns true if a device is found.
There will be a number of retries to connect, default 3.
- **void requestTemperatures()** trigger temperature conversion.
- **bool isConversionComplete()** check if conversion is complete.
- **float getTempC(bool checkConnect = true)** returns temperature in Celsius.
  - -127 = DEVICE_DISCONNECTED (only when checkConnect == true)
  - -128 = DEVICE_CRC_ERROR
  - can be faster by setting checkConnect to false. (experimental)
- **bool setResolution(uint8_t resolution = 9)** resolution = 9..12 (9 is default).
Returns false if no device is found.
- **uint8_t getResolution()** return resolution set.
- **bool getAddress(uint8_t \* buf)** returns true if the sensor is configured (available).
Buf must be a byte array of at least 8 bytes.

This "async only" allows the class to be both minimal in size and non-blocking. 
In fact the class has no support for a synchronous read in one call. 
This choice will teach people how to work in a non-blocking way from the start.

Effort has been taken to keep the code, variables and function names compatible with 
ATCL library mentioned above. This way you can step over to that one with relatively
few problems when you need more functionality like multiple sensors on one pin.

Finally this library will probably make it easier to use a DS18B20 with processing 
boards or IC's with small memory footprint.


#### Config

- **void setConfig(uint8_t config)** set DS18B20_CLEAR or DS18B20_CRC. 
If DS18B20_CRC flag is set the library will check the CRC, otherwise it won't.
Not checking the CRC is a few milliseconds faster.
- **uint8_t getConfig()** get current configuration 
  - 1 == DS18B20_CRC
  - 0 == no flag set.


## Operation

This library supports only **one** DS18B20 per Arduino/ MCU pin.

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


#### Disconnect

During tests with **DS18B20_test_disconnect.ino** I noticed:
- set resolution to 9 bits + disconnected data line ==> sensor blocks and keeps 9 bits resolution.
- set resolution to 9 bits + disconnected VCC line ==> sensor stops and restarts at 12 bits resolution.
- set resolution to 9 bits + disconnected GND line ==> sensor keeps running at 9 bits resolution.


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


#### Diagnosis notes

It was noted that the library sometimes give unexpected values, and keep 
sending these values.

This is due to the fact that by default the CRC is not checked to speed up reading. 
In fact, default only the two temperature registers are read.
By setting ```sensor.setConfig(DS18B20_CRC);``` the whole scratchpad is read
and the CRC can be checked. 


table of known "strange values" and actions one could take.
It is meant to start some diagnosis.

| value   | possible cause                      | optional action |
|:--------|:------------------------------------|:----------------|
|  0.0000 | data line has no pull up            | use pull up     |
| -0.0625 | data line is constantly pulled HIGH | check GND       |
| -128    | CRC error                           | wrong pull up, bad sensor ? | 
| -127    | DISCONNECTED                        | check wires     }

If a value occurs only once in a while, wiring is often the cause, 
or it can be caused by e.g. induction e.g. switching on a motor while 
sensor is read.


## Credits

Miles Burton who originally developed the Arduino Temperature Control Library.
and all people who contributed to that lib.


## Future

#### Must

- elaborate performance connected state.

#### Should

- add examples
- investigate performance gain of no CRC.
- Extend oneWireSearch with device types
  - see oneWireScanner.ino (2016 version)
- should checkConnect be a **config** flag like CRC?

#### Could

#### Wont

- unit tests
  - get it working is too time consuming.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

