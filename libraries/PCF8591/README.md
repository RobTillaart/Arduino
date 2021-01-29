
[![Arduino CI](https://github.com/RobTillaart/PCF8591/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PCF8591/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PCF8591.svg?maxAge=3600)](https://github.com/RobTillaart/PCF8591/releases)


# PCF8591

Arduino Library for PCF8591 I2C 4 channel 8 bit ADC + 1 channel 8 bit DAC


## Description

**warning** during tests I could overclock the chip at 650 kHz but it is only specified 
to run at 100 kHz. After getting pretty hot it broke down. 
So overclocking is fun but not recommended.

PCF8591 has one 8 bit ADC on board for 4 channels. The ADC is 8 bit and quite fast.
At 100 kHz one gets \> 2000 reads per second for **analogRead()** and 
\> 2000 writes per second for **analogWrite()**.  
Note that most time is probably spend on I2C communication.

The auto-increment functionality is used in the **analogRead4()** function.
The library only supports it for the mode 0 (plain ADC, no differential). 
The **lastRead()** function is needed to get access to the values.
First tests shows it is 2.6 x faster than 4 individual reads.

**analogRead4()** needs investigation in the future for the other modi.


## Interface

### Generic

- **PCF8591(const uint8_t address, TwoWire \*wire = &Wire)** constructor with I2C address, default is 0x48, optional set the WireN I2C bus.
- **begin(uint8_t sda, uint8_t scl, uint8_t val = 0)** set wire pins for ESP series.   
Also set initial value for the DAC. Returns **true** if successful.
- **begin(uint8_t val = 0)** Set initial value for the DAC. Returns **true** if successful.
- **isConnected()** test to see if chip can be reached.


### ADC part

The PCF8591 has four 8 bit ADC channels. Values = 0..255

- **enableINCR()** used in analogRead4(); Could become private in the future.
- **disableINCR()** idem.
- **isINCREnabled()** idem.
- **analogRead(uint8_t channel, uint8_t mode = 0)** read one of the 4 analog ports.  
Default mode is single ports. For comparator modes test datasheet.
- **analogRead4()** read all 4 channels in one call. 
Uses **enableINCR()** to do that efficiently. 
It is  about 2.6 x faster than 4 individual **analogRead()**, although the latter 
allows for optimized timing per channel. 
Only 4x single ports mode supported for now, comparator modi needs investigation.
- **lastRead(uint8_t channel)** get last read value from cache.  
This cache is filled both by **analogRead()** and **analogRead4()**. See example sketch.


### DAC part

The PCF8591 has one 8 bit DAC. Value 0..255

- **enableDAC()** switch on the analog output 
- **disableDAC()** switch off the analog output (high impedance) Sort of energy saving mode.
- **isDACEnabled()** check the modus operandi.
- **analogWrite(uint8_t value = 0)** writes a value 0..255 to the DAC. Check datasheet for voltage.
- **lastWrite()** get last written value from cache.
- **lastError()** always check this value after a read / write to see if it was OK (== 0).
After the read the error value is reset to OK


## Future

- Improve comparator modi support, how to do that?  
dedicated functions? return type int8_t?
- **analogRead4()** needs investigation for the other modi. Does it work?  
Is it user understandable?


## Operations

See examples.
