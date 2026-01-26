
[![Arduino CI](https://github.com/RobTillaart/DS18B20_INT/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DS18B20_INT/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DS18B20_INT/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DS18B20_INT/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DS18B20_INT/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DS18B20_INT.svg)](https://github.com/RobTillaart/DS18B20_INT/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DS18B20_INT/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DS18B20_INT.svg?maxAge=3600)](https://github.com/RobTillaart/DS18B20_INT/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DS18B20_INT.svg)](https://registry.platformio.org/libraries/robtillaart/DS18B20_INT)


# DS18B20_INT

Arduino library for the DS18B20 temperature sensor - restricted to one sensor per pin.


## Arduino Temperature Control Library (ATCL)

This DS18B20 library is not a full featured library for the DS18B20 family.
This library supports only one DS18B20 per Arduino/ MCU pin.
Furthermore this library will give only temperatures in whole degrees C.
Goal is to minimize footprint.

If you need more functions or control over the DS18B20 family I refer to the library
of Miles Burton - https://github.com/milesburton/Arduino-Temperature-Control-Library

I'm a great fan of the above library however some time ago I needed to strip it down 
to save a few dozen bytes. I reworked that minimalistic version into a library and I 
added a number of Arduino examples to help you get started.

Effort has been taken to keep the code, variables and function names compatible with 
ATCL library mentioned above. This way you can step over to that one with relatively
few problems when you need more functionality like multiple sensors on one pin.

Finally this library will probably make it easier to use a DS18B20 with processing 
boards or IC's with small memory footprint.

Feedback, as always, is welcome.


### Footprint OneWire

This library depends (is build) upon the **OneWire** library of Paul Stoffregen.
- https://github.com/PaulStoffregen/OneWire - the reference imho.

In issue [#31](https://github.com/RobTillaart/DS18B20_RT/issues/31) the footprint of 
the OneWireNG seems to be smaller when build on platformIO.

So if you are in need to save some more bytes, you might try [OneWireNG]
(https://github.com/pstolarz/OneWireNg).


### Compatibles

|  device      |  tested  |   power   |  bits  |  notes  |
|:-------------|:--------:|:---------:|:------:|:--------|
|  DS18B20     |    yes   |   3-5 V   |  9-12  |  the reference
|  DS18S20     |     n    |   3-5 V   |  9     |
|  DS1822      |     n    |   3-5 V   |  9-12  |
|  DS1820      |     n    |   5 V     |  9     |
|  MAX31820    |     n    |   3 V     |  9-12  |

Not all tested, but expected to work. If there are missing devices or you have
tested one, please let me know. 


### Related

This library is related to

- https://github.com/RobTillaart/DHTNew DHT11/22 etc
- https://github.com/RobTillaart/DHTStable DHT11/22 etc
- https://github.com/RobTillaart/DHT_Simulator
- https://github.com/RobTillaart/DS18B20_INT OneWire temperature sensor
- https://github.com/RobTillaart/DS18B20_RT OneWire temperature sensor
- https://github.com/RobTillaart/DS18B21 OneWire temperature sensor (8 bit)
- https://github.com/milesburton/Arduino-Temperature-Control-Library
- https://github.com/milesburton/Arduino-Temperature-Control-Library/issues/244#event-9253126638
- https://github.com/RobTillaart/PCT2075 11 bit I2C temperature sensor with thermal watchdog.
- https://github.com/RobTillaart/SHT31 Sensirion humidity / temperature sensor
- https://github.com/RobTillaart/SHT85 Sensirion humidity / temperature sensor
- https://www.kandrsmith.org/RJS/Misc/Hygrometers/calib_many.html (interesting)
- https://github.com/RobTillaart/Temperature (conversions, dewPoint, heat index etc.)


Dependency
- https://github.com/PaulStoffregen/OneWire
- https://github.com/pstolarz/OneWireNg (alternative)


## Interface

```cpp
#include "DS18B20_INT.h"
```


### Constructor

This DS18B20_INT library supports only the DS18B20, only one sensor per pin, no parasite 
mode, no Fahrenheit and no alarm functions. The only feature the class supports is 
the asynchronous reading of the temperature by means of three core functions:

- **DS18B20_INT(OneWire \*)** constructor needs a reference to OneWire object.
- **bool begin(uint8_t retries = 3)** resets oneWire and set resolution default to 9 bit.  
Returns true if address / device is found and all is OK. 
There will be a number of retries to connect, default 3.
- **bool isConnected(uint8_t retries = 3)** Returns true if address / device is found.
There will be a number of retries to connect, default 3.
- **bool getAddress(uint8_t \* buffer)** returns true if the sensor is configured (available).
Buffer must be a byte array of at least 8 bytes.

### Core

- **void requestTemperatures()** trigger temperature conversion.
- **bool isConversionComplete()** check if conversion is complete.
- **int16_t getTempC(bool connectCheck = true)** returns temperature in whole degrees only. 
-55..125  or  -127 = DEVICE_DISCONNECTED
Is faster when connectCheck is set to false. Default true = backwards compatible.
- **bool getAddress()** returns true if the sensor is configured (available).


### CentiC part

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


### -127 and 85

Two specific return values from reading the sensor:

- minus 127 == DEVICE_DISCONNECTED
- plus 85 is the power on default. 
If you get this unexpected it may indicate a power problem


### Pull up resistor

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


### Diagnostic notes

It was noted that the library sometimes give unexpected values, and keep 
sending these values.

This is due to the fact that by default the CRC is not checked to speed up reading. 
In fact, only the two temperature registers are read.

Table of known "strange values" and actions one could take.
It is meant to start some diagnosis.

(note these are all known errors, not perse for this library)

| value   | possible cause                      |  optional action  |
|:--------|:------------------------------------|:------------------|
|  0.0000 | data line has no pull up            |  use pull up
| -0.0625 | data line is constantly pulled HIGH |  check GND
| -127    | DISCONNECTED                        |  check wires
| -128    | CRC error                           |  wrong pull up, bad sensor ? | 
| -129    | POR error                           |  no convert done after power up. redo convert call.
| -130    | GND error                           |  if parasitic mode, check Vdd must be connected to GND.

If a value occurs only once in a while, wiring is often the cause, 
or it can be caused by e.g. induction e.g. switching on a motor while 
sensor is read.

Additional notes:

- https://github.com/milesburton/Arduino-Temperature-Control-Library/pull/289



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

- improve documentation
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

