
[![Arduino CI](https://github.com/RobTillaart/HX711_MP/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/HX711_MP/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/HX711_MP/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/HX711_MP/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/HX711_MP/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/HX711_MP.svg)](https://github.com/RobTillaart/HX711_MP/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/HX711_MP/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/HX711_MP.svg?maxAge=3600)](https://github.com/RobTillaart/HX711_MP/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/HX711_MP.svg)](https://registry.platformio.org/libraries/robtillaart/HX711_MP)


# HX711_MP

Arduino library for HX711 24 bit ADC used for load cells. 
Has a multipoint calibration (MP) to compensate for non-linear sensor readings.


## Description

This https://github.com/RobTillaart/HX711_MP library is derived from https://github.com/RobTillaart/HX711
version 0.3.5. Although related and partly similar interface there are not compatible.

Currently HX711_MP is experimental and need to be tested more. 
Good news is that it is based upon tested code, so no big problems are expected.

The original HX711 library uses a linear relation between raw measurements and weights.
This improved library uses multi point calibration - up to 10 points for now.
This allows to compensate for non-linearities in the readings of the sensor.
Between these calibration points interpolation is still linear.

**WARNING: An important difference is that HX711_MP (version now) does not 
interpolate beyond the calibration data points.**

If problems occur or there are questions, please open an issue at GitHub.



#### 10 or 80 SPS

The datasheet mentions that the HX711 can run at 80 samples per second SPS. 
To select this mode connect the **RATE** pin(15) of the chip to Vcc (HIGH).
Connecting **RATE** to GND gives 10 SPS.

All breakout boards I tested have **RATE** connected to GND and offer no
pin to control this from the outside.

This library does not provide means to control the **RATE**.


#### Related

- https://github.com/bogde/HX711
- https://github.com/RobTillaart/weight  (conversions kg <> stone etc.)
- https://github.com/RobTillaart/HX711
- https://github.com/RobTillaart/HX711_MP


#### Differences HX711

Although the library is derived from the HX711 library they are not compatible.
Almost is the right word here.

Due to the different way of calibration the default **tare()** function is not 
supported any more.
This function used to calculate the offset in the raw data to get the zero point.
As in the multi point calibration there are up to 10 points that can indicate
the zero point the whole concept of offset and scale has "left the building".

In practice the return value of **get_value()**, **read()** functions et al differs 
that original raw-zero offset from the HX711 library.
This means the libraries are not 1 to 1 interchangeable, even a HX711_MP with only 
two points will behave slightly differently on this point.
This is even more true as the zero point does not need to be the lowest possible value.
Due to the support of non linear negative weights / forces the zero point can be at 
any point in the array.

The performance is not tested yet, expect a slightly slower **get_units()** as there
is more math involved for converting raw data to weights.


## Interface

```cpp
#include "HX711_MP.h"
```

#### Base

- **HX711_MP(uint8_t size)** constructor. 
Parameter sets the size of for the calibration arrays. 
Allowed range for size is 2..10.
- **~HX711_MP()**
- **void begin(uint8_t dataPin, uint8_t clockPin, bool fastProcessor)** sets a fixed gain 128 for now.
The fastProcessor option adds a 1 uS delay for each clock half-cycle to keep the time greater than 200 nS.
- **void reset()** set internal state to start condition.
Reset also does a power down / up cycle.
It does not reset the calibration data.
- **bool is_ready()** checks if load cell is ready to read.
- **void wait_ready(uint32_t ms = 0)** wait until ready, check every ms.
- **bool wait_ready_retry(uint8_t retries = 3, uint32_t ms = 0)** wait max retries.
- **bool wait_ready_timeout(uint32_t timeout = 1000, uint32_t ms = 0)** wait max timeout milliseconds.
- **float read()** raw read.
- **float read_average(uint8_t times = 10)** get average of times raw reads. times = 1 or more.
- **float read_median(uint8_t times = 7)** get median of multiple raw reads. 
times = 3..15 - odd numbers preferred.
- **float read_medavg(uint8_t times = 7)** get average of "middle half" of multiple raw reads.
times = 3..15 - odd numbers preferred.
- **float read_runavg(uint8_t times = 7, float alpha = 0.5)** get running average over times measurements.
The weight alpha can be set to any value between 0 and 1, times >= 1.
- **uint32_t last_read()** returns timestamp in milliseconds of last read.


#### Gain + channel

Use with care as it is not 100% reliable - see issue #27 (HX711 lib). (solutions welcome).

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


#### Mode 

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


#### Get values

Get values from the HX711.

Note that in **HX711_RAW_MODE** the times parameter will be ignored => just call **read()** once.

- **float get_value(uint8_t times = 1)** return raw value, optional averaged etc.
- **float get_units(uint8_t times = 1)** return units, typical grams.


#### Calibration

The multipoint calibration array is based upon https://github.com/RobTillaart/multiMap.
One can compensate for a non linear sensor by interpolating linear over multiple points.
It does not use a smooth nth degree function to interpolate.

The user has to measure a number of raw weights, typical including a zero weight.
These numbers are set into the object with **setCalibrate(index, raw, weight)**.
Note: Increasing indices must have an increasing raw number.

Typical use is to hardcode earlier found values in the setup() phase.

- **bool setCalibrate(uint8_t index, float raw, float weight)** maps a raw measurement
to a certain weight.
Note the index is zero based so a size of 10 uses index 0..9.
- **float getCalibrateSize()** returns the size of the internal array, typical 2..10
- **float getCalibrateRaw(uint8_t index)** get the raw value for the calibration point at index.
Returns 0 is index is out of range.
- **float adjustCalibrateRaw(uint8_t index, float amount)** changes the raw value at the array.
Returns 0 is index is out of range.
Used for run time calibration.
- **float getCalibrateWeight(uint8_t index)** get the mapped weight for the calibration point at index.
Returns 0 is index is out of range.

This way of calibration allows:
- to compensate for a non linear sensor by interpolating linear between two adjacent points.
- to adjust runtime the values in the array, adjusting the mapping.
- to use of negative weights (forces) as the


#### Power management

- **void power_down()** idem. Explicitly blocks for 64 microseconds. 
(See Page 5 datasheet). 
- **void power_up()** wakes up the HX711_MP. 
It should reset the HX711_MP to defaults but this is not always seen. 
See discussion issue #27 GitHub. Needs more testing.


## Notes


#### Connections HX711_MP

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


#### Temperature

Load cells do have a temperature related error. (see datasheet load cell)
This can be reduced by doing the calibration and take the tare
at the operational temperature one uses for the measurements.

Another way to handle this is to add a good temperature sensor
(e.g. DS18B20, SHT85) and compensate for the temperature
differences in your code.


## Future

Points from HX711 are not repeated here


#### Must

- keep in sync with HX711 library where relevant.
- update documentation

#### Should

- test a lot
  - different load cells.
- investigate interpolation beyond calibration range.
- add examples
  - runtime changing of the mapping.
- investigate malloc/free for the mapping arrays
- add performance figures
- Calibration
  - Returns 0 is index is out of range ==> NaN ?

#### Could

- add error handling?
  - HX711_INDEX_OUT_OF_RANGE
  - ??
- investigate temperature compensation.

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


