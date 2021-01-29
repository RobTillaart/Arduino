
[![Arduino CI](https://github.com/RobTillaart/MCP_ADC/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MCP_ADC/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MCP_ADC.svg?maxAge=3600)](https://github.com/RobTillaart/MCP_ADC/releases)

# MCP_ADC

Arduino library for MCP3002 MCP3004 MCP3008 MCP3202 MCP3204 MCP3208


## Description

This library reads the ADC ports of the MCP ADC convertors. 
The chips are comunicates with SPI and support both hardware SPI or optional software SPI.

| type | bits | channels | notes |
|:----|:----:|:----:|:---|
| MCP3002 | 10 | 2 |    |
| MCP3004 | 10 | 4 |    |
| MCP3008 | 10 | 8 |    |
| MCP3202 | 12 | 2 |    |
| MCP3204 | 12 | 4 |    |
| MCP3208 | 12 | 8 |    |

Current version allows manual override of the hardware SPI clock as the speed is not
optimized per ADC type. 

The MCP ADC allow single mode which compares voltage of a channel against GND.
Furthermore they allow a differential mode which compares two channels IN+ and IN- 
to each other. if the IN+ is equal or below IN- the ADC will return 0. 

Build into the library is a delta mode which is a software enhanced differential mode.
This delta mode can return negative values too. 


## Interface

If the pins are not set in the constructor, the class will automatically
use the hardware SPI, otherwise it will use a software SPI 
- **MCP3002(dataIn, dataOut, clock)** constructor 10 bit ADC 2 channel
- **MCP3004(dataIn, dataOut, clock)** constructor 10 bit ADC 4 channel
- **MCP3008(dataIn, dataOut, clock)** constructor 10 bit ADC 8 channel
- **MCP3202(dataIn, dataOut, clock)** constructor 12 bit ADC 2 channel
- **MCP3204(dataIn, dataOut, clock)** constructor 12 bit ADC 4 channel
- **MCP3208(dataIn, dataOut, clock)** constructor 12 bit ADC 8 channel
- **void begin(select)** set select pin.
- **uint8_t channels()** returns the number of channels
- **int16_t maxValue()** returns maxReading of adc, e.g. 1023. 
This makes it easy to calculate relative measurements.
- **int16_t analogRead(channel)** reads the value of the channel
- **int16_t differentialRead(channel)** reads differential between two channels  
Check datasheet for details  
Note if the IN+ is equal or below IN- this function will return 0.
- **int16_t deltaRead(channel)** reads differential like above however it
will return a negative value if IN+ is below IN-.
- **void setSPIspeed(speed)** sets SPI clock in Hz, please read datasheet
of the ADC first to get optimal speed.
- **uint32_t getSPIspeed()** gets current speed in Hz


Differential channel table

| Channel | diff IN+ | diff IN- | MCP |
|:----:|:----:|:----:|----:|
| 0 |  0 | 1 | 3x02/3x04/3x08 |
| 1 |  1 | 0 | 3x02/3x04/3x08 |
| 2 |  2 | 3 | 3x04/3x08 |
| 3 |  3 | 2 | 3x04/3x08 |
| 4 |  4 | 5 | 3x08 |
| 5 |  5 | 4 | 3x08 |
| 6 |  6 | 7 | 3x08 |
| 7 |  7 | 6 | 3x08 |


## Future / ideas / improvements

- testing, a lot ...
- set SPI-speed in classes directly
- get / setF(float A, float B) => float readF(channel)   output = A*value + B;
- analogRead (mask, int array ) read ports (set in mask) in an array in one call.

## Operations

See examples.
