# Histogram Library

## Description

One of the main applications for the Arduino board is reading and logging of sensor data.
We often want to make a histogram of this data to get insight of the distribution of the
measurements. This is where this Histogram library comes in.

If you need more quantitative analysis, you might need the statistics library, also available on github.

## Operation

The Histogram distributes the values added to it into buckets and keeps count.
The interface consists of:

* Histogram(uint8_t len, float *bounds);  // constructor
* ~Histogram();                           // destructor
* void clear();                           // reset all counters
* void add(float val);                    // add a value, increase count
* void sub(float val);                    // 'add' a value, but decrease count
* uint8_t size();                         // number of buckets
* unsigned long count();                  // number of values added
* long bucket(uint8_t idx);               // count of single bucket
* float frequency(uint8_t idx);           // the relative frequency of a bucket
* uint8_t find(float f);                  // find the bucket for value f

// experimental
* float PMF(float val);       // Probability Mass Function
* float CDF(float val);       // Cumulative Distribution Function
* float VAL(float prob);      // Value
(:sourceend:)

When the class is initialized an array of the boundaries to define the borders of the
buckets is passed to the constructor. This array should be declared global as the
Histogram class does not copy the values to keep memory usage low. This allows to change
the boundaries runtime, so after a clear(), a new Histogram can be created.

Internally the library does not record the individual values, only the count per bucket.
If a new value is added - add() or sub() - the class checks in which bucket it belongs
and the buckets counter is increased.

The sub() function is used to decrease the count of a bucket and it can cause the count
to become below zero. ALthough seldom used but still depending on the application it can
be useful. E.g. when you want to compare two value generating streams, you let one stream
add() and the other sub(). If the histogram is similar they should cancel each other out
(more or less), and the count of all the buckets should be around 0. [not tried].

Frequency() may be removed to reduce footprint as it can be calculated quite easily with
the formula (1.0* bucket(i))/count().

There are three experimental functions: PMF, CDF and VAL.
* PMF is quite similar to frequency, but uses a value as parameter.
* CDF gives the sum of frequencies <= value.
* VAL is CDF inverted.

As the Arduino typical uses a small number of buckets these functions are quite 
coarse/inaccurate (linear interpolation within bucket is still to be investigated)

## Todo list

* Copy the boundaries array?
* Always Refactor
* Additional values per bucket.
** Sum, Min, Max, (average acan be derived)
** separate bucket-array for sub()
** improve strategy for find() the right bucket..
** investigate linear interpolation for PMF, CDF and VAL functions to improve accuracy.
** clear individual buckets
** merge buckets


## License

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

