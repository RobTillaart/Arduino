
[![Arduino CI](https://github.com/RobTillaart/ACS712/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/ACS712/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/ACS712.svg?maxAge=3600)](https://github.com/RobTillaart/ACS712/releases)

# ACS712

Library for the ACS712 Current Sensor - 5A, 20A, 30A


## Description

The ACS712 is a chip to measure current, both AC or DC. The chip has an
analog output that provides a voltage that is lineair with the current.
The ACS712 library supports only a built in ADC by means of analogRead().
There are 2 core functions:

- **int mA_DC()**
- **int mA_AC()**

To measure DC current a single analogRead() with some conversion math is sufficient to get
a value. To stabilize the signal analogRead() is called twice.

To measure AC current **a blocking loop for 20 millis** is run to determine the
peak to peak value which is converted to the RMS value. To convert the peak2peak
value to RMS one need the so called crest or form factor. This factor depends heavily
on the signal form. For a perfect sinus the value is sqrt(2)/2.


## Interface

#### Base

- **ACS712(analogPin, volts = 5.0, maxADC = 1023, mVperA = 100)** constructor
- **mA_AC(freq = 50)** blocks ~21 ms to sample a whole 50 or 60 Hz period.
- **mA_DC()** 

#### Midpoint

- **setMidPoint(mp)** sets midpoint ADC for DC only
- **autoMidPoint(uint8_t freq = 50)** Auto midPoint, assuming zero DC current or any AC current
- **getMidPoint()** read back setting
- **incMidPoint()** manual increase midpoint (manually)
- **decMidPoint()** manual decrease midpoint (manually)


#### Formfactor 

Also known as crest factor;  affects AC only. 
Default = 0.5 \* sqrt(2) = ~0.70710678...

- **setFormFactor(ff)** manually sets formfactor  0.0 .. 1.0
- **getFormFactor()** returns current formFactor

#### Noise

Default = 21 mV.
- **setNoisemV(noisemV)** set noise level 
- **getNoisemV()** returns set value

#### mV per Ampere

Both for AC and DC
- **setmVperAmp(mva)** sets the milliVolt per Ampere measured.
- **getmVperAmp()** returns set value.


## Test

The library is tested with the RobotDyn ACS712 20A breakout and an Arduino UNO.


## Operation

With the constructor the parameters **volts** and **maxADC (steps)** of the ADC are set
together with the **milliVolt per Ampere** value. The last parameter can be adjusted
afterwards, e.g. to callibrate this value runtime. Note this parameter affects both
AC and DC measurements.

To callibrate the zero level for DC measurements, 5 functions are available to
adjust the midPoint.

To callibrate the RMS value for AC measurements, 2 functions are available to
get and set the formFactor.

To callibrate the noise level (used for AC measurements), 2 functions are available to
get and set the noise in mV.

The examples show the basic working of the functions.

## Future

- mA_AC blocks 20 ms so might affect taskscheduling on a ESP32.
This needs to be investigated.
- int point2point(uint8_t freq) function for AC. Is part of mA_AC() allready.
