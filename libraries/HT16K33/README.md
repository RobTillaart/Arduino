
[![Arduino CI](https://github.com/RobTillaart/HT16K33/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/HT16K33/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/HT16K33/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/HT16K33/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/HT16K33/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/HT16K33.svg)](https://github.com/RobTillaart/HT16K33/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/HT16K33/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/HT16K33.svg?maxAge=3600)](https://github.com/RobTillaart/HT16K33/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/HT16K33.svg)](https://registry.platformio.org/libraries/robtillaart/HT16K33)


# HT16K33

Arduino Library for HT16K33 I2C 4x7segment display.


## Description

This library is for the Adafruit 4x7segment display with HT16K33 driver,
http://www.adafruit.com/products/1002

This library is functionally less capable than Adafruits. 
However as it caches the values written to the display per position 
it is faster for writing on average. The actual gain depends on the
application and of course the values. 


#### 0.4.0 Breaking change

Version 0.4.0 introduced a breaking change.
You cannot set the pins in **begin()** any more.
This reduces the dependency of processor dependent Wire implementations.
The user has to call **Wire.begin()** and can optionally set the Wire pins 
before calling **begin()**.


## Performance 

Version 0.3.0 allows one to switch the caching on/off to enforce
writing all positions e.g. in case of noisy I2C bus. 

The example **demo_cache.ino** measures the performance gain of caching 
for different I2C bus speeds. 

```
Test on UNO, I2C.setClock(100000);  // version 0.1.2
0-9999 integers       3.960 sec
0-65535 hexadecimal  23.685 sec

Test on UNO, I2C.setClock(800000);  // version 0.1.2
0-9999 integers       1.223 sec
0-65535 hexadecimal   6.350 sec

Test on UNO, I2C.setClock(100000);  // version 0.3.0
0-9999 integers       4.092 sec     // ~3% slower due to robustness & cache control 
0-65535 hexadecimal  24.336 sec
```


## Multiple display 

The library supports only one display. Using multiple displays (cascading) e.g. to
display more than 4 digits must done by the user - see **demo_dual1.ino**. 
With dual display it is important to **setDigits()** for the displays correctly to
get leading/trailing zero's correctly.


## Interface

```cpp
#include "HT16K33.h"
```

#### Setup behaviour

- **HT16K33(const uint8_t address)** address is 0x70..0x77 depending on the jumpers A0..A2. **0x70** is default.
- **bool begin()** initialize library and calls **reset()**.
Returns false if address not seen on I2C bus.
- **bool isConnected()** Returns false if address not seen on I2C bus.
- **void reset()** resets display.

#### Cache

- **void clearCache()** forced clearing of the cache, to be used to switch the cache off just for one write.
- **void cacheOn()** enable caching, this is default behaviour.
- **void cacheOff()** disable caching, will force writing to every position.

#### Display

- **void displayOn()** enable display.
- **void displayOff()** disable display, fast way to darken display e.g. for energy consumption.
- **void setBrightness(uint8_t value)** values (dim) 0..15 (bright).
- **void getBrightness()** returns (dim) 0..15 (bright).
- **void setBlink(uint8_t value)** values 0..3   0 = off.
- **void getBlink(uint8_t value)** values 0..3   0 = off.
- **void setDigits(uint8_t value)** values 0..4, minimal number of digits shown, mandatory for large numbers on dual display.

#### Data types

The bool return value indicates that the value displayed is in range.

- **void displayClear()** fill display with spaces => results in an empty display.
- **bool displayInt(int n)** values -999 .. 9999
- **bool displayHex(uint16_t n)** values 0000 .. FFFF
- **bool displayDate(uint8_t left, uint8_t right, bool lz = true)** values 00.00..99.99 Date could be {month.day} or {day.hour}  
It uses **.** as separator. Optional the leading zero (lz) 
can be replaced by a space to look more natural e.g 1:54  instead of  01:54
- **bool displayTime(uint8_t left, uint8_t right, bool colon = true, bool lz = true)** values 00:00..99:99 
Time could be hh:mm or mm:ss or ss:uu (hundreds), it uses **:** as separator. 
Optional the colon is set to false (e.g. to simulate blink) and optional the leading zero (lz) 
can be replaced by a space to look more natural e.g 1:54  instead of  01:54
- **void displaySeconds(uint16_t seconds, bool colon, bool lz = true)** displays 00:00..99:99 units in seconds (or minutes) - splits % 60 : as separator
Optional the colon is set to false (to simulate blink). 
Optional the leading zero (lz) can be replaced by a space to look more natural e.g 1:54  instead of 01:54
- **bool displayFloat(float f, uint8_t decimals = 3)** values -999..0.000..9999
The number of decimals = 0,1,2,3 = default. When less decimals are displayed, the number will be right aligned.
- **bool displayUnit(float f, uint8_t decimals = 2, uint8_t unitChar = HT16K33_SPACE)** values -99..0.000..999
The number of decimals = 0,1,2 = default. When less decimals are displayed, the number will be right aligned.
The unitChar is a postFix character like C or F for temperature H for humidity. 
The unitChar must be one of the chars supported like HT16K33_C, HT16K33_TOP_C or HT16K33_DEGREE (see below).
So **displayUnit(25.6, 1, HT16K33_DEGREE)** will display **23.5°**.

#### Fixed point

- **bool displayFixedPoint0(float f)** displays values -999  .. 9999 without decimals.
- **bool displayFixedPoint1(float f)** displays values -99.9 .. 999.9 with 1 decimals.
- **bool displayFixedPoint2(float f)** displays values -9.99 .. 99.99 with 2 decimals.
- **bool displayFixedPoint3(float f)** displays values 0.000 .. 9.999 with 3 decimals.

#### Special VU meters

- **bool displayVULeft(uint8_t value)** display used as sort VU meter, values 0..8  Vales > 8 are treated as 8 (but return false).
- **bool displayVURight(uint8_t value)** display used as sort VU meter, values 0..8 Vales > 8 are treated as 8 (but return false).

#### Lower level workers

- **void display(uint8_t \* array)** array of 4 bytes to control one 7seg display.
- **void display(uint8_t \* array, uint8_t point)** idem + point = position of the digit with point (0..3).
- **void displayColon(uint8_t on)** 0 = off, all values other are on.
- **void displayRaw(uint8_t \* array, bool colon)** array of 4 bytes to control one 7seg display + colon flag.
- **void displayExtraLeds(uint8_t value)** switch on extra LEDs.
value is in fact a bit mask see table below. 0 = all off.

When using the consts SEG_A etc from .h file, for the **displayRaw()**
one can use the individual segments SEG_A..SEG_G and SEG_DP.

![layout](https://upload.wikimedia.org/wikipedia/commons/0/02/7_segment_display_labeled.svg "").

_Image courtesey wikimedia_


#### Extra LEDs table

|  mask  |  description  |
|:------:|:--------------|
|  0x00  |  all off 
|  0x02  |  colon.
|  0x04  |  upper left point, left of the 1st digit.
|  0x08  |  lower left point, left of the 1st digit.
|  0x10  |  upper point between 3rd and 4th digit.

( based upon issue #21 )


#### Debugging

- **void displayTest(uint8_t del)** debugging / test function.
- **void dumpSerial(uint8_t \* array, uint8_t point)** debugging equivalent of the display.
Prints to Serial.
- **void dumpSerial()** print HEX codes equivalent of the display to Serial.
- **uint8_t getAddress()** idem.


#### Obsolete soon

- brightness() use setBrightness()
- blink() use setBlink()


## Characters supported

from .h file, elaborate

```cpp
#define HT16K33_0                0
#define HT16K33_1                1
#define HT16K33_2                2
#define HT16K33_3                3
#define HT16K33_4                4
#define HT16K33_5                5
#define HT16K33_6                6
#define HT16K33_7                7
#define HT16K33_8                8
#define HT16K33_9                9
#define HT16K33_A                10
#define HT16K33_B                11
#define HT16K33_C                12
#define HT16K33_D                13
#define HT16K33_E                14
#define HT16K33_F                15
#define HT16K33_SPACE            16
#define HT16K33_MINUS            17
#define HT16K33_TOP_C            18     //  c
#define HT16K33_DEGREE           19     //  °
#define HT16K33_NONE             99
```

If other chars are needed please file an issue.


## Operation

See examples


## Future


#### Must

Mainly for a 0.4.x

- **bool isDisplayOn()** and similar state functions
  - configuration byte: 4 bits brightness, 1 bit on off flag, 1 bit cache flag, 2 blink rate

#### Should 


#### Could

- VU metering using halve bars allows two VU from 0..8   **new**
- VU metering using halve bars allows one VU from 0..17. extension of current VUleft/right
- optimize math if possible - performance and footprint. + float + int division
- low level I2C error detection
- write single position - **writePos(uint8_t pos, uint8_t mask)**
  - [status] dd.d
- add examples
  - car battery monitor (voltage divider & analogRead)
- add more "special chars"?
  - #define HT16K33_P  Pascal / Pressure   0x73
  - #define HT16K33_J  joule               0x0E
  - #define HT16K33_H  humidity            0x76


#### Wont (unless sponsored)

- **rotate(bool rot = false)**
  - 180 degree rotation of all digits for mounting  
  - reverse digit order
  - flip every digit (function to overwrite the char array)
- **HUD(bool hud = false)** = Heads Up Display
  - flip every digit
- **lastTime()** in millis  too much overhead.
- add special chars to keywords?  nope
- **readCache(int n)** access internal cache => dumpSerial()


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

