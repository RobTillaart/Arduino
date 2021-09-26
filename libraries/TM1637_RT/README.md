[![Arduino CI](https://github.com/robtillaart/TM1637_RT/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/TM1637_RT/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/TM1637_RT/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/TM1637_RT/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/TM1637_RT/actions/workflows/jsoncheck.yml)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/TM1637_RT.svg?maxAge=3600)](https://github.com/RobTillaart/TM1637_RT/releases)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/TM1637_RT/blob/master/LICENSE)


# TM1637

Library for TM1637 driven displays.


## Description

The TM1637 drives 7 segment displays

Library is tested with Arduino UNO and a 6 digits display.

ESP32 is supported since 0.2.0 see https://github.com/RobTillaart/TM1637_RT/pull/5


TO ELABORATE


## Interface

- **TM1637()** constructor
- **void init(uint8_t clockPin, uint8_t dataPin, uint8_t digits = 6)** set up the connection of the pins to the display.
As the display is only tested with a 6 digit display, this is used as the default of the digits parameter.
- **void displayRaw(uint8_t \* data, uint8_t pointPos)** low level write function.
- **void displayInt(long value)** idem
- **void displayFloat(float value)** idem
- **void displayHex(uint32_t value)** idem
- **void displayClear()** writes spaces to all positions, effectively clearing the display.
- **void setBrightness(uint8_t b)** brightness = 0 .. 7 default = 3.
- **uint8_t getBrightness()** returns value set.


### Tuning function

To tune the timing of writing bytes.

- **void    setBitDelay(uint8_t bitDelay = 10)**
- **uint8_t getBitDelay()**


### Tuning minimum pule length

The class has a conditional code part in writeSync to guarantee the length of pulses
when the library is used with an ESP32. The function called there **nanoDelay(n)**
needs manual adjustment depending upon processor frequency and time needed for a digitalWrite.
Feel free to file an issue to get your processor supported.


## Operation

See examples


## Future

- elaborate documentation
- testing
- rename **init()** to **begin()** ?
- 
