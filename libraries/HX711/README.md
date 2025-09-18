
[![Arduino CI](https://github.com/RobTillaart/HX711/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/HX711/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/HX711/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/HX711/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/HX711/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/HX711.svg)](https://github.com/RobTillaart/HX711/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/HX711/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/HX711.svg?maxAge=3600)](https://github.com/RobTillaart/HX711/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/HX711.svg)](https://registry.platformio.org/libraries/robtillaart/HX711)


# HX711

Arduino library for HX711 24 bit ADC used for load cells and scales.


## Description

This HX711 library has a public interface (API) which is a superset of the 
public interface of the HX711 library, version 0.7.3, by [Bogde](https://github.com/bogde/HX711).
The API is reused to be compatible on the basic interaction level, so credits 
for the reused API go to Bogde.

The implementation of both libraries differ from the beginning. 
The HX711 by Bogde is in several ways more sophisticated than this HX711 library. 
In this HX711 library, missing functions, modes and more were added to get more 
info from the library.
So you can choose the library that fit your needs most.

Another important difference is that this HX711 library uses floats. 
The 23 bits mantissa of the IEEE754 float matches the 24 bit ADC very well. 
Furthermore, using floats gave a smaller footprint on the Arduino UNO R3.

Note that the 24 bits of the HX711 contains some noise so depending on setup, 
load etc. only 16 to 20 of the bits are expected significant in practice. 
This translates roughly to 4 or max 5 significant digits in a single measurement
That's why it is advised to average (median) multiple measurements to reduce the noise.


### Breaking change 0.4.0

The **begin()** function has a new parameter **bool fastProcessor** which is default false.
It is used to slow down the internal **shiftIn()** to keep clock pulses within the 
specification. For most processors the internal code is "slow enough".
If the processor can set an IO pin faster than 0.4 us (spec datasheet == 0.2 us), 
the parameter **fastProcessor** must be set to true.


### Breaking change 0.3.0

In issue #11 it became clear that the timing of the default **shiftIn()** function to 
read the value of the internal ADC was too fast on some processor boards for the HX711.
This resulted in missing the first (= sign) bit or the value read could be a factor two
higher than it should. If one calibrated the sensor this would be compensated with the 
factor that is derived in the calibration process.

In 0.3.0 a dedicated **shiftIn()** function is added into this library that uses hard
coded delayMicroseconds to keep the timing of the clock within HX711 datasheet parameters. 
This should guarantee that the sign bit is always read correctly on all platforms. 
Drawback is that reading the HX711 takes an extra 50-55 microseconds.
How much this affects performance is to be investigated.


### HX711_MP

- https://github.com/RobTillaart/HX711_MP

The library HX711_MP is derived from this HX711 library version 0.3.5.

The HX711_MP is not compatible, see readme.md of HX711_MP

The main difference is that the HX711_MP uses a multi-point calibration
which replaces the "offset + scale" concept.
Functions related to this concept are removed in HX711_MP and replaced by
its own set of calibration functions.

This multi-point calibration allows to compensate for non-linear behaviour 
in the sensor readings.


### 10 or 80 SPS

The datasheet mentions that the HX711 can run at 80 samples per second (SPS). 
To select this mode connect the **RATE** pin(15) of the chip to VCC (HIGH).
Connecting **RATE** to GND (LOW) gives 10 SPS.

Having the RATE set to 10 or 80 SPS also changes the time to start up.
At 10 SPS it takes 400 milliseconds, at 80 SPS it takes 50 milliseconds.

All breakout boards I tested have **RATE** connected to GND and offer no
pin to control this from the outside.
Adafruit however has a breakout board with **RATE** exposed.
See https://www.adafruit.com/product/5974
There might be more.

If you have the schema of your board you should be able to expose the **RATE**
pin, e.g. by removing the pull down resistor to GND.

This library provide experimental means to control the **RATE**, see below.

If you need more SPS you could consider using the HX71708 device.
This is a close "relative" of the HX711 that allows to set the SPS to 
10, 20, 80, or 320 Hz. 
- https://github.com/beniseman/HX71708 


### Related

- https://github.com/bogde/HX711
- https://github.com/RobTillaart/weight  (conversions kg <> stone etc.)
- https://github.com/RobTillaart/HX710AB
- https://github.com/RobTillaart/HX711
- https://github.com/RobTillaart/HX711_MP  multipoint calibration version.

Discussion about resolution of the ADC
- https://forum.arduino.cc/t/scale-from-50-kg-to-5000kg-what-adc/1139710

Support for the HX71708 device (close related)
- https://github.com/beniseman/HX71708 allows to set the SPS to 10, 20, 80, or 320 Hz

Load cells go to very high weights, this side sells them up to 200 ton.
Never seen one and cannot tell if it will work with this library.
- https://stekon.nl/load-cells

Breakout with RATE exposed by ADAfruit
- https://www.adafruit.com/product/5974


### Faulty boards

- https://forum.arduino.cc/t/load-cell-amplifier-hx711-wrong-ground/1046075


## Main flow

First action is to call **begin(dataPin, clockPin)** to make connection to the **HX711**.

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
#include "HX711.h"
```

### Constructor

- **HX711()** constructor.
- **~HX711()** destructor.
- **void begin(uint8_t dataPin, uint8_t clockPin, bool fastProcessor = false, bool doReset = true)** sets a fixed gain 128 for now.
  - The parameter fastProcessor adds a 1 uS delay for each clock half-cycle to keep the time greater than 200 nS.
  - The parameter doReset is experimental in 0.6.3.
  It defaults to true (== backwards compatible) causing a call to reset(), taking extra time 
  before the device is ready to make new measurements. See reset() below. 
  Note that not calling reset() leaves the ADC in the previous or even an undefined state, 
  so use with care. (needs testing)
- **void reset()** set internal state to the start condition.
Reset() also does a power_down() / power_up() cycle. 
This cycle adds a delay of 400 (RATE = 10 SPS) or 50 (RATE = 80 SPS) milliseconds.


### isReady

There are different ways to wait for a new measurement.

- **bool is_ready()** checks if load cell is ready to read.
- **void wait_ready(uint32_t ms = 0)** wait until ready, check every ms.
- **bool wait_ready_retry(uint8_t retries = 3, uint32_t ms = 0)** wait max retries.
- **bool wait_ready_timeout(uint32_t timeout = 1000, uint32_t ms = 0)** wait max timeout milliseconds.


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


### Gain + channel

Use with care as it is not 100% reliable - see issue #27. (solutions welcome).

Read datasheet before use.

Constants (see .h file)

- **HX711_CHANNEL_A_GAIN_128 = 128**  This is the default in the constructor.
- **HX711_CHANNEL_A_GAIN_64 = 64**
- **HX711_CHANNEL_B_GAIN_32 = 32**  Note fixed gain for channel B.

The selection of channels + gain is in theory straightforward. 

- **bool set_gain(uint8_t gain = 128, bool forced = false)** values: 128 (default), 64 or 32.
If one uses an invalid value for the parameter gain, the channel and gain are not changed.
If forced == false it will not set the new gain if the library "thinks" it
already has the right value.
If forced == true, it will explicitly try to set the gain/channel again.
This includes a dummy **read()** so the next "user" **read()** will give the right info.
- **uint8_t get_gain()** returns set gain (128, 64 or 32).

By setting the gain to one of the three constants the gain and the channel is selected.
The **set_gain()** does a dummy read if gain has changed (or forced == true) so the 
next call to **read()** will return info from the selected channel/gain.

According to the datasheet the gain/channel change may take up to 400ms (table page 3).

Warning 1: if you use **set_gain()** in your program the HX711 can be in different states.
If there is an expected or unexpected reboot of the MCU, this could lead 
to an unknown state at the reboot of the code. 
So in such case it is strongly advised to call **set_gain()** explicitly in **setup()** 
so the device is in a known state.

Warning 2: In practice it seems harder to get the channel and gain selection as reliable
as the datasheet states it should be. So use with care. (feedback welcome)
See discussion #27 HX711. 


### Read mode

Get and set the operational mode for **get_value()** and indirect **get_units()**.

Constants (see .h file)

- **HX711_RAW_MODE**
- **HX711_AVERAGE_MODE**
- **HX711_MEDIAN_MODE**
- **HX711_MEDAVG_MODE**
- **HX711_RUNAVG_MODE**


In **HX711_MEDIAN_MODE** and **HX711_MEDAVG_MODE** mode only 3..15 samples are allowed
to keep memory footprint relative low.

- **void set_raw_mode()** will cause **read()** to be called only once!
- **void set_average_mode()** take the average of n measurements.
- **void set_median_mode()** take the median of n measurements.
- **void set_medavg_mode()** take the average of n/2 median measurements.
- **void set_runavg_mode()** default alpha = 0.5.
- **uint8_t get_mode()** returns current set mode. Default is **HX711_AVERAGE_MODE**.


### Get values

Get values from the HX711 corrected for offset and scale.
Note that in **HX711_RAW_MODE** the times parameter will be ignored => just call **read()** once.

- **float get_value(uint8_t times = 1)** read value, corrected for offset.
- **float get_units(uint8_t times = 1)** read value, converted to proper units.
- **bool set_scale(float scale = 1.0)** set scale factor which is normally a positive 
number larger than 50. Depends on load-cell used.
Returns false if scale == 0.
Note that for some specific applications, scale might be negative. 
- **float get_scale()** returns set scale factor.
- **void set_offset(int32_t offset = 0)** idem.
- **int32_t get_offset()** idem.


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

A load cell + HX711 module without weight gives a raw value, mostly not equal to zero.
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
- **void power_up()** wakes up the HX711. 
It should reset the HX711 to defaults but this is not always seen. 
See discussion issue #27 GitHub. Needs more testing.

Note: Having the RATE set to 10 or 80 SPS changes the time to start up.
At 10 SPS it takes 400 milliseconds, at 80 SPS it takes 50 milliseconds.
(See datasheet, Output settling time on page 3)


### Rate

**Experimental**

See section "10 or 80 SPS" above.

Note this only works if the **RATE** pin is exposed and connected to
the IO pin configured in set_rate_pin().
If not configured the other functions won't work.

- **void set_rate_pin(uint8_t pin)** sets the IO pin for SPS selection.
- **void set_rate_10SPS()** sets rate to 10 SPS.
- **void set_rate_80SPS()** sets rate to 80 SPS.
- **uint8_t get_rate()** returns 10 d(default) or 80.


### Pricing

Some price functions were added to make it easy to use this library
for pricing goods or for educational purposes. 
These functions are under discussion if they will stay in the library.
For weight conversion functions see https://github.com/RobTillaart/weight

- **float get_price(uint8_t times = 1)** idem.
- **void  set_unit_price(float price = 1.0)** idem.
- **float get_unit_price()** idem.


### Millivolts

**Experimental**

To be verified in a test setup.

In issue #53, a question was asked to convert the input of the HX711 to millivolts.
Thinking about this question resulted in a simple and elegant idea:

- Apply 0.000 mV to the system.
- Call **tare(times)** to calibrate the zero point. 
- Then apply 20.000 mV to the system.
- Call **calibrate_scale(20000)** to map the raw reading to 20000 µV = 20 mV.

Assuming the scale is linear, the HX711 now works like a millivolt meter.
And the **float get_units(uint8_t times = 1)** will return microvolts.

In fact, one could map any linear unit this way, e.g. if the voltage applied 
is linear with temperature, humidity or wind speed one can map this directly.


## Notes


### Scale values for load cells

These scale values worked pretty well with a set of load cells I have, 
Use calibrate to find your favourite values.

- 5 KG load cell   scale.set_scale(420.52);
- 20 KG load cell  scale.set_scale(127.15);


### Connections HX711

- A+/A-  uses gain of 128 or 64
- B+/B-  uses gain of 32

Colour scheme wires of two devices.

|  HX711 Pin  |  Colour dev 1   |  Colour dev 2   |
|:-----------:|:---------------:|:---------------:|
|      E+     |  red            |  red            |
|      E-     |  black          |  black          |
|      A-     |  white          |  blue           |
|      A+     |  green          |  white          |
|      B-     |  not connected  |  not connected  |
|      B+     |  not connected  |  not connected  |


### Temperature

Load cells do have a temperature related error. (see datasheet load cell)
This can be reduced by doing the calibration and take the tare
at the operational temperature one uses for the measurements.

Another way to handle this is to add a good temperature sensor
(e.g. DS18B20, SHT85) and compensate for the temperature
differences in your code.


## Multiple HX711


### Separate lines

Simplest way to control multiple HX711's is to have a separate **DOUT** and **CLK** 
line for every HX711 connected.


### Multiplexer

Alternative one could use a multiplexer like the https://github.com/RobTillaart/HC4052
or possibly an https://github.com/RobTillaart/TCA9548.
Although to control the multiplexer one need some extra lines and code.


### Share CLOCK line

See **HX_loadcell_array.ino**

Another way to control multiple HX711's is to share the **CLK** line. 
This has a few side effects which might be acceptable or not.

Known side effects - page 4 and 5 datasheet.

- The **CLK** is used to select channel and to select gain for the NEXT sample.
- The **CLK** is used for power down.
- After wake up after power down all HX711's will reset to channel A and gain 128.
**WARNING:** if one of the objects does a **powerDown()** or **reset()** it resets its internal states.
The other objects however won't reset their internal state, so a mismatch can occur.

So in short, sharing the **CLK** line causes all HX711 modules share the same state.
This can introduce extra complexity if one uses mixed gains or channels.
If all HX711's use the same settings it should work, however extra care is needed for
**powerDown()** and **reset()**.

**WARNING: Sharing the data lines is NOT possible as it could cause short circuit.**

See https://github.com/RobTillaart/HX711/issues/40


## Future


#### Must

- update documentation
- keep in sync with HX711_MP, HX710AB library.

#### Should

- test
  - different load cells.
  - B channel explicitly.
  - test reset and reboot behaviours.
  - test and verify the proper working of the rate functions.
- investigate read()
  - investigate the need of yield after interrupts
  - investigate blocking loop at begin => less yield() calls ?
- add performance figures

#### Could

- add error handling?
- optimize fastProcessor code (possible better performance)
  - injecting 2 micro delays is not always needed.
  - int flag instead of bool.
- make enum of the MODE's
- add examples
  - example the adding scale
  - void weight_clr(), void weight_add(), float weight_get() - adding scale
  - example for using rate functions.
- investigate temperature compensation.
- decide pricing keep/not => move to .cpp

#### Wont

- why store the gain as \_gain while the iterations m = 1..3 is used most
  - read() less code
  - **changes from explanatory code to vague**
  - very small performance gain.
  - code moves to both get/set_gain() so footprint might rise.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

