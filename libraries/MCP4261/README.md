
[![Arduino CI](https://github.com/RobTillaart/MCP4261/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MCP4261/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MCP4261/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MCP4261/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MCP4261/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MCP4261.svg)](https://github.com/RobTillaart/MCP4261/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MCP4261/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MCP4261.svg?maxAge=3600)](https://github.com/RobTillaart/MCP4261/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MCP4261.svg)](https://registry.platformio.org/libraries/robtillaart/MCP4261)

[![Commits since latest](https://img.shields.io/github/commits-since/RobTillaart/MCP4261/latest)](https://github.com/RobTillaart/MCP4261/commits/master)


# MCP4261

Arduino library for MCP4261 SPI based digital potentiometers and compatibles.


## Description

**Experimental**

The MCP4261 library supports both hardware SPI and software SPI up to 10 MHz.

These series of potmeters (rheostats) come in values of 5, 10, 50 and 100 kΩ (±20%).

Where other potmeters uses a range of 0..127 or 0.255, these series potmeters
use a range 0..129 and 0..257. This implies some extra care to set the wiper
to end position.

The library supports setting the value of the potmeters and caches this setting.
This way it can be retrieved very fast.

Furthermore the library has two functions to increase and decrease
the value of a potmeter.


Feedback, issues and improvements are welcome, 
Please open an issue on GitHub.


### Not implemented yet

The library is under development and not all functionality is implemented.
(as I only needed to set values).

- EEPROM, 10 addresses of 10 bits. (MCP4261 et al )
- Non volatile registers for power on setup.. (partially)
- read back from device
- read status
- TCON register
- High Voltage something?


### Compatibles

These are the devices that should work with this library.
Only the 4261 is tested.

|  Number  |  Type    |  pots  |   POR    |  MaxValue  |  Notes  |
|:--------:|:--------:|:------:|:--------:|:----------:|:--------|
| MCP4141  | Potmeter |   1    | NV-Wiper |    129     |
| MCP4142  | Rheostat |   1    | NV-Wiper |    129     |
| MCP4161  | Potmeter |   1    | NV-Wiper |    257     |
| MCP4162  | Rheostat |   1    | NV-Wiper |    257     |
| MCP4241  | Potmeter |   2    | NV-Wiper |    129     |
| MCP4242  | Rheostat |   2    | NV-Wiper |    129     |
| MCP4261  | Potmeter |   2    | NV-Wiper |    257     |  base class
| MCP4262  | Rheostat |   2    | NV-Wiper |    257     |

To investigate:

MCP4131/32/51/52, MCP4231/32/51/52, these have no NV RAM so they 
have a POR power on reset of  middle value (= half max value.


MCP4151 Reichelt  
MCP4262 Mouser


### Related

TODO: list of other digital pot meters / rheostats.


#### Related



|  Address  |  Function                |  Memory Type  |
|:---------:|:------------------------:|:--------------|
|  00h      |  Volatile Wiper 0        |  RAM          |
|  01h      |  Volatile Wiper 1        |  RAM          |
|  02h      |  Non-Volatile Wiper 0    |  EEPROM       |
|  03h      |  Non-Volatile Wiper 1    |  EEPROM       |
|  04h      |  Volatile TCON Register  |  RAM          |
|  05h      |  Status Register         |  RAM          |
|  06h      |  Data EEPROM             |  EEPROM       |
|  07h      |  Data EEPROM             |  EEPROM       |
|  08h      |  Data EEPROM             |  EEPROM       |
|  09h      |  Data EEPROM             |  EEPROM       |
|  0Ah      |  Data EEPROM             |  EEPROM       |
|  0Bh      |  Data EEPROM             |  EEPROM       |
|  0Ch      |  Data EEPROM             |  EEPROM       |
|  0Dh      |  Data EEPROM             |  EEPROM       |
|  0Eh      |  Data EEPROM             |  EEPROM       |
|  0Fh      |  Data EEPROM             |  EEPROM       |


## Interface

```cpp
#include "MCP4261.h"
```


### Constructor

- **MCP4261(uint8_t select, uint8_t shutdown, \__SPI_CLASS__ \* mySPI = &SPI)**
HW SPI constructor.
- **MCP4261(uint8_t select, uint8_t shutdown, uint8_t dataIn, uint8_t dataOut, uint8_t clock)**
SW SPI Constructor. The dataIn pin is not used yet.
- **void begin(uint8_t value)** user must explicit set initial value.
- **void reset(uint8_t value)** user must explicit set initial value.
- **uint8_t pmCount()** returns 1 or 2, depending on device type.


### Set Volatile Values

- **bool setValue(uint8_t value)** set all potmeters to the same value. (wrapper).
Returns true.
- **bool setValue(uint8_t pm, uint8_t value)** set single potmeter (0 or 1).
Returns false if pm > pmCount.
- **uint8_t getValue(uint8_t pm = 0)** returns value from cache.
- **bool incrValue(uint8_t pm)**
- **bool decrValue(uint8_t pm)**


### Set Volatile Values

**Experimental**

TODO: how does this fit in interface as reset() always sets a value.

- **bool setValueNV(uint8_t pm, uint16_t value)**


### EEPROM

Not implemented yet

### SPI

Note changing the SPI speed might affect other devices on the same SPI bus.
So use with care.

- **void setSPIspeed(uint32_t speed)** default 1MHz, typical 4 MHz.
- **uint32_t getSPIspeed()** idem.
- **bool usesHWSPI()** idem.


### Power

- **void powerOn()** idem.
- **void powerOff()** idem.
- **bool isPowerOn()** idem.


## Future

#### Must

- improve documentation

#### Should 

- read registers.
  - read values.
  - status register
  - TCON

#### Could

- EEPROM support
  - 10 registers, 10 bit
  - bool writeEEPROM(address, uint16_t value);
  - uint16_t readEEPROM(address);
- write to non-volatile register 02/03 to set Power On Reset values
  - read when reset?
  - how to fit in use model.
- unit tests
- examples
- error handling
  - improve return values
- investigate performance 
  - AVR SW SPI?

#### Won't


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

