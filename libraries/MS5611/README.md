
[![Arduino CI](https://github.com/RobTillaart/MS5611/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MS5611/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MS5611/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MS5611/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MS5611/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MS5611/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MS5611.svg?maxAge=3600)](https://github.com/RobTillaart/MS5611/releases)


# MS5611

Arduino library for MS5611 temperature and pressure sensor.


## Description

The MS5611 is a high resolution temperature and pressure sensor.
The high resolution is made possible by oversampling (many times).

The device address is 0x76 or 0x77 depending on the CSB pin.

This library only implements the I2C interface. 

```cpp
//
//  BREAKOUT  MS5611  aka  GY63 - see datasheet
//
//  SPI    I2C
//              +--------+
//  VCC    VCC  | o      |
//  GND    GND  | o      |
//         SCL  | o      |
//  SDI    SDA  | o      |
//  CSO         | o      |
//  SDO         | o L    |   L = led
//          PS  | o    O |   O = opening  PS
//              +--------+
//
//  PS to VCC  ==>  I2C
//  PS to GND  ==>  SPI
//  CS to VCC  ==>  0x76
//  CS to GND  ==>  0x77
//
```

## important Changes

#### 0.3.0 breaking change

1. fixed math error so previous versions are **obsolete**.
2. temperature is a float expressed in degrees Celsius.
3. pressure is a float expressed in mBar.


#### 0.3.5 NANO 33 BLE

After lots of hours of testing it appeared that the I2C/Wire library of the NANO 33 BLE
does not handle **isConnected()** like other platforms do. 
It looks like an uninitialized length of the I2C buffer, causing failure when calling **begin()**.
Adding a **wire->write(0x00)** seems to fix the issue.


## Interface

- **MS5611(uint8_t deviceAddress)** constructor.
- **bool begin(uint8_t sda, uint8_t scl, TwoWire \*wire = &Wire)** for ESP and alike, optionally set Wire interface. initializes internals, 
- **bool begin(TwoWire \*wire = &Wire)** for UNO and alike, optionally set Wire interface. Initializes internals.
- **bool isConnected()** checks availability of device address on the I2C bus.
- **reset()** resets the chip and loads constants from its ROM.
- **int read(uint8_t bits)** the actual reading of the sensor. Returns MS5611_READ_OK upon success.
- **int read()** the actual reading of the sensor, uses the preset oversampling (see below). Returns MS5611_READ_OK upon success.
- **void setOversampling(osr_t samplingRate)** sets the amount of oversampling. 
See table below and test example how to use.
- **osr_t getOversampling()** returns amount of oversampling.
- **float getTemperature()** returns temperature in °C. Subsequent calls will return same value until a new **read()** is called.
- **float getPressure()** pressure is in mBar. Subsequent calls will return same value until a new **read()** is called.
- **int getLastResult()** checks last I2C communication (replace with more informative error handling?)
- **uint32_t lastRead()** last time when **read()** was called in milliseconds since startup.


#### Oversampling table

(numbers from datasheet, actual time differs - todo)

| definition     | value | oversampling ratio | resolution (mbar) | time (ms) | notes |
|:--------------:|:-----:|:------------------:|:----------------:|:---------:|:------:|
| OSR_ULTRA_HIGH |  12   |        4096        |      0.012       |   8.22    |
| OSR_HIGH       |  11   |        2048        |      0.018       |   4.1     |
| OSR_STANDARD   |  10   |        1024        |      0.027       |   2.1     |
| OSR_LOW        |  9    |        512         |      0.042       |   1.1     |
| OSR_ULTRA_LOW  |  8    |        256         |      0.065       |   0.5     | Default = backwards compatible


## Disclaimer

The library is still experimental. So all feedback is welcome.


## Operation

See examples


## Future

- update documentation
- create a SPI based library (same base class if possible?)
  - first get it working 100%
- proper error handling
- redo lower level functions?
- handle the read + math of temperature first? 
- add get- and setPressureOffset()
- add get- and setTemperatureOffset()

