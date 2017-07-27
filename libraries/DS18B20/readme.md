# DS18B20 Library

## Arduino Temperature Control Library (ATCL)

This DS18B20 library is not a full featured library for the DS18B20 family.
If you need more functions or control over the DS18B20 family I refer to the library
of Miles Burton - https://github.com/milesburton/Arduino-Temperature-Control-Library

## Description

I'm a great fan of the above library however some time ago I needed to strip it down 
to save a few dozen bytes. I reworked that minimalistic version into a library and I 
added a number of Arduino examples to help you get started. 

The DS18B20 library supports only the DS18B20, only one sensor per pin, no parasite 
mode, no Fahrenheit and no alarm functions. The only feature the class supports is 
the asynchronous reading of the temperature by means of three core functions:

* requestTemperatures()
* isConversionComplete()
* readTempC()

This allowed the class to be both minimal in size and non-blocking. In fact the class
has no support for a synchronous read in one call. This choice will teach people
how to work in a non-blocking way from the start.

Effort has been taken to keep the code, variables and function names compatible with 
ATCL library mentioned above. This way you can step over to that one with relatively
few problems when you need more functionality like multiple sensors on one pin.

Finally this library will probably make it easier to use a DS18B20 with processing 
boards or IC's with small memory footprint.

## Operation

This library supports only one DS18B20 per Arduino/ MCU pin.
Pin1 = Ground
Pin2 = Data
Pin3 = VCC

Connect a pull-up resistor 4.7 KOhm between pin3 and pin2. When the wires are longer 
this resistor needs to be smaller.

## Credits

Miles Burton who originally developed the Arduino Temperature Control Library.
and all people who contributed to that lib.

## License

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

