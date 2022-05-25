
[![Arduino CI](https://github.com/RobTillaart/RS485/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/RS485/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/RS485/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/RS485/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/RS485/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/RS485/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/RS485.svg?maxAge=3600)](https://github.com/RobTillaart/RS485/releases)


# RS485

Arduino library for RS485.


## Description

RS485 is an **experimental** library to make half duplex communication easier.
The library implements the Stream interface so the user can use
**print()** and **write()** calls just like one does with **Serial**.

Preferably the library is to be used with a hardwareSerial as these 
can buffer incoming characters in the background.

The 0.2.0 version of the library has no (tested) protocol for multi-byte 
messages so the user must implement such on top of this class.


## Interface

#### Base

- **RS485(Stream stream, uint8_t sendPin, uint8_t deviceID = 0)** constructor.
The default device ID is 0 (typically master uses this, or if deviceID is not used).
The stream is typically Serial, and the baud rate, timeout etc. should be set 
via the Serial class. 
The sendPin is the pin that connects to the transmit/receive enable pins.
The library sets the pinMode and defaults it to LOW (receiving mode).
- **void     setMicrosPerByte(uint32_t baudRate)** set the delay per character needed.
This gives the hardware enough time to flush the buffer. 
- **uint32_t getMicrosPerByte()** returns the current delay in micros used.
- **void setTXmode()** explicitly set mode to transmitting / sending.
This implies that the device will stop listening on the RS485 bus.
- **void setRXmode()** explicitly set mode to receiving / listening.
This is the default behaviour of every RS485 device.
- **uint8_t getMode()** returns the current mode, 1 == TX, 0 == RX.


#### Stream interface

- **int available()** returns the number of characters available in the buffer.
- **int read()** read a character from the RS485 stream.
- **int peek()** peeks a character ahead. (less used).
- **void flush()** flush the stream. (less used).

All variations of **print()**, **println()** and **write()** can be used,
the library calculates the time needed to set the RS485 chip in transmit mode.


## Operation

A RS485 controlled device is typically waiting for a command or message 
and is therefore default in listening or receiving mode. Only when
the device needs to answer the library will automatically set the RS485 
chip in sending mode, wait for enough time to "flush the buffer" and 
resumes with listening. 

- see examples (TODO).


## Future

- improve documentation
- setUsPerByte() parameter does not feel 100%
- add **send()** and **receive()** for longer messages.
  - which handshake?
  - dynamic buffer size?
  - should this be a sort of message class / struct. fixed size?
- add **yield()** for large messages that are blocking.
- prevent blocking if possible.
- add examples
- add unit tests


