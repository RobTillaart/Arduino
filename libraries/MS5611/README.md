
[![Arduino CI](https://github.com/RobTillaart/MS5611/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MS5611/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MS5611/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MS5611/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MS5611/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MS5611/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MS5611.svg?maxAge=3600)](https://github.com/RobTillaart/MS5611/releases)


# MS5611

Arduino library for MS5611 temperature and pressure sensor.


## Description

The MS5611 is a high resolution temperature and pressure sensor a.k.a GY-63.
The high resolution is made possible by oversampling many times.

The device address is 0x76 or 0x77 depending on the CSB/CSO pin.

This library only implements the I2C interface. 


#### breakout

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
//          PS  | o    O |   O = opening  PS = protocol select
//              +--------+
//
//  PS to VCC  ==>  I2C
//  PS to GND  ==>  SPI
//  CS to VCC  ==>  0x76
//  CS to GND  ==>  0x77
//
```

#### related libraries

For pressure conversions see - https://github.com/RobTillaart/pressure

For temperature conversions see - https://github.com/RobTillaart/Temperature


## Release Notes

#### 0.3.0 breaking change

1. fixed math error so previous versions are **obsolete**.
2. temperature is a float expressed in degrees Celsius.
3. pressure is a float expressed in mBar.


#### 0.3.5 NANO 33 BLE

The I2C/Wire library of the NANO 33 BLE does not see the device on the I2C bus. 
After hours of testing it looks like that the I2C/Wire library of the NANO 33 BLE 
does not handle **isConnected()** like other platforms do. 
Adding a **wire->write(0x00)** in **isConnected()** fixes the problem, 
however more investigation is needed to understand the root cause.


#### 0.3.6 

The **write(0)** in **isConnected()** is made conditional explicit for the NANO 33 BLE.

The timing for convert is adjusted from TYPICAL to MAX - datasheet page 3.


## Interface

#### Base

- **MS5611(uint8_t deviceAddress)** constructor.
- **bool begin(uint8_t sda, uint8_t scl, TwoWire \*wire = &Wire)** for ESP and alike, optionally set Wire interface. initializes internals, 
- **bool begin(TwoWire \*wire = &Wire)** for UNO and alike, optionally set Wire interface. Initializes internals.
- **bool isConnected()** checks availability of device address on the I2C bus.
(see note above NANO 33 BLE).
- **reset()** resets the chip and loads constants from its ROM.
- **int read(uint8_t bits)** the actual reading of the sensor. 
Number of bits determines the oversampling factor. Returns MS5611_READ_OK upon success.
- **int read()** wraps the **read()** above, uses the preset oversampling (see below). 
Returns MS5611_READ_OK upon success.
- **float getTemperature()** returns temperature in °C. 
Subsequent calls will return the same value until a new **read()** is called.
- **float getPressure()** pressure is in mBar. 
Subsequent calls will return the same value until a new **read()** is called.


#### Oversampling

- **void setOversampling(osr_t samplingRate)** sets the amount of oversampling. 
See table below and test example how to use.
- **osr_t getOversampling()** returns amount of oversampling.


Some numbers from datasheet, page 3 MAX column rounded up. (see #23)
(actual read time differs - see performance sketch)

| definition     | value | oversampling ratio | resolution (mbar) | time (us) | notes  |
|:--------------:|:-----:|:------------------:|:-----------------:|:---------:|:------:|
| OSR_ULTRA_HIGH |  12   |        4096        |      0.012        |   9100    |
| OSR_HIGH       |  11   |        2048        |      0.018        |   4600    |
| OSR_STANDARD   |  10   |        1024        |      0.027        |   2300    |
| OSR_LOW        |  9    |        512         |      0.042        |   1200    |
| OSR_ULTRA_LOW  |  8    |        256         |      0.065        |    600    | Default = backwards compatible



#### Offset 

The offset functions are added (0.3.6) to calibrate the sensor against e.g. a local weather station. 
This calibration can only be done runtime.

- **void setPressureOffset(float offset = 0)** Set an offset to calibrate the pressure. 
Can be used to get the pressure relative to e.g. 1 Atm. 
Set the offset to -1013 HPa/mBar and you get a sort of relative pressure.
Default the offset is set to 0.
- **float getPressureOffset()** returns the current pressure offset.
- **void setTemperatureOffset(float offset = 0)** Set an offset to calibrate the temperature. 
Can be used to get the temperature in degrees Kelvin, just set the offset to +273.15.
Default the offset is set to 0.
- **float getTemperatureOffset()** returns the current temperature offset.


#### Misc

- **int getLastResult()** checks last I2C communication. Replace with more informative error handling?
- **uint32_t lastRead()** last time when **read()** was called in milliseconds since startup.


## Operation

See examples


## Future

- update documentation
  - separate release notes?
- create a SPI based library (same base class if possible?)
  - first get this lib working 100%
- proper error handling
- redo lower level functions?
- handle the read + math of temperature first? 
-
