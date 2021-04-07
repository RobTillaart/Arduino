
[![Arduino CI](https://github.com/RobTillaart/AM232X/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AM232X/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AM232X.svg?maxAge=3600)](https://github.com/RobTillaart/AM232X/releases)

# AM232X

Arduino library for AM2320 AM2321 and AM2322 I2C temperature and humidity sensor


## Description

AM232X is a sensor similar to the DHT12 with an I2C interface. 
Although in theory this could enable multiple sensors on one bus
the AM232X has a fixed address **0x5C** so one need to implement a 
multiplexing strategy to have multiple sensors in practice. 
See multiplexing below.


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
- **bool isConnected(uint16_t timeout = 3000)** returns true if device-address is found on I2C bus. As the device can be in sleep modus it will retry for the defined timeout (in micros) with a minimum of 1 try. minimum = 800 us and maximum = 3000 us according to datasheet.


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
- **bool wakeUp()** function that will try for 3 milliseconds to wake up the sensor.


## Operation

See examples

In setup() you have to call the **begin()** to initialize 
the Wire library and do an initial **read()** to fill the 
variables temperature and humidity. 
To access these values one must use **getTemperature()** and **getHumidity()**. 

Note that the sensor can go into sleep mode and one might need to call **wakeUp()**
before the **read()**.


## Multiplexing 

Multiplexing the AM232X can be done in several ways.
This is not a complete list or tutorial but should get you started.

1. Control the power line by means of an extra pin (+ transistor). 
Only switch on the sensor you want to use. Drawback might be time 
the sensor takes to boot and to be ready for the first measurement.
2. Use an AND gate between the I2C SCL (clock) line and the I2C SCL 
pin of the sensors. This way one can enable / disable communication 
per sensor. This will still need an IO pin per sensor but does not 
have the "boot time" constraint mentioned above.
3. Use a TCA9548A I2C Multiplexer, or similar. 

Which method fit your application depends on your requirements and constraints.



## Future



## Warning

The library has not been tested extensively yet so use at own risk.

See also LICENSE
