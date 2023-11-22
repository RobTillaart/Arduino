
[![Arduino CI](https://github.com/RobTillaart/SWSerialOut/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/SWSerialOut/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/SWSerialOut/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/SWSerialOut/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/SWSerialOut/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/SWSerialOut.svg)](https://github.com/RobTillaart/SWSerialOut/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/SWSerialOut/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/SWSerialOut.svg?maxAge=3600)](https://github.com/RobTillaart/SWSerialOut/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/SWSerialOut.svg)](https://registry.platformio.org/libraries/robtillaart/SWSerialOut)


# SWSerialOut

Arduino library for SWSerialOut, supports only data out (TX).


## Description

**Experimental**

SWSerialOut is a library that only implements the transmit function.
There are devices that do not send back information, or in some cases 
you do not use the "returned" information.
In those cases there is no need for the receive function, interrupt 
handling, buffers etc.

This is where SWSerialOut comes in, it can only transmit data and does
that by implementing the **public Stream** interface.
So its interface is similar to any Stream like Serial or SoftwareSerial,
as the user can use **print()** and **println()** for al the output.

The input side of the Stream interface, **available()**, **peek()**, 
and **read()** are stubs returning 0.

The library does not need to buffer incoming data, and it does not buffer outgoing data either. Therefore it can be blocking.
So use the library with care.


#### Test 

Test are done with example sketch **SWSO_test.ino** et al which
reads the send data back via hardware Serial.
The serial pulses, especially baud rates above 19200, will improve 
with a proper pull up resistor e.g. 4K7.

|  baud    |  UNO  |  ESP32  |  other  |
|---------:|:-----:|:-------:|:-------:|
|  300     |   Y   |    Y    |
|  600     |   Y   |    Y    |
|  1200    |   Y   |    Y    |
|  2400    |   Y   |    Y    |
|  4800    |   Y   |    Y    |
|  7200    |   Y   |    Y    |
|  9600    |   Y   |    Y    |
|  19200   |   Y   |    Y    |
|  38400   |   -   |    Y    |
|  57600   |   -   |    Y    |
|  76800   |   -   |    Y    |
|  100000  |   -   |    Y    |


Note: the code is not really optimized for any platform (yet). 
So the library will not match the top speed of other software serial implementations.

If you have tested this library with another platform, please let me know by
opening an issue with the relevant data.


#### Related

- https://github.com/RobTillaart/MiniMP3 - minimal version only needs serial out.


## Interface

```cpp
#include "SWSerialOut.h"
```

#### Constructor

- **SWSerialOut(uint8_t TXpin)** constructor.
- **void begin(uint32_t baudRate)** set baud rate (see table above)
- **void begin(uint32_t baudRate, char \* params)** params implemented.
however not tested yet.
The params are range checked.

params is e.g. "8N1" = 8 bit, None parity, 1 stop-bit

|  param    |  value    |  default  |  notes  |
|:---------:|:----------|:---------:|:--------|
|   bit     |  5,6,7,8  |     8     |  to be tested
| parity    | N,E,O,S,M |     N     |  to be tested
| stop bits |  0,1,2,3  |     1     |  to be tested


#### Stream interface

The SWSerialOut implements the **public Stream** interface, so
it will support the following functions (indirect from Print):

- **size_t write(char c)** idem.
- **size_t print(...)** idem.
- **size_t println(...)** idem.

The input functions are stubs, just returning 0.


#### Interrupts

To have a more constant timing while sending the bits one can disable 
interrupts during the transfer of the data.

- **void disableInterrupts(bool b)** enable/disable interrupts during send.


#### Debug

- **void debug()** dump internal variables.


## Future


#### Must

- update documentation
- test bits, parity, stop bits

#### Should

- examples
  - performance sketch

#### Could

- unit tests?
- support inverse logic.
- support 9 bits (low priority)
- add RTS / CTS handshake?
- investigate optimized transfer per platform 
  - higher baud rates, especially AVR.

#### Wont

- read()
- non blocking version 

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

