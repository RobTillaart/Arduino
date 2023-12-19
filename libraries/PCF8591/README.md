
[![Arduino CI](https://github.com/RobTillaart/PCF8591/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PCF8591/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PCF8591/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PCF8591/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PCF8591/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/PCF8591.svg)](https://github.com/RobTillaart/PCF8591/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PCF8591/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PCF8591.svg?maxAge=3600)](https://github.com/RobTillaart/PCF8591/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/PCF8591.svg)](https://registry.platformio.org/libraries/robtillaart/PCF8591)


# PCF8591

Arduino Library for PCF8591 I2C 4 channel 8 bit ADC + 1 channel 8 bit DAC.


## Description

**warning** during tests I could overclock the PCF8591 chip up to 650 KHz.
However it is only specified to run at 100 kHz. 
After some time it was getting pretty hot and it broke down. 
So overclocking is fun but **not recommended**.

PCF8591 has one 8 bit ADC on board for 4 channels. The ADC is 8 bit and quite fast.
At 100 KHz one gets \> 2000 reads per second for **read()** and 
\> 2000 writes per second for **write()**.  
Note that most time is probably spend on I2C communication.

The auto-increment functionality is used in the **read4()** function.
The library only supports it for the mode 0 (plain ADC, no differential). 
The **lastRead()** function is needed to get access to the values.
First tests shows it is 2.6 x faster than 4 individual reads.


#### 0.4.0 Breaking change

The version 0.4.0 has breaking changes in the interface. 
The rationale is that the programming environment of the **Arduino ESP32 S3** 
board uses a remapping by means of the include file **io_pin_remap.h**.
This file remaps the pins of several core Arduino functions. 
The remapping is implemented by #define macros and these implement "hard" text 
replacements without considering context. 
The effect is that methods from this class (and several others) which have the same 
name as those Arduino core functions will be remapped into something not working.

The following library functions have been renamed:

|  old name        |  new name    |  notes  |
|:-----------------|:-------------|:--------|
|  analogRead()    |  read()      |
|  analogWrite()   |  write()     |
|  pinMode()       |  pinMode1()  |
|  digitalRead()   |  read1()     |
|  digitalWrite()  |  write1()    |


#### 0.3.0 Breaking change

Version 0.3.0 introduced a breaking change.
You cannot set the pins in **begin()** any more.
This reduces the dependency of processor dependent Wire implementations.
The user has to call **Wire.begin()** and can optionally set the Wire pins 
before calling **begin()**.


#### Related

- https://github.com/RobTillaart/MCP_DAC
- https://github.com/RobTillaart/MCP_ADC



## Interface

```cpp
#include "PCF8591.h"
```

#### Constructor

- **PCF8591(uint8_t address = 0x48, TwoWire \*wire = &Wire)** constructor with I2C address.
Default is 0x48, optional set the WireN I2C bus.
- **bool begin(uint8_t value = 0)** Set initial value for the DAC.
Returns false if address out of range, or if it cannot be seen on the I2C bus.
Returns **true** if successful.
- **bool isConnected()** test to see if address can be reached on the I2C bus.
- **uint8_t getAddress()** returns address set in constructor.


#### ADC channels

The PCF8591 has four 8 bit ADC channels. Values = 0..255.

- **void enableINCR()** used in read4(). 
Could become private in the future.
- **void disableINCR()** idem.
- **bool isINCREnabled()** idem.
- **uint8_t read(uint8_t channel, uint8_t mode = 0)** returns value of the analogue channel.
Return 0 in case of an error, so check **lastError()** to be verify validity.
Default mode is PCF8591_FOUR_SINGLE_CHANNEL, see table below.
For details comparator modes see datasheet figure 4 page 6.
- **uint8_t read4()** read all 4 channels in one call.
Works in PCF8591_FOUR_SINGLE_CHANNEL mode only.
Uses **enableINCR()** to do that efficiently. 
It is about 2.6 times faster than 4 individual **read()** calls.
The latter allows for optimized timing per channel and the order 
in which the channels are read.
Use **lastRead()** to access the 4 values.
Returns **PCF8591_OK** or an error code if appropriate.
- **uint8_t lastRead(uint8_t channel)** get last read value from cache.  
This cache is filled both by **read()** and **read4()**. 
See example sketch.


|  ADC mode                     |  Value  |  Notes    |
|:------------------------------|:-------:|:----------|
|  PCF8591_FOUR_SINGLE_CHANNEL  |  0x00   |  default  |
|  PCF8591_THREE_DIFFERENTIAL   |  0x01   |
|  PCF8591_MIXED                |  0x02   |
|  PCF8591_TWO_DIFFERENTIAL     |  0x03   |


#### Comparator

Since 0.2.0 four direct comparator calls are added to make the code more explicit.
These four calls are in fact wrappers around the **read()**.
These still need to be tested as I had no hardware available.

- **int readComparator_01()** == read(channel = 0, mode = 3);
- **int readComparator_23()** == read(channel = 1, mode = 3);
- **int readComparator_03()** == read(channel = 0, mode = 1);
- **int readComparator_13()** == read(channel = 1, mode = 1);

The values of the comparator calls are cached and can be accessed with **lastRead()**.
Be sure to select the right channel for **lastRead()**.

Note: these functions do never use PCF8591_MIXED (2) mode.


#### DAC channel

The PCF8591 has one 8 bit DAC. output value 0..255 == 0..Vref Volts (datasheet).

- **void enableDAC()** switch on the analogue output.
- **void disableDAC()** switch off the analogue output (high impedance). Sort of energy saving mode.
- **bool isDACEnabled()** check the modus operandi.
- **bool write(uint8_t value = 0)** writes a value 0..255 to the DAC. Check datasheet for voltage.
Note, this is a real voltage not a PWM signal like **analogWrite()** on an UNO.
- **uint8_t lastWrite()** get last value written (from cache).


#### Error codes

- **int lastError()** always check this value after a read / write to see if it was OK (== 0).
After the read the error value is reset to OK.

|  Error code             |  Value  |  Notes  |
|:------------------------|:-------:|:--------|
|  PCF8591_OK             |  0x00   |
|  PCF8591_PIN_ERROR      |  0x81   |
|  PCF8591_I2C_ERROR      |  0x82   |
|  PCF8591_MODE_ERROR     |  0x83   |
|  PCF8591_CHANNEL_ERROR  |  0x84   |
|  PCF8591_ADDRESS_ERROR  |  0x85   |


## Operations

See examples.


## Future

#### Must

- improve documentation
- test / verify comparator calls with hardware.
  - datasheet (par.8.2 figure 4)

#### Should

- add examples 
  - for comparator calls.
  - schema?
- add examples boards
  - ESP32, RP2040 (pins)

#### Could


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


