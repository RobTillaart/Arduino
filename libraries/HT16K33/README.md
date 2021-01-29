
[![Arduino CI](https://github.com/RobTillaart/HT16K33/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/HT16K33/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/HT16K33.svg?maxAge=3600)](https://github.com/RobTillaart/HT16K33/releases)


# HT16K33

Arduino Library for HT16K33 I2C 4x7segment display


## Description

This library is for the Adafruit 4x7segment display with HT16K33 driver,
http://www.adafruit.com/products/1002

This library is functionally less capable than Adafruits. 
However as it caches the values written to the display per position 
it is faster for writing on average. The actual gain depends on the
application and of course the values. 


## Perfomance 

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


### Setup behaviour

- **HT16K33(address)** address is 0x70..0x77 depending on the jumpers A0..A2. **0x70** is default
- **bool begin(sda, scl)** for ESP32, select I2C pins, initialize I2C and calls **reset()**. 
Returns false if device not seen on I2C bus.
- **bool begin()** initialize I2C and calls **reset()**.
Returns false if device not seen on I2C bus.
- **bool isConnected()** Returns false if device not seen on I2C bus.
- **void reset()** resets display
- **void clearCache()** forced clearing of the cache, to be used to switch the cache off just for one write.
- **void cacheOn()** enable caching, this is default behavior
- **void cacheOff()** disable caching, will force writing to every position
- **void displayOn()** enable display
- **void displayOff()** disable display, fast way to darken display e.g. for energy consumption
- **void brightness(val)** values (dim) 0..15 (bright)
- **void blink(val)** values 0..3   0 = off
- **void setDigits(val)** values 0..4, minimal number of digits shown, mandatory for large numbers on dual display.
- **void suppressLeadingZeroPlaces(val)** obsolete, replaced by setDigits


### Datatypes

The bool return value indicates that the value displayed is in range.

- **void displayClear()** empty display
- **bool displayInt(n)** values -999 .. 9999
- **bool displayHex(n)** values 0000 .. FFFF
- **bool displayDate(left, right)** values 00.00..99.99 Date could be {month.day} or {day.hour}           . as separator
- **bool displayTime(left, right, colon = true)** values 00:00..99:99 Time could be hh:mm or mm:ss or ss:uu (hundreds)  : as separator. 
Optional the colon is set to false (to simulate blink)
- **void seconds(seconds, colon)** displays 00:00..99:99 units in seconds (or minutes) - splits % 60 : as separator
Optional the colon is set to false (to simulate blink).
- **bool displayFloat(f, decimals = 3)** values -999..0.000..9999
The number of decimals = 0,1,2,3 = default. When less decimals are displayed, the number will be right aligned.


### Experimental

These functions are new and still under investigation.

- **bool displayFixedPoint0(float f)** displays values -999  .. 9999 without decimals.
- **bool displayFixedPoint1(float f)** displays values -99.9 .. 999.9 with 1 decimals.
- **bool displayFixedPoint2(float f)** displays values -9.99 .. 99.99 with 2 decimals.
- **bool displayFixedPoint3(float f)** displays values 0.000 .. 9.999 with 3 decimals.


### Special

- **bool displayVULeft(val)** display used as sort VU meter, values 0..8  Vales > 8 are treated as 8 (but return false)
- **bool displayVURight(val)** display used as sort VU meter, values 0..8 Vales > 8 are treated as 8 (but return false)


### Lower level workers

- **void display(uint8_t \*arr)** array of 4 bytes to control one 7seg display
- **void display(uint8_t \*arr, uint8_t pt)** idem + pt = position of the digit with point (0..3)
- **void displayColon(on)** 0 = off, all values other are on.
- **void displayRaw(uint8_t \*arr, colon)** array of 4 bytes to control one 7seg display + colon flag


### Debugging

- **void displayTest(uint8_t del)** debugging / test function
- **void dumpSerial(uint8_t \*arr, uint8_t pt)** debugging equivalent of display.


### Future

**0.4.0**
- **bool isDisplayOn()** and similar state functions
  - config byte: 4 bits brightness, 1 bit on off flag, 1 bit cacheflag, 2 blinkrate
- **void setBrightness()** and **uint8_t getBrightness()**
- **void setBlink()** and **uint8_t getBlink()**
- **void getDigits()**
- **FixedPoint()** regular (experimental in 0.3.2)
- overflow flag ? or not decission

**unknown**
- VU metering using halve bars allows two VU from 0..8   **new**
- VU metering using halve bars allows one VU from 0..17. extension of current VUleft/right
- optimize the math if possible - performance and footprint. +float + int division
- low level I2C error detection

## Operation

See examples

