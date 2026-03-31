
[![Arduino CI](https://github.com/RobTillaart/HX712/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/HX712/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/HX712/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/HX712/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/HX712/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/HX712.svg)](https://github.com/RobTillaart/HX712/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/HX712/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/HX712.svg?maxAge=3600)](https://github.com/RobTillaart/HX712/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/HX712.svg)](https://registry.platformio.org/libraries/robtillaart/HX712)


# HX712

Arduino library for HX712 24 bit ADC used for load cells and scales.


## Description

*This readme.md is based upon the HX711 readme.md, so it may contain some sections
that are not updated yet.*

**Experimental**

This HX712 library has a public interface (API) which is based upon my HX711 library
which was based upon version 0.7.3, by [Bogde](https://github.com/bogde/HX712).
So credits for API reuse to Bogde.
The API of the HX711 is reused as much as possible to be compatible on the basic
interaction level.

The HX712 is **not compatible** with the HX711 on hardware connections.
See the datasheet for details.
The HX712 is however similar to the HX711 in applications as it is also an 24 bit ADC.
Functionally the HX712 has two distinctive features, battery monitoring and software
switching between 10 and 40 SPS which the HX711 not has.
Note the HX711 can (in theory) switch between 10 and 80 SPS but only through hardware.
Another difference is that the HX711 has 2 channels where the HX712 has only one.
Furthermore the GAIN factors are different. See table below.

The library was written as I encountered the HX712 datasheet and found the software
switching of 10/40 SPS more than interesting. Reason enough to implement an initial
version for an Arduino library.

The library is not tested yet as I have no breakout board / hardware.
So if you have experience with the HX712 please let me know.

Feedback as always is welcome.


### Comparison HX711 vs HX712

|  Function          |  HX711  |  HX712  |
|:-------------------|:-------:|:-------:|
|  Channels          |    2    |    1    |
|  GAIN levels       |    3    |    2    |
|  Battery monitor   |    N    |    Y    |
|  SPS               |  10/80  |  10/40  |
|  SPS SW switching  |    N    |    Y    |


### Related

- https://github.com/bogde/HX711
- https://github.com/RobTillaart/weight  (conversions kg <> stone etc.)
- https://github.com/RobTillaart/HX710AB
- https://github.com/RobTillaart/HX711
- https://github.com/RobTillaart/HX711_MP  multipoint calibration version.
- https://github.com/RobTillaart/HX712 this library

More links see HX711 library.


## Main flow

First action is to call **begin(dataPin, clockPin)** to make connection to the **HX712**.

Second step is to check **isReady()** to wait until the device is ready for measurements.

Next step is calibration for which a number of functions exist.
- **tare()** measures the offset of the zero point.
- **set_scale(factor)** set a known conversion factor e.g. from EEPROM.
- **calibrate_scale(weight, times)** determines the scale factor based upon a known weight e.g. 1 Kg.
The weight is typical in grams, however any unit can be used, depending on the
load cell used.

Steps to take for calibration
1. clear the scale.
1. wait until **isReady()** returns true.
1. call **tare()** to determine and set the zero weight offset.
1. put a known weight on the scale.
1. call **calibrate_scale(float weight)**, weight typical in grams, however any unit can be used.
1. scale factor is calculated.
1. save the offset and scale for later use e.g. EEPROM.

Note that the units used in **calibrate_scale()** will be returned by **get_units()**.


## Interface

```cpp
#include "HX712.h"
```

### Constructor

- **HX712()** constructor.
- **~HX712()** destructor.
- **void begin(uint8_t dataPin, uint8_t clockPin, bool fastProcessor = false, bool doReset = true)**
sets the gain to 128 and SPS to 10.
  - The parameter fastProcessor adds a 1 uS delay for each clock half-cycle to keep the time greater than 200 nS.
  - The parameter doReset is experimental (in 0.6.3 HX711).
  It defaults to true (== backwards compatible) causing a call to reset(), taking extra time
  before the device is ready to make new measurements. See reset() below.
  Note that not calling reset() leaves the ADC in the previous or even an undefined state,
  so use with care. (needs testing)
- **void reset()** set internal state to the start condition.
Reset() also does a power_down() / power_up() cycle.
This cycle adds a delay of 400 (RATE = 10 SPS) or 100 (RATE = 40 SPS) milliseconds.


### isReady

There are different ways to wait for a new measurement.

- **bool is_ready()** checks if load cell is ready to read.
- **void wait_ready(uint32_t ms = 0)** wait until ready, check every ms milliseconds.
- **bool wait_ready_retry(uint8_t retries = 3, uint32_t ms = 0)** wait max retries, check every ms milliseconds.
- **bool wait_ready_timeout(uint32_t timeout = 1000, uint32_t ms = 0)** wait max timeout milliseconds, check every ms milliseconds.


### Read

Warning: the read calls are blocking calls, which can take up to 400 ms in the first read() call.
Best practice is to check with isReady() before calling read().

- **float read()** get a raw read.
- **float read_average(uint8_t times = 10)** get average of times raw reads. times = 1 or more.
- **float read_median(uint8_t times = 7)** get median of multiple raw reads.
times = 3..15 - odd numbers preferred.
- **float read_medavg(uint8_t times = 7)** get average of "middle half" of multiple raw reads.
times = 3..15 - odd numbers preferred.
- **float read_runavg(uint8_t times = 7, float alpha = 0.5)** get running average over times measurements.
The weight alpha can be set to any value between 0 and 1, times >= 1.
- **uint32_t last_read()** returns timestamp in milliseconds of last read.


### Read Battery

- **float read_battery()** returns the value of battery.
TODO test how this is coded and if a factor is needed.

### Gain

The HX712 has only one channel

Constants (see .h file)

- **HX712_GAIN_128 = 128** This is the default in the constructor.
- **HX712_GAIN_256 = 256**
- **HX712_RATE_10 = 10** default
- **HX712_RATE_40 = 40**

The selection of gain is in theory straightforward.

- **bool set_gain_rate(uint8_t gain = HX712_GAIN_128, uint8_t rate = HX712_RATE_10)** values: 128 (default) or 256.
If one uses an invalid value for gain or rate, the function returns false.
The function will execute a dummy **read()** so the next "user" **read()** will give the right info.
- **uint16_t get_gain()** returns set gain (128 or 256).

According to the datasheet (table page 3), the gain/SPS change may take up to 400 ms.

If you use **set_gain_rate()** the HX712 can be in different states.
If there is an expected or unexpected reboot of the MCU, this could lead
to an unknown state at the reboot of the code.
Therefore it is strongly advised to call **set_gain_rate()** explicitly in **setup()**
so the device is in a known state.


### Read mode

Get and set the operational mode for **get_value()** and indirect **get_units()**.

Constants (see .h file)

- **HX712_RAW_MODE**
- **HX712_AVERAGE_MODE**
- **HX712_MEDIAN_MODE**
- **HX712_MEDAVG_MODE**
- **HX712_RUNAVG_MODE**
- **HX712_BATTERY_MODE**  TODO implement


In **HX712_MEDIAN_MODE** and **HX712_MEDAVG_MODE** mode only 3..15 samples are allowed
to keep memory footprint relative low.

- **void set_raw_mode()** will cause **read()** to be called only once!
- **void set_average_mode()** take the average of n measurements.
- **void set_median_mode()** take the median of n measurements.
- **void set_medavg_mode()** take the average of n/2 median measurements.
- **void set_runavg_mode()** default alpha = 0.5.
- **uint8_t get_mode()** returns current set mode. Default is **HX712_AVERAGE_MODE**.


### Get values

Get values from the HX712 corrected for offset and scale.
Note that in **HX712_RAW_MODE** the times parameter will be ignored => just call **read()** once.

- **float get_value(uint8_t times = 1)** read value, corrected for offset.
- **float get_units(uint8_t times = 1)** read value, converted to proper units.
- **bool set_scale(float scale = 1.0)** set scale factor which is normally a positive
number larger than 50. Depends on load-cell used.
Returns false if scale == 0.
Note that for some specific applications, scale might be negative.
- **float get_scale()** returns set scale factor.
- **void set_offset(int32_t offset = 0)** idem.
- **int32_t get_offset()** idem.

If one sets the scale to 1.0 and offset to 0.0, one gets the raw measurements from the HX712.


### Tare & calibration I

Steps to take for calibration
1. clear the scale.
1. call **tare()** to determine and set the zero weight offset.
1. put a known weight on the scale.
1. call **calibrate_scale(float weight)**, weight typical in grams, however any unit can be used.
1. scale factor is calculated.
1. save the offset and scale for later use e.g. EEPROM.

Note that the units used in **calibrate_scale()** will be returned by **get_units()**.

- **void tare(uint8_t times = 10)** call tare to determine the offset
to calibrate the zero (reference) level. See below.
- **float get_tare()** returns the offset \* scale.
Note this differs after calls to **calibrate_scale()**.
Use **get_offset()** to get only the offset.
- **bool tare_set()** checks if a tare has been set.
Assumes offset is not zero, which is true for all load cells tested.
- **void calibrate_scale(float weight, uint8_t times = 10)**
The calibration weight averages times measurements to improve accuracy.
Weight is typical in grams, however any unit can be used.
Be aware this unit will also be returned by **get_units()**.

Since 0.6.0 the weight is defined as float which allows easier calibration in
other units e.g. define the weight as 2.5 kg instead of 2500 gram.
The function **GetUnits()** will then return its value in kg too.

Also by using a float the range of calibration weights is substantially increased.
One can now define 250 gram as 250000 milligram, where before the value was max
65535 units (theoretical increase of precision from 4.8 to 6.9 digits).
This allows the calibration of superheavy load cells, e.g 500 kg and use a
defined weight of 100000 gram.
Finally the use of floats allow the use of decimals e.g. a calibration weight
of 125.014 kg or 306.4 gram.

Note: calibrate_scale() uses averaging and does not use the mode set.

Note: calibrate_scale() can have a negative value as weight e.g. force of a balloon.


### Tare & calibration II

A load cell + HX712 module without weight gives a raw value, mostly not equal to zero.
The function **get_tare()** is used to measure this raw value and allows the user
to define this value as a zero weight (force) point.
This zero point is normally without any load, however it is possible to define
a zero point with a "fixed" load e.g. a cup, a dish, even a spring or whatever.
This allows the system to automatically subtract the weight / force of the cup etc.

**Warning**: The user must be aware that the "fixed" load together with the
"variable" load does not exceed the specifications of the load cell.

E.g. a load cell which can handle 1000 grams with a cup of 300 grams should not
be calibrated with a weight of more than 700 grams.
In fact it is better to calibrate with a weight in the order of 80 to 90% of
the maximum load so in this example a weight of 500 to 600 grams.
That would make the total 800-900 grams == 80/90% of the max load.

Another point to consider when calibrating is to use a weight that is
in the range you want to make your measurements.
E.g. if you want to measure coffee beans in portions of 250 grams, use
a weight in the range 200-300 grams. Could just save an extra bit.

Furthermore it is also important to do the calibration at the temperature you
expect to do the weight measurements. See temperature section below.


### Inner formula

Weight = **get_scale()** x raw + **get_tare()**.

With the two parameters one can interpolate the inner formula.
This can be used e.g to make an ideal graph of the conversion.
This can be compared with actual values to get an indication
of the accuracy of the load cell.


### Power management

- **void power_down()** idem. Explicitly blocks for 64 microseconds.
(See Page 5 datasheet).
- **void power_up()** wakes up the HX712.
It should reset the HX712 to defaults but this is not always seen.
See discussion issue #27 GitHub. Needs more testing.

Note: Having the RATE set to 10 or 40 SPS changes the time to start up.
At 10 SPS it takes 400 milliseconds, at 40 SPS it takes 100 milliseconds.
(See datasheet, Output settling time on page 3)

Note: add a pull up resistor on the CLK pin prevents waking up when the
processor goes to sleep and cannot keep the CLK pin HIGH.


## Notes


### Connections HX712

TODO

### Temperature

Load cells do have a temperature related error. (see datasheet load cell)
This can be reduced by doing the calibration and take the tare
at the operational temperature one uses for the measurements.

Another way to handle this is to add a good temperature sensor
(e.g. DS18B20, SHT85) and compensate for the temperature
differences in your code.


## Multiple HX712


### Separate lines

Simplest way to control multiple HX712's is to have a separate **DOUT** and **CLK**
line for every HX712 connected.


### Multiplexer

Alternative one could use a multiplexer like the https://github.com/RobTillaart/HC4052
or possibly an https://github.com/RobTillaart/TCA9548.
Although to control the multiplexer one need some extra lines and code.


### Share CLOCK line

See **HX_loadcell_array.ino**

Another way to control multiple HX712's is to share the **CLK** line.
This has a few side effects which might be acceptable or not.

Known side effects - page 4 and 5 datasheet.

- The **CLK** is used to select channel and to select gain for the NEXT sample.
- The **CLK** is used for power down.
- After wake up after power down all HX712's will reset to channel A and gain 128.
**WARNING:** if one of the objects does a **powerDown()** or **reset()** it resets its internal states.
The other objects however won't reset their internal state, so a mismatch can occur.

So in short, sharing the **CLK** line causes all HX712 modules share the same state.
This can introduce extra complexity if one uses mixed gains or channels.
If all HX712's use the same settings it should work, however extra care is needed for
**powerDown()** and **reset()**.

**WARNING: Sharing the data lines is NOT possible as it could cause short circuit.**

See https://github.com/RobTillaart/HX711/issues/40


## Future


#### Must

- update documentation
- test with hardware.
- implement HX712_BATTERY_MODE

#### Should

- keep in sync with HX711.


#### Could

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

