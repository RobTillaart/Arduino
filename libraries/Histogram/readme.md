
[![Arduino CI](https://github.com/RobTillaart/Histogram/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Histogram/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Histogram.svg?maxAge=3600)](https://github.com/RobTillaart/Histogram/releases)

# Histogram

Arduino library for creating histograms math.

## Description

One of the main applications for the Arduino board is reading and logging of sensor data.
We often want to make a histogram of this data to get insight of the distribution of the
measurements. This is where this Histogram library comes in.

The Histogram distributes the values added to it into buckets and keeps count.

If you need more quantitative analysis, you might need the statistics library, 
a- https://github.com/RobTillaart/Statistic

## Interface 

### Constructor

- **Histogram(uint8_t len, float \*bounds)** constructor, get an array of boundary values and array length
- **~Histogram()** destructor

### Base

- **void clear()** reset all counters
- **void add(float val)** add a value, increase count of bucket
- **void sub(float val)** 'add' a value, but decrease count
- **uint8_t size()** number of buckets
- **unsigned long count()** total number of values added
- **long bucket(uint8_t idx)** count of single bucket, can be negative due to **sub()**
- **float frequency(uint8_t idx)** the relative frequency of a bucket
- **uint8_t find(float f)** find the bucket for value f

When the class is initialized an array of the boundaries to define the borders of the
buckets is passed to the constructor. This array should be declared global as the
Histogram class does not copy the values to keep memory usage low. This allows to change
the boundaries runtime, so after a **clear()**, a new Histogram can be created.

The values in the boundary array do not need to be equidistant (equal in size).

Internally the library does not record the individual values, only the count per bucket.
If a new value is added - **add()** or **sub()** - the class checks in which bucket it belongs
and the buckets counter is increased.

The **sub()** function is used to decrease the count of a bucket and it can cause the count
to become below zero. ALthough seldom used but still depending on the application it can
be useful. E.g. when you want to compare two value generating streams, you let one stream
**add()** and the other **sub()**. If the histogram of both streams is similar they should cancel 
each other out (more or less), and the value of all buckets should be around 0. \[not tried\].

The **frequency()** function may be removed to reduce footprint as it can be calculated with
the formula **(1.0 \* bucket(i))/count()**.

### Experimental

- **float PMF(float val)** Probability Mass Function
- **float CDF(float val)** Cumulative Distribution Function
- **float VAL(float prob)** Value Function

There are three experimental functions:
- **PMF()** is quite similar to frequency, but uses a value as parameter.
- **CDF()** gives the sum of frequencies <= value.
- **VAL()** is **CDF()** inverted.

As the Arduino typical uses a small number of buckets these functions are quite 
coarse/inaccurate (linear interpolation within bucket is still to be investigated)

## Todo list

- Copy the boundaries array?
- Additional values per bucket.
  - Sum, Min, Max, (average can be derived)
- separate bucket-array for sub()
- improve strategy for **find()** the right bucket..
- investigate linear interpolation for **PMF()**, **CDF()** and **VAL()** functions to improve accuracy.
- explain **PMF()**, **CDF()** and **VAL()** functions
- clear individual buckets
- merge buckets
- bucket full / overflow warning.
- make github issues of the above...

## Operation

See examples

