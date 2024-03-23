
[![Arduino CI](https://github.com/RobTillaart/I2C_LCD/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/I2C_LCD/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/I2C_LCD/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/I2C_LCD/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/I2C_LCD/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/I2C_LCD.svg)](https://github.com/RobTillaart/I2C_LCD/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/I2C_LCD/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/I2C_LCD.svg?maxAge=3600)](https://github.com/RobTillaart/I2C_LCD/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/I2C_LCD.svg)](https://registry.platformio.org/libraries/robtillaart/I2C_LCD)


# I2C_LCD

Arduino library for I2C_LCD LCD displays.


## Description

**Experimental** Arduino library for the I2C LCD display, typical **20x4** characters.

The library is inspired by the excellent [New-LiquidCrystal](https://github.com/fmalpartida/New-LiquidCrystal) library by F. Malpartida. 
Therefore the interface is kept quite identical, extended with some additional functions.
The goal of the library is to minimize footprint and improve performance.
This is partly done by dedicate the library to I2C only.

The library implements the print interface, so all data types are printable
assuming they fit on the display.

Additional functions not in the reference:

| name                  | description  |
|:----------------------|:-------------|
| isConnected()         | test if display address is seen on I2C bus.
| clearEOL()            | clears line from current position
| \t                    | printing of a tab char moves to next multiple of 4.
| special(index)        | prints the customized char at index (0..7)
| center(row, str)      | centers a char array on chosen row.
| right(col, row, str)  | right align a char array from chosen position.


#### Compatibility

Reasonable compatible with F. Malpartida's I2C library, relative minor differences
mostly in the constructors.
Furthermore the current version does not support all functionality, and
more important it is not tested as much as the reference.
Only the 5x8 font is supported.

So if you need full functionality, robustness or reliability, you should use 
the reference **New-liquidCrystal** library.


#### Tests

Tested on an UNO and a **20x4** character LCD, and limited on a **16x2** LCD.

The versions 0.1.0 and 0.1.1 were not stable and gave a garbled display. 
It looked like the data came too fast for the display to handle.
The problems seems to be solved since version 0.1.2 as the problems did not
occur any more.


## Performance

The most important optimization is to send every byte in a single I2C transaction.
This takes 5 bytes to transport, which is 3 less than the reference.

Furthermore there is an optimization if the pins are in ascending order, as then
it is far easier to get the nibble (half bytes) to send. 

First performance tests are good. See example **I2C_LCD_performance.ino**.


#### dataPins in ascending order UNO

Measurement is the time in microseconds to write 8 characters.
Use the sketch I2C_LCD_performance.ino to make measurements.

Measurements done with **UNO** (5V, 16 MHz), data pins are in ascending order.

|  I2C clock  |  0.1.0  |  0.1.1  |  0.1.4  |  0.2.0  |  0.2.1  |  notes  |
|:-----------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|
|  100000     |   4316  |   4640  |   4312  |   4316  |   4316  |
|  200000     |   2440  |   2760  |   2456  |   2448  |   2448  |
|  300000     |   1780  |   2108  |   1792  |   1792  |   1792  |
|  400000     |   1496  |   1820  |   1512  |   1508  |   1508  |  (1)
|  500000     |   1308  |   1632  |   1324  |   1332  |   1332  |
|  600000     |   1176  |   1500  |   1188  |   1188  |   1188  |
|  700000     |   1076  |   1400  |   1084  |   1084  |   1084  |
|  800000     |   1024  |   1348  |   1040  |   1044  |   1044  |


_Note 1: 0.1.0 had problems with spectrum examples - too much data too fast, corrupted my display.
Timing in the 0.1.1 version is roughly 400 us slower than 0.1.0 for 8 characters. However the 0.1.1 is more robust as far as tested.
Advice is to use version 0.2.0 or higher._


Measurements with **ESP8266** (3V3, single core 80 MHz), data pins are in ascending order.

|  I2C clock  |  0.2.0  |  notes  |
|:-----------:|:-------:|:-------:|
|  100000     |   5355  |
|  200000     |   2637  |
|  300000     |   1730  |
|  400000     |   1294  | 
|  500000     |   1025  |
|  600000     |   823   |
|  700000     |   688   |  clear() blocked
|  800000     |   570   |


Given the above measurements, the I2C speed should be 400 KHz or max 600 KHz.
Of course also depending on wire length etc.

#### Tuning

In the file **I2C_LCD.cpp** there is this line you can tune the hard delay
in microseconds after every character.

```cpp
//  40 us is a save value at any speed.
//  20 us is a save value for I2C at 400K.
const uint8_t I2C_LCD_CHAR_DELAY = 20;
```

The datasheet states one need the 37 us so 40 us is a very safe value.
However the I2C at 400 KHz takes at least 40 us to send an address and 
the first 4 bits.
So 20 us is a safe value, and 10 us or even 0 us should work well.
The math above does not include other overhead like preparing the bits etc.
At 100 KHz the I2C for 2 bytes takes 160 us, so it can safely set to 0.

Setting the delay to zero (0.1.4), gives roughly the 0.1.0 timing again.


#### DataPins not in ascending order

The performance measurement is done on an UNO. (order is simulated)

|  I2C clock  |  0.2.0  |  0.2.1  |  notes  |
|:-----------:|:-------:|:-------:|:-------:|
|  100000     |   4352  |   4352  |
|  200000     |   2480  |   2480  |
|  300000     |   1824  |   1824  |
|  400000     |   1544  |   1544  |
|  500000     |   1352  |   1360  |
|  600000     |   1216  |   1224  |
|  700000     |   1128  |   1124  |
|  800000     |   1072  |   1072  |

Per character 4 micros slower, on average +1.7%, than when data pins are {4,5,6,7}, as the alternative code is optimized too.

Note: Performance is also a matter of developing an optimal algorithm.
This is often a trade between code size, memory used and speed.
See **I2C_LCD_demo_spectrum_row.ino** for an example.


#### Related

- https://github.com/fmalpartida/New-LiquidCrystal The reference.
- https://github.com/RobTillaart/ANSI for VT100 alike terminals.
- https://maxpromer.github.io/LCD-Character-Creator/


## Interface

```cpp
#include "I2C_LCD.h"
```

The parameters of most functions below are not checked to keep performance and 
footprint optimal. The user should check if he wants robustness.


#### Constructor

- **I2C_LCD(uint8_t address, TwoWire \* wire = &Wire)** Constructor, 
mandatory address and optional alternative I2C bus.
- **void config(uint8_t address, uint8_t enable, uint8_t readWrite, uint8_t registerSelect, 
                   uint8_t data4, uint8_t data5, uint8_t data6, uint8_t data7, 
                   uint8_t backlight, uint8_t polarity)** pin configuration.
Will probably change in the future, less compatible.
- **bool begin(uint8_t cols = 20, uint8_t rows = 4)** initializes library size.
User must call the appropriate **Wire.begin()** before calling **lcd.begin(()**
It is advised to initialize the LCD as last device as it blocks until 100 milliseconds
since startup have passed to give the LCD time to boot.
- **bool isConnected()** returns true if address can be seen on the I2C bus chosen.


#### Backlight

- **void setBacklightPin(uint8_t pin, uint8_t polarity)** pin should be 0..7, polarity 0..1.
There are no checks, user is responsible.
- **void setBacklight(bool on)** if backlight is off, the display is also set off.
- **void backlight()** wrapper for setBacklight(true).
- **void noBacklight()** wrapper for setBacklight(false).


#### Display

- **void display()** set display on. Printing to the LCD is visible.
- **void noDisplay()** set display off. Printing to the LCD is not visible.
- **void on()** set display on.  Compatibility wrapper.
- **void off()** set display off. Compatibility wrapper.


#### Positioning and cursor

- **void clear()** clear whole screen and set cursor to 0, 0 (upper left).
- **void clearEOL()** clears line from current pos. **NEW**
- **void home()** set cursor to 0, 0 (upper left).
- **bool setCursor(uint8_t col, uint8_t row)** set cursor to given position.
There is a check if this is out of range, if so the function will return false.
- **void noBlink()** idem.
- **void blink()** idem.
- **void noCursor()** idem.
- **void cursor()** idem.


#### Miscellaneous

Minimal tested.

- **void scrollDisplayLeft(void)** idem.
- **void scrollDisplayRight(void)** idem.
- **void moveCursorRight(uint8_t n = 1)** moves cursor n places to right or
until end of line reached.
- **void moveCursorLeft(uint8_t n = 1)** moves cursor n places to left or
until start of line reached.

The next 4 have only limited support  
(either autoscroll or leftToRight can be set, not both)

- **void autoscroll(void)**
- **void noAutoscroll(void)**
- **void leftToRight(void)**
- **void rightToLeft(void)**


#### Create your own characters

A charmap consists of an array of 8 bytes with values 0..31 (5 bits).
There are 8 slots to place a special character, index 0..7.
The custom characters can be printed with **special(index)** which is 
a wrapper around **write((uint8_t)index)**

- **void createChar(uint8_t index, uint8_t \* charmap)** index = 0..7.
- **size_t special(uint8_t index)** to print the special char.

See examples e.g. spectrum, for how to use custom characters.

See also **I2C_LCD_custom_chars.h**

Finally, there is a very handy online tool to create characters.
- https://maxpromer.github.io/LCD-Character-Creator/


#### Print interface

- **size_t write(uint8_t c)**

Two helper functions, please note these work only with a char array, not with numbers.
To right align numbers, see examples.

- **size_t center(uint8_t row, char \* message)** centers a string on the defined row.
- **size_t right(uint8_t col, uint8_t row, char \* message)** right align a string.
col is the align position.


## I2C_LCD_special_chars.h

This include file has some defines for often used (at least by me) characters. 
These characters are mostly Greek characters, like alpha, beta and rho. 

Note however that these will work on displays with the ROM CODE A00 and not 
with ROM CODE A02 (datasheet).


## Experimental


#### Tab printing

When **'\t'** (character 9) is printed to the LCD, it moves to the first position
that is a multiple of 4.
This allows a simple way to get some sort of tabular data representation.
See the example.

Idea for the future might be to set the tab-stops instead of current hardcoded ones.


## Debug

#### Position tracking

The library tries to keep track of the current position on the line it is.
When going beyond the number of columns, it will not print any more.
This protects against printing beyond screen position (and writing
one some other line).
Additional it saves some time.

This position tracking only works for "standard" use, no display 
scrolling, right to left mode etc. 
So it can cause unwanted side effects, which can be fixed by removing
the "pos < cols" condition from **write()**.

- **uint8_t getColumn()**

The library does not track the row (yet)


#### getWriteCount()

As I encountered problems during tests (display garbled) I added a counter 
of the number of writes (each char => 5 bytes I2C).
For now a development only, so expect it to be removed in future.

- **uint32_t getWriteCount()** idem.

Not reset-able.


## Future

#### Must

- update documentation

#### Should

- test, test, test.
- test other platforms.
- test other display sizes.

#### Could

- function to define the tab-stops, instead of hard coded ones.
- make a separate include file for charmaps by name.
  - I2C_LCD_spectrum.h ?
- derived class for I2C_LCD4567 (optimized pins)

#### Wont (for now).

- investigate reading busy flag over I2C.
  - not successful so far.
- **size_t write(array, length)** is not implemented as there was no gain.
- implement unit tests (possible?)
- add timestamp last print
- investigate other special characters to support, like
  - \r => go to begin of current line.
  - \n => go to begin of next line.
  - FF => form feed is clear screen.
  - BELL => blink of the display  (oeps 7 is already a special char )


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

