
[![Arduino CI](https://github.com/RobTillaart/AD520X/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AD520X/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AD520X.svg?maxAge=3600)](https://github.com/RobTillaart/AD520X/releases)

# AD520X

Arduino library for SPI AD5204 and AD5206 digital potentiometers

## Description

The library is still experimental as not all functionality is tested (enough).

The **AD5204** (4 pm) and **AD5206** (6 pm) are SPI based digital potentiometers.
This library consists of a base class **AD520X** that does the work.

The interface is straightforward, one can set a value per pm between 0..255.

_Although not tested this library should work for the older **AD8400** (1 pm),
the **AD8402** (2 pm) and **AD8403** (4 pm) as the interface is very similar
(datasheet comparison). If you can confirm it works, please let me know._

## Interface


### Constructors

- **AD520X(select, reset, shutdown, dataOut = 255, clock = 255)** constructor  
Base class, not to be used directly.
If dataOut and clock are set to 255 (default) it uses hardware SPI. 
If dataOut and clock are set to another (valid) value) it uses software SPI.
reset and shutdown may be set to 255 too, which effectively disables them.  
Note: hardware SPI is 10+ times faster on an UNO.
- **AD5204(select, reset, shutdown, dataOut = 255, clock = 255)** uses 4 pm.
- **AD5206(select, reset, shutdown, dataOut = 255, clock = 255)** uses 6 pm.
- **AD8400(select, reset, shutdown, dataOut = 255, clock = 255)** uses 1 pm.
- **AD8402(select, reset, shutdown, dataOut = 255, clock = 255)** uses 2 pm.
- **AD8403(select, reset, shutdown, dataOut = 255, clock = 255)** uses 4 pm.

### Base
- **begin(value = 128)** value is the initial value of all potentiometer.
- **setValue(pm, value)** set a potentiometer to a value
- **setAll(value)** set all potentiometers to the same value e.g. 0 or max or mid
- **getValue(pm)** returns the last set value of a specific potmeter
- **reset(value = 128)** resets all potentiometers to value, default 128.

### Misc
- **pmCount()** returns the number of internal potmeters.
- **powerOn()** switches the module on
- **powerOff()** switches the module off
- **powerDown()** use powerOFf() instead
- **isPowerOn()** returns true if on (default) or 

## Future

- **setInvert(pm)** invert flag per potmeter
   - 0..255 -> 255..0
   - 1 uint8_t can hold 8 flags
- **getInvert(pm)**

- **follow(pm_B, pm_A, percentage = 100)**
  - makes pm_B follow pm_A unless pm_B is addressed explicitly
  - array cascade = 0xFF or pm_A.
  - It will follow pm_A for certain percentage default 100.
  
- **setPercentage(pm, float value)** 0..100%
- **getPercentage(pm)**
- logarithmic effect? setGamma(pm, value);
  easier with setPercentage()


## Operations

See examples.
