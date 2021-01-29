
[![Arduino CI](https://github.com/RobTillaart/Statistic/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Statistic/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Statistic.svg?maxAge=3600)](https://github.com/RobTillaart/Statistic/releases)


# Statistic

Statistic library for Arduino includes sum, average, variance and std deviation


## Description

The statistic library is made to get basic statistical information from a 
one dimensional set of data, e.g. a stream of values of a sensor.

The stability of the formulas is improved by the help of Gil Ross (Thanks!)

## Interface

- **Statistic(bool useStdDev = true)** Constructor, default use the standard deviation
functions. Setting this flag to **false** reduces math so slight increase of performance.
- **void clear(bool useStdDev = true)** resets all variables.
- **float add(float value)** (since 0.4.3) returns value actually added to internal sum.
If this is (much) different from what should be added it becomes time to call **clear()**
- **uint32_t count()** returns zero if count == zero (of course)
- **float sum()**      returns zero if count == zero
- **float minimum()**  returns zero if count == zero
- **float maximum()**  returns zero if count == zero
- **float average()**  returns NAN if count == zero

These three functions only work if **useStdDev == true**

- **variance()**         returns NAN if count == zero
- **pop_stdev()**        population stdev, returns NAN if count == zero
- **unbiased_stdev()**   returnsNAN if count == zero


## Operational

See examples

## FAQ

#### Q: Are individual samples still available?

The values added to the library are not stored in the lib as it would use lots 
of memory quite fast. Instead a few calculated values are kept to be able to 
calculate the most important statistics. 


#### Q: How many samples can the lib hold?  Part 1: internal variables and overflow

The counter of samples is an **uint32_t**, implying a maximum of about **4 billion** samples. 
In practice 'strange' things might happen before this number is reached. 
There are two internal variables, **\_sum** which is the sum of the values and **\_ssq** 
which is the sum of the squared values. Both can overflow especially **\_ssq** 
can and probably will grow fast. The library does not protect against it.

There is a workaround for this (to some extend) if one knows the approx 
average of the samples before. Before adding values to the lib subtract 
the expected average. The sum of the samples would move to around zero. 
This workaround has no influence on the standard deviation. 

!! Do not forget to add the expected average to the calculated average.

- Q: should this subtraction trick be build into the lib?


#### Q: How many samples can the lib hold?  Part 2: order of magnitude floats

The samples are added in the internal variable **\_sum** and counted in **\_cnt**. 
In time **\_sum** will outgrow the added values in order of magnitude.
As **\_sum** is a float with 23 bite = ~7 digits precision this problem starts 
to become significant between 1 and 10 million calls to **add()**. 
The assumption here is that what's added is always in the same order of magnitude
(+- 1) e.g. an analogRead. 10 million looks like a lot but an analogRead takes only 
~0.1 millisecond on a slow device like an UNO.

Beyond the point that values aren't added anymore, and the count still growing,
one will see that the average will go down (very) slowly, but down.

There are 2 ways to detect this problem:
- check **count()** and decide after 100K samples to call **clear()**. 
- (since 0.4.3) Check the return value of **add()** to see what value is actually
added to the internal **\_sum**. If this substantial different, it might be time 
to call **clear()** too. 

For applications that need to have an average of large streams of data there also
exists a **runningAverage** library. This holds the last N (< 256) samples and take the 
average of them. This will often be the better tool. 

Also a consideration is to make less samples if possible. When temperature does 
not change more than 1x per minute, it makes no sense to sample it 2x per second.


#### Q: How about the precision of the library?

The precision of the internal variables is restricted due to the fact 
that they are 32 bit float (IEEE754). If the internal variable **\_sum** has 
a large value, adding relative small values to the dataset wouldn't 
change its value any more. Same is true for **\_ssq**. One might argue that 
statistically speaking these values are less significant, but in fact it is wrong.

There is a workaround for this (to some extend). If one has the samples in an 
array or on disk, one can sort the samples in increasing order (abs value) 
and add them from this sorted list. This will minimize the error, 
but it works only if the samples are available and the they may be added 
in the sorted increasing order.


#### Q: When will internal var's overflow? esp. squared sum

IEEE754 floats have a max value of about **+-3.4028235E+38**


#### Q: Why are there two functions for stdev?

There are two stdev functions the population stdev and the unbiased stdev. 
See Wikipedia for an elaborate description of the difference between these two.



