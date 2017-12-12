# DHT Library

## Description

The DHT11, 21, 22, 33 and 44 are relative inexpensive sensors for measuring temperature and humidity.

This library can be used for reading both values from these DHT sensors.
The DHT11 only returns integers (e.g. 20) and does not support negative values.
The others are quite similar and provide one decimal digit (e.g. 20.2)
The hardware pins of the sensors and handshake are identical so ideal to combine in one lib.

The library (0.1.13 version) is confirmed to work on:

*UNO (tested myself)
*2009 (tested myself)
*MEGA2560
*DUE
*attiny85 @8MHz
*Digistump Digix @ 84 MHz

Later 0.1.xx versions are optimized for AVR.

More information - http://playground.arduino.cc//Main/DHTLib -

## Operational

TODO pin description


## Versions:

==> See DHTStable library for latest stable version for all platforms.

* version 0.1.13 is the last stable version for both AVR and ARM 
* version 0.1.14 and up are not compatible anymore with pre 1.0 Arduino
* version 0.1.14 and up have breaking changes wrt ARM based arduino's e.g DUE.
* version 0.1.15 is stable version for AVR only
* version 0.1.16 and 0.1.17 have breaking changes for DHT11
* version 0.1.18 works again for DHT11 (avr only)
* version 0.1.19 fixed masking bug DHT11 (avr only)
* version 0.1.20 Reduce footprint (34 bytes) by using int8_t as error codes. (thanks to chaveiro)
* version 0.1.21 replace delay with delayMicroseconds() + small fix (thanks to codingforfun)
* version 0.1.22 undo delayMicroseconds() for wakeups larger than 8
* version 0.1.23 FIX https://github.com/RobTillaart/Arduino/issues/31
* version 0.1.24 FIX https://github.com/RobTillaart/Arduino/issues/33
* version 0.1.25 FIX https://github.com/RobTillaart/Arduino/issues/80
* version 0.1.26 Explicit support for AM23XX series and DHT12
