
[![Arduino CI](https://github.com/RobTillaart/AD524X/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AD524X/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AD524X/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AD524X/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AD524X/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AD524X.svg)](https://github.com/RobTillaart/AD524X/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AD524X/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AD524X.svg?maxAge=3600)](https://github.com/RobTillaart/AD524X/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AD524X.svg)](https://registry.platformio.org/libraries/robtillaart/AD524X)


# AD524X

Arduino class for I2C digital potentiometer AD5241 AD5242 AD5280 AD5282.


## Description

The AD5241, AD5242, AD5280 and AD5282 are digital potentiometers.
The AD5241/80 has one, the AD5242/82 has two potentiometers.
Both types have two output lines O1 and O2.

The main difference in the AD524x and AD528x series is the resistance.
See the table below.

The AD5280/82 is compatible with AD5241/42 (based upon datasheet compare).
The library provides separate classes for the AD5280/82 however these are 
not tested with actual hardware yet.
Please let me know if you get the AD5280/82 classes working.

|  device  |  channels  |  steps  |  ranges KΩ      | 
|:--------:|:----------:|:-------:|:---------------:|
|  AD5241  |     1      |   256   |  10, 100, 1000  |
|  AD5242  |     2      |   256   |  10, 100, 1000  |
|  AD5280  |     1      |   256   |  20,  50,  200  |
|  AD5282  |     2      |   256   |  20,  50,  200  |


An important property of the devices is that they defaults
to their mid position at startup.

The library defines AD524X_MIDPOINT == 127.
To be used to set to defined mid-point.


#### 0.5.0 Breaking change

The ESP32 specific **begin(sda, scl)** is removed.
The user has to call **Wire.begin()** or equivalent himself before calling **begin()**.


#### Related

- https://github.com/RobTillaart/AD520x
- https://github.com/RobTillaart/AD524X
- https://github.com/RobTillaart/AD5245
- https://github.com/RobTillaart/AD5248 (also AD5243)
- https://github.com/RobTillaart/AD5144A
- https://github.com/RobTillaart/AD5263
- https://github.com/RobTillaart/X9C10X


#### Compatibles ?

If you find compatible devices please let me know.


## I2C address

The AD524X has two address lines to configure the I2C address. 0x2C - 0x2F

| Addr(dec)| Addr(Hex) |  AD1  |  AD0  |
|:--------:|:---------:|:-----:|:-----:|
|  44      |  0x2C     |  GND  |  GND  |
|  45      |  0x2D     |  GND  |  +5V  |
|  46      |  0x2E     |  +5V  |  GND  |
|  47      |  0x2F     |  +5V  |  +5V  |


## Interface

```cpp
#include "AD524X.h"
```

The library has a number of functions which are all quite straightforward.
One can get / set the value of (both) the potentiometer(s), and the O1 and O2 output lines.


#### Constructors

- **AD524X(uint8_t address, TwoWire \*wire = &Wire)** constructor base class,
creates an instance with 2 potentiometer.
This class does not distinguish between AD5241/42/80/82.
The developer is responsible for handling this correctly.
- **AD5241(uint8_t address, TwoWire \*wire = &Wire)** create an instance with 1 potentiometer.
- **AD5242(uint8_t address, TwoWire \*wire = &Wire)** create an instance with 2 potentiometer.
- **AD5280(uint8_t address, TwoWire \*wire = &Wire)** create an instance with 1 potentiometer.
- **AD5282(uint8_t address, TwoWire \*wire = &Wire)** create an instance with 2 potentiometer.


#### Wire initialization

- **bool begin()** initialization of the object. 
Note the user must call **wire.begin()** or equivalent before calling **begin()**.
- **bool isConnected()** See if the address set in constructor is on the I2C bus.
- **uint8_t getAddress()** returns address set in constructor, convenience.


#### Basic IO

- **uint8_t write(uint8_t rdac, uint8_t value)** set channel rdac 0/1 to value 0..255.
- **uint8_t write(uint8_t rdac, uint8_t value, uint8_t O1, uint8_t O2)** idem + set output lines O1 and O2 too.
- **uint8_t read(uint8_t rdac)** read back set value.
- **uint8_t setO1(uint8_t value = HIGH)** value = HIGH (default) or LOW.
- **uint8_t setO2(uint8_t value = HIGH)** value = HIGH (default) or LOW.
- **uint8_t getO1()** read back O1 line.
- **uint8_t getO2()** read back O2 line.


#### Misc

- **uint8_t zeroAll()** sets potentiometer's to 0 and I/O to LOW.
- **uint8_t reset()** sets potentiometer's to midpoint == 127 and I/O to LOW. (startup default)
- **uint8_t midScaleReset(uint8_t rdac)** resets one potentiometer to midpoint == 127.
- **uint8_t readBackRegister()** read register back, for debugging.


#### Experimental

- **uint8_t shutDown()** check datasheet, not tested yet, use at own risk.


## Interface AD5421 + AD5280 specific

Since 0.4.1 the library supports writing explicit to port 0
as that is the only port.

- **uint8_t write(const uint8_t value)** set rdac 0 to value 0..255.
- **uint8_t write(const uint8_t value, const uint8_t O1, const uint8_t O2)**
idem + set output lines O1 and O2 too.

Note that **uint8_t write(rdac, value)** and **uint8_t write(rdac, value, O1, O2)**
can be called and return **AD524X_ERROR** if **rdac > 0**. 


## Error codes

|  define        |  value  |
|:---------------|:-------:|
|  AD524X_OK     |   0     |
|  AD524X_ERROR  |   100   |


## Future

#### Must

- improve documentation.

#### Should

- verify the working of AD5280 and AD5282.
- improve error handling.
- sync with AD520X library.

#### Could


#### Wont

- make midpoint 128


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

