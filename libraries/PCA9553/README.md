
[![Arduino CI](https://github.com/RobTillaart/PCA9553/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PCA9553/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PCA9553/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PCA9553/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PCA9553/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PCA9553/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PCA9553.svg?maxAge=3600)](https://github.com/RobTillaart/PCA9553/releases)


# PCA9553

Arduino library for PCA9553 I2C 8 bit PWM LED driver, 4 channel.


## Description

This library is to control the I2C PCA9553 PWM extender.
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


#### I2C adresses

|  type        |  Address  |
|:-------------|:---------:|
|  PCA9553/01  |  0x62     | 
|  PCA9553/02  |  0x63     |


#### Related

- https://github.com/RobTillaart/PCA9634 (8 channel)
- https://github.com/RobTillaart/PCA9553 (16 channel)
- https://github.com/RobTillaart/PCA9685_RT (16 channel)
- https://github.com/RobTillaart/PCA9553  (4 channel)


## Interface

```cpp
#include "PCA9553.h"
```


#### Constructor

- **PCA9553(uint8_t deviceAddress, TwoWire \*wire = &Wire)** Constructor with I2C device address,  Address = 0x62 or 0x63.
and optional the Wire interface as parameter.
- **bool begin()** initializes the library after startup.
Returns true if device address is available on I2C bus.
- **bool begin(int sda, int scl)**
idem, ESP32 ESP8266 only.
- **bool isConnected()** checks if address is available on I2C bus.
- **uint8_t channelCount()** returns the number of channels = 4.


#### Input

- **getInput()** read current output levels.
Only the lower 4 bits are used.


#### Prescalers Frequency

- **void setPrescaler0(uint8_t psc = 255)** set prescaler 0, default 255.
- **uint8_t getPrescaler0()** get set value.
- **void setPrescaler1(uint8_t psc = 255)** set prescaler 1, default 255.
- **uint8_t getPrescaler1()** get set value.

The main oscillator frequency can be divided by a pre-scaler.
The period of ```BLINK = (PSC + 1) / 44```
This gives the output a blink range of 0.172 Hz to 44 Hz.

Some "magic" pre-scalers.  (to be confirmed).

|  psc  |  period  |  frequency  |
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

- **void setPWM0(uint8_t pwm = 128)** set PWM0, default 128 == 50%.
- **uint8_t getPWM0()** return set PWM.
- **void setPWM1(uint8_t pwm = 128)** set PWM0, default 128 == 50%.
- **uint8_t getPWM1()** return set PWM.

The duty cycle of ```BLINK = (256 - PWM) / 256```

|  pwm  |  duty cycle  |
|:-----:|:------------:|
|    0  }     0%       |
|   64  |    25%       |
|  128  |    50%       |
|  192  |    75%       |
|  255  |   100%       |

Note: one might need a Gamma brightness correction - https://github.com/RobTillaart/GAMMA


#### LED source selector

- **bool setLEDSource(uint8_t led, uint8_t source)** set the source 
of the selected led.
  - led == 0..3, source == 0..3, see table below
  - returns false if parameter is out of range.
- **uint8_t getLEDSource(uint8_t led)** returns current setting.
  - led == 0..3
  - return source, see table below.
  - returns 0xFF if led parameter out of range. 

|  source  |  output              |
|:--------:|:---------------------|
|    00    |  is set LOW (LED on)
|    01    |  is set high-impedance (LED off; default)
|    10    |  blinks at PWM0 rate
|    11    |  blinks at PWM1 rate


#### Error codes

These are kept similar to PCA9635 et al error codes.

|  Error code             |  Value  |  Description           |
|:------------------------|:-------:|:-----------------------|
|  PCA9553_OK             |   0x00  |  Everything went well
|  PCA9553_ERROR          |   0xFF  |  Generic error
|  PCA9553_ERR_WRITE      |   0xFE  |
|  PCA9553_ERR_CHAN       |   0xFD  |
|  PCA9553_ERR_MODE       |   0xFC  |
|  PCA9553_ERR_REG        |   0xFB  |
|  PCA9553_ERR_I2C        |   0xFA  |

To be elaborated in the source code.


## Future

#### Must

- improve documentation
- test test test

#### Should

- **reset()**  power on reset...
- GPIO modi pins
  - **pinMode()**
  - **digitalWrite()**
  - **digitalRead()**
- improve error handling
  - return values, where etc.
- **setLEDSource(src0, src1, src2, src3)** one call
- defines for sources
- getAddress()

#### Could

#### Wont (on request)

- no usage of autoincrement register
- percent interface for PWM
- time interface for prescaler
- default setup in begin (what how)
- alternative interface calls
  - **setPWM(pwm0, pwm1)**
  - **setPrescaler(psc0, psc1)**
  - **setChannel(channel, psc0, pwm)**
  - **setPWM(channel, pwm);
  - **setPrescaler(channel, psc1)**
