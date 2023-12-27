
[![Arduino CI](https://github.com/RobTillaart/PCA9553/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PCA9553/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PCA9553/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PCA9553/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PCA9553/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/PCA9553.svg)](https://github.com/RobTillaart/PCA9553/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PCA9553/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PCA9553.svg?maxAge=3600)](https://github.com/RobTillaart/PCA9553/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/PCA9553.svg)](https://registry.platformio.org/libraries/robtillaart/PCA9553)


# PCA9553

Arduino library for PCA9553 I2C 8 bit PWM LED driver, 4 channel.


## Description

This experimental library is to control the I2C PCA9553 PWM extender.
This device has two possible hardcoded I2C addresses 0x62 and 0x63, 
see table below.
If you need to connect more PCA9553 devices to a single I2C bus you 
need a I2C multiplexer like https://github.com/RobTillaart/TCA9548.

The device has two PWM "generators", 0 and 1, and one can set the 
duty cycle and the frequency by means of a pre-scaler. 

Every output channel 0..3 can select to which PWM generator it is 
connected, or if it is set to ON or OFF.

The output channels can also be used as generic GPIO, however that
is not implemented in the first release.


#### From datasheet

Maximum output sink current is 25 mA per bit and 100 mA per package.

Power-On Reset (POR) initializes the registers to their default state, 
all zeroes, causing the bits to be set HIGH (LED off).


#### 0.4.0 Breaking change

The version 0.4.0 has breaking changes in the interface. 
The rationale is that the programming environment of the **Arduino ESP32 S3** 
board uses a remapping by means of the include file **io_pin_remap.h**.
This file remaps the pins of several core Arduino functions. 
The remapping is implemented by #define macros and these implement "hard" text 
replacements without considering context. 
The effect is that methods from this class (and several others) which have the same 
name as those Arduino core functions will be remapped into something not working.

The following library functions have been renamed:

|  old name        |  new name    |  notes  |
|:-----------------|:-------------|:--------|
|  analogRead()    |  read()      |
|  analogWrite()   |  write()     |
|  pinMode()       |  pinMode1()  |
|  digitalRead()   |  read1()     |
|  digitalWrite()  |  write1()    |


#### 0.3.0 Breaking change

Version 0.3.0 introduced a breaking change.
You cannot set the pins in **begin()** any more.
This reduces the dependency of processor dependent Wire implementations.
The user has to call **Wire.begin()** and can optionally set the Wire pins 
before calling **begin()**.


#### I2C adresses

|  type        |  Address  |
|:-------------|:---------:|
|  PCA9553/01  |  0x62     | 
|  PCA9553/02  |  0x63     |


#### Related

- https://github.com/RobTillaart/PCA9551  (8 channel)
- https://github.com/RobTillaart/PCA9552  (16 channel)
- https://github.com/RobTillaart/PCA9553  (4 channel)

Follow up series
- https://github.com/RobTillaart/PCA9634  (8 channel)
- https://github.com/RobTillaart/PCA9635  (16 channel)
- https://github.com/RobTillaart/PCA9685_RT  (16 channel)



## Interface

```cpp
#include "PCA9553.h"
```


#### Constructor

- **PCA9553(uint8_t deviceAddress, TwoWire \*wire = &Wire)** Constructor with I2C device address,  
Address = 0x62 or 0x63.
Optional the Wire interface as parameter.
- **bool begin()** initializes the library after startup.
Returns true if device address is available on I2C bus.
- **bool isConnected()** checks if address is available on I2C bus.
- **uint8_t getAddress()** returns I2C address.
- **uint8_t outputCount()** returns the number of channels = 4.
- **uint8_t reset()**


#### GPIO

- **uint8_t getInput()** read all current output levels.
- **void pinMode1(uint8_t pin, uint8_t mode)** set output pin to INPUT or OUTPUT.
- **void write1(uint8_t pin, uint8_t value)** set output pin HIGH or LOW.
- **uint8_t read1(uint8_t pin)** read current state of output pin.


#### Prescaler Frequency

Get and set the pre-scaler of the PWM generator.

- **void setPrescaler(uint8_t gen, uint8_t psc = 255)** set pre-scaler for generator, default 255.
- **uint8_t getPrescaler(uint8_t gen)** get the set value.

gen = 0 or 1

The main oscillator frequency can be divided by a pre-scaler.
The period of ```BLINK = (PSC + 1) / 44```
This gives the output a blink range of 0.172 Hz to 44 Hz.

Some "magic" pre-scalers.  (to be confirmed).

|  psc  |  Period  |  Frequency  |
|:-----:|:--------:|:-----------:|
|    0  |  0.0227  |  44.00 Hz   |
|    1  |  0.0455  |  22.00 Hz   |
|    3  |  0.0909  |  11.00 Hz   |
|    7  |  0.1818  |   5.50 Hz   |
|   10  |  0.250   |   4.00 Hz   |
|   21  |  0.500   |   2.00 Hz   |
|   43  |  1.000   |   1.00 Hz   |
|   87  |  2.000   |   0.50 Hz   |
|  175  |  4.000   |   0.25 Hz   |
|  219  |  5.000   |   0.20 Hz   |
|  255  |  5.818   |  0.172 Hz   |


#### PWM

Get and set the duty cycle of the PWM generator.

- **void setPWM(uint8_t gen, uint8_t psc = 128)** set PWM for generator, 
default value = 128.
- **uint8_t getPWM(uint8_t gen)** get the set value.

gen = 0 or 1

The duty cycle of ```BLINK = (256 - PWM) / 256```

|  pwm  |  Duty Cycle  |
|:-----:|:------------:|
|    0  |     0%       |
|   64  |    25%       |
|  128  |    50%       |
|  192  |    75%       |
|  255  |   100%       |

Note: one might need a Gamma brightness correction - https://github.com/RobTillaart/GAMMA


#### Output Mode

- **uint8_t setOutputMode(uint8_t pin, uint8_t mode)** set the mode for 
the selected output pin to one of 4 modi operandi.
See table below.
  - pin == 0..3, mode == 0..3, see table below.
  - returns 0 if OK
  - returns error code if parameter is out of range.
- **uint8_t getOutputMode(uint8_t led)** returns current setting.
  - pin == 0..3
  - returns mode, see table below.
  - returns error code if parameter is out of range. 

|  Define             |  Value  |  Output pin          |
|:--------------------|:-------:|:---------------------|
|  PCA9553_MODE_LOW   |    0    |  is set LOW (LED on)
|  PCA9553_MODE_HIGH  |    1    |  is set high-impedance (LED off; default)
|  PCA9553_MODE_PWM0  |    2    |  blinks at PWM0 rate
|  PCA9553_MODE_PWM1  |    3    |  blinks at PWM1 rate


#### Power On Reset

The PCA9553 will keep its settings as long as it is powered on. 
This means it can start with an previous configuration when uploading 
two different sketches short after each other.

To handle this the library has a **reset()** function which sets
the device in the Power On state.


#### Error codes

These are kept similar to PCA9635 et al error codes.

|  Error code             |  Value  |  Description           |
|:------------------------|:-------:|:-----------------------|
|  PCA9553_OK             |   0x00  |  Everything went well
|  PCA9553_ERROR          |   0xFF  |  Generic error
|  PCA9553_ERR_WRITE      |   0xFE  |
|  PCA9553_ERR_CHAN       |   0xFD  |  output pin out of range / channel error
|  PCA9553_ERR_MODE       |   0xFC  |  mode parameter out of range.
|  PCA9553_ERR_REG        |   0xFB  |
|  PCA9553_ERR_I2C        |   0xFA  |


## Future

#### Must

- improve documentation
- test with hardware

#### Should

- improve error handling
  - return values, where etc.
- test
  - reset function


#### Could


#### Wont (on request)

- no usage of autoincrement register
- percent interface for PWM
- time interface for pre-scaler
- default setup in begin (what how)


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


