# DS18B20

Arduino library for the DS18B20 sensor - restricted to one sensor per pin.

## Arduino Temperature Control Library (ATCL)

This DS18B20 library is not a full featured library for the DS18B20 family.
This library supports only one DS18B20 per Arduino/ MCU pin.

If you need more functions or control over the DS18B20 family I refer to the library
of Miles Burton - https://github.com/milesburton/Arduino-Temperature-Control-Library

## Description

I'm a great fan of the above library however some time ago I needed to strip it down 
to save a few dozen bytes. I reworked that minimalistic version into a library and I 
added a number of Arduino examples to help you get started. 

The DS18B20 library supports only the DS18B20, only one sensor per pin, no parasite 
mode, no Fahrenheit and no alarm functions. The only feature the class supports is 
the asynchronous reading of the temperature by means of three core functions:

* void requestTemperatures()
* bool isConversionComplete()
* float readTempC()

The other main functions are
* bool begin(void);  *// returns true if the sensor is configured (available)*
* void setResolution(uint8_t);
* bool getAddress(uint8_t*)  *// returns true if the sensor is configured (available)*

This allowed the class to be both minimal in size and non-blocking. In fact the class
has no support for a synchronous read in one call. This choice will teach people
how to work in a non-blocking way from the start.

Effort has been taken to keep the code, variables and function names compatible with 
ATCL library mentioned above. This way you can step over to that one with relatively
few problems when you need more functionality like multiple sensors on one pin.

Finally this library will probably make it easier to use a DS18B20 with processing 
boards or IC's with small memory footprint.

## Operation

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
	
This library supports only one DS18B20 per Arduino/ MCU pin.

Connect a pull-up resistor 4.7 KOhm between pin3 and pin2. When the wires are longer 
this resistor needs to be smaller. 

### Pull up resistor

An **indicative** table for pull up resistors, (E12 series), to get started.

Note: thicker wires require smaller resistors (typically 1 step in E12 series) 


| Length        | - 5.0 Volt  | - 3.3 Volt |
|--------------:|------------:|----------:|
| 10cm (4")     | 10K0  | 6K8 |
| 20cm (8")     |  8K2  | 4K7 |
| 50cm (20")    |  4K7  | 3K3 | 
| 100cm (3'4")  |  3K3  | 2K2 | 
| 200cm (6'8")  |  2K2  | 1K0 | 
| 500cm (16'8") |  1K0  | *   |  
| longer        |    *  | *   |

\* = no info, smaller 


## Credits

Miles Burton who originally developed the Arduino Temperature Control Library.
and all people who contributed to that lib.

