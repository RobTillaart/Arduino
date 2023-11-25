
[![Arduino CI](https://github.com/RobTillaart/I2C_EEPROM/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/I2C_EEPROM/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/I2C_EEPROM/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/I2C_EEPROM/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/I2C_EEPROM/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/I2C_EEPROM.svg)](https://github.com/RobTillaart/I2C_EEPROM/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/I2C_EEPROM/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/I2C_EEPROM.svg?maxAge=3600)](https://github.com/RobTillaart/I2C_EEPROM/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/I2C_EEPROM.svg)](https://registry.platformio.org/libraries/robtillaart/I2C_EEPROM)


# I2C_eeprom_cyclic_store

Utility class for storing data using cyclic writes to eeprom memory.


## Description

In order to maximize the life expectancy of an eeprom this class implements 
a method to spread the write operations across as much of the eeprom as possible, 
rather than writing to the same fixed location.

This is suitable for a situation where a single data structure (buffer), 
such as settings, configuration or metric data, is written to the eeprom.

It operates by partitioning the eeprom into slots large enough to hold the 
declared buffer (and header) and then writing each new version of the data 
to the next slot, overwriting any older version already in there. 
As it reaches the end of the alotted region of the eeprom it wraps around 
and starts writing from the start of the memory again. 
When initializing an instance it scans the eeprom to find the last written 
version and continues from that.

In order to use an eeprom that already has data (and if the structure of the
 buffer changes) the eeprom has to be prepared by formatting the indexes.

The interface is pretty straightforward

- **begin(eeprom, pageSize, totalPages)** initialization
- **format()** erase data from eeprom
- **read(buffer)** read buffer from last location prom
- **write(buffer)** write buffer to next location on eeprom
- **getMetrics(slots, writeCounter)** get usage metrics


## Limitation

The class does not handle changes in buffer size or structure, nor does
it detect an eeprom that has data that wasn't written using the class.


## Operational

See examples

