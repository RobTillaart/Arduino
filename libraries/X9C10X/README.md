
[![Arduino CI](https://github.com/RobTillaart/X9C10X/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/X9C10X/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/X9C10X/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/X9C10X/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/X9C10X/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/X9C10X.svg)](https://github.com/RobTillaart/X9C10X/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/X9C10X/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/X9C10X.svg?maxAge=3600)](https://github.com/RobTillaart/X9C10X/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/X9C10X.svg)](https://registry.platformio.org/libraries/robtillaart/X9C10X)


# X9C10X

Arduino Library for X9C10X series digital potentiometer.


## Description

This **experimental** library provides 
- a minimal X9C base class, 
- an elaborated X9C10X class and 
- four derived classes for specific digital potentiometer.

| class  | resistance | tested  |  notes       |
|:------:|:----------:|:-------:|:-------------|
| X9C    | no support |    Y    |  minimalistic base class |
| X9C10X |    generic |    Y    |  base class  |
| X9C102 |    1 KΩ    |    N    |  10 \* 10^2  |
| X9C103 |   10 KΩ    |    Y    |  10 \* 10^3  |
| X9C104 |  100 KΩ    |    N    |  10 \* 10^4  |
| X9C503 |   50 KΩ    |    N    |  50 \* 10^3  |


_Note: Ω Ohm sign = ALT-234_

The X9C10X object keeps track of the position of the potentiometer,
but the user should set it with **setPosition(position, true);**
Otherwise the library and device will probably not be in sync.

Since 0.2.1 the library also supports **restoreInternalPosition(position)**
to set the internal position with the value from the latest **store()** call.
See the examples.


#### Multiple devices

Multiple devices can be controlled by assigning them an unique selectPin (CS).
This behaviour is similar to the SPI select pin.

It should be possible to share the U/D and INC lines (not tested) when controlling
multiple X9C devices.

Note: one should select one device at a time.
Sharing a CS pin or sending pulses to multiple devices at the same time will
cause the library and devices get out of sync.


#### PINOUT


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
//  INC     pulses
//  U/D     UP = 1   DOWN = 0
//  VCC     +5V
//  GND     ground
//  RH      resistor high end
//  RL      resistor low end
//  Rwiper  resistor wiper
//  CS      chip select
```

It is advised to use pull up resistors - e.g. 10 KΩ - on the CS, UD and INC line. 
This will help the lines to start in a defined state and will
improve the signal quality. 
The pulses esp. INC can be quite short, so especially with longer lines the
quality can become an issue. (not investigated further)


#### Related

- https://github.com/RobTillaart/AD520x
- https://github.com/RobTillaart/AD524X
- https://github.com/RobTillaart/AD5245
- https://github.com/RobTillaart/AD5144A
- https://github.com/RobTillaart/AD5245
- https://github.com/RobTillaart/AD5263
- https://github.com/RobTillaart/X9C10X


## Interface

```cpp
#include "X9C10X.h"
```

## X9C base class

This is the most minimalistic base class. 
It does not provide position information but sometimes that is just enough.

- **X9C()** Constructor.
- **void begin(uint8_t pulsePin, uint8_t directionPin, uint8_t selectPin)** 
sets the INC, UD and CS pins used by the device.  
Note: **begin()** has a hard coded 500uS delay so the device can wake up.
- **void incr()** moves one position up (if possible). 
- **void decr()** moves one position down (if possible).
- **void store()** stores the current position in NV-RAM to be used at the next restart. 
Does not return a value as the position cannot be read from the device.
So the user must keep track of the position if needed.


## X9C10X base class

This class is derived from the X9C class and adds position, Ohm and type information.

- **X9C10X(uint32_t Ohm = 10000)** Constructor, default initializes the resistance to 10000 Ω. 
To calibrate one can fill in any other (measured) value e.g. 9950 Ω.
This can be useful e.g. if one sets a fixed resistor parallel over the X9C one.
- **void begin(uint8_t pulsePin, uint8_t directionPin, uint8_t selectPin)** 
sets the INC, UD and CS pins used by the device.  
Note: **begin()** has a hard coded 500uS delay so the device can wake up.
- **uint8_t setPosition(uint8_t position, bool forced = false)** sets the wiper 
to a position between 0 and 99. 
The movement is relative to the current (internal) position.
If forced is set to true, the wiper will be moved to the closest "end" position 
and from there moved to the requested position. 
The internal position is replaced by the new position.
If the new position > 99 the new position is truncated to 99.
Returns new position 0 .. 99.
- **uint8_t getPosition()** returns the current (internal) position. 0..99
- **bool incr()** moves one position up (if possible). 
Returns true if moved and false if already at end position
according to internal position math.
- **bool decr()** moves one position down (if possible).
Returns true if moved and false if already at begin position
according to internal position math.
- **uint8_t store()** stores the current position in the NVRAM of the device. 
Returns the current position so it can later be used as position parameter 
for **setPosition()** or **restoreInternalPosition()**.
  - Warning: use with care (not tested).
  - Note: **store()** blocks for 20 milliseconds.
- **uint8_t restoreInternalPosition(uint8_t position)** hard overwrite of the current 
(internal) position to initialize the library with the value returned by **store()**.
The potentiometer will not be moved() in this process, and the user is responsible
to provide the right value. 
Returns new position 0 .. 99.
This function allows users e.g. to save the position returned by **store()** in EEPROM 
to initialize the library with this EEPROM value after a reboot.
  - Warning: use with care (not tested).

Note: **begin()** changed in 0.2.0 as the implicit parameter position
was removed for the explicit function call to **setPosition()**.
If **setPosition()** is not called, the device uses the last stored
value as position. Unfortunately the position cannot be read from the device.
This will result in a mismatch between the internal position and the 
external one. 

Since 0.2.1 the function **uint8_t restoreInternalPosition(uint8_t position)** 
gives some means to solve this, see examples.
Be aware that if a system resets and the position has been changed since last 
**store()** the restore and therefore the library will not be in sync with the device. 
To create a fool proof system additional hardware is needed, see Concept read position below.


#### Ohm

- **uint32_t getOhm()** returns the position expressed in Ohm.
The returned value does depend on the value passed in the constructor
and the current position. 
Note: value returned might differ a bit from the actual value, see below.
- **uint32_t getMaxOhm()** returns the maximum value ( =  parameter from constructor). Convenience function.
- **uint32_t Ohm2Position(uint32_t value, bool invert = false)**
Calculates (with rounding) the position nearest to the requested value. 
If **invert == true** it uses the other wiper end as reference.

One can measure the resistance between RH and RL and use this value to set 
in the constructor. Although the value will not differ much from the datasheet
one can get more precise values from the **getOhm()** function this way.


## Derived classes 

There are 4 derived classes, each with a other (appropriate) default value for the resistance. 

- **X9C102(uint32_t Ohm = 1000)** idem.
- **X9C103(uint32_t Ohm = 10000)** idem.
- **X9C104(uint32_t Ohm = 100000)** idem.
- **X9C503(uint32_t Ohm = 50000)** idem.

These classes have the same interface as the X9C10X base class.
The only difference is that the type is set to a non zero value.


## Performance

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

Note: no performance improvements since 0.1.2


## Operation

See examples.


#### Voltage divider 

The digital potentiometer (esp 10 KΩ and up) can be used as a voltage divider.
Connect RL to GND and RH to +5V and you can do 5V in 100 steps of ~0.05V
A voltage of **3V3** would be **setPosition(66)**. 

Note: check datasheet for the range of the max voltage and current allowed.


#### Concept read position 

If you need to make a robust system with X9C devices you can solder two devices "in parallel".
One to control whatever you need to control, and the other to create a feedback loop through analogRead().
Lets name them feedback device and control device.
The two devices should share the select, direction and pulse pins in hardware.
This way they will get the exact same pulses and signals and would therefore be in the exact same position
after initialization.

The feedback device would be a voltage divider, splitting 5 Volts in 100 level.
To read these levels you need at least an 8 bit ADC or better.
This setup would allow you to read the position in the control device 100% of the time. 

The price is at least twice as high in terms of hardware, the performance will be less at some times 
and the code will be slightly more complex

It might be possible to measure the voltage of the wiper of the control device.
However that might not always be easy or possible, due to voltage used, etc.


## Future

#### Must

- update documentation
  - concept of **read()** => put 2 X9C parallel and read one with analogRead().
  
#### Should

- test different platforms
- investigate and test **store()**

#### Could

- add error codes ?
- add examples
- test multiple devices configuration
- would ohm in float be more precise/accurate?
  - especially for the 1K?
  - how exact is this device, does it make sense, linear enough?

#### Wont

- voltage divider example
- in the constructor rename **Ohm** parameter to value? 
  - The potentiometer can be used as a voltage divider (see above)
    so a better parameter name could be the anonymous **value**.
  - **getOhm()** ==> **getValue()**
  - **getMaxOhm()** ==> **getMaxValue()**
  - think milliVolt, ohm, lux, speed, etc. 
    User can do this too with **getPosition() \* factor**


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


