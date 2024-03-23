
[![Arduino CI](https://github.com/RobTillaart/DS2401/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DS2401/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DS2401/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DS2401/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DS2401/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DS2401.svg)](https://github.com/RobTillaart/DS2401/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DS2401/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DS2401.svg?maxAge=3600)](https://github.com/RobTillaart/DS2401/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DS2401.svg)](https://registry.platformio.org/libraries/robtillaart/DS2401)


# DS2401

Library for the DS2401 1-wire unique identification chip.


## Description

The DS2401 is an ID chip that uses the oneWire (1-Wire) protocol. 
In fact it just returns its address as these are (quite) unique.

Every oneWire device has a unique 48 bit number which together with
the device family byte and an 8 bits CRC forms 8 byte unique code.
The family byte adds to the uniqueness however the CRC does not.
Although the CRC does not add to the uniqueness, it is taken into
the UID as it allows to check the other 7 bytes for integrity.

As there are at least 8 device types / families known, there are 
thus at least 51 bits of uniqueness.
This gives in total more than 10^15 bit patterns, which should be 
sufficient for most applications.
Leaving out the family byte, still gives more than 10^14 bit patterns.
This is implemented in **getUID6()** and **compareUID6()**.

The library is meant for DS2401 chips but allows all oneWire devices
to be used as an unique ID (UID). This implies that functionality
like e.g. temperature sensing is not available with this library.

Known family bytes, there are many other 1-Wire devices with unknown family.

|  byte  |  device    |  description  |
|:------:|:----------:|:--------------|
|  0x01  |  DS2401    |  UID device
|  0x05  |  DS2405    |  Switch
|  0x10  |  DS18S20   |  thermometer
|  0x22  |  DS1822    |  thermometer
|  0x26  |  DS2438    |  Battery monitor
|  0x28  |  DS18B20   |  thermometer
|  0x2D  |  DS2807    |  EEPROM
|  0x38  |  DS1825    |  thermometer
|  0x3B  |  MAX31850  |  thermometer
|  0x42  |  DS28EA00  |  thermometer


#### Related

- https://github.com/RobTillaart/DS2401
- https://github.com/RobTillaart/DS28CM00    (I2C)
- https://github.com/RobTillaart/UUID
- https://github.com/RobTillaart/DS18B20_INT
- https://github.com/RobTillaart/DS18B20_RT
- https://github.com/milesburton/Arduino-Temperature-Control-Library


## Interface

```cpp
#include "DS2401.h"
```

#### Constructor

This DS2401 library supports only one device per pin, and no parasite mode.
The class supports getting an UID and compare an UID.

- **DS2401(OneWire \* ow)** constructor needs a reference to OneWire object.
- **bool begin()** resets oneWire and search for the device address. 
Returns true if address / UID of the device is found.
Must be called to read the UID.


#### 8 bytes UID

- **void getUID(uint8_t \* buffer)** copies the found UID (64 bits) in 
**begin()** to a buffer which should be at least 8 bytes.
- **bool compareUID(uint8_t \* buffer)** compares the buffer (8 bytes) 
with the internal UID. Returns true if they are identical.


#### 6 bytes UID

The 6 bytes interface does not use the family byte and the CRC byte in the UID.
The reason is that these are either constant or can be calculated from the other
bytes, so not unique.

- **void getUID6(uint8_t \* buffer)** copies the found UID (48 bits) in 
**begin()** to a buffer which should be at least 6 bytes.
- **bool compareUID6(uint8_t \* buffer)** compares the buffer (6 bytes) 
with 6 bytes of the internal UID.
Returns true if they are identical.


#### 4 bytes UID

The 4 bytes interface only uses 4 bytes of the unique part of the address.
These functions are added as it allows to copy the number directly into a
uint32_t variable.

- **void getUID4(uint32_t \* buffer)** copies 4 unique bytes of the found UID 
to a uint32_t variable.
- **bool compareUID4(uint32_t \* buffer)** compares the uint32_t variable
with 4 unique bytes of the internal UID.
Returns true if they are identical.


## Operation

This library supports only one DS2401 per Arduino / MCU pin.

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

Connect a pull-up resistor 4.7 KΩ between pin3 and pin2. 
When the wires are longer this resistor needs to be smaller.


## Future

#### Must

- Improve documentation.
- test with different hardware.
- verify UID4 interface with hardware


#### Should


#### Could

- performance test. (mainly fetching)

#### Wont

- get any subset of the 8 bytes? => user can do this.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

