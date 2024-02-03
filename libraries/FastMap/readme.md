
[![Arduino CI](https://github.com/RobTillaart/FastMap/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/FastMap/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/FastMap/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/FastMap/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/FastMap/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/FastMap.svg)](https://github.com/RobTillaart/FastMap/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/FastMap/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/FastMap.svg?maxAge=3600)](https://github.com/RobTillaart/FastMap/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/FastMap.svg)](https://registry.platformio.org/libraries/robtillaart/FastMap)


# FastMap

Fast mapping and constraining.


## Description

FastMap replaces the Arduino **map()** function which does integer mapping.
The result of integer mapping is that the (internal) division truncates and looses precision.

Another problem possible problem of the **map()** function is that it can extrapolate
outside the output range specified if the input is outside the input range.
This behaviour is not always wanted, and can cause unexpected side effects.

**FastMap** is an object that pre-calculates (internal) floats to make a mapping function 
especially for floats (and doubles).
The usage of floats reduces the truncating problem of **map()** and keeps precision.
As it pre-calculates the mapping partially the performance is good.
See **FastMap_performance_test.ino**.

To prevent extrapolating **FastMap** provides so called **constrainedMap()** which takes
care that the returned value is within the specified output range.
The library provides three variations, see API below.

Finally the **FastMap** provides a **back()** function to reverse the mapping. 
This only works well with floats, and less with integers, so use with care and
verify if it meet your requirements. 

An important difference with the traditional **map()** function is that both 
**init()** and **map()** accepts floats as parameters.
See the precision notes below

Since 0.4.0 the **init()** function will not accept a zero range defining input or output parameters.
This is to prevent NaN errors and **init()** will return false if such range is detected.

If the **init()** function is not called a 1 to 1 mapping is used.

#### Related

Other mapping libraries

- https://github.com/RobTillaart/FastMap
- https://github.com/RobTillaart/Gamma
- https://github.com/RobTillaart/map2colour
- https://github.com/RobTillaart/moduloMap
- https://github.com/RobTillaart/MultiMap


## Performance notes

(based upon tests https://github.com/RobTillaart/FastMap/issues/4 )
- On AVR (UNO and MEGA) no gain is made mapping integers with FastMap, 130% slower = substantial.
- On AVR the gain for float is limited, 10% faster.
- On ESP32 the gain for integers and float is both in the order of 25%.

To see the actual gain in your project on your hardware you should test and compare.

**FastMap** is faster when mapping floats as it uses less float operations than the standard map formula does.
The performance results from pre-calculating values in the **init()** function.
An actual mapping therefore needs only one multiply and one add operation where the 
standard **map()** function uses four adds, a multiplication and a division.
The pre-calculation in **init()** should be taken in account and if every **map()** 
call needs an **init()** there will be no gain, on contrary.


## Precision notes

The implementation of **FastMap()** uses floats (typical 32 bits) which might result in more memory usage 
and loss of precision for mapping of larger values, especially 32 and 64 bit integers.

This is caused by the limits of the mantissa (~23 bits) of the standard 4 byte float.
To solve this a **FastMapDouble** class is added which uses the **double** type for the platforms
that support 8 byte floats. 
If your platform does not support double it will often be mapped to float, so no gain.
Furthermore using double might imply a performance penalty on some platforms.


## Interface

```cpp
#include "FastMap.h"
```

#### Base

- **FastMap()** Constructor
- **bool init(float in_min, float in_max, float out_min, float out_max)** defines the linear mapping parameters. 
Be sure that in_min must be smaller than in_max. 
The **init()** function calculates all needed values for the **map()**, the **back()** call and the **constrainXX()** functions.
The **init()** function can be called again with new values when needed to do other mapping,
although it will give less overhead if you create an FastMap object per conversion needed.  
Returns false if (out_max == out_min) or (in_max == in_min). (breaking change in 0.4.0).
If **init()** is not called the default is 1 to 1 mapping.
- **float map(float value)** maps the parameter.
- **float back(float value)** does the inverse mapping.


#### Constrains

FastMap supports three versions of constraining the map function, based upon the parameters of **init()**.

- **float constrainedMap(float value);** returns a value between outMin .. outMax
- **float lowerConstrainedMap(float value);** returns a value between outMin .. infinity, ==> no upper limit.
- **float upperConstrainedMap(float value);** returns a value between -infinity .. outMax ==> no lower limit.

To change the constrain values call **init()** with new limits, or use the standard **constrain()**.

Note there are **NO** constrain-versions for **back(value)** function.


## FastMapDouble

Version 3.0 adds **FastMapDouble** which has the same interface as **FastMap()**.
This class is meant to support 8 bytes doubles in their native accuracy and precision. 
To display doubles one might need the **sci()** function of my **printHelpers** class.
https://github.com/RobTillaart/printHelpers

Note that on most embedded platforms the performance of doubles is less than floats.
See below.


#### boards supporting double

|  board         |  float  |  double  |
|:---------------|:-------:|:--------:|
|  UNO           |  yes    |  no      |
|  ATMEGA        |  yes    |  no      |
|  MKR1000       |  yes    |  yes     |
|  Zero          |  yes    |  yes     |
|  Teensy        |  yes    |  ?       |
|  ESP32         |  yes    |  yes     |
|  RP2040        |  yes    |  ?       |

To elaborate table.  (if someone has a good link, please let me know).


test code.
```cpp
void setup() {
  Serial.begin(115200);
  Serial.print("size of double:\t");
  Serial.println(sizeof(double));
  Serial.print("size of float: \t");
  Serial.println(sizeof(float));
}
void loop() {}
```


## Performance 

Tested version 0.4.1 with **FastMap_performance_test.ino**

|         |  MAP     |  FastMap  |  FastMap dbl  |  Notes  |
|:--------|:--------:|:---------:|:-------------:|:-------:|
|  UNO    |  496072  |  211888   |  211888       |  float == double
|  ESP32  |  1814    |  627      |  6924         |  


UNO scores factor 2.34
ESP32 scores factor 2.89

Note: the 8 byte double (ESP32) is ~11 x slower than the float version,
and ~4 x slower than the default map function.
So unless the precision of 8 bytes double is required one better
uses the float version.

Note: always do your own performance measurements!

If you have additional performance figures for other boards,
please let me know (report via an issue).


## Percentage

An often useful mapping is an input range upon percentage.
```
FM.init(in_min, in_max, 0.0, 100.0);
```


## Future

#### Must

- update documentation

#### Should


#### Could

- investigate map function for 64 bit integers.
- investigate map function for complex numbers? / coordinates?
  - what does linear interpolation mean, map an input area upon an output area?
- Template class?
- investigate exponential mapping: ```x -> alpha * beta^x```??
- do we need **constrainedBack()**? in three versions?

#### Wont

- can FastMap and FastMapDouble be in a class hierarchy? limited gain?


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,



