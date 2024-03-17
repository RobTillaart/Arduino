
[![Arduino CI](https://github.com/RobTillaart/AD5263/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AD5263/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AD5263/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AD5263/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AD5263/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AD5263.svg)](https://github.com/RobTillaart/AD5263/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AD5263/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AD5263.svg?maxAge=3600)](https://github.com/RobTillaart/AD5263/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AD5263.svg)](https://registry.platformio.org/libraries/robtillaart/AD5263)


# AD5263

Arduino library for I2C digital potentiometer AD5263 and compatibles.


## Description

The AD5263 is a digital potentiometer with 4 channels and very much alike the 
AD524X (single / dual channels).
This digital potentiometers come in 20, 50 and 200 kΩ and can be set in 256 steps.
This library only implements the I2C interface (See future for SPI).

An important property of the AD5263 device is that it defaults
to their mid position at startup.
The library defines **AD5263_MIDPOINT** == 128 (as per datasheet).
To be used to set to defined mid-point.

(Library is based on datasheet Rev.F )


#### Related

This library is related to

- https://github.com/RobTillaart/AD520x  multi port digital potentiometer.
- https://github.com/RobTillaart/AD524X  single/dual port digital potentiometer.
- https://github.com/RobTillaart/AD5245  single port digital potentiometer.
- https://github.com/RobTillaart/AD5248  (also AD5243) dual port potentiometer / rheostat.
- https://github.com/RobTillaart/AD5144A
- https://github.com/RobTillaart/AD5263
- https://github.com/RobTillaart/X9C10X
- https://www.analog.com/media/en/technical-documentation/data-sheets/ad5263.pdf


#### Compatibles

None known so far.


## Hardware connection AD5263

Please read datasheet for all details!

|  Pin  |   Name    |  Description (short)                   |  Notes  |
|:-----:|:----------|:---------------------------------------|:--------|
|   1   |       B1  |  Resistor Terminal B1.                 |
|   2   |       A1  |  Resistor Terminal A1    (ADDR = 00)   |
|   3   |       W1  |  Wiper Terminal W1.                    |
|   4   |       B3  |  Resistor Terminal B3.                 |
|   5   |       A3  |  Resistor Terminal A3.                 |
|   6   |       W3  |  Wiper Terminal W3       (ADDR = 10)   |
|   7   |      VDD  |  Positive Power Supply                 |
|   8   |      GND  |  Ground.                               |
|   9   |      DIS  |  SPI/I2C Select.  SPI = 0, I2C = 1     | connect to VDD |
|  10   |   VLOGIC  |  2.7 - 5.5V Logic Supply Voltage.      | connect to VDD |
|  11   |  SDI/SDA  |  (SPI data in)    I2C SDA              |
|  12   |  CLK/SCL  |  Serial Clock     I2C SCL              |
|  13   |   CS/AD0  |  (SPI Chip Select). I2C address bit 0  | see Address below |
|  14   |  RES/AD1  |  (SPI RESET) I2C Address bit 1         | see Address below |
|  15   |     SHDN  |  Shutdown. Tie to +5 V if not used.    |
|  16   |   SDO/O1  |  (SPI data out)   I2C  Output O1       |
|  17   |    NC/O2  |  (SPI No Connect) I2C Output O2        |
|  18   |      VSS  |  Negative Power Supply.                |
|  19   |       W4  |  Wiper Terminal W4       (ADDR = 11)   |
|  20   |       A4  |  Resistor Terminal A4.                 |
|  21   |       B4  |  Resistor Terminal B4.                 |
|  22   |       W2  |  Wiper Terminal W2       (ADDR = 01)   |
|  23   |       A2  |  Resistor Terminal A2.                 |
|  24   |       B2  |  Resistor Terminal B2.                 |


#### VLOGIC

The logic supply voltage should always be less than or equal to VDD.
In addition, logic levels must be limited to the logic supply voltage regardless of VDD.


## I2C

#### Address

The AD5263 has two address lines to configure the I2C address. 0x2C - 0x2F

|  Addr(dec) |  Addr(Hex)  |  AD0  |  AD1  |  Notes  |
|:----------:|:-----------:|:-----:|:-----:|:-------:|
|    44      |    0x2C     |  GND  |  GND  |
|    45      |    0x2D     |  GND  |  +5V  |
|    46      |    0x2E     |  +5V  |  GND  |
|    47      |    0x2F     |  +5V  |  +5V  |

Note the AD5263 uses the same range as the AD524X devices.


#### Performance

Timing in microseconds, writing a new value to device.

|  Speed   |  UNO  |  ESP32  |  RP2040  |  notes  |
|:--------:|:-----:|:-------:|:--------:|:--------|
|  100000  |  340  |         |          |
|  150000  |  240  |         |          |
|  200000  |  196  |         |          |
|  250000  |  168  |         |          |
|  300000  |  148  |         |          |
|  350000  |  140  |         |          |
|  400000  |  136  |         |          |  max advised speed  |
|  450000  |  128  |         |          |
|  500000  |  124  |         |          |  max working speed  |


The Arduino UNO failed to communicate above 500K, therefore
the maximum speed advised is 400000 bits/sec.

**TODO** Test with ESP32 / RP2040 / ... to fill the table


## Interface

```cpp
#include "AD5263.h"
```

The library has a number of functions which are all quite straightforward.
One can get / set the value of (both) the potentiometer(s), and the O1 and O2 output lines.


#### Constructors

- **AD5263(uint8_t address, TwoWire \*wire = &Wire)** constructor,
creates an instance with 4 potentiometer.
- **bool begin()** if connected **begin()** resets the device,
otherwise returns false.
- **bool isConnected()** See if address set in constructor is on the bus.
- **uint8_t getAddress()** Returns address set in the constructor.


#### Basic IO

- **uint8_t write(uint8_t rdac, uint8_t value)** set channel rdac 0..3 to value 0..255.
- **uint8_t write(uint8_t rdac, uint8_t value, uint8_t O1, uint8_t O2)** idem + set output lines O1 and O2 too.
- **uint8_t read(uint8_t rdac)** read back set value.
rdac should be 0..3.
- **uint8_t setO1(uint8_t value = HIGH)**  value = HIGH (default) or LOW.
- **uint8_t setO2(uint8_t value = HIGH)**  value = HIGH (default) or LOW.
- **uint8_t getO1()** read back O1 line.
- **uint8_t getO2()** read back O2 line.


#### Misc

- **uint8_t zeroAll()** sets potentiometer's to 0 and I/O to LOW.
- **uint8_t reset()** sets potentiometer's to midpoint == 128 and O1 and O2 to LOW. (startup default)
- **uint8_t setAll(uint8_t value)** sets potentiometer's to value and O1 and O2 to LOW.
- **uint8_t midScaleReset(uint8_t rdac)** resets one potentiometer to midpoint == 128.
- **uint8_t readBackRegister()** read register back, for debugging.


#### Experimental

- **uint8_t shutDown()** check datasheet, not tested, use at own risk.


## Error codes

|  define        |  value  |
|:---------------|:-------:|
|  AD5263_OK     |   0     |
|  AD5263_ERROR  |   100   |


## Future

#### Must

- update documentation.

#### Should


#### Could

- improve error handling.
- sync with AD520X / AD524X library
- optimize footprint **write()** versions.
- optimize **midScaleReset()** = ```return write(rdac, AD5263_MIDPOINT);``` 
  - is this the same?
- investigate SPI interface (performance better)

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

