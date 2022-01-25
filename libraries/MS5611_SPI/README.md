
[![Arduino CI](https://github.com/RobTillaart/MS5611_SPI/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MS5611_SPI/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MS5611_SPI/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MS5611_SPI/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MS5611_SPI/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MS5611_SPI/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MS5611_SPI.svg?maxAge=3600)](https://github.com/RobTillaart/MS5611_SPI/releases)


# MS5611_SPI

Arduino library (SPI) for MS5611 temperature and pressure sensor.


# WARNING EXPERIMENTAL

**Note: This library is under development and NOT stable**

SPI communication sec seems to work as "reasonable" values are read.

All SPI tests so far gave too high temperatures, some were rising slowly, others faster.
Values are read correctly but somehow the selection of SPI as protocol seems to cause internal heating.

As I only have 1 sensor I cannot verify if there is something broken.
Selecting I2C still does give stable results from the sensor.


| Platform        | tested | time (us)| Notes   |
|:----------------|-------:|:--------:|--------:|
|  UNO SW SPI     |  fail  |          | temperature is rising very fast (stopped)
|  UNO HW SPI     |  fail  |          | no data, 
|  ESP32 SW SPI V |   Y    |   1299   | VSPI pins; temperature is rising slowly
|  ESP32 SW SPI H |   Y    |   1298   | HSPI pins; temperature too high (+3) but looks stable
|  ESP32 HSPI     |   Y    |   1396   | temperature is rising slowly
|  ESP32 VSPI     |   Y    |   1395   | temperature is rising slowly
|  NANO 33 SW SPI |   -    |    -     | not tested yet
|  NANO 33 HW SPI |   -    |    -     | not tested yet


#### Note UNO

for VCC 3V3 was used as the other pins CLK and SDI have a voltage converter in the GY-63.
Unclear why HW SPI blocks for UNO. (to investigate)


#### Note ESP32 

HSPI pins: not reliable at start, incorrect PROM reads, both HW and SW. 
adjusting the timing improves this a bit.
+ these pins also interfere with uploading.


#### Conclusion for now

In short a lot of open ends to investigate. 

If you have experiences with this library please share them in the issues.

----

## Description

The MS5611 is a high resolution temperature and pressure sensor a.k.a GY-63.
The high resolution is made possible by oversampling many times.

This library only implements the SPI interface.

Based upon the 0.3.6 version of the I2C library, 
see - https://github.com/RobTillaart/MS5611


#### Breakout GY-63

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
//  PS to VCC  ==>  I2C  (GY-63 board has internal pull up, so not needed)
//  PS to GND  ==>  SPI
//  CS to VCC  ==>  0x76
//  CS to GND  ==>  0x77
//
```

#### Related libraries

For pressure conversions see - https://github.com/RobTillaart/pressure

For temperature conversions see - https://github.com/RobTillaart/Temperature


## Release Notes

### 0.1.0 initial release

Based upon 0.3.8 of the I2C MS5611 library.


## Interface

#### Base

- **MS5611_SPI(uint8_t select, uint8_t dataOut = 255, uint8_t dataIn = 255, uint8_t clock = 255)** constructor.
- **bool begin()** initializes internals, 
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


#### DeviceID

- **uint32_t getDeviceID()** returns the hashed values of the calibration PROM. 
As these calibration are set in the factory and differ (enough) per sensor these can serve as an unique deviceID.

Having a device-ID can be used in many ways:
- use known offsets for each sensor automatically, 
- work as an identification of that specific copy of the project (customer specific tracking).
- ID in a mesh network
- etc.

Note: this is not an official ID from the device / datasheet, it is made up from calibration data.


#### 2nd order pressure compensation

- **setCompensation(bool flag = true)** to enable/desiable the 2nd order compensation. 
The default = true. 
Disabling the compensation will be slightly faster but you loose precision.
- **getCompensation()** returns flag set above.


#### SPI functions

// to be tested.

- **void setSPIspeed(uint32_t speed)**
- **uint32_t getSPIspeed()**
- **bool usesHWSPI()**


#### SPI - ESP32 specific

// to be tested.

- **void selectHSPI()**
- **void selectVSPI()**
- **bool usesHSPI()**
- **bool usesVSPI()**
- **void setGPIOpins(uint8_t clk, uint8_t miso, uint8_t mosi, uint8_t select)**


## Operation

See examples


## Future

- follow I2C library.
- investigate internal heating with SPI.
