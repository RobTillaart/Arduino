
[![Arduino CI](https://github.com/RobTillaart/I2C_SCANNER/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/I2C_SCANNER/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/I2C_SCANNER/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/I2C_SCANNER/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/I2C_SCANNER/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/I2C_SCANNER.svg)](https://github.com/RobTillaart/I2C_SCANNER/issues)

[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](https://github.com/RobTillaart/I2C_SCANNER/blob/master/LICENSE)
[![GitHub Release](https://img.shields.io/github/release/RobTillaart/I2C_SCANNER.svg?maxAge=3600)](https://github.com/RobTillaart/I2C_SCANNER/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/I2C_SCANNER.svg)](https://registry.platformio.org/libraries/robtillaart/I2C_SCANNER)


# I2C_SCANNER

Arduino class to implement an I2C scanner.


## Description

I2C_SCANNER is a class to build an I2C scanner, either minimal or more complex.

The class provides different functions to analyse the connectivity of devices
on the I2C bus. There are functions to adjust the frequency and functions to 
select the bus in case of multiple I2C ports.

A typical other use is to see if all devices are available (breadboard test).

Furthermore there are different functions to scan the I2C port, 
see the section scanning below.

The address range for "normal" I2C devices is from 9 to 119. 
The user may use other values for address at his own risk. 

If there is missing functionality in this library, please file an issue.


#### 0.3.0 Breaking change

Version 0.3.0 introduced a breaking change.
You cannot set the pins in **begin()** any more.
This reduces the dependency of processor dependent Wire implementations.
The user has to call **Wire.begin()** and can optionally set the Wire pins 
before calling **begin()**.


#### Testing

The library is tested with the following boards:

|   board   |  works  |
|:---------:|:-------:|
|  UNO      |   yes   |
|  MEGA     |   yes   |
|  NANO     |    ?    |
|  ESP8266  |    ?    |
|  ESP32    |   yes   |

Please file an issue if your board does work (or not).


#### Related

- https://github.com/RobTillaart/MultiSpeedI2CScanner


## Interface

```cpp
#include "I2C_SCANNER.h"
```

#### Constructor

- **I2C_SCANNER(TwoWire \*wire = &Wire)** Constructor with the default Wire I2C bus.
- **bool begin()** To start the Wire library.


#### Configuration

- **bool setClock(uint32_t clockFrequency = 100000UL)** sets the speed of the I2C bus.
Returns true.
Note the supported frequency is board dependent. Check your boards datasheet.
- **uint32_t getClock()** supported by some platforms, including ESP32.
Please fill in issue if your board is missing here.
- **uint8_t getWireCount()** returns the number of Wire ports (hardware I2C).
To be used by **setWire(uint8_t n)**.
- **bool setWire(uint8_t n)** sets the Wire port by number.
Assumes there exist Wire, Wire1 ... Wire5.
The number n should not exceed the value returned by **getWireCount()**
- **bool setWire(TwoWire \*wire = &Wire)** set a Wire port by 'name' e.g. Wire1.
- **TwoWire \* getWire()** returns the Wire object set.


#### Scanning

- **uint16_t ping(uint8_t address, uint16_t count = 1)** Tries to make contact with I2C address.
Returns the number of successful "contacts / connections" with the address.
Typical number of retries is 1..5, however one can also do a long test up to 65535 retries.
Can be used for endurance test / diagnosis of responsiveness.  
Note the function does not call **yield()** intern so use with care.  
Note that when count is large, the function call will block for a long time. 
Better use a loop of e.g. 100 retries at a time. 
- **int diag(uint8_t address)** Tries to make contact with I2C address.
Returns Wire status code 0 == OK, other return values might depend on platform used.
- **int32_t pingTime(uint8_t address)** Tries to make contact with I2C address.
Returns time used in micros. Returns a negative time (< 0) if failed to contact.
- **uint8_t count(uint8_t start = 0, uint8_t end = 127)** pings address range.
Includes start and end address too. Returns the number of addresses found.


#### Reset

(needs testing)

- **int softwareReset(uint8_t method = 0)** sends a I2C SWRST command over the configured I2C bus.
This will cause all devices that support this command to do a "power on" reset.
The code implements two methods, 
  - 0 = NXP spec (default)
  - 1 = from PCA9634 issue.

The **softwareReset()** function should return 0 for success. 
The value -999 indicates invalid method selected.
Other are I2C specific error codes.


#### Timeout

Experimental

Not all platforms support this functionality, you need to patch I2C_SCANNER.cpp file to get 
this working for your platform.
- **bool setWireTimeout(uint32_t timeOut)**
- **uint32_t getWireTimeout()**


## Future ideas

#### Must

- documentation.

#### Should

- add examples.
- add **setWireTimeOut(uint32_t timeout, bool reset_with_timeout = true)**
  - portable? clear? reset? default?
  - needs to be set for every Wire interface
  - ESP8266 does have a **setClockStretchLimit(timeout)**

#### Could

- add **bool hardwareReset()** 
  - keep data HIGH for X clock pulses - google this.
  - (needs investigation)
  - https://github.com/esp8266/Arduino/issues/1025
- read the state of the I2C pins
  - **uint8_t readSDA()** diagnose the I2C bus. Board specific!
  - **uint8_t readSCL()** diagnose the I2C bus. Board specific!
- implement **getClock()** for AVR based platforms
  - reverse calculate TWBR and pre-scaler.
  - needs investigation
- support for RP2040
  - needs investigation
- add table with default I2C pins per platform / board
  - https://www.arduino.cc/reference/en/language/functions/communication/wire/


#### Won't

- device analysis
  - add **bool send(address, uint8_t \*buffer, uint8_t length)**
  - add **bool receive(address, uint8_t \*buffer, uint8_t length)**
- add iterator 
  - **uint8_t first(uint8_t start = 0)** returns address or 255
  - **uint8_t next()** returns address or 255.
- **uint8_t \_devices[16]** cache hits ?
  - No
- implement a **SW_I2C**
  - No, user may use a SW_I2C that derives from TwoWire.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

