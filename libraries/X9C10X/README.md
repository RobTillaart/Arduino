
[![Arduino CI](https://github.com/RobTillaart/X9C10X/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/X9C10X/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/X9C10X/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/X9C10X/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/X9C10X/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/X9C10X/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/X9C10X.svg?maxAge=3600)](https://github.com/RobTillaart/X9C10X/releases)


# X9C10X

Arduino Library for X9C10X series digital potentiometer.


## Description

This experimental library provides a X9C10X base class and four derived classes for specific digital potentiometer.

| type   | resistance | tested  |  notes       |
|:------:|:----------:|:-------:|:-------------|
| X9C10X |    generic |    Y    |  base class  |
| X9C102 |    1 KΩ    |    N    |  10 \* 10^2  |
| X9C103 |   10 KΩ    |    Y    |  10 \* 10^3  |
| X9C104 |  100 KΩ    |    N    |  10 \* 10^4  |
| X9C503 |   50 KΩ    |    N    |  50 \* 10^3  |


_Note: Ω Ohm sign = ALT-234_

The library keeps cache of the position. 


### PINOUT


```cpp
//  PINOUT  X9C10X TOP VIEW  (see datasheet)
//
//       +--------+
//  INC  | o    o |  VCC
//  U/D  | o    o |  CS
//  RH   | o    o |  RL
//  GND  | o    o |  Rwiper
//       +--------+
//
//  INC   pulses
//  U/D   UP = 1 DOWN = 0
//  VCC   +5V
//
```


## Interface


## X9C10X base class

Use **\#include "X9C10X.h"**

- **X9C10X(uint32_t Ohm = 10000)** Constructor, default initializes the resistance to 10000 Ω. 
To calibrate one can fill in any other value e.g. 9950 Ω.
- **void begin(uint8_t pulsePin, uint8_t directionPin, uint8_t selectPin, uint8_t position = 0)** 
sets the pins used by the device, and resets the position (default to 0).
The position parameter allows to start the device with a previous stored position. 
Use this position with care.

Note: **begin()** has a hard coded 500uS delay so the device can wake up.

Note: multiple devices can be controlled, just by giving them an unique selectPin.
This behaviour is similar to the SPI select pin.

- **void setPosition(uint8_t position)** sets the wiper to a position between 0 and 99. 
- **uint8_t getPosition()** returns the current position.
- **void incr()** moves one position up (if possible).
- **void decr()** moves one position down (if possible).
- **uint32_t getOhm()** returns the position expressed in Ohm.
The returned value does depend on the value passed in the constructor.
- **uint32_t getMaxOhm()** returns the maximum value ( =  parameter from constructor). 


#### Store 

Warning: use with care.

- **uint8_t store()** stores the current position in the NVRAM of the device, 
and returns the current position so it can later be used as position parameter for **begin()**. 

If one uses an incorrect parameter position in **begin()** the internal state and the device 
will probably be out of sync. One way to sync is call **begin()** with the right parameters. 
The other way is to call **setPosition(0)** followed by **setPosition(99)** (or vice versa) 
to get a defined internal state.


#### Calibration

One can measure the resistance between RH and RL and use this value to set 
in the constructor. Although the value will not differ much from the datasheet
one can get more precise values from the **getOhm()** function this way.


## Derived classes 

There are 4 derived classes, each with a other (appropriate) default value for the resistance. 

- **X9C102(uint32_t Ohm = 1000)** idem.
- **X9C103(uint32_t Ohm = 10000)** idem.
- **X9C104(uint32_t Ohm = 100000)** idem.
- **X9C503(uint32_t Ohm = 50000)** idem.

These classes have the same interface as the base class.
The only difference is that the type is set.


#### Performance

The table below is tested on a (relative slow) Arduino UNO 16 MHz with IDE 1.18.19.
Other processors might give similar or faster times. See performance example.

X9C10X_LIB_VERSION: 0.1.2

 | function            | time in us | notes                   |
 |:--------------------|:----------:|:------------------------|
 | getPosition         |     4      | cached value            |
 | setPosition(33)     |   304      | from 0 to 33            |
 | setPosition(66)     |   524      | from 0 to 66            |
 | setPosition(99)     |   780      | from 0 to 99            |
 | setPosition(33)     |   288      | from 0 to 33            |
 | setPosition(66)     |   276      | from 33 to 66           |
 | setPosition(99)     |   276      | from 66 to 99           |
 | setPosition(33)     |    12      | from 33 to 33 = no move |
 | setPosition(66)     |     4      | from 66 to 66 = no move |
 | setPosition(99)     |     4      | from 99 to 99 = no move |
 | getMaxOhm           |     4      | cached value            |
 | getOhm()            |    48      |                         |
 | incr()              |    28.8    | average 10 calls        |
 | decr()              |    29.2    | average 10 calls        |

Time per step is 780 / 99 = ~8 us per step on an UNO.


## Operation

See examples.


#### Voltage divider 

The digital potentiometer (esp 10 KΩ and up) can be used as a voltage divider.
Connect RL to GND and RH to +5V and you can do 5V in 100 steps of ~0.05V
A voltage of **3V3** would be **setPosition(66)**. 

Note: check datasheet for the range of the max voltage allowed.


## Future

- test different platforms
- improve the hardcoded 500us delay in **begin()**
- add return code to **setPosition() incr() decr()** ?
- add error codes ?
- test **store()**
