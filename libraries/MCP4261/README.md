
[![Arduino CI](https://github.com/RobTillaart/MCP4261/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MCP4261/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MCP4261/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MCP4261/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MCP4261/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MCP4261.svg)](https://github.com/RobTillaart/MCP4261/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MCP4261/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MCP4261.svg?maxAge=3600)](https://github.com/RobTillaart/MCP4261/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MCP4261.svg)](https://registry.platformio.org/libraries/robtillaart/MCP4261)


# MCP4261

Arduino library for MCP4261 SPI based digital potentiometers and compatibles.


## Description

**Experimental**

The MCP4261 library supports both hardware SPI and software SPI up to 10 MHz.

These series of potmeters (rheostats) come in values of 5, 10, 50 and 100 kΩ (±20%).

Where other potmeters uses a range of 0..127 or 0..255, these series potmeters
use a range 0..128 (129 steps) and 0..256 (257 steps). 
This implies some extra care to set the wiper to end position. 

The library supports setting the value of the potmeters and caches this setting.
This way it can be retrieved very fast. 
The library also support to fetch the value from the device. 
This is useful to get the start value in **begin()** and more.

Furthermore the library has two functions to increase and decrease
the value of a potmeter.

The library supports reading / writing the **Terminal Control** register.
This allows one to disconnect either, A, B or the Wiper pin from the internal
resistor array. (needs investigation how it works in detail).

The library can read the **Status** register, this is e.g. needed to see if one can
write to EEPROM or to the NON-Volatile registers (power on values). 
Note the library does not check this.
Furthermore the status register shows the status of both the shutdown and write 
protect pins.
The **Status** register also shows the wiper lock state, however the library
does not support locking/unlocking the wipers.

Finally the library supports setting and getting from the 10 **EEPROM** locations.
Only 9 bits, so the values 0..511 are supported. 
E.g. one could use these to store 5 x 2 wiper states or something more exciting.


#### Obsolete

Version 0.2.0 has many additional functions and some were fixed so 0.1.x versions 
are obsolete.


#### Feedback

The library is tested only limited with a MCP4261, so feedback, issues and 
improvements are as always welcome. Please open an issue on GitHub.


### Compatibles

These are the devices that should work with this library.
However only the MCP4261 is tested.

|  Number  |  Type    |  pots  |   POR    |  MaxValue  |  Notes  |
|:--------:|:--------:|:------:|:--------:|:----------:|:--------|
| MCP4141  | Potmeter |   1    | NV-Wiper |    128     |
| MCP4142  | Rheostat |   1    | NV-Wiper |    128     |
| MCP4161  | Potmeter |   1    | NV-Wiper |    256     |
| MCP4162  | Rheostat |   1    | NV-Wiper |    256     |
| MCP4241  | Potmeter |   2    | NV-Wiper |    128     |
| MCP4242  | Rheostat |   2    | NV-Wiper |    128     |
| MCP4261  | Potmeter |   2    | NV-Wiper |    256     |  base class, under test.
| MCP4262  | Rheostat |   2    | NV-Wiper |    256     |


#### To investigate:

MCP4131/32/51/52, MCP4231/32/51/52, these have no NV RAM so they 
have a POR (power on reset) of the middle value (= half max value).  
Support EEPROM?


### Related

Mainly other digital potentiometers / rheostats.

- https://github.com/RobTillaart/AD520x
- https://github.com/RobTillaart/AD524X
- https://github.com/RobTillaart/AD5245
- https://github.com/RobTillaart/AD5144A
- https://github.com/RobTillaart/AD5263
- https://github.com/RobTillaart/MCP_POT
- https://github.com/RobTillaart/MCP4261
- https://github.com/RobTillaart/X9C10X


#### Registers

Table 4.1 from datasheet (p 29)

|  Address  |  Function                |  Memory Type  |  Notes  |
|:---------:|:------------------------:|:--------------|:--------|
|  00h      |  Volatile Wiper 0        |  RAM          |  range 0..256 (128)
|  01h      |  Volatile Wiper 1        |  RAM          |  range 0..256 (128)
|  02h      |  Non-Volatile Wiper 0    |  EEPROM       |  set Power on Reset, range idem.
|  03h      |  Non-Volatile Wiper 1    |  EEPROM       |  set Power on Reset, range idem.
|  04h      |  Volatile TCON Register  |  RAM          |
|  05h      |  Status Register         |  RAM          |  read only
|  06-0Fh   |  Data EEPROM             |  EEPROM       |  10 values, range 0..511

Is this overview needed?

## Performance indication

See performance example.

Indicative times in microseconds, version 0.2.0

|       |  function        |  1 MHz  |  2 MHz  |  4 MHz  |  8 MHz  |  SW SPI  |
|:-----:|:-----------------|:-------:|:-------:|:-------:|:-------:|:--------:|
|  UNO  |  setValue        |  34.4   |  26.4   |  22.3   |  20.3   |  312.5   |
|  UNO  |  getValue        |   0.8   |   0.8   |   0.8   |   0.8   |    0.8   |
|  UNO  |  getValueDevice  |  36.4   |  28.34  |  24.4   |  22.3   |  314.3   |
|  UNO  |  incrValue       |  24.2   |  20.2   |  18.2   |  17.2   |  162.9   |
|  UNO  |  decrValue       |  23.9   |  20.0   |  17.9   |  16.9   |  162.6   |

Other boards might be added.

Notes:
- EEPROM and NON-Volatile registers read performance is in the same order as the
getValueDevice() function.  
-  EEPROM and NON-Volatile registers write performance is in the same order as the 
setValue() function, however depends on if there was a recent write (< 5 ms ago).


## Interface

```cpp
#include "MCP4261.h"
```


### Constructor

- **MCP4261(uint8_t select, uint8_t shutdown, \__SPI_CLASS__ \* mySPI = &SPI)**
HW SPI constructor. If the shutDown pin is not used, is should be set to 255.
- **MCP4261(uint8_t select, uint8_t shutdown, uint8_t dataIn, uint8_t dataOut, uint8_t clock)**
SW SPI Constructor. If the shutDown pin is not used, is should be set to 255.
- **void begin()** initializes the device and reads the default values of the two potmeters
from the device. These values are cached.
- **void reset(uint16_t value)** resets the device, and sets both wipers to an explicit value.
- **uint8_t pmCount()** returns 1 or 2, depending on device type.


### Set Volatile Values

- **bool setValue(uint16_t value)** set all potmeters to the same value. (wrapper).
Value can be 0..256 (128 depending on type).
Returns true.
- **bool setValue(uint8_t pm, uint16_t value)** set a single potmeter (0 or 1).
Returns false if pm > pmCount or if value too large.
- **uint16_t getValue(uint8_t pm = 0)** returns value from cache. (fast).
- **uint16_t getValueDevice(uint8_t pm = 0)** returns value from the device. (robust).
- **bool incrValue(uint8_t pm = 0)** increments potmeter by 1 if possible. 
Returns false if this fails, e.g. max value reached.
- **bool decrValue(uint8_t pm = 0)** decrements potmeter by 1 if possible. 
Returns false if this fails, e.g. zero reached.


### Set NON-Volatile Values

- **bool setValueNV(uint8_t pm, uint16_t value)** set the power on reset value for potmeter.
- **uint16_t getValueNV(uint8_t pm)** retrieves set value from device.

The NV functions do not check the status register if an EEPROM write is pending. 
If you want to write both registers you need to pause 5-10 ms between the calls.


### Terminal Control register (TCON)

Needs more investigation how this works in detail.

To connect and disconnect the A, B and Wiper from the internal resistor array.
See datasheet form details.

- **void setTCONMask(uint16_t mask)**
- **uint16_t getTCONMask()**


### Status register

See datasheet form details.

- **uint16_t getStatusMask()** read only bit mask, (5 bits used).

|  bit  |   Description         |  notes  |
|:-----:|:----------------------|:--------|
|   0   |  Write Protect        |
|   1   |  Shut Down            |
|   2   |  Wiper Lock 0         |  not supported
|   3   |  Wiper Lock 1         |  not supported
|   4   |  EEPROM Write Active  |


### EEPROM

- **bool setEEPROM(uint8_t index, uint16_t value)** index = 0..9  value = 0..511.
Returns false if index > 9 or value out of range.
- **uint16_t getEEPROM(uint8_t index)** Returns set value, or 0 if index > 9.

The EEPROM functions do not check the status register if an EEPROM write is 
pending. (might take up to 10 ms).

If you want to write multiple registers you need to pause 5-10 ms between the calls.

### SPI

Note changing the SPI speed might affect other devices on the same SPI bus.
So use with care.

- **void setSPIspeed(uint32_t speed)** default 1 MHz, typical 4 MHz.
- **uint32_t getSPIspeed()** idem.
- **bool usesHWSPI()** idem, depends on which constructor used.


### Power

Uses the shutdown pin from the constructor.

- **void powerOn()** idem.
- **void powerOff()** idem.
- **bool isPowerOn()** idem.


## Future

#### Must

- improve documentation

#### Should 

- investigate compatibility (what is supported)
  - MCP4131/32/51/52, 
  - MCP4231/32/51/52
- pending EEPROM write?
  - blocking 5-10 ms?, see page 10 datasheet.
  - status check for EEPROM? (robust, also in MT environment)
  - lastEE_timestamp? (fast, works if long ago)
  - mix?
  - What is a good strategy?
  - **bool isEEWritePending()**? should be non-blocking.
  - Also for the NV write function as one needs to write two registers.
- elaborate TCON settings.
  - investigate behaviour.

#### Could

- support write protect pin.
  - define pin, set, get
- investigate error handling
  - improve return values
- investigate performance
  - extend performance sketch.
  - other boards, extend table.
  - AVR SW SPI? (only on request)
  - const usage?

#### Won't

- add unit tests (takes too much time).
- High voltage functions


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

