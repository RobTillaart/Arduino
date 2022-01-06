
[![Arduino CI](https://github.com/RobTillaart/PCA9634/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PCA9634/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PCA9634/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PCA9634/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PCA9634/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PCA9634/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PCA9634.svg?maxAge=3600)](https://github.com/RobTillaart/PCA9634/releases)


# PCA9634

Arduino library for PCA9634 I2C 8 bit PWM LED driver, 8 channel.


## Description

This library is to control the I2C PCA9634 PWM extender.
The 8 channels are independently configurable in steps of 1/256.
this allows for better than 1% fine tuning of the duty-cycle
of the PWM signal. 

library is a 8 channel derived variation of the PCA9635 class.
(these might merge in the future)


## Interface


### Constructor

- **PCA9634(uint8_t deviceAddress, TwoWire \*wire = &Wire)** Constructor with I2C device address, 
and optional the Wire interface as parameter.
- **bool begin()** initializes the library after startup. Mandatory.
- **bool begin(uint8_t sda, uint8_t scl)** idem, ESP32 ESP8266 only. Library does not support 
multiple Wire instances (yet).
- **void reset()** resets the library to start up conditions.
- **bool isConnected()** checks if address is available on I2C bus.
- **uint8_t channelCount()** returns the number of channels = 8.

### LedDriverMode

- **uint8_t setLedDriverMode(uint8_t channel, uint8_t mode)** mode is 0..3 See datasheet for full details.
- **uint8_t getLedDriverMode(uint8_t channel)** returns the current mode of the channel.

| LED mode           | Value | Description                       |
|:-------------------|:-----:|:----------------------------------|
| PCA9634_LEDOFF     | 0x00  | led is 100% off, default @startup |
| PCA9634_LEDON      | 0x01  | led is 100% on.                   |
| PCA9634_LEDPWM     | 0x02  | set LED in PWM mode, 0..255       |
| PCA9634_LEDGRPPWM  | 0x03  | add LED to the GRPPWM*            |

\* all LEDs in the group GRPPWM can be set to the same PWM value in one set.
This is ideal to trigger e.g. multiple LEDs (servo's) at same time.


### Read and write

- **uint8_t write1(uint8_t channel, uint8_t value)** writes a single 8 bit PWM value.
- **uint8_t write3(uint8_t channel, uint8_t R, uint8_t G, uint8_t B)** writes three consecutive PWM registers.
typical use is to write R, G, B values for a full colour LED.
- **uint8_t writeN(uint8_t channel, uint8_t \* array, uint8_t count)** write count consecutive PWM registers. 
May return **PCA9634_ERR_WRITE** if array has too many elements 
(including channel as offset).
- **uint8_t writeMode(uint8_t reg, uint8_t value)** configuration of one of the two configuration registers.
check datasheet for details.
- **uint8_t readMode(uint8_t reg)** reads back the configured mode, 
useful to add or remove a single flag (bit masking).


### Group PWM and frequency

- **void setGroupPWM(uint8_t value)** sets all channels that are part of the PWM group to value.
- **uint8_t getGroupPWM()** get the current PWM setting of the group.
- **void setGroupFREQ(value)** see datasheet for details. 
- **uint8_t getGroupFREQ()** returns the freq of the PWM group.


### Miscellaneous

- **int lastError()** returns **PCA9634_OK** if all is OK, and other error codes otherwise.

| Error code        | Value | Description          |
|:------------------|:-----:|:---------------------|
| PCA9634_OK        | 0x00  | Everything went well
| PCA9634_ERROR     | 0xFF  | Generic error
| PCA9634_ERR_WRITE | 0xFE  | Tries to write more elements than PWM channels
| PCA9634_ERR_CHAN  | 0xFD  | Channel out of range
| PCA9634_ERR_MODE  | 0xFC  | Invalid mode
| PCA9634_ERR_REG   | 0xFB  | Invalid register
| PCA9634_ERR_I2C   | 0xFA  | PCA9634 I2C communication error


## Operation

See examples


## Future

- improve documentation
- unit tests
- add examples
- follow PCA9635 developments
- merge with PCA9635 and a PCA963X base class if possible

