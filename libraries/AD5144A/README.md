
[![Arduino CI](https://github.com/RobTillaart/AD5144A/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AD5144A/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AD5144A.svg?maxAge=3600)](https://github.com/RobTillaart/AD5144A/releases)


# AD5144A

Arduino library for **I2C AD5144A** 4 channel digital potentiometer.


## Description

The library is an experimental library for the **I2C AD5144A** 4 channel digital potentiometer.
- it is not tested extensively, (AD5144A partly)
- so use at own risk, and
- please report problems and/or success.

From the datasheet it is expected that the library will work more or less 
for the family of related AD devices. However as said before this is not tested.
If there are problems, please file an issue.

This library uses the **I2C** interface to communicate with the device. 
It does not work for the **SPI** versions of these devices. 
See TODO.


## I2C

For the selection of the address, see table 12 / 13 datasheet.

The AD5144A devices support standard 100 kHz, and fast 400 kHz, data transfer modes.


## Interface

The library has a number of functions which are all quite straightforward.

As the library is experimental, function signatures might change in the future.

### Constructors

- **AD51XX(uint8_t address, TwoWire \*wire = &Wire)** base class, to set the I2C address and optional the Wire bus used. 
This class does not distinguish between the derived classes.  
The developer is responsible for handling this correctly when using the base class.

| device  |  #potmeters | # rheostats | range  | tested  |
|:--------|:-----------:|:-----------:|:------:|:-------:|
| AD5123  |   2         |   2         | 0..127 | no      |
| AD5124  |   4         |   0         | 0..127 | no      |
| AD5143  |   2         |   2         | 0..255 | no      |
| AD5144  |   4         |   0         | 0..255 | partial |
| AD5144A |   4         |   0         | 0..255 | partial |
| AD5122A |   2         |   0         | 0..127 | no      |
| AD5142A |   2         |   0         | 0..255 | no      |
| AD5121  |   1         |   0         | 0..127 | no      |
| AD5141  |   1         |   0         | 0..255 | no      |

Derived classes:
- **AD5123(uint8_t address, TwoWire \*wire = &Wire)**
- **AD5124(uint8_t address, TwoWire \*wire = &Wire)**
- **AD5143(uint8_t address, TwoWire \*wire = &Wire)**
- **AD5144(uint8_t address, TwoWire \*wire = &Wire)**
- **AD5144A(uint8_t address, TwoWire \*wire = &Wire)**
- **AD5122A(uint8_t address, TwoWire \*wire = &Wire)**
- **AD5142A(uint8_t address, TwoWire \*wire = &Wire)**
- **AD5121(uint8_t address, TwoWire \*wire = &Wire)**
- **AD5141(uint8_t address, TwoWire \*wire = &Wire)**


### I2C / device initialization

- **bool begin(uint8_t sda, uint8_t scl)** ESP32 a.o initializing of Wire. 
Returns true if the address of the device can be found on the I2C bus.
- **bool begin()** for UNO, returns true if the address of the device can be found on the I2C bus.
- **bool isConnected()** returns true if the address of the device can be found on the I2C bus.
- **uint8_t reset()** calls the built in RESET command, check datasheet for details,


### Basic IO

Used to set one channel at the time. 

- **uint8_t write(rdac, value)** set channel rdac 0..3 to value 0..255 (depending on type less channels and lower max value should be used)
The value is also written into a cache of last set values for fast retrieval later.
- **uint8_t read(rdac)** read back set value from the **cache**, not from the device.


### EEPROM

The value stored in the EEPROM is the value the 4 potmeters will start at boot time.
This allows to start at predefined values and makes it possibly easier to continue after
a reboot.

- **uint8_t storeEEPROM(rdac)** store the current channel value in EEPROM.
- **uint8_t storeEEPROM(rdac, value)** store a specific (new) value in EEPROM.
- **uint8_t recallEEPROM(rdac)** get the value from EEPROM and set the channel.


### Async 

Sets values in sequence, not at exact same time

- **uint8_t writeAll(value)** write the same value to all channels.
- **uint8_t zeroAll()** sets all channels to 0
- **uint8_t midScaleAll()** sets all channels to their midpoint 128 / 64
- **uint8_t maxAll()** sets all channels to the max 255 / 127
- **uint8_t zero(rdac)** sets one channel to 0
- **uint8_t midScale(rdac)** sets one channel to its midpoint = 128 / 64
- **uint8_t maxValue(rdac)** sets one channel to the max 255 / 127


### Sync

- **uint8_t preload(rdac, value)** prepare a rdac for a new value but only use it after **sync()** is called.
- **uint8_t preloadAll(value)** prepape all rdacs with the same value, and wait for **sync()**
- **uint8_t sync(mask)** will transfer the preloaded values to the (4) rdacs at the very same moment. The 4-bit mask is used to select which rdacs to sync.


### ReadBack

These function read back from the internal registers of the actual device.

- **uint8_t readBackINPUT(rdac)** reads back the "preload value" in the INPUT register.
- **uint8_t readBackEEPROM(rdac)** reads the **boot value** for the selected rdac from EEPROM.
- **uint8_t readBackCONTROL(rdac)** read back the control register. Read the datasheet for the details of the individual bits.
- **uint8_t readBackRDAC(rdac)** reads the value of the rdac from the device. 


### Write control register

- **uint8_t writeControlRegister(uint8_t mask)** writes to the control register. 
Read the datasheet for the details of the individual bits.
**Warning** use with care!


### Misc

- **uint8_t pmCount()** returns the number of potmeters / channels the device has. Useful when writing your own loops over all channels.
- **uint8_t shutDown()** check datasheet, not tested yet, use at own risk.


## Operation

The examples show the basic working of the functions.


## TODO

See also open issues.

#### Must

- testing ...
- example sketches

#### Could

- CI test code
- SPI based version of the library ?
- test for maxValue when writing a channel as not all derived use 0..255

- some functions can be performance optimized
  - writing a value is not needed is last value is the same?

