
[![Arduino CI](https://github.com/RobTillaart/FastTrig/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/FastTrig/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/FastTrig/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/FastTrig/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/FastTrig/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/FastTrig/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/FastTrig.svg?maxAge=3600)](https://github.com/RobTillaart/FastTrig/releases)


# FastTrig

Arduino library with interpolated lookup for sin() and cos(). Trades speed for accuracy.


## Description

**Warning: The library trades speed for accuracy so use at own risk**

The library provides one lookup table that is used for
**isin(degrees)** and **icos(degrees)** and **itan(degrees)**. 
This lookup table is optimized for interpolation so the values for whole degrees are not optimal. 
Furthermore the **itan()** on AVR has almost no performance gain over the regular **tan()** so on AVR one is advised to use **tan()**. 
On ESP32 the **itan(degrees)** does have a serious performance gain so use it if you need speed.

These functions are to be used as replacements for **sin(radians)**, **cos(radians)** and **tan(radians)**. 
Important to know is that they are NOT direct replaceable as the parameter differs a factor (PI/180.0) or its inverse.

Similar to ```cos(x) == sin(x + PI)``` it is also true that ```icos(x) == isin(x + 90)```, 
so **icos()** can use the very same lookup table at the cost of a single addition. 
In fact it uses ```icos(x) == isin(x - 270)``` as that performs better, due to the folding.

The **i** in the names stands for **int** and **interpolated** as the core is using integer math and lookup table of 91 uint16_t = 182 bytes. 
By folding and mirroring the whole 360 degrees and beyond can be handled. 
When **isin(x)** is called and ```x == int(x)``` then the library will not interpolate and this will improve performance. 
When x is not a whole number the library will linear interpolate between **isin(int(x))** and **isin(int(x+1))**. 
Of course this introduces an error but it is quite fast (which was the goal).


#### Lookup tables

The lookup tables are optimized (sketch provided) to minimize the error when using the interpolation, 
this implies that the points in the table might not be optimal when you use only whole degrees. 
A sketch that generates lookup tables is in the examples folder. 
This generator sketch can also generate tables with different resolution e.g. 24, 14, 12 or even 6, 5 or 4 bit lookup tables. 
So depending on the application these tables can be ideal, but verify they meet your requirements.

The lookup tables used by **isin()** can be used directly in your program, the names are:
- **sinTable16\[\]** index 0..90, values need to be (float) divided by 65535.0
- **sinTable8\[\]** index 0..90, values need to be (float) divided by 255.0

The **sinTable8** is not really for doing accurate math, 
however it is great to use in a LEDstrip or motor movements when less accuracy is needed.

Although the tables can be written to, it is advised not to do so.

*OK, the optimize example does a write to improve the table to minimize errors*


#### atan, atan2

Since version 0.2.1 two functions are added:
- **float atanFast(float f)** input range -1 .. 1 is faster.
Returns -PI/2 .. PI/2
- **float atan2Fast(float y, float x)** all input possible except (0, 0).
This (0,0) singularity returns NAN.
Returns -PI .. PI for all other values.

These functions do not use a lookup table but are faster than the default
atan() and atan2() functions. 
Use **fastTrig_atan_performance.ino** to check the gain on your board.
Price is that the values are less accurate, but the difference is < 0.001.


## Performance isin icos itan

time in us - calls 0 - 360 step 1 degree and calls 720 - 1080 (lib version 0.1.5)
(clock speeds in MHz)

| function | UNO 16 | ESP32 240 | UNO (720-1080) | ESP (720-1080) |
|:--------:|:------:|:---------:|:--------------:|:--------------:|
|    sin   | 120.43 |   10.90   |    124.19      |   10.91        |
|   isin   |  44.24 |    1.09   |     85.00      |    1.11        |
|    cos   | 120.27 |   10.81   |    123.98      |   10.83        |
|   icos   |  51.40 |    1.16   |     91.42      |    1.18        |
|    tan   | 147.59 |   18.07   |    151.39      |   18.07        |
|   itan   | 126.73 |    1.31   |    129.93      |    1.29        |

*Note: itan() 0.1.3 was ( 131.23, 3.05 ) so it improved quite a bit on ESP32. *

Performance gain is most evident for the ESP32 processor, and much less on AVR.
The effect of the modulo (360 degrees) can be seen explicitly in AVR. 
Furthermore the **itan()** on AVR is not faster when there is also interpolation (not in table) 

The 0.1.4 version of **itan()** is faster for ESP32 than 0.1.3 version but the 
improvement on AVR is minimal. So this will stay on the TODO list.

Furthermore a lot of gain is lost when the angle is not within 0..360
and needs to be normalized ( expensive modulo on AVR ). It is worth noting that the
original **sin()** **cos()** and **tan()** only have a small overhead for 
values outside the 0..360 range.

Please, verify the performance to see if it meets your requirements.


## Accuracy isin icos itan

errors - based upon example sketch - lib version 0.1.5

ESP32 calls 0.0 - 360.0 step 0.1 degree

| function | max abs error | avg abs error | max rel error | avg rel error |
|:--------:|--------------:|--------------:|--------------:|--------------:|
|   isin   |   0.00010264  |  0.00002059   |  0.02955145   |  0.00035180   |
|   icos   |   0.00010264  |  0.00002031   |  0.02955145   |  0.00034868   |
|   itan   |   0.69696045  |  0.00640957   |  0.00144703   |  0.00010100   |

UNO calls 0.0 - 360.0 step 0.1 degree

| function | max abs error | avg abs error | max rel error | avg rel error |
|:--------:|--------------:|--------------:|--------------:|--------------:|
|   isin   |   0.00010270  |  0.00002059   |  0.02955145   |  0.00035171   |
|   icos   |   0.00010264  |  0.00002032   |  0.02949960   |  0.00034869   |
|   itan   |   0.72760009  |  0.00641527   |  0.00144703   |  0.00037889   | 

*Note: 0.1.3 for AVR was bad:   17.41900634 , 0.02249339 , 0.02953807 for itan() *

Strange that the **itan()** on UNO and ESP32 differs (OK same order of magnitude).
Different implementation of goniometry / float maths?

Please, verify the performance to see if it meets your requirements.


## Performance iasin iacos iatan

(added 0.1.5)

time in us - calls -1 ..+1 step 0.001 degree

| function | UNO 16 -| ESP32 240 |
|:--------:|:-------:|:---------:|
|   asin   |  149.76 |  16.71    |
|  iasin   |  107.70 |   2.58    |
|   acos   |  169.50 |  15.44    |
|  iacos   |  114.65 |   2.67    |
|   atan   |  155.75 |  11.68    |
|  iatan   |   NI    |   NI      |

- the interpolated reverse lookup is around 30% faster on UNO an 80+% on ESP32
- **iatan()** is **Not** Implemented.

Please, verify the accuracy to see if it meets your requirements.


## Accuracy iasin iacos iatan

(added 0.1.5)

ESP32 calls -1 ..+1 step 0.001 degree

| function | max abs error | avg abs error | max rel error | avg rel error |
|:--------:|--------------:|--------------:|--------------:|--------------:|
|  iasin   |  0.22498322   |  0.00195790   |  0.00456106   |  0.00005727   |
|  iacos   |  0.22498587   |  0.00195794   |  0.64284271   |  0.00021902   |
|  iatan   |    NI         |  NI           |  NI           |  NI           |

- largest error at 0.999981 - second largest error 0.052841 at -0.999000
- **iatan()** is **Not** Implemented



UNO calls -1 ..+1 step 0.001 degree

| function | max abs error | avg abs error | max rel error | avg rel error |
|:--------:|--------------:|--------------:|--------------:|--------------:|
|  iasin   |  0.22499084   |  0.00195719   |  0.00456125   |  0.00005725   |
|  iacos   |  0.22498588   |  0.00195740   |  0.64284276   |  0.00021901   |
|  iatan   |    NI         |  NI           |  NI           |  NI           |

- largest error at 0.999981 - second largest error 0.052841 at -0.999000
- max relative error is high as it occurred near zero.
- **iatan()** is **Not** Implemented


Please, verify the accuracy to see if it meets your requirements.


## Performance atanFast, atan2Fast

Times in microseconds (first  measurement)

|  function  |  atan  |  atanF  |  atan2  |  atan2F  |  factor  |  notes  |
|:----------:|:------:|:-------:|:-------:|:--------:|:--------:|:--------|
|  UNO       |  188   |    96   |   196   |   124    |   ~1.6   | range -1 .. 1
|  UNO       |  220   |   124   |   212   |   128    |   ~1.6   |  
|  ESP32     |   50   |    15   |    44   |    13    |   ~3.3   |

The range 

Additional measurements are welcome.
(use performance sketch)


## Accuracy atanFast, atan2Fast

The atan2Fast() uses atanFast() so the accuracy for both is the same.
The test sketch indicates a maximum error is smaller than 0.001.

To be elaborated


## versions

See changelog.md


## Operation

See examples


## Future

- How to improve the accuracy of the whole degrees, as now the table is optimized for interpolation.
- sinc(x)  = sin(x)/x function.?
