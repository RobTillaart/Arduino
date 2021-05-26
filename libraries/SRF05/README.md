
[![Arduino CI](https://github.com/RobTillaart/SRF05/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/SRF05/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/SRF05.svg?maxAge=3600)](https://github.com/RobTillaart/SRF05/releases)


# SRF05

Arduino library for the SRF05 distance sensor (and compatibles)


## Description

Class to use the distance sensor SRF05 and compatibles.

The library allows to adjust the speed of the sound waves.
Reasons to use a different value are temperature, humidity, 
type of gas, composition etc.

Default value for the SOS is set to 343 m/s. (~20°C)

Several correction formulas for the SOS are available on the internet

v = 331.3 + 0.606 \* temperature °C (m/s)
v = 331.4 + 0.606 \* temperature °C + 0.0124 \* rel_humidity  (m/s)

In fact humidity has an effect which increases with temperature.

https://forum.arduino.cc/t/ultrasonic-sensor-to-determine-water-level/64890/12


| temp |   10%  |   20%  |   30%  |   40%  |   50%  |   60%  |   70%  |   80%  |   90%  |
|:----:|:------:|:------:|:------:|:------:|:------:|:------:|:------:|:------:|:------:|
|  0   | 331.5  | 331.5  | 331.5  | 331.6  | 331.6  | 331.6  | 331.7  | 331.7  | 331.7  |
|  5   | 334.5  | 334.6  | 334.6  | 334.7  | 334.7  | 334.7  | 334.8  | 334.8  | 334.9  |
|  10  | 337.5  | 337.6  | 337.7  | 337.7  | 337.8  | 337.9  | 337.9  | 338.0  | 338.0  |
|  15  | 340.5  | 340.6  | 340.7  | 340.8  | 340.9  | 341.0  | 341.1  | 341.2  | 341.2  |
|  20  | 343.5  | 343.6  | 343.7  | 343.9  | 344.0  | 344.1  | 344.2  | 344.4  | 344.5  |
|  25  | 346.4  | 346.6  | 346.8  | 347.0  | 347.1  | 347.3  | 347.5  | 347.6  | 347.8  |
|  30  | 349.4  | 349.6  | 349.9  | 350.1  | 350.3  | 350.5  | 350.8  | 351.0  | 351.2  |

(from https://www.engineeringtoolbox.com/air-speed-sound-d_603.html)

The library has several ways to improve the quality of the measurements.
By taking the average or the median of multiple readings.

The library allows to set a correction factor to compensate for the timing of 
the **pulseIn()** function. This has in the end the same effect as changing the 
speed of sound however it is technically more correct to split the two.


## Interface

- **SRF05(const uint8_t trigger, const uint8_t echo, const uint8_t out = 0)** constructor to set the trigger and echo pin.
It is not clear yet what the purpose of the OUT pin is.


### Configuration

- **void setSpeedOfSound(float sos)** adjust the speed of sound.
- **float getSpeedOfSound()** return set value.
- **void setCorrectionFactor(float cf = 1)** adjust the timing by a few percentage e.g. to adjust clocks. Should not be used to correct the speed of sound :)
- **float getCorrectionFactor()** returns the set correction factor.


normally a single read should be OK.
- **void setModeSingle()** read single time.
- **void setModeAverage(uint8_t cnt)** read cnt times and take the average.
- **void setModeMedian(uint8_t cnt)** read cnt times and take the median. cnt = 3..15
- **void setModeRunningAverage(float alpha)** use a running average algorithm with a weight (depends on your application).
- **uint8_t getOperationalMode()** return the operational mode 0..3.


### Get distance

- **uint32_t getTime()** returns distance in microseconds.
- **uint32_t getMillimeter()** returns distance in millimeter.
- **float getCentimeter()** returns distance in centimeter.
- **float getMeter()** returns distance in meter.
- **float getInch()** returns distance in inches. (1 inch = 2.54 cm).
- **float getFeet()** returns distance in feet. (1 feet = 12 inch).


### Experimental - calibration

Experimental, put the sensor at exactly 1 meter from a wall,
and based upon the timing it will give an estimate for the
speed of sound. Current version seems accurate within 3 - 5 %.

- **float determineSpeedOfSound()**


### Experimental - configuration


### Performance

Assumes default speed of sound of 340 m/sec

| Distance | time (us) | 
|:--------:|----------:|
|    1     |     2.94  |
|    2     |     5.88  |
|    5     |    14.71  |
|    10    |    29.41  |
|    20    |    58.82  |
|    50    |   147.06  |
|    100   |   294.12  |
|    200   |   588.24  |
|    300   |   882.35  |
|    400   |  1176.47  |


## Operational

See examples..


## TODO

- print feet as 3'2" or  3-7/8 feet 
- enumerate mode operandi.
- investigate purpose of the OUT pin.
- example sketch with a DHT22 and the formula for SOS
- fix magic conversion numbers.


