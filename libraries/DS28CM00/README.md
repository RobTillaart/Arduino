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

## Operation

See examples.

The class is not tested with ESP32 / ESP8266 yet, but an example sketch exist and compiles.
(feedback welcome)
