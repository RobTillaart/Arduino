
[![Arduino CI](https://github.com/RobTillaart/RS485/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/RS485/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/RS485/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/RS485/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/RS485/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/RS485.svg)](https://github.com/RobTillaart/RS485/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/RS485/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/RS485.svg?maxAge=3600)](https://github.com/RobTillaart/RS485/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/RS485.svg)](https://registry.platformio.org/libraries/robtillaart/RS485)


# RS485

Arduino library for RS485 communication.


## Description

RS485 is an **experimental** library to make half duplex communication easier.
The library implements the Stream interface so the user can use
**print()** and **write()** calls just like one does with **Serial**.

Preferably the library is to be used with a **hardwareSerial** as these 
can buffer incoming characters in the background. 
A software Serial that uses pin interrupts would also work quite well,
needs to be tested.

The 0.2.0 version of the library has no (tested) protocol for multi-byte 
messages so the user must implement such on top of this class.


#### Connection schema

```
         Processor                      MAX485
    +------------------+            +-------------+
    |                  |            |             |
    |              RX  |<-----------|  RO         |
    |              TX  |----------->|  DI         |
    |                  |            |             |
    |                  |       +--->|  RE         |
    |          sendPin |-------+--->|  DE         |
    |                  |            |             |
    |             VCC  |------------|  VCC        |
    |             GND  |------------|  GND        |
    |                  |            |             |
    +------------------+            +-------------+
   
    RX = Receive Serial               RO = Receiver Output
    TX = Transmit Serial              DI = Driver Input
    sendPin = IO.pin                  RE = Receiver Output Enable
                                      DE = Driver Output Enable
```

#### Related

- https://www.gammon.com.au/forum/?id=11428
- http://en.wikipedia.org/wiki/RS485
- https://www.ti.com/lit/an/snla049b/snla049b.pdf - 10 ways to bulletproof your RS485
- https://github.com/RobTillaart/CRC
- https://www.arduino.cc/reference/en/language/functions/communication/stream/


## Interface

```cpp
#include "RS485.h"
```


#### Base

- **RS485(Stream \* stream, uint8_t sendPin, uint8_t deviceID = 0)** constructor.
The default device ID is 0 (typically master uses this, or if deviceID is not used).
The stream is typically Serial, and the baud rate, timeout etc. should be set 
via the Serial class. 
The sendPin is the pin that connects to the transmit/receive enable (DE/RE) pins.
See connection schema above.
The library sets the pinMode and defaults it to LOW (receiving mode).
- **void setMicrosPerByte(uint32_t baudRate)** set the delay per character needed.
This gives the hardware enough time to flush the buffer. 
- **uint32_t getMicrosPerByte()** returns the current delay in micros used.
- **void setTXmode()** explicitly set mode to transmitting / sending.
This implies that the device will stop listening on the RS485 bus.
- **void setRXmode()** explicitly set mode to receiving / listening.
This is the default behaviour of every RS485 device.
- **uint8_t getMode()** returns the current mode, 1 == TX, 0 == RX.


#### Stream interface

The most important commands of the Stream interface are:

- **int available()** returns the number of characters available in the buffer.
- **int read()** read a character from the RS485 stream.
- **int peek()** peeks a character ahead. (less used).
- **void flush()** flush the stream. (less used).
- https://www.arduino.cc/reference/en/language/functions/communication/stream/

All variations of **print()**, **println()** and **write()** can be used,
the library calculates the time needed to set the RS485 chip in transmit mode.

An important command from the stream interface is the **setTimeOut()** as
this allows reads on the RS485 bus that are limited.


#### Experimental

Work in progress. The library has an experimental protocol implemented to
send and receive larger messages between the nodes in the network. 
This network consists of one master that can poll multiple slaves. 

In 0.2.5 this protocol has been tested and some bugs in the receive parser
have been fixed. It still is experimental and it needs more testing.

The library functions are:
- **void send(uint8_t receiverID, uint8_t msg[], uint8_t len)**
  - send a buffer of given length to a receiver.
- **bool receive(uint8_t &senderID, uint8_t msg[], uint8_t &len)**
  - receive a packet, senderID identifies the sender. 

Current implementation limits messages up to 48 bytes (hardcoded buffer size)
which is in many cases enough.

See two example sketches.


## Operation

A RS485 controlled device is typically waiting for a command or message 
and is therefore default in listening or receiving mode. Only when
the device needs to answer the library will automatically set the RS485 
chip in sending mode, wait for enough time to "flush the buffer" and 
resumes with listening.


#### Sniffer hex dump

Since 0.2.5 an example is added that sniffs the bytes on the RS485 bus 
and prints them as a HEX dump.

Can be used for debugging.


#### Pull up resistors

Do not forget to use one pull up (A line) and one pull down (B line) 
at only one end of the bus.
Values depend on the length of the cables, start with 1 KΩ (kilo ohm)


#### Wires

Preferred wire for RS485 is STP (Shielded Twisted Pair), however 
UTP (Unshielded) will works in many cases.
Typical for most applications CAT5 (100 Mbit) will do the job.
Do not forget to connect GND to the shield later of the STP.

Note CAT5 has 4 x 2 twisted wires so there are 6 cables to spare.
These could be used e.g. to build a FULL DUPLEX version in which
every slave has 2 RS485 ports, one for receiving and one for sending.
Another application is to use these as power lines e.g 5 and 12 V.


#### yield()

For RTOS environments the **yield()** function needs to be called 
when code might be blocking. As the RS485 baud rate can be pretty low, 
the **write(array, length)** function can be blocking for too long 
so the function can call **yield()** every 4 milliseconds if enabled.

To enable **yield()** uncomment the following line in **RS485.cpp**

```cpp
// #define RS485_YIELD_ENABLE  1
```

or set this flag in the command line compile option.

Note: the **yield()** calling version is substantial slower, depending 
on the baud rate. Use with care.

TODO: to be tested on ESP32 - RTOS.


#### Protocol design

An error I made in one of my first RS485 experiments was that a possible
response of one module would trigger another module to also send a response.
Of course these two responses interacted quite consistent but wrong.
It took some time to find the cause and to redesign the protocol used.

Lesson learned was to spend more time designing the protocol up front.
And keep commands and responses 100% disjunct.

An example of a simple byte protocol could use commands all with 
bit 7 set to 1, and all responses with bit 7 set to 0 (E.g ASCII).
Would allow 127 different 1 byte commands.


## Future

#### Must

- improve documentation

#### Should

- improve **send()** and **receive()** for longer messages.
  - should be a message class.
  - extract from this lib (for now in the library).
  - dynamic receive buffer size?
- investigate error handling?
- expand write to other data types?
- test other platforms
  - ESP32.

#### Could

- setUsPerByte() parameter does not feel 100% (investigate)
  - rename to begin().
- improve the examples.
  - add binary protocol example
  - multi-master?
- add unit tests
- investigate yield() on ESP32/RTOS behaviour

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


