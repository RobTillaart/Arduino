
[![Arduino CI](https://github.com/RobTillaart/RAIN/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/RAIN/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/RAIN/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/RAIN/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/RAIN/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/RAIN.svg)](https://github.com/RobTillaart/RAIN/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/RAIN/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/RAIN.svg?maxAge=3600)](https://github.com/RobTillaart/RAIN/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/RAIN.svg)](https://registry.platformio.org/libraries/robtillaart/RAIN)


# RAIN

RAIN is an Arduino library for a rain sensor (analog).


## Description

**Experimental**

A rain sensor like the **FC-37, YL-83, HM-RD** a.o. is a relative simple device.
It measures the resistance between wires when these are put in a liquid, water or in the ground.
The device converts the resistance to a voltage typical 0 .. 5 Volt.
The more the wires are covered by the liquid, the lower the voltage.
0.0 Volt is WET, and a high voltage is DRY.

The breakout (LM393 comparator) I used to test also has a digital output,
which goes LOW if a threshold (to be set with a potentiometer on the breakout) is reached.

The library is experimental as it needs more testing.
Changes of the interface are definitely possible.

Feedback as always is welcome.


### How to determine intensity of rain

**Experimental**

Some thoughts about determination of rain intensity.
These are triggered by questions in issue #5 and 
The ideas are not tested but should get you started.
So all disclaimers apply.

A way to test the intensity of the rain involves placing the FC-37 under an angle.
The angle has to be determined how much, a first guess is 30°-45°.
This way a raindrop will stay only for a short time on the sensor as gravity takes care 
rolling it downwards.
An additional heating element can remove the remaining water quickly. 
This latter could be controlled automatically by the DO (Digital Out) line.

From the frequency of (interval between) the raindrops on the FC-37 the intensity 
of the rain and precipitation can be estimated.

Some estimated numbers for the raindrops to intensity math.

- There are roughly 15000 - 25000 raindrops / liter => 0.040 - 0.067 ml per raindrop.
- The volume of an average raindrop = 0.050 ml (20000 drops / liter).
- The size of the sensor area of an FC-37 = 7.2 cm2 = 1.0 / 1389 m2  
- Assume you can detect / count the individual raindrops. 

So 1 raindrop of water on 7.2 cm2 

- 0.040 x 1389 ==> 55.6 ml / m2 ==> 0.0556 mm
- 0.050 x 1389 ==> 69.5 ml / m2 ==> 0.0695 mm (average raindrop)
- 0.067 x 1389 ==> 93.1 ml / m2 ==> 0.0931 mm

Note: if you have a light rain with only a few raindrops, they tend to be smaller (0.040 ml/raindrop or less). 
In heavy rain the raindrops might be larger than average (0.060 ml/raindrop or more). 
This factor is not elaborated in this section, however this factor indicates that
there is a substantial margin in the accuracy.


#### Raindrops to mm table 

This results in this indicative table (under above assumptions 0.050 ml/raindrop) for
the number of raindrops in a given time frame. 

|  drops  |  mL / m2  |   mm   |  notes  |
|:-------:|----------:|-------:|:--------|
|    1    |      70   |  0.07  |  rounded to 70
|    2    |     140   |  0.14  |
|    3    |     210   |  0.21  |
|    4    |     280   |  0.28  |
|    5    |     350   |  0.35  |
|    7    |     490   |  0.49  |  7.1 drops ~ half a liter = 0.5 mm
|   10    |     700   |  0.70  |
|   14    |     980   |  0.98  |  14.3 drops ~ 1 liter / m2 = 1 mm
|   15    |    1050   |  1.05  |
|   20    |    1400   |  1.40  |


Note: the orientation of the tilted sensor with respect to the wind direction
when the rain falls has probably an effect. This is not investigated.

Note: To improve measurements one could "add" multiple FC-37 devices.


#### Intensity table

From Google an indication of mm/hour to intensity (1 mm/hour = 1 liter/m2/hour)

|  intensity    |  rate mm/h    |  description  |
|:--------------|:--------------|:--------------|
|  Dry          |  0.0          |  Dry
|  Trace        |  < 0.25       |  Barely measurable; fine mist or fog.
|  Very Light   |  0.25 - 1.00  |  Very light drizzle
|  Light        |  1.00 - 2.50  |  Steady light rain; you can walk without an umbrella for short periods.
|  Moderate     |  2.50 - 10.0  |  Puddles form slowly; an umbrella is highly recommended.
|  Heavy        |  10.0 - 50.0  |  Rapid puddle formation, noticeable splashing, reduced visibility.
|  Violent      |  > 50.0       |  Torrential downpours, potential flash flooding, significantly restricted visibility.

Adding columns:

- The raindrops/hour (on the FC-37) is based upon mm/hour and a raindrop volume of 0.050 ml.
- The interval (in seconds) is calculated from drops/hour, at a certain moment individual raindrops are not 
- The colour column is added for GUI purpose (or RGB LED), see https://github.com/RobTillaart/map2colour  

|  interval s  |  raindrops/h  |  rate mm/h    |  intensity    |  colour  |
|:-------------|:--------------|:--------------|:--------------|:---------|
|  -           |  0            |  0.0          |  Dry          |  white   |
|  > 1000      |  < 3.6        |  < 0.25       |  Trace        |  blue    |
|  1000 - 250  |  3.6 - 14.4   |  0.25 - 1.00  |  Very Light   |  green   |
|  250 - 100   |  14.4 - 36.0  |  1.00 - 2.50  |  Light        |  yellow  |
|  100 - 25    |  36.0 - 144   |  2.50 - 10.0  |  Moderate     |  orange  |
|  25 -  5     |  144 -  719   |  10.0 - 50.0  |  Heavy        |  red     |
|  < 5         |  > 720        |  > 50.0       |  Violent      |  purple  |


So assume we determined an interval between raindrops of 93.1 seconds on an FC-37 device.
That would imply 3600 / 93.1 = 38.7 raindrops per hour = 38.7 x 69 ml = 2668 ml/hour = 2.7 liter/hour ==> light to moderate rain.

Interval of 10 minutes = 6 drops/hour = 6 x 69 ml = 0.414 liter / hour ==> very light rain

Interval of  20 seconds = 180 drops/hour = 180 x 69 ml = 12.240 liter /hour ==> heavy rain.


### Related

Datasheet
- https://urolakostapk.wordpress.com/wp-content/uploads/2016/10/yl-83-rain-detector-datasheet_low.pdf

How to
- https://randomnerdtutorials.com/guide-for-rain-sensor-fc-37-or-yl-83-with-arduino/
- https://randomnerdtutorials.com/guide-for-soil-moisture-sensor-yl-69-or-hl-69-with-the-arduino/

Other
- https://github.com/RobTillaart/map2colour - to make a colour scale for rain intensity
- https://github.com/RobTillaart/VolumeConverter
- https://wind101.net/raindrop/ - higher raindrop math


## Hardware connection

Typical connection

```
      Processor             LM393             SENSOR FC-37
   +-------------+      +----------+     +---------------------+
   |             |      |          |     |                     |
   |         GND |----->| GND      |     |                     |
   |    powerPin |----->| 5V       |-----|                     |
   |    analogIn |<-----| AO       |     |                     |
   |             |      |          |-----|                     |
   |  digital in |<-----| DO       |     |                     |
   |             |      |          |     |                     |
   +-------------+      +----------+     +---------------------+

```

The DO pin is not supported in the library. 
It could be connected to any GPIO pin, or interrupt pin.

It is possible to have the 5V connected to 5V so the device 
is not switchable with the power pin.


## Interface

```cpp
#include "rain.h"
```

### Constructor

- **RAIN(uint8_t analogPort, uint8_t powerPin = 255)** constructor.
analogPort is the internal analog port to use.
powerPin is optional, but recommended.
The default 255 means **NO** powerPin selected.
- **bool begin(float maxVoltage, uint16_t maxSteps)** sets the ADC parameters.
Allows to be changed runtime, e.g. if voltage fluctuates the math can be adapted by calling **begin()** again.
Might be a separate **setVoltage()** is more efficient.


### Read

- **float raw(uint8_t times = 1)** makes 1 or more measurements and averages them.
returned value is the average number of ADC steps.
- **float read(uint8_t times = 1)** makes 1 or more measurements, averages them and convert the average to a voltage.
This voltage is returned, and also cached for **percentage()** and **getLevel()**.


### Power control

Will only work if the **powerPin** is set in the constructor.

- **void powerOn()** switch the sensor on.
- **void powerOff()** switch the sensor off.
- **void setPowerDelay(uint8_t powerDelay = 100)** delay in microseconds
in powerOn() to stabilize the rain sensor.
Default is 100 microseconds.
- **uint8_t getPowerDelay()** returns the set value.

The powerPin is used to switch the LM393 ON and OFF so the sensor is powered
only when the sensor is read.
This reduces corrosion and minimizes the usage of energy.
Note: when the power is OFF, the digital-out cannot be used e.g. for interrupts.
So check what your project needs.

Note: the powerOn() default delays for 100 us to give the LM393 time to stabilize.
Adjust this time if you want to optimize performance, power consumption or corrosion.
Values can be 0 .. 255.


### Analysis

- **void setDryReference(float dryRef)** used to calibrate the voltage when the sensor is dry.
Use **read()** to read / calibrate the voltage when the sensor is dry.
If not explicitly set, the max ADC voltage is used.
- **void getDryReference()** returns the set value.
- **float percentage()** returns the last **read()** converted to a percentage.
Note one needs to call read() again to get a new value as this uses a cached value.
- **float delta()** returns the delta voltage compared to previous read.
It give the first derivative of the signal, indicating how fast does the signal rises or falls.
- **bool setLevel(uint8_t nr, uint16_t millivolts)** allows a user to set 4 voltage levels in milliVolts.
Level 0 can't be set.
- **uint8_t getLevel()**
Returns the level of the current cached voltage.
See example.

The library allows the user to set 4 thresholds or levels for the **getLevel()** function.
These 4 levels + 1 zero level can help to control behaviour of a system at a certain level.
Typical levels are almost empty, almost full and full.
The level do not need to be on a linear mapping like 20% steps, if your project need
other levels you can define these.

Note it is possible to adjust the levels runTime with **setLevel()**


### MultiMap

For a continuous mapping one can use the **MultiMap** library.
It allows to map the voltage to any other useful unit as it can handle
even non-linearities well.
See https://github.com/RobTillaart/MultiMap


## Operation

The examples show the basic working of the functions of the library.

The rain sensor can be used in different types of projects.
Every project has a typical orientation of the sensor.

|  project         |  orientation     |  measurement  |
|:-----------------|:----------------:|:-------------:|
|  rain sensor     |  angle 30 - 45°  |  polling
|  leak detection  |  horizontal      |  interrupt - digital OUT
|  water level     |  vertical        |  polling

For other applications it depends.


## Future

#### Must

- update documentation

#### Should

- improve rain_demo_count.ino state machine
- add **uint32_t lastRead()**
- optimizations
  - a lot of floats...==> more uint16_t millivolts? (0.2.0)
- getLevel() split into level() + getLevel(nr);  //  semantics
  - breaking change == 0.2.0
  - level(0) should be settable too

#### Could

- add unit-tests
- **float readExt(float voltage)** for external ADC
  - See **ACS712** library how this can be done.
- investigate: **getLevel()** should it do a read()?
  - **setForcedRead(bool flag)** + getter
- investigate "a scale of wetness"
- investigate
  - different salinity
  - different liquids? which?
  - how linear is the device?

#### Won't (unless requested)

- example with multiMap
  - see multiMap library.
- **incrLevel(nr, amount = 1)** + **decrLevel(nr, amount = 1)**
  to allow easier runtime tuning
- investigate level-changed "event"
  - user should poll ==> keeps the lib simple.
- make the number of levels configurable
  - dynamic array allocation.?


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

