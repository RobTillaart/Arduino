
[![Arduino CI](https://github.com/RobTillaart/AD524X/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AD524X/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AD524X/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AD524X/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AD524X/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AD524X/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AD524X.svg?maxAge=3600)](https://github.com/RobTillaart/AD524X/releases)


# AD524X

Arduino class for I2C digital potentiometer AD5241 AD5242.


## Description

The AD5241 and AD5242 are digital potentiometers.
The AD5241 has one, the AD5242 has two potentiometers.
Both types have two output lines O1 and O2.

These digital potentiometers come in 10K, 100K and 1M
and can be set in 256 steps.

An important property of the devices is that they defaults
to their mid position at startup.


#### Related libraries

This library is related to - https://github.com/RobTillaart/AD5245
The AD5245 is a single port digital potentiometer.


## I2C address

The AD524X has two address lines to configure the I2C address. 0x2C - 0x2F 

| Addr(dec)| Addr(Hex) | AD0  | AD1  |
|:--------:|:---------:|:----:|:----:|
|  44      |  0x2C     | GND  | GND  |
|  45      |  0x2D     | GND  | +5V  |
|  46      |  0x2E     | +5V  | GND  |
|  47      |  0x2F     | +5V  | +5V  |


## Interface

The library has a number of functions which are all quite straightforward.
One can get / set the value of (both) the potentiometer(s), and the O1 and O2 lines.


### Constructors

- **AD524X(uint8_t address, TwoWire \*wire = &Wire)** base class, 
creates an instance with 2 potentiometer.
This class does not distinguish between AD5241 and AD5242. 
The developer is responsible for handling this correctly.
- **AD5241(uint8_t address, TwoWire \*wire = &Wire)** create an instance with 1 potentiometer.
- **AD5242(uint8_t address, TwoWire \*wire = &Wire)** create an instance with 2 potentiometer.


### Wire initialization

- **bool begin(uint8_t sda, uint8_t scl)** ESP32 a.o initializing of Wire.
- **bool begin()** for UNO.
- **bool isConnected()** See if address set in constructor is on the bus.


### Basic IO

- **uint8_t write(uint8_t rdac, uint8_t value)** set channel rdac 0/1 to value 0..255.
- **uint8_t write(uint8_t rdac, uint8_t value, uint8_t O1, uint8_t O2)** idem + set output lines O1 and O2 too.
- **uint8_t read(uint8_t rdac)** read back set value.
- **uint8_t setO1(uint8_t value = HIGH)**  value = HIGH (default) or LOW.
- **uint8_t setO2(uint8_t value = HIGH)**  value = HIGH (default) or LOW.
- **uint8_t getO1()** read back O1 line.
- **uint8_t getO2()** read back O2 line.


### Misc

- **uint8_t zeroAll()** sets potentiometer's to 0 and I/O to LOW.
- **uint8_t reset()** sets potentiometer's to midpoint = 127 and I/O to LOW. (startup default)
- **uint8_t midScaleReset(uint8_t rdac)** resets one potentiometer to midpoint = 127.
- **uint8_t readBackRegister()** read register back, for debugging.


### Experimental

- **uint8_t shutDown()** check datasheet, not tested yet, use at own risk.


## Operation

The examples show the basic working of the functions.


## Error codes

|  define        |  value  |
|:---------------|:-------:|
|  AD524X_OK     |   0     |
|  AD524X_ERROR  |   100   |


## Future

### should
- improve error handling.
- sync with AD520X library


#### wont
- make midpoint 128
