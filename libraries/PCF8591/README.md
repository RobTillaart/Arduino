
[![Arduino CI](https://github.com/RobTillaart/PCF8591/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PCF8591/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PCF8591/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PCF8591/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PCF8591/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PCF8591/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PCF8591.svg?maxAge=3600)](https://github.com/RobTillaart/PCF8591/releases)


# PCF8591

Arduino Library for PCF8591 I2C 4 channel 8 bit ADC + 1 channel 8 bit DAC.


## Description

**warning** during tests I could overclock the PCF8591 chip up to 650 KHz.
However it is only specified to run at 100 kHz. 
After some time it was getting pretty hot and it broke down. 
So overclocking is fun but not recommended.

PCF8591 has one 8 bit ADC on board for 4 channels. The ADC is 8 bit and quite fast.
At 100 KHz one gets \> 2000 reads per second for **analogRead()** and 
\> 2000 writes per second for **analogWrite()**.  
Note that most time is probably spend on I2C communication.

The auto-increment functionality is used in the **analogRead4()** function.
The library only supports it for the mode 0 (plain ADC, no differential). 
The **lastRead()** function is needed to get access to the values.
First tests shows it is 2.6 x faster than 4 individual reads.


## Interface

```cpp
#include "PCF8591.h"
```


#### Constructor

- **PCF8591(const uint8_t address = 0x48, TwoWire \*wire = &Wire)** constructor with I2C address.
Default is 0x48, optional set the WireN I2C bus.
- **bool begin(uint8_t sda, uint8_t scl, uint8_t value = 0)** set wire pins for ESP series.
Also set initial value for the DAC. 
Returns **true** if successful.
- **bool begin(uint8_t value = 0)** Set initial value for the DAC. 
Returns **true** if successful.
- **bool isConnected()** test to see if chip can be reached.


#### ADC channels

The PCF8591 has four 8 bit ADC channels. Values = 0..255.

- **void enableINCR()** used in analogRead4(). 
Could become private in the future.
- **void disableINCR()** idem.
- **bool isINCREnabled()** idem.
- **uint8_t analogRead(uint8_t channel, uint8_t mode = 0)** returns value of the analogue channel.
Return 0 in case of an error, so check **lastError()** to be verify validity.
Default mode is PCF8591_FOUR_SINGLE_CHANNEL, see table below.
For details comparator modes see datasheet figure 4 page 6.
- **uint8_t analogRead4()** read all 4 channels in one call.
Works in PCF8591_FOUR_SINGLE_CHANNEL mode only.
Uses **enableINCR()** to do that efficiently. 
It is about 2.6 times faster than 4 individual **analogRead()** calls.
The latter allows for optimized timing per channel and the order 
in which the channels are read.
Use **lastRead()** to access the 4 values.
Returns **PCF8591_OK** or an error code if appropriate.
- **uint8_t lastRead(uint8_t channel)** get last read value from cache.  
This cache is filled both by **analogRead()** and **analogRead4()**. 
See example sketch.


|  ADC mode                     |  Value  |  Notes    |
|:------------------------------|:-------:|:----------|
|  PCF8591_FOUR_SINGLE_CHANNEL  |  0x00   |  default  |
|  PCF8591_THREE_DIFFERENTIAL   |  0x01   |
|  PCF8591_MIXED                |  0x02   |
|  PCF8591_TWO_DIFFERENTIAL     |  0x03   |


#### Comparator

Since 0.2.0 four direct comparator calls are added to make the code more explicit.
These four calls are in fact wrappers around the **analogRead()**.
These still need to be tested as I had no hardware available.

- **int readComparator_01()** == analogRead(channel = 0, mode = 3);
- **int readComparator_23()** == analogRead(channel = 1, mode = 3);
- **int readComparator_03()** == analogRead(channel = 0, mode = 1);
- **int readComparator_13()** == analogRead(channel = 1, mode = 1);

The values of the comparator calls are cached and can be accessed with **lastRead()**.
Be sure to select the right channel for **lastRead()**.

Note: these functions do never use PCF8591_MIXED (2) mode.


#### DAC channel

The PCF8591 has one 8 bit DAC. output value 0..255 == 0..Vref Volts (datasheet).

- **void enableDAC()** switch on the analogue output.
- **void disableDAC()** switch off the analogue output (high impedance). Sort of energy saving mode.
- **bool isDACEnabled()** check the modus operandi.
- **bool analogWrite(uint8_t value = 0)** writes a value 0..255 to the DAC. Check datasheet for voltage.
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

- add examples for comparator calls.
  - schema?


#### Could


#### Wont


