
[![Arduino CI](https://github.com/RobTillaart/AD5144A/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AD5144A/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AD5144A/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AD5144A/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AD5144A/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AD5144A/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AD5144A.svg?maxAge=3600)](https://github.com/RobTillaart/AD5144A/releases)


# AD5144A

Arduino library for **I2C AD5144A** 4 channel digital potentiometer.

Library has also classes for AD5123, AD5124, AD5143, AD5144, AD5144A, AD5122A, AD5142A, AD5121, AD5141

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
See Future below.


### Types supported

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


### Type AD51xy decomposition

- x = 2 => range = 0..127    
- x = 4 => range = 0..255
- y = 1 => 1 potentiometer
- y = 2 => 2 potentiometers
- y = 4 => 4 potentiometers
- y = 3 => 2 potentiometers + 2 rheostats


## I2C

For the selection of the address, see table 12 / 13 datasheet.

The AD5144A devices support standard 100 kHz, and fast 400 kHz, data transfer modes.


## Interface

The library has a number of functions which are all quite straightforward.

As the library is experimental, function signatures might change in the future.


### Constructor

- **AD51XX(uint8_t address, TwoWire \*wire = &Wire)** base class, to set the I2C address and optional the Wire bus used. 
This class does not distinguish between the derived classes.  
The developer is responsible for handling these differences correctly when using the base class.


#### Derived classes

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

- **bool begin(int dataPin, int clockPin, bool doReset = true)** ESP32 a.o initializing of the I2C data and clock pins.
If these pins are set to 255 (or above)  the default pins will be used.
If **doReset** == true (default) **reset()** is called, to load last values stored in EEPROM. 
Returns true if the address of the device can be found on the I2C bus. 
If the device cannot be found, **reset()** won't be called, even if **doReset** == true.
- **bool begin(bool doReset = true)** for UNO, if **doReset** == true (default) **reset()** is called, 
to load last values stored in EEPROM. 
Returns true if the address of the device can be found on the I2C bus. 
If the device cannot be found, **reset()** won't be called, even if **doReset** == true.
- **bool isConnected()** returns true if the address of the device can be found on the I2C bus, false otherwise.
- **uint8_t reset()** calls the built in RESET command.
This loads the last values stored in EEPROM in the RDAC's. 
Factory default is **midScale()** check datasheet for details.



### Basic IO

Used to set one channel at the time. 

- **uint8_t write(uint8_t rdac, uint8_t value)** set channel rdac 0..3 to value 0..255 
(depending on type less channels and lower max value should be used)
The value is also written into a cache of last set values for fast retrieval later.
If value > maxValue an error **AD51XXA_INVALID_VALUE** is returned.
- **uint8_t read(uint8_t rdac)** read back set value from the **cache**, not from the device.


### EEPROM

The value stored in the EEPROM is the value the 4 potentiometers will start at boot time.
This allows to start at predefined values and makes it possibly easier to continue after
a reboot.

- **uint8_t storeEEPROM(uint8_t rdac)** store the current channel value in EEPROM.
- **uint8_t storeEEPROM(uint8_t rdac, uint8_t value)** store a specific (new) value in EEPROM.
If value > maxValue an error **AD51XXA_INVALID_VALUE** is returned.
- **uint8_t recallEEPROM(uint8_t rdac)** get the value from EEPROM and set the channel.

Note: **reset()** resets all 4 channels from the last values stored in EEPROM.
(Page 28 datasheet REV-C)


### Asynchronous

Sets values in sequence, not at exact same time

- **uint8_t writeAll(uint8_t value)** write the same value to all channels.  
If value > maxValue an error **AD51XXA_INVALID_VALUE** is returned.
- **uint8_t zeroAll()** sets all channels to 0.
- **uint8_t midScaleAll()** sets all channels to their midpoint 128 / 64.
- **uint8_t maxAll()** sets all channels to the max 255 / 127.
- **uint8_t zero(uint8_t rdac)** sets one channel to 0.
- **uint8_t midScale(uint8_t rdac)** sets one channel to its midpoint = 128 / 64.
- **uint8_t maxValue(uint8_t rdac)** sets one channel to the max 255 / 127.


### Synchronous

- **uint8_t preload(uint8_t rdac, uint8_t value)** prepare a single rdac for a new value but only use it after **sync()** is called.
If value > maxValue an error **AD51XXA_INVALID_VALUE** is returned.
- **uint8_t preloadAll(uint8_t value)** prepare all rdacs with the same value, and wait for **sync()**.
If value > maxValue an error **AD51XXA_INVALID_VALUE** is returned.
- **uint8_t sync(uint8_t mask)** will transfer the preloaded values to the (4) rdacs at the very same moment. 
The 4-bit mask is used to select which rdacs to synchronize.


### TopScale BottomScale

See page 27 datasheet REV-C

- **uint8_t setTopScale(uint8_t rdac)**
- **uint8_t clrTopScale(uint8_t rdac)**
- **uint8_t setTopScaleAll()**
- **uint8_t clrTopScaleAll()**
- **uint8_t setBottomScale(uint8_t rdac)**
- **uint8_t clrBottomScale(uint8_t rdac)**
- **uint8_t setBottomScaleAll()**
- **uint8_t clrBottomScaleAll()**


### Operational modes

See page 27-28 datasheet REV-C

- **uint8_t setLinearMode(uint8_t rdac)**
- **uint8_t setPotentiometerMode(uint8_t rdac)**
- **// 0 = potentiometer, 1 = linear
- **uint8_t getOperationalMode(uint8_t rdac)**
- **uint8_t incrementLinear(uint8_t rdac)**
- **uint8_t incrementLinearAll()**
- **uint8_t decrementLineair(uint8_t rdac)**
- **uint8_t decrementLineairAll()**
- **uint8_t increment6dB(uint8_t rdac)**
- **uint8_t increment6dBAll()**
- **uint8_t decrement6dB(uint8_t rdac)**
- **uint8_t decrement6dBAll()**


### ReadBack

These function read back from the internal registers of the actual device.

- **uint8_t readBackINPUT(uint8_t rdac)** reads back the "preload value" in the INPUT register.
- **uint8_t readBackEEPROM(uint8_t rdac)** reads the **boot value** for the selected rdac from EEPROM.
- **uint8_t readBackCONTROL(uint8_t rdac)** read back the control register. 
Read the datasheet for the details of the individual bits.
- **uint8_t readBackRDAC(uint8_t rdac)** reads the value of the rdac from the device. 


### Write control register

- **uint8_t writeControlRegister(uint8_t mask)** writes to the control register. 
Read the datasheet for the details of the individual bits.
**Warning** use with care!


### Misc

- **uint8_t pmCount()** returns the number of potentiometers / channels the device has. 
Useful when writing your own loops over all channels.
- **uint8_t maxValue()** return maxValue of the potentiometer. Values expected are 127 or 255.
- **uint8_t shutDown()** check datasheet, not tested yet, use at own risk.


## Operation

The examples show the basic working of the functions.


## Future

**must**
- update documentation
- some functions can be performance optimized
  - writing a value is not needed if last value is the same?

**could**
- improve unit testing CI
- more testing with hardware.
- SPI based version of the library ?


