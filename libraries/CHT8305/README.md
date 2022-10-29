[![Arduino CI](https://github.com/RobTillaart/CHT8305/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/CHT8305/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/CHT8305/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/CHT8305/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/CHT8305/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/CHT8305/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/CHT8305.svg?maxAge=3600)](https://github.com/RobTillaart/CHT8305/releases)

# CHT8305

Arduino library for CHT8305 temperature and humidity sensor.

**EXPERIMENTAL** minimal tested.

If you are able to test this library, please let me know your experiences.


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


#### Tests

- Temperature() and humidity() works on AVR.
  - default about 14 milliseconds at 14 bit resolution.
- offset functions work.
- getVoltage() function works on AVR but meaning unclear.
- getManufacturer(), getVersionID() works on AVR.
- 

The ALERT functions are not tested.
The reason is that the sensor I have does not expose the ALERT pin.

If you are able to test the ALERT functions, please let me know your experiences.


### Hardware

Always check datasheet for connections.

```cpp
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
//
//  check datasheet
//  VCC     RED
//  GND     BLACK
//  SDA     YELLOW
//  SCL     WHITE
```


### Register map 

See datasheet page 10 for details

|  Address  |  Register name             |
|:---------:|:---------------------------|
|   0x00    |  CHT8305_REG_TEMPERATURE   |
|   0x01    |  CHT8305_REG_HUMIDITY      |
|   0x02    |  CHT8305_REG_CONFIG        |
|   0x03    |  CHT8305_REG_ALERT         |
|   0x04    |  CHT8305_REG_VOLTAGE       |
|   0xFE    |  CHT8305_REG_MANUFACTURER  |
|   0xFF    |  CHT8305_REG_VERSION       |


### Alert

The CHT8305 has an ALERT logic output pin with an open drain structure.
This output is active low. (if the breakout supports this.)


## I2C 

I2C bus speeds supported up to 400 KHz.

|  AD0  |   Address  |  Notes  |
|:-----:|:----------:|:--------|
|  GND  |    0x40    |  CHT8305_DEFAULT_ADDRESS
|  VCC  |    0x41    |
|  SDA  |    0x42    |
|  SCL  |    0x43    |

Pull ups are needed on SDA, SCL and optional to ALERT.


## Interface

- **CHT8305(TwoWire \*wire = &Wire)** Constructor with default I2C bus.
- **int begin(const uint8_t address = CHT8305_DEFAULT_ADDRESS)** sets address, default = 0x40.
- **int begin(int sda, int scl, const uint8_t address = CHT8305_DEFAULT_ADDRESS)** idem ESP32 et. al.
- **bool isConnected()** checks if address can be seen on the I2C bus.
- **int read()** reads both the temperature and humidity.
Can be called once per second.
- **int readTemperature()** read only temperature (slightly faster than read)
- **int readHumidity()** read only humidity (slightly faster than read)
- **uint32_t lastRead()** returns lastRead in MilliSeconds since start sketch.
- **float getHumidity()** returns last humidity read.
Will return the same value until **read()** is called again.
- **float getTemperature()** returns last temperature read.
Will return the same value until **read()** is called again.

Note: read(), readTemperature() and readHumidity() blocks each other,
so you can call one of them every second.


### Conversion delay

- **void setConversionDelay(uint8_t cd = 14)** default is 14 milliseconds (datasheet).
7 ms failed. 8 ms worked, so values below 8 are mapped to 8 in the library.
Expect 10 ms is pretty save. Use at own risk.
It might be that lower resolutions allow shorter delays. This is not tested.
- **uint8_t getConversionDelay()** returns set value.


### Offset

Adding offsets works well in the "normal range" but might introduce 
under- or overflow at the ends of the sensor range.
  
- **void setHumOffset(float offset)** idem.
- **void setTempOffset(float offset)** idem.
- **float getHumOffset()** idem.
- **float getTempOffset()** idem.

If the offset is not the same over the operational range, 
consider a mapping function for temperature and humidity.


### Configuration register

Check the datasheet for details of the register bits.

- **void setConfigRegister(uint16_t bitmask)** idem. Default value 0x1004.
- **uint16_t getConfigRegister()** idem. 

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
|  3    | 0x0008 |  T-ALT          |  Temperature Alert status
|  2    | 0x0004 |  VCC enable     |  1 = enable VCC measurement (default), 0 = disable
|  1-0  | 0x0003 |  reserved.      |  do not change. 


#### Getters / setters config register

Note: setting **setConfigRegister(bitmask)** can be faster.

Wrapper functions for easy configuration.

- **void softReset()** sets the soft reset bit in the configuration, causing the sensor to reset.
- **void setI2CClockStretch(bool on = false)** check datasheet.
- **bool getI2CClockStretch()**
- **void setHeaterOn(bool on = false)** switch on internal heater. 
Can improve humidity readings.
See datasheet for (limited) details.
  - **WARNING** User is responsible for timing as library does not support timing.
- **bool getHeater()** Returns status of the heater.
- **void setMeasurementMode(bool both = true)** both T and H or single value.
- **bool getMeasurementMode()** returns mode set above. 
- **bool getVCCstatus()** 1 ==  > 2.8V  0 == < 2.8V  Useful when battery operated?
- **void setTemperatureResolution(uint8_t res = 0)** 1 = 11 bit, 0 = 14 bit (default).
- **uint8_t getTemperatureResolution()** idem.
- **void setHumidityResolution(uint8_t res = 0)** 2 = 8 bit, 1 = 11 bit, 0 = 14 bit (default).
- **uint8_t getHumidityResolution()** idem.
- **void setVCCenable(bool enable = false)** idem.
- **bool getVCCenable()** idem.


### Alert

See register 3 datasheet page 12 for details.

- **void setAlertTriggerMode(uint8_t mode)** see table below.
- **uint8_t getAlertTriggerMode()** returns 0, 1, 2 or 3.

|  mode  |  trigger  |  notes    |
|:------:|:---------:|:----------|
|   0    |  T or H   |  default  |
|   1    |  T        |
|   2    |  H        |
|   3    |  T and H  |

- **bool getAlertPendingStatus()** idem.
- **bool getAlertHumidityStatus()** idem.
- **bool getAlertTemperatureStatus()** idem.
- **bool setAlertLevels(float temperature, float humidity)** 
  - the values will be truncated to the nearest value possible.
  - the ALERT supports HIGH limit only ==> there is no LOW limit ALERT.
  - note: the datasheet is ambiguous with respect to the formula used.
- **float getAlertLevelTemperature()** returns the truncated value set.
- **float getAlertLevelHumidity()** returns the truncated value set.


The ALERT pin triggers with a falling edge (from HIGH to LOW).


### Voltage

VCC measurement should be enabled by means of **void setVCCenable(true)**
or by **setConfigRegister(0x0004)**.

- **float getVoltage()** unclear what unit is used.

Best guess for now: 16 bit data implies ```voltage = 5.0V * value / 32768.0;``` 
Varied slightly 5.000 - 4.999 also for 3V3 power supply.

Conclusion: it is unclear how to interpret this register.


### Meta data

- **uint16_t getManufacturer()** returns 0x5959.
- **uint16_t getVersionID()** return value may differ. 
Test returned 0x8305.


## Future

- test (see below)
- elaborate documentation.

#### test

- test ESP32, other platforms?
- test performance.
- test resolution bits.
  - delay ?
- test configuration functions.
- test ALERT functions.
- test write / readRegister with a single uint16_t to simplify code.

#### Could


