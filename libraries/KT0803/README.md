
[![Arduino CI](https://github.com/RobTillaart/KT0803/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/KT0803/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/KT0803/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/KT0803/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/KT0803/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/KT0803.svg)](https://github.com/RobTillaart/KT0803/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/KT0803/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/KT0803.svg?maxAge=3600)](https://github.com/RobTillaart/KT0803/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/KT0803.svg)](https://registry.platformio.org/libraries/robtillaart/KT0803)



# KT0803

Arduino Library for KT0803 FM transmitter.


## Legal point of attention

In different countries there are different laws with respect to using transmitting devices 
and their range. 
Please inform yourself of the local rules and laws if and how you may or may not use a 
device like the KT0803 in your projects, either hobby, commercial or otherwise.


## Description

This **experimental** library allows basic control of the KT0803 FM transmitter device.
It is written as I wanted to understand the possibilities and the interface of the device.

The library is not tested yet with hardware. (see future).

There are some newer, more capable, follow up devices like model K, L and M however these 
are not supported (yet) although they probably will work as they seem backwards compatible.

#### Warning

The KT0803 is an 3.3 Volt device and cannot be connected directly to 5V MCU's.


#### Related

- https://github.com/RobTillaart/KT0803
- https://www.hackster.io/hesam-moshiri/stereo-digital-fm-transmitter-circuit-arduino-code-2dbd8d
- https://www.hackster.io/hesam-moshiri/full-digital-fm-receiver-with-arduino-and-tea5767-52be37
- https://www.hackerstore.nl/Artikel/388



## Interface

```cpp
#include "KT0803.h"
```

`
#### Constructor

- **KT0803(uint8_t address, TwoWire \*wire = &Wire)** constructor, 
optional Wire interface.
- **bool begin()** initializes the library.
Furthermore it checks if the deviceAddress is available on the I2C bus.
Returns true if deviceAddress is found on the bus, false otherwise.
- **bool isConnected()** test to see if deviceAddress is found on the I2C-bus.


#### Frequency

- **bool setFrequency(float frequency)** converts the frequency to call **setChannel()**
- **float getFrequency()** returns the current frequency, can be slightly different,
due to rounding math. 
The return value if derived from **getChannel()**
- **bool setChannel(uint16_t channel)** sets the channel to broadcast on.
- **uint16_t getChannel()** returns the set channel.
 
 
#### PGA, RFGain

Read datasheet.

- **bool setPGA(uint8_t pga)**
- **uint8_t getPGA()**

|  pga  |  gain   |
|:-----:|:-------:|
|  111  |  12dB   |
|  110  |   8dB   |
|  101  |   4dB   |
|  100  |   0dB   |
|  000  |   0dB   |
|  001  |  -4dB   |
|  010  |  -8dB   |
|  011  |  -12dB  |

- **bool setRFGain(uint8_t rfgain);
- **uint8_t getRFgain();

TODO RFGAIN table


#### Region selection

Read datasheet.

The first four are convenience wrappers for **setPHTCNST()**

- **void setEurope()**
- **void setAustralia()**
- **void setUSA()**
- **void setJapan()**
- **bool setPHTCNST(bool on)**
- **bool getPHTCNST()**

If some region is missing please let me know and I can add it.


#### PilotToneAdjust

Read datasheet.

- **bool setPilotToneAdjust(uint8_t mode)**  //  HIGH = 1 LOW = 0
- **uint8_t getPilotToneAdjust()**


#### Mute

- **bool setMute(bool mute)** enables or disables the transmitting.
- **bool getMute()** returns the current state. 


## Derived classes

The KT0803K/L/M devices might work as they seem backwards compatible.



## Future

#### Must

- improve documentation
  - fill in gaps (TODO).
- buy hardware
- test and verify.

#### Should

- check validity/range parameters
  - enums for parameters - readability?
- investigate support 
  - KT0803K, KT0803L, KT0803M (derived classes)
- at startup
  - mute device
  - set 'dummy' channel
  - preset channel array in .h file (hardcoded)


#### Could

- investigate efficiency of register access.
  - caching all (allowed) registers in **begin()** 0.1.1
    -  3 bytes for KT0803
    - 12 bytes for KT0803K
  - cache frequency.
  - only writing is needed. 
- need hardware to test.
- examples
  - create frequency hopping device
  - preset channels (eeprom?)
  - send binary data over FM?
- investigate tea5767 FM receiver


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

