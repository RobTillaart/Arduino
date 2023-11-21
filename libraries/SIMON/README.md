
[![Arduino CI](https://github.com/RobTillaart/SIMON/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/SIMON/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/SIMON/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/SIMON/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/SIMON/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/SIMON.svg)](https://github.com/RobTillaart/SIMON/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/SIMON/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/SIMON.svg?maxAge=3600)](https://github.com/RobTillaart/SIMON/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/SIMON.svg)](https://registry.platformio.org/libraries/robtillaart/SIMON)


# SIMON

Arduino library to build the "Simon says" game or a digital lock.


## Description

SIMON is a simple library to make a "Simon says" game.

This same class can also be used for e.g. a digital lock
or access control. 


## Interface

```cpp
#include "simon.h"
```

#### Construction

- **SIMON()** constructor.

- **bool setSequence(uint8_t \* array, uint8_t length)** set the (secret) sequence.
Returns false if length > **SIMON_MAXSIZE** or array == **NULL**.
- **uint8_t getSequence(uint8_t \* array)** fills the array with the set sequence.
Returns the length of the array.
- **bool generateSequence(uint8_t length, uint8_t minimum, uint8_t maximum)** generates a
random sequence of given length. 
Each value is between minimum and maximum inclusive, so ```generateSequence(5, 0, 10);``` may include both 0 and 10.
Seed for the random function will be **micros()** for now.


#### Core

- **void add(uint8_t value)** add next element to the answer.
if the length of the answer becomes too large it is automatically cleared.
- **void clear()** explicit clears the current answer.
- **bool verify()** check if the answer matches the (secret) sequence.
- **bool verify(uint8_t \* array, uint8_t length)** check if array matches the sequence.


#### Meta info

- **uint8_t length()** returns the length of the answer so far.
- **uint8_t size()** returns the size of the "hidden" sequence.
- **uint8_t maxSize()** returns**SIMON_MAXSIZE**.


## Operation

A SIMON object holds a sequence of bytes of a given length which
is set by **setSequence(array, length)**.
The user can then **add()** elements to an internal storage 
and **verify()** if the the storage matches the original sequence. 


## Ideas

#### Game Simon says

(not implemented yet)

The game of **Simon says** has 4 lights, red, blue, yellow and green.
It generates a random sequence and the user must repeat that sequence
in the same order. If success the length of the sequence is increased
otherwise decreased.

Also the timing can be shortened to make the game more difficult.

This can be implemented by generating a random sequence of increasing length
every time the user inputs the right sequence. 
If the user fails to input the right sequence, the random sequence is shortened 
by one, or worst case "game over" and start over from 1.


#### Lock - access control

(not implemented yet)

The SIMON object can be used to hold a sequence that represents a code.
The user must fill in the same code and test if they are the same.
If **verify()** returns true, the lock may open, or the access is granted.

A safer lock won't tell the user the length of the code.

Note that the "secret code" is not encrypted (at least for now)
so it is not as safe as it can be. 
For real security, other methods are needed.


## Future

#### Must

- improve documentation

#### Should

- add examples
  - simon says game
  - digital lock

### Could

- encrypted sequence (one way hash)
  - derived class.
  - disables **getSequence()** and **size()** and **maxSize()**
  - time constant version of **verify()**
- add **bool mastermind(uint8_t \* array, uint8_t &black, uint8_t &white)** compare? 
  - (good-wrong_location + good-good_location)
  - needs another type of verification.
  - class of its own.
  - MM solver and MM master

#### Wont

- add use of EEPROM to store a sequence over reboots
  - **SIMON(uint16_t EEPROM_ADDR)** constructor with EEPROM address
- constructor that changes **SIMON_MAXSIZE** or ?
  - define is OK for now, allows compile time changes.
  - dynamic allocation of array's? Nope
  
  
## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,
