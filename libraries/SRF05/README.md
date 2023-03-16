
[![Arduino CI](https://github.com/RobTillaart/SRF05/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/SRF05/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/SRF05/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/SRF05/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/SRF05/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/SRF05/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/SRF05.svg?maxAge=3600)](https://github.com/RobTillaart/SRF05/releases)


# SRF05

Arduino library for the SRF05 distance sensor and compatibles.


## Description

The library allows to adjust to the speed of sound (sos).
Reasons to use a different value are temperature, humidity, type of gas, composition etc.

Default value for the speed of sound is set to 340 m/s. (~15°C)


#### Effect temperature and humidity

Several correction formulas for the speed of sound are available on the internet.

```
// temperature in °C
v = 331.3 + 0.606 * temperature (m/s)
v = 331.4 + 0.606 * temperature + 0.0124 * rel_humidity (m/s)
v = 20.05 * sqrt(273.16 + temperature) (m/s)
```

In fact humidity has an effect which increases with temperature so the formula is more complex.
See - https://forum.arduino.cc/t/ultrasonic-sensor-to-determine-water-level/64890/12


| temp |   10%  |   20%  |   30%  |   40%  |   50%  |   60%  |   70%  |   80%  |   90%  | notes |
|:----:|:------:|:------:|:------:|:------:|:------:|:------:|:------:|:------:|:------:|:------|
| -30  | 313.5  | 329.5  | 312.9  | 329.6  | 313.0  | 329.6  | 313.1  | 329.7  | 329.7  | extrapolated indication 
| -25  | 316.5  | 332.6  | 316.0  | 332.7  | 316.1  | 332.7  | 316.2  | 332.8  | 332.9  | extrapolated indication 
| -20  | 319.5  | 335.6  | 319.1  | 335.7  | 319.2  | 335.9  | 319.3  | 336.0  | 336.0  | extrapolated indication 
| -15  | 322.5  | 330.5  | 322.2  | 330.6  | 322.3  | 330.6  | 322.4  | 330.7  | 330.7  | extrapolated indication 
| -10  | 325.5  | 333.6  | 325.3  | 333.7  | 325.4  | 333.7  | 325.5  | 333.8  | 333.9  | extrapolated indication 
| -5   | 328.5  | 336.6  | 328.4  | 336.7  | 328.5  | 336.9  | 328.6  | 337.0  | 337.0  | extrapolated indication 
|  0   | 331.5  | 331.5  | 331.5  | 331.6  | 331.6  | 331.6  | 331.7  | 331.7  | 331.7  |
|  5   | 334.5  | 334.6  | 334.6  | 334.7  | 334.7  | 334.7  | 334.8  | 334.8  | 334.9  |
|  10  | 337.5  | 337.6  | 337.7  | 337.7  | 337.8  | 337.9  | 337.9  | 338.0  | 338.0  |
|  15  | 340.5  | 340.6  | 340.7  | 340.8  | 340.9  | 341.0  | 341.1  | 341.2  | 341.2  |
|  20  | 343.5  | 343.6  | 343.7  | 343.9  | 344.0  | 344.1  | 344.2  | 344.4  | 344.5  |
|  25  | 346.4  | 346.6  | 346.8  | 347.0  | 347.1  | 347.3  | 347.5  | 347.6  | 347.8  |
|  30  | 349.4  | 349.6  | 349.9  | 350.1  | 350.3  | 350.5  | 350.8  | 351.0  | 351.2  |
|  35  | 352.4  | 352.6  | 353.0  | 353.2  | 353.5  | 353.7  | 354.1  | 354.4  | 354.6  | extrapolated indication 
|  40  | 355.4  | 355.6  | 356.1  | 356.3  | 356.7  | 356.9  | 357.4  | 357.8  | 358.0  | extrapolated indication 
|  45  | 358.4  | 358.6  | 359.2  | 359.4  | 359.9  | 360.1  | 360.7  | 361.2  | 361.4  | extrapolated indication 
|  50  | 361.4  | 361.6  | 362.3  | 362.5  | 363.1  | 363.3  | 364.0  | 364.6  | 364.8  | extrapolated indication 
|  55  | 364.4  | 364.6  | 365.4  | 365.6  | 366.3  | 366.5  | 367.3  | 368.0  | 368.2  | extrapolated indication 
|  60  | 367.4  | 367.6  | 368.5  | 368.7  | 369.5  | 369.7  | 370.6  | 371.4  | 371.6  | extrapolated indication 

(table based upon https://www.engineeringtoolbox.com/air-speed-sound-d_603.html)


The library has several ways to improve the quality of the measurements.
E.g. by taking the average or the median of multiple readings.
This can be set with the mode commands.

The library allows to set a correction factor to compensate for the timing of 
the **pulseIn()** function. This has in the end the same effect as changing the 
speed of sound however it is technically more correct to keep the two separated.


## Interface

```cpp
#include "SRF05.h"
```


#### Constructor

- **SRF05(const uint8_t trigger, const uint8_t echo, const uint8_t out = 0)** constructor to set the trigger and echo pin.
It is not clear what the purpose of the OUT pin is, effectively it is not used yet.


#### Configuration

- **void setSpeedOfSound(float sos)** adjust the speed of sound.
See table above.
- **float getSpeedOfSound()** return set value.
- **bool setCorrectionFactor(float factor = 1)** adjust the timing by a few percentage e.g. to adjust clocks.
Typical values are between 0.95 and 1.05 to correct up to 5%.
Should not be used to correct the speed of sound :)
Returns false if factor <= 0.
- **float getCorrectionFactor()** returns the current correction factor.


#### Operational mode

Normally a single read should be OK.

- **void setModeSingle()** read a single time. 
This is the default and typical the fastest.
- **void setModeAverage(uint8_t count)** read count times and take the average.
Note: between the reads there is a delay of 1 millisecond.
- **void setModeMedian(uint8_t count)** read count times and take the median. 
count must between 3 and 15 otherwise it is clipped.
Note: between the reads there is a delay of 1 millisecond.
- **void setModeRunningAverage(float alpha)** use a running average algorithm 
with a weight alpha. Value for alpha depends on your application.
- **uint8_t getOperationalMode()** returns the operational mode 0..3.
See table below.


|  operational mode        |  value  |  Notes  |
|:-------------------------|:-------:|:-------:|
|  SRF05_MODE_SINGLE       |    0    |         |
|  SRF05_MODE_AVERAGE      |    1    |         |
|  SRF05_MODE_MEDIAN       |    2    |         |
|  SRF05_MODE_RUN_AVERAGE  |    3    |         |
|                          |  other  |  error  |


#### Get distance

- **uint32_t getTime()** returns distance in microseconds.
- **uint32_t getMillimeter()** returns distance in millimetre.
- **float getCentimeter()** returns distance in centimetre.
- **float getMeter()** returns distance in meter.
- **float getInch()** returns distance in inches. (1 inch = 2.54 cm).
- **float getFeet()** returns distance in feet. (1 feet = 12 inch).


#### Experimental - setTriggerLength

Since 0.1.4 two experimental functions are added to tune the length
of the trigger signal. 
The idea is that shorter triggers can be used with harder surfaces
or short distances. Longer trigger for longer distances.

The effects and value of adjusting trigger length needs investigation.
Experiences are welcome.

- **void setTriggerLength(uint8_t length = 10)** default length == 10 us.
- **uint8_t getTriggerLength()** returns set length.


#### Experimental - calibration

Put the sensor at exactly 1.00 meter from a wall, and based 
upon the timing it will give an estimate for the speed of sound. 
0.1.2 version seems to be accurate within 5 %.

- **float determineSpeedOfSound(uint16_t distance)** distance is between 
sensor and the wall - not forth and back.
The distance is averaged over 16 measurements.

Function can be used to compensate for temperature and humidity.


#### Performance

Assumes default speed of sound of 340 m/sec.

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

to be elaborated.


## Operational

See examples.


## Future

#### Must

- investigate purpose/possibilities of the OUT pin.


#### Should

- add examples
  - DHT22 and the formula for SOS
- add **float calcSOS(float temp, float humidity = 0)**
- investigate 
  - should **setSpeedOfSound(float sos)** return bool if sos <=0 ?
  - value of **setTriggerLength()**


#### Could

- set default SOS to an SOS from the table instead of 340.
- add example to determine the correction factor?
- delay(1) in average configurable?


#### Wont

- print feet as 3'2" or  3-7/8 feet (is that needed in this lib)
  - in printHelpers ?
- fix magic conversion numbers.
- add ```float lastValue()``` ?  
  - not all paths update this variable.
- add ```float delta()``` difference with last value.
  - how to handle different units? or only time?