
[![Arduino CI](https://github.com/RobTillaart/SIMON/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/SIMON/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/SIMON/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/SIMON/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/SIMON/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/SIMON/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/SIMON.svg?maxAge=3600)](https://github.com/RobTillaart/SIMON/releases)


# SIMON

Arduino library to build the "Simon says" game or a digital lock.


## Description

SIMON is a simple library to make a "Simon says" game.

This same class can also be used for e.g. a digital lock
or access control. 


## Interface

#### Base

- **SIMON()** constructor.

- **bool setSequence(uint8_t \* array, uint8_t length)** set the 
returns false if count > max size or array == NULL
- **uint8_t getSequence(uint8_t \* array)** returns length and 
fills the array with the set sequence.
- **bool generateSequence(uint8_t length, uint8_t minimum, uint8_t maximum)** generates a
random sequence of given length. 
Each value is between minimum and maximum inclusive, so ```generateSequence(5, 0, 10);``` may include both 0 and 10.
Seed for the random function will be **micros()** for now.

- **void add(uint8_t value)** add next element to answer.
if length becomes too large it is automatically cleared.
- **void clear()** clears the current answer.


- **bool verify()** check if answer matches the sequence.
- **bool verify(uint8_t \* array, uint8_t length)** check if array matches the sequence.


- **uint8_t length()** returns the length of the answer so far.
- **uint8_t size()** returns the size of the "hidden" sequence.


## Operation

A SIMON object holds a sequence of bytes of a given length which
is set by **setSequence(array, length)**.
The user can then **add()** elements to an internal storage and **verify()** if the the storage matches the original sequence. 


### Game Simon says

The game of **Simon says** has 4 lights, red, blue, yellow and green.
It generates a random sequence and the user must repeat that sequence
in the same order. If success the length of the sequence is increased
otherwise decreased.

Also the timing can be shortened to make the game more difficult.


### Lock - access control

The SIMON object can be used to hold a sequence that represents a code.
The user must fill in the same code and test if they are the same.
If **verify()** returns true, the lock may open, or the access is granted.

A safer lock won't tell the user the length of the code.

Note that the "secret code" is not encrypted (at least for now)
so it is not as safe as it can be. 
For real security other methods are needed.


## Future

### must

- improve documentation
- add use of EEPROM to store a sequence over reboots
  - **SIMON(uint16_t EEPROM_ADDR)** constructor with EEPROM address
- add examples
  - simon says game
  - digital lock


### could

- encrypted sequence (one way hash)
  - derived class.
  - disables **getSequence()** and **size()** and **maxSize()**
- add **bool mastermind(uint8_t \* array, uint8_t &black, uint8_t &white)** compare? (good-wrong_location + good-good_location)
  - class of its own.
  - MM solver and MM master
- constructor that changes **SIMON_MAXSIZE** or ?
  - define is OK for now, allows compile time changes.
  - dynamic allocation of array's?

