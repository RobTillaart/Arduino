
[![Arduino CI](https://github.com/RobTillaart/SRF05/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/SRF05/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/SRF05/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/SRF05/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/SRF05/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/SRF05.svg)](https://github.com/RobTillaart/SRF05/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/SRF05/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/SRF05.svg?maxAge=3600)](https://github.com/RobTillaart/SRF05/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/SRF05.svg)](https://registry.platformio.org/libraries/robtillaart/SRF05)


# SRF05

Arduino library for the SRF05 distance sensor and compatibles.


## Description

This library implements a API for a PING type of sensor. 
It is expected to work for quite a range of them. 
Till version 0.2.0 of the library, it only supported the SRF04 compatibility mode which uses a 
separate **TRIGGER** and **ECHO** pin. 

Version 0.3.0 implements support for the SRF05 mode in which **TRIGGER** and **ECHO** are the same.
One need to connect the MODE pin to GND to select this mode in the device.
Note that not all PING type of sensors will support the single pin mode.
See also Connection section below.

An important feature of this library is that it allows to adjust the speed of sound (SOS).
Reasons to use a different value for the speed of sound is that it varies depending on
temperature, humidity, composition of the air, air pressure, other type of gas, etc.

Default value for the speed of sound is set to **340 m/s**. (air, ~15°C, sea level pressure)

Since the version 0.2.0 the library has an interpolation formula to calculate the speed of sound
given a temperature and humidity.

The library has several ways to adjust / improve the quality of the measurements.
E.g. by taking the average or the median of multiple readings, there will be less noise.
This can be set with the different mode commands.

The library allows to set a correction factor to compensate for the timing of 
the **pulseIn()** function. This has in the end the same effect as changing the 
speed of sound however it is technically more correct to keep the two separated.


#### Connection 

How to connect:
- https://www.robot-electronics.co.uk/htm/srf05tech.htm


#### Effect temperature and humidity

Several correction formulas for the speed of sound are available on the internet
to adjust the speed for temperature (°C) and humidity (%RH).

```
// temperature in °C
v = 331.3 + 0.606 * temperature (m/s)
v = 331.4 + 0.606 * temperature + 0.0124 * rel_humidity (m/s)
v = 20.05 * sqrt(273.16 + temperature) (m/s)
```

In fact humidity has an effect which increases with temperature so the formula is more complex.
See discussion - https://forum.arduino.cc/t/ultrasonic-sensor-to-determine-water-level/64890/12

Note that the speed of sound is also altered by air pressure (sea level .. high in sky)
and wind speed. The latter is a bit compensated for, as the acoustic pulse will go one time 
"against" the wind and one time "with" the wind.


#### Table speed of sound for temperature and humidity in air at sea level.

(table redone completely in 0.2.0)

Temperature in Celsius, Humidity in %, constant pressure == 1013 mBar, SOS in m/s.

| temp |    0%  |   10%  |   20%  |   30%  |   40%  |   50%  |   60%  |   70%  |   80%  |   90%  |  100%  |
|:----:|:------:|:------:|:------:|:------:|:------:|:------:|:------:|:------:|:------:|:------:|:------:|
| -40  | 306.22 | 306.23 | 306.24 | 306.25 | 306.26 | 306.26 | 306.27 | 306.28 | 306.29 | 306.30 | 306.31 |
| -35  | 309.49 | 309.50 | 309.50 | 309.51 | 309.52 | 309.52 | 309.53 | 309.54 | 309.54 | 309.55 | 309.56 |
| -30  | 312.72 | 312.73 | 312.73 | 312.74 | 312.74 | 312.75 | 312.75 | 312.76 | 312.76 | 312.77 | 312.78 |
| -25  | 315.92 | 315.93 | 315.93 | 315.94 | 315.94 | 315.95 | 315.95 | 315.96 | 315.96 | 315.97 | 315.98 |
| -20  | 319.09 | 319.10 | 319.10 | 319.11 | 319.12 | 319.12 | 319.13 | 319.14 | 319.14 | 319.15 | 319.16 |
| -15  | 322.22 | 322.23 | 322.24 | 322.25 | 322.26 | 322.27 | 322.28 | 322.29 | 322.30 | 322.31 | 322.32 |
| -10  | 325.33 | 325.34 | 325.36 | 325.37 | 325.39 | 325.40 | 325.42 | 325.43 | 325.45 | 325.46 | 325.47 |
|  -5  | 328.40 | 328.42 | 328.44 | 328.47 | 328.49 | 328.51 | 328.53 | 328.56 | 328.58 | 328.60 | 328.62 |
|   0  | 331.45 | 331.48 | 331.51 | 331.54 | 331.57 | 331.61 | 331.64 | 331.67 | 331.70 | 331.73 | 331.76 |
|   5  | 334.47 | 334.52 | 334.56 | 334.61 | 334.65 | 334.70 | 334.74 | 334.79 | 334.83 | 334.88 | 334.93 |
|  10  | 337.46 | 337.52 | 337.58 | 337.64 | 337.70 | 337.76 | 337.82 | 337.88 | 337.94 | 338.00 | 338.06 |
|  15  | 340.43 | 340.52 | 340.61 | 340.70 | 340.79 | 340.88 | 340.97 | 341.06 | 341.15 | 341.24 | 341.33 |
|  20  | 343.37 | 343.49 | 343.62 | 343.74 | 343.87 | 343.99 | 344.12 | 344.24 | 344.37 | 344.49 | 344.61 |
|  25  | 346.29 | 346.46 | 346.63 | 346.80 | 346.97 | 347.14 | 347.31 | 347.48 | 347.65 | 347.82 | 347.99 |
|  30  | 349.18 | 349.41 | 349.64 | 349.87 | 350.10 | 350.32 | 350.55 | 350.78 | 351.01 | 351.24 | 351.47 |
|  35  | 352.04 | 352.35 | 352.65 | 352.96 | 353.27 | 353.57 | 353.88 | 354.19 | 354.49 | 354.80 | 355.11 |
|  40  | 354.89 | 355.29 | 355.70 | 356.10 | 356.50 | 356.91 | 357.31 | 357.71 | 358.12 | 358.52 | 358.92 |
|  45  | 357.71 | 358.24 | 358.76 | 359.29 | 359.82 | 360.34 | 360.87 | 361.40 | 361.92 | 362.45 | 362.98 |
|  50  | 360.51 | 361.19 | 361.87 | 362.55 | 363.23 | 363.92 | 364.60 | 365.28 | 365.96 | 366.64 | 367.32 |
|  55  | 363.29 | 364.16 | 365.04 | 365.91 | 366.78 | 367.66 | 368.53 | 369.40 | 370.28 | 371.15 | 372.02 |
|  60  | 366.05 | 367.16 | 368.27 | 369.38 | 370.49 | 371.59 | 372.70 | 373.81 | 374.92 | 376.03 | 377.14 |


**Notes on table**
- values for 0% are calculated with ```sos = 331.45 * sqrt(1 + T/273.16);  //  T in Celsius```
- values for 90% are calculated with - https://sengpielaudio.com/calculator-airpressure.htm
  - these match - https://www.engineeringtoolbox.com/air-speed-sound-d_603.html
- the other values are linear interpolated between the 0 and 90 column (100% is extrapolated)
- the table range is from -40 to +60 as that covers 99% of the "normal" temperatures occuring.

For temperatures under 0°C the effect of humidity goes to zero as we look how the difference
between 90% and 0% decreases when temperature drops.

The function **float calculateSpeedOfSound()** uses two interpolations derived from the table above.
The function has no look-up table and uses no lookup table / RAM.
This function returns a speed of sound with an overall error margin less than 1%, and mostly even 
lower than 0.5% compared to the numbers above.


#### Related

- https://www.robot-electronics.co.uk/htm/srf05tech.htm (good description of the sensor)


## Interface

```cpp
#include "SRF05.h"
```

#### Constructor

- **SRF05(const uint8_t trigger, const uint8_t echo = 0)** constructor to set the trigger and echo pin.
The echo pin can be left out, or set to the same as the trigger pin.
In total one can do it in three ways.

```cpp
const int trigger = 7;
const int echo    = trigger;

SRF05 SRF(trigger, echo);
SRF05 SRF(trigger, trigger);
SRF05 SRF(trigger);
```

To select single pin mode in the hardware the MODE pin of the device must be connected to GND.
For the two pin (compatibility) mode the MODE pin must be left floating.


#### Configuration

- **void setSpeedOfSound(float sos = 340)** adjust the speed of sound in meters per second (m/s).
See table above.
The function has **no range check** and accepts even negative values.
This will cause a negative sign in the distances which can be useful sometimes when you have 
two sensors in opposite directions.
- **float getSpeedOfSound()** return set value (m/s)
- **bool setCorrectionFactor(float factor = 1)** adjust the timing by a few percentage e.g. to adjust clocks.
Typical values are between 0.95 and 1.05 to correct up to 5%.
Should not be used to correct the speed of sound :)
Returns false if factor is negative, <= 0.
- **float getCorrectionFactor()** returns the current correction factor.


#### Operational mode

Normally a single read should be sufficient, but the library has more modi.

- **void setModeSingle()** read a single time. 
This is the default and typical the fastest.
- **void setModeAverage(uint8_t count)** read count times and take the average.
Note: between the reads there is a default delay of 1000 microseconds.
- **void setModeMedian(uint8_t count)** read count times and take the median. 
count must between 3 and 15 otherwise it is clipped.
Note: between the reads there is a default delay of 1000 microseconds.
- **void setModeRunningAverage(float alpha)** use a running average algorithm 
with a weight alpha. Value for alpha depends on your application.
Alpha must be larger than zero and smaller or equal to one. Alpha == <0..1]
Lower alpha averages great for static distances, a higher alpha is better
suited for changing distances.
- **uint8_t getOperationalMode()** returns the operational mode 0..3.
See table below.
- **void setSampleInterval(uint16_t microSeconds = 1000)** changes the interval used
in **SRF05_MODE_AVERAGE** and **SRF05_MODE_MEDIAN**.
Default is 1000 us == 1 milliSecond. Maximum is 65535 microseconds.
- **uint16_t getSampleInterval()** return set interval.

|  Operational mode        |  Value  |  Notes  |
|:-------------------------|:-------:|:-------:|
|  SRF05_MODE_SINGLE       |    0    |
|  SRF05_MODE_AVERAGE      |    1    |  default sample interval 1000 us
|  SRF05_MODE_MEDIAN       |    2    |  default sample interval 1000 us
|  SRF05_MODE_RUN_AVERAGE  |    3    |
|                          |  other  |  error

If other modi are needed, please open an issue and I see if it fits. 
Of course one can create more elaborated processing of measurements 
outside the library.


#### Get distance

- **uint32_t getTime()** returns distance in microseconds.
This is the core measurement function, the next five are wrappers 
around this one.
- **uint32_t getMillimeter()** returns distance in millimetre.
- **float getCentimeter()** returns distance in centimetre.
- **float getMeter()** returns distance in meter.
- **float getInch()** returns distance in inches. (1 inch = 2.54 cm).
- **float getFeet()** returns distance in feet. (1 feet = 12 inch).
- **float getYards()** returns distance in yards. (1 yard = 3 feet = 36 inch).


#### Experimental - setTriggerLength

Since 0.1.4 two experimental functions are added to tune the length
of the trigger signal. 
The idea is that shorter triggers can be used with harder surfaces
or short distances. Longer trigger thus for longer distances.

The effects and value of adjusting trigger length needs investigation.
Experiences are welcome.

- **void setTriggerLength(uint8_t length = 10)** default length == 10 us.
- **uint8_t getTriggerLength()** returns set length.


#### Experimental - calibration

Put the sensor at exactly 1.00 meter from a wall, and based 
upon the timing it will give an estimate for the speed of sound. 
0.1.2 version seems to be accurate within 5 %.

- **float determineSpeedOfSound(float distance, uint8_t count = 64)** distance is between 
sensor and the wall, single trip, not forth and back.
The distance is in meters, returns meters/second.
The distance is averaged over count measurements.

This function can be used to compensate for temperature, humidity
or even other types of gas (e.g. N2 only)


#### Experimental - calculateSpeedOfSound

- **float calculateSpeedOfSound(float temperature, float humidity)**
Calculates the speed of sound given a temperature in Celsius (-40..60) 
and relative humidity (0..100).

The function uses an interpolation formula derived from the table above.
This returns a speed with an error margin less than 1%, and for the most
part it is even better than 0.5%.

Be aware that especially humidity sensors have an accuracy, often in the 
range from two to five percent. So it won't get much better.


#### Performance

Assumes default speed of sound of 340 m/sec.

Expected pulse timing.

| distance (cm) | time (us) |
|:-------------:|----------:|
|        1      |     29.4  |
|        2      |     58.8  |
|        5      |    147.1  |
|       10      |    294.1  |
|       20      |    588.2  |
|       50      |   1470.6  |
|      100      |   2941.2  |
|      200      |   5882.4  |
|      300      |   8823.5  |
|      400      |  11764.7  |
|      500      |  14705.9  |

To be elaborated.


## Operational

See examples.


## Future

#### Must

- investigate purpose/possibilities of the OUT pin.

#### Should

- add examples
  - DHT22 and the formula for SOS
- investigate effect of wind (speed of air) on the speed of sound.
- investigate 
  - value of **setTriggerLength()**
- investigate "guard time" between reads of 50 ms (20x /sec max).


#### Could

- set default SOS to an SOS from the table instead of 340.
  - function **begin(T, H)** ?
- add example to determine the correction factor?
- add uint16_t **PulseTimeOut** = 200;  //  milliSeconds?
  - void setPulseTimeOut(uint16_t milliSeconds = 200);
  - uint16_t getPulseTimeOut();


#### Wont

- should **setSpeedOfSound(float sos)** return bool if sos <=0 ?
- print feet as 3'2" or  3-7/8 feet (is that needed in this lib)
  - see printHelpers lib **printFeet(float feet)**
- fix magic conversion numbers.
- add ```float lastValue()``` ?  
  - not all paths update this variable.
- add ```float delta()``` difference with last value.
  - how to handle different units? or only time?


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

