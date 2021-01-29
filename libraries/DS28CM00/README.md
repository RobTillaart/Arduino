
[![Arduino CI](https://github.com/RobTillaart/DS28CM00/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DS28CM00/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DS28CM00.svg?maxAge=3600)](https://github.com/RobTillaart/DS28CM00/releases)


# DS28CM00

Arduino library for I2C DS28CM00 unique identification chip.  \[48 bit\]

## Description

THe DS28CM00 IC has a 64 bit address consisting of one type byte, 0x50, 6 bytes unique serial and a CRC
over the previous 7 bytes. This results in an 48 bits unique ID giving 281.474.976.710.656 combinations.
If that number is not unique enough, you could use 2 or more of them with an I2C multiplexer.

The DS28CM00 IC has the same addressing scheme as the better known DS18B20, except for the type byte.
Therefor one could use an DS18B20 as an unique ID chip in a similar way and getting a temperature sensor
as bonus. 

The DS28CM00 can work in 2 modes, I2C and SMBus mode. check datasheet for details.

## Interface

### Constructor

- **DS28CM00(TwoWire \*wire)**
- **DS28CM00(dataPin, clockPin)** ESP32, ESP8266

### public
- **void begin()** initializes I2C bus, default DS28CM00_I2C_MODE
- **bool getUID(uint8_t \*serial)** get unique 8 bytes serial number or error.
- **bool setI2CMode()** set DS28CM00_I2C_MODE (0x00)
- **bool setSMBusMode()** set DS28CM00_SMBUS_MODE (0x01)
- **bool getMode(uint8_t &mode)** returns mode set above

## Operation

See examples.

The class is not tested extensively e.g. with ESP32 / ESP8266.
An example sketch for ESP32 exist and compiles. (feedback welcome)

