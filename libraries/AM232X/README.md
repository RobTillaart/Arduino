
[![Arduino CI](https://github.com/RobTillaart/AM232X/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AM232X/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AM232X.svg?maxAge=3600)](https://github.com/RobTillaart/AM232X/releases)

# AM232X

Arduino library for AM2320 AM2321 and AM2322 I2C temperature and humidity sensor


## Description

AM232X is a sensor similar to the DHT12 with an I2C interface. 
Although in theory this could enable multiple sensors on one bus
the AM232X has a fixed address **0x5C** so 

Typical parameters

|        |  range | accuracy | repeatability
|:-------|:------:|:------:|:------:|
| Temperature | -40 - 80   | 0.5°C  | ±0.1 |
| Humidity    | 0.0 - 99.9 | 3%     | ±0.1 |
| Sample time | 2 seconds  |        |      |


```
//  Bottom view 
//       +---+
//  VDD  |o  |
//  SDA  |o  |
//  GND  |o  |
//  SCL  |o  |
//       +---+
```


## Interface

### Constructor

- **AM232X(TwoWire \*wire = &Wire)** constructor, optionally set Wire0..WireN.
- **bool begin(uint8_t sda, uint8_t scl)** for ESP32 alike devices, returns true if device is connected
- **bool begin()** for AVR alike devices, returns true if device is connected
- **bool isConnected()** returns true if device-address is found on I2C bus.


### Base calls

- **int read()** fetches the values from the sensor
- **float getHumidity()** returns the last read humidity
- **float getTemperature()** returns the last read temperature


### Misc

check datasheet for details.

- **int getModel()** idem
- **int getVersion()** idem
- **uint32_t getDeviceID()** idem
- **int getStatus()**
- **int getUserRegisterA()**
- **int getUserRegisterB()**
- **int setStatus(uint8_t value)**
- **int setUserRegisterA(int value)**
- **int setUserRegisterB(int value)**


## Operation

See examples

In setup() you have to call the **begin()** to initialize 
the Wire library and do an initial **read()** to fill the 
variables temperature and humidity. 
To access these values one must use **getTemperature()** and **getHumidity()**. 


## Future



## Warning

The library has not been tested extensively yet so use at own risk.

See also LICENSE
