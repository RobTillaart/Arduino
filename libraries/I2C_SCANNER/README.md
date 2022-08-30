
[![Arduino CI](https://github.com/RobTillaart/I2C_SCANNER/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/I2C_SCANNER/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/I2C_SCANNER/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/I2C_SCANNER/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/I2C_SCANNER/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/I2C_SCANNER/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/I2C_SCANNER.svg?maxAge=3600)](https://github.com/RobTillaart/I2C_SCANNER/releases)


# I2C_SCANNER

Arduino class to implement an I2C scanner.


## Description

I2C_SCANNER is a class to build an I2C scanner, either minimal or more complex.

The class provides different functions to analyse the connectivity of devices
on the I2C bus. There are functions to adjust the frequency and functions to 
select the bus in case of multiple I2C ports. 

Furthermore there are different functions to scan the I2C port, 
see the section scanning below.

If there is missing functionality, please file an issue.


## Interface

### Constructor
- **I2C_SCANNER(TwoWire \*wire = &Wire)** Constructor with the default Wire I2C bus.
- **bool begin()** To start the Wire library.
- **bool begin(int sda, int scl)** idem for ESP32 et al.


### Configuration

- **bool setClock(uint32_t clockFrequency = 100000UL)** sets the speed of the I2C bus.
Returns true
- **uint32_t getClock()** for supported platforms
- **uint8_t getWireCount()** returns the number of Wire ports (hardware I2C).
- **bool setWire(TwoWire \*wire = &Wire)** set a Wire port by 'name' e.g. Wire1.
- **bool setWire(uint8_t n)** sets the Wire port by number.
- **TwoWire \* getWire()** returns the Wire object set.


### Scanning

- **bool ping(uint8_t address)** Tries to make contact with I2C address.
Returns true on success.
- **int diag(uint8_t address)** Tries to make contact with I2C address.
Returns Wire status code 0 == OK, others might depend on platform used.
- **int32_t pingTime(uint8_t address)** Tries to make contact with I2C address.
Returns time used in micros. Returns minus time (<0) if failed to contact.
- **uint8_t count(uint8_t start = 0, uint8_t end = 127)** pings address range.
Includes start and end address too. Returns the number of addresses found.


## Operation

See examples.


## Future ideas

#### Should

- add examples.

- documentation
- add **bool softwareReset()** (0.1.2)
  - command 0x03
- **uint8_t \_devices[16]** cache hits ?
  
#### Could

- add unit tests
- add **bool hardwareReset()** (needs investigation)
  - keep data HIGH for X clock pulses - google this.


#### Won't

- device analysis
  - add **bool send(address, uint8_t \*buffer, uint8_t length)**
  - add **bool receive(address, uint8_t \*buffer, uint8_t length)**
- add iterator 
  - **uint8_t first(uint8_t start = 0)** returns nr or 255
  - **uint8_t next()** returns nr or 255.

