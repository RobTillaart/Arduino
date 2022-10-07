[![Arduino CI](https://github.com/RobTillaart/CHT8305/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/CHT8305/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/CHT8305/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/CHT8305/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/CHT8305/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/CHT8305/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/CHT8305.svg?maxAge=3600)](https://github.com/RobTillaart/CHT8305/releases)

# CHT8305

Arduino library for CHT8305 temperature and humidity sensor.

**EXPERIMENTAL** not tested yet - TODO buy hardware + test.

If you happen to have hardware and are able to test this library, 
please let me know your experiences.


## Description

The CHT8305 is a temperature and humidity sensor.

|  sensor       |  range       |  accuracy\*  |  resolution  |
|:-------------:|:------------:|:------------:|:------------:|
|  temperature  |  -40°..125°  |  max 2°C     |  0.1° C      |
|  humidity     |  0%..100% RH |  max 5% RH   |  0.1% RH     |

\* Accuracy for full range.
More exact details for smaller ranges, see datasheet (page 8).


One of the interesting functions is the support of an ALERT function.
This prevents the need for continuous polling of the sensor.
The ALERT function is not supported in the first release of library.

Register map see datasheet page 10.


### Hardware

Always check datasheet for connections.

```
//
//             +---------------+
//     VCC ----| VCC           |
//     SDA ----| SDA  CHT8305  |
//     GND ----| GND           |
//     SCL ----| SCL           |
//      ?  ----| AD0           |   ? depends on address see table below.
//             |               |
//     IRQ ----| ALERT         |   only if enabled.
//             +---------------+
```


### Alert

It has ALERT logic output pin with open drain structure, which is active low.
(if the breakout supports this)


## I2C 

I2C bus speeds supported up to 400 KHz.

|  AD0  |   Address  |
|:-----:|:----------:|
|  GND  |    0x40    |
|  VCC  |    0x41    |
|  SDA  |    0x42    |
|  SCL  |    0x43    |


Pull ups are needed on SDA, SCL and optional to ALERT.


## Interface

- **CHT8305(TwoWire \*wire = &Wire)** Constructor with default I2C bus.
- **int begin(const uint8_t address = 0x40)** sets address, deault = 0x40.
- **int begin(int sda, int scl, const uint8_t address = 0x40)** idem ESP32 et. al.
- **bool isConnected()** checks if address can be seen onthe I2C bus.
- **int read()** reads the temperature and humidity.
- **uint32_t lastRead()** returns lastRead is in MilliSeconds since start sketch.
- **float getHumidity()** returns last humidity read.
Will return the same value until **read()** is called again.
- **float getTemperature()** returns last temperature read.
Will return the same value until **read()** is called again.

  
### Offset

Adding offsets works well in normal range but might introduce 
under- or overflow at the ends of the sensor range.
  
- **void setHumOffset(float offset)** idem.
- **void setTempOffset(float offset)** idem.
- **float getHumOffset()** idem.
- **float getTempOffset()** idem.


### Config register

Check the datasheet for details of the register bits.

- **void setConfigRegister(uint16_t bitmask)** idem.
- **uint16_t getConfigRegister()** idem. 
- **void softReset()** sets the soft reset bit in the configuration, causing the sensor to reset.

|  bit  |  mask  |  name           |  description  |
|:-----:|:------:|:----------------|:--------------|
|  15   | 0x8000 |  soft reset     |  1 = reboot the sensor to default 
|  14   | 0x4000 |  clock stretch  |  1 = ON, 0 = OFF (default)
|  13   | 0x2000 |  heater         |  1 = ON, 0 = OFF (default)
|  12   | 0x1000 |  mode           |  1 = read both (default), 0 = read T or RH
|  11   | 0x0800 |  vccs           |  1 = >2.8V,  0 = <2.8V
|  10   | 0x0400 |  T-RES          |  1 = 11 bit, 0 = 14 bit (default)
|  9-8  | 0x0300 |  H-RES          |  10 = 8 bit, 01 = 11 bit, 00 = 14 bit (default)
|  7-6  | 0x00C0 |  ALTM           |  Alert Mode (datasheet)
|  5    | 0x0020 |  APS            |  Alert pending status
|  4    | 0x0010 |  H-ALT          |  Humidity Alert status
|  3    | 0x0004 |  T-ALT          |  Temperature Alert status
|  2    | 0x0002 |  VCC enable     |  1 = enable VCC measurement, 0 = disable (default)
|  1-0  | 0x0003 |  reserved.      |  do not change. 

Additional specific functions per field might be added in future releases


### Alert

TODO elaborate

- high limit only (no low limit alert) << verify.
- Register 3 datasheet page 12.
- FALLING edge


### Voltage

Note: VCC measurement should be enabled (bit 2 config register)

- **float getVoltage()** to be tested what unit exactly

16 bit data implies 5.0V \* value / 65535.0;


### Meta data

TODO elaborate

- **uint16_t getManufacturer()** 
- **uint16_t getVersionID()**


## Future

- improve documentation.
- make code functional complete.
  - config register.
  - alert function
- fix TODO's in code.
- fix TODO's in readme.
- implement ALERT functions


#### test

- buy hardware 
- test AVR, ESP32, ...
- test performance
= test I2C speed
- test resolution bits
- test ALERT functions
- test getVoltage(), getManufacturer(), getVersionID().

