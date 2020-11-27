# FastMap

Fast mapping and constraining

## Description

FastMap is an object that precalculates (internal) floats to make a mapping function especially for floats.
The Fastmap also provides a **back()** function to reverse the mapping. 
This only works well with floats, so use with care.

An important difference with the traditional **map()** function is that both **init()** and **map()** 
accepts floats as parameters, allowing mapping that would be hard to achieve with the normal **map()**
function.

## Performance notes

(based upon tests https://github.com/RobTillaart/FastMap/issues/4 )
- On AVR (UNO and MEGA) no gain is made mapping integers with fastMap, 130% slower = substantial
- On AVR the gain for float is limited, 10% faster
- On ESP32 the gain for integers and float is both in the order of 25%

To see the actual gain in your project on your hardware you should test and compare.

FastMap is faster when mapping floats as it uses less float operations than the standard map formula does.
The perfomance results from precalculating values in the  **init()** function so actual mapping needs only 
one multiply and add, where the standard **map()** function uses four adds, a multiplication and a division.
The precalculation in **init()** should be taken in account and if every **map()** call needs an **init()**
there will be no gain, on contrary.

The implementation uses floats (typical 32 bits) which might result in more memory usage and loss of precision 
for mapping of larger values, especially 32 and 64 bit integers. This is caused by the limits of the mantissa 
(~23 bits) of the standard 4 byte float.

## Interface

- **void init(in_min, in_max, out_min, out_max);** defines the linear mapping parameters.  
The **init()** function calculates all needed values for the **map()**, the **back()** call and the **constrainXX()** functions.
The **init()** function can be called again with new values when needed to do other mapping, 
although it will give less overhead if you create an fastMap object per conversion needed.
Note: **init()** does not check for a divide by zero (out_max == out_min) or (in_max == in_min)
- **float map(float value)** maps the parameter.
- **float back(float value)** does the inverse mapping

FastMap supports three versions of constraining the map function, based upon the parameters of **init()**
- **float constrainedMap(float value);** returns a value between outMin .. outMax
- **float lowerConstrainedMap(float value);** returns a value between outMin .. inf  (No upper limit)
- **float upperConstrainedMap(float value);** returns a value between -inf .. outMax

To change the constrain values call **init()** with new limits, or call **constrain()**

Note there are **NO** constrain-versions for **back(value)** function.


## FastMapDouble

Version 3.0 adds **fastMapDouble** which has the same interface.
This class is meant to support 8 bytes doubles in their native accuracy and precision. 
To display doubles one might need the **sci()** function of my **printHelpers** class.

## Usage

See examples.
