
[![Arduino CI](https://github.com/RobTillaart/ACS712/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/ACS712/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/ACS712/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/ACS712/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/ACS712/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/ACS712/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/ACS712.svg?maxAge=3600)](https://github.com/RobTillaart/ACS712/releases)


# ACS712

Library for the ACS712 Current Sensor - 5A, 20A, 30A.


## Description

The ACS712 is a chip to measure current, both AC or DC. The chip has an
analogue output that provides a voltage that is linear with the current.
The ACS712 library supports only a built in ADC by means of **analogRead()**.
There are 2 core functions:

- **int mA_DC()**
- **int mA_AC(float freq = 50)** The frequency can be set to typically 50 or 60 Hz
however other values e.g. 50.1 or 40 or 123.456 are possible.

To measure DC current a single **analogRead()** with conversion maths is sufficient to get
a value. To stabilize the signal **analogRead()** is called twice.

To measure AC current **a blocking loop for 20 milliseconds** is run to determine the
peak to peak value which is converted to the RMS value. To convert the peak2peak
value to RMS one need the so called crest or form factor. This factor depends heavily
on the signal form. For a perfect sinus the value is sqrt(2)/2 == 1/sqrt(2).
See Form factor below.


## Interface

#### Base

- **ACS712(uint8_t analogPin, float volts = 5.0, uint16_t maxADC = 1023, uint8_t mVperA = 100)** constructor. 
It defaults a 20 A type sensor, which is defined by the default value of mVperA. See below.
- **int mA_AC(float freq = 50)** blocks ~21 ms (depending on the freq) to sample a whole 50 or 60 Hz period.  
Since version 0.2.2 frequencies other integer values than 50 and 60 are supported, the lower the frequency, 
the longer the blocking period.
Since version 0.2.3 floating point frequencies are supported to tune optimally.
- **int mA_DC()** blocks < 1 ms (Arduino UNO) as it just needs one **analogRead()**.


| type sensor  | mVperA | LSB 5V-10bit |
|:-------------|:------:|:------------:|
|  5 A         |  185   |  ~25 mA      |
|  20 A        |  100   |  ~50 mA      |
|  30 A        |  66    |  ~75 mA      |


#### Midpoint

- **void setMidPoint(uint16_t mp)** sets midpoint for the ADC conversion.
- **void autoMidPoint(float freq = 50)** Auto midPoint, assuming zero DC current or any AC current. 
Note it will block for 2 periods. Since version 0.2.2 frequencies other than 50 and 60 are supported.
By setting the frequency to e.g 1, the code will sample for 2 seconds, possibly getting a better average.
- **uint16_t getMidPoint()** read the value set / determined.
- **void incMidPoint()** manual increase midpoint, e.g. useful to manually adjust the midPoint in an interactive application.
- **void decMidPoint()** manual decrease midpoint.


#### Form factor 

Also known as crest factor;  affects AC signals only. 

- **void setFormFactor(float ff = ACS712_FF_SINUS)** manually sets form factor, must be between 0.0 and 1.0
- **float getFormFactor()** returns current form factor. 

The library has a number of predefined form factors:

|  definition          | value         | approx | notes   |
|:---------------------|:--------------|:------:|:--------|
| ACS712_FF_SQUARE     | 1.0           | 1.000  |         |
| ACS712_FF_SINUS      | 1.0 / sqrt(2) | 0.707  | default |
| ACS712_FF_TRIANGLE   | 1.0 / sqrt(3) | 0.577  |         |
|                      |               |        |         |

It is important to measure the current with a calibrated multimeter
and determine / verify the form factor of the signal. 
This can help to improve the quality of your measurements.


#### Noise

Default = 21 mV.

- **void setNoisemV(uint8_t noisemV = 21)** set noise level, 
is used to determine zero level e.g. in AC measurements.
- **uint8_t getNoisemV()** returns the set value.


#### mV per Ampere

Both for AC and DC. Is defined in the constructor and depends on sensor used. 

- **void setmVperAmp(uint8_t mva)** sets the milliVolt per Ampere measured.
- **uint8_t getmVperAmp()** returns the set value.

Typical values see constructor above.


#### Experimental

- **float detectFrequency(float minimalFrequency = 40)** Detect the frequency of the AC signal.
- **void setMicrosAdjust(float factor = 1.0)** adjusts the timing of micros in **detectFrequency()**.
Values are typical around 1.0 ± 1%
- **float getMicrosAdjust()** returns the set factor. 

The minimum frequency of 40 Hz is used to sample enough time to find the minimum and maximum for 50 and 60 Hz signals. 
Thereafter the signal is sampled 10 cycles to minimize the variation of the frequency.

The **microsAdjust()** is to adjust the timing of **micros()**. 
It is only useful if one has a good source like a calibrated function generator to find the factor 
to adjust. Testing with my UNO I got a factor 0.9986.

Current version is not performance optimized. 


## Test

The library is tested with the RobotDyn ACS712 20 A breakout and an Arduino UNO.


## Operation

With the constructor the parameters **volts** and **maxADC (steps)** of the ADC are set
together with the **milliVolt per Ampere** value. The last parameter can be adjusted
afterwards, e.g. to calibrate this value runtime. Note this parameter affects both
AC and DC measurements.

To calibrate the zero level for DC measurements, 5 functions are available to
adjust the midPoint.

To calibrate the RMS value for AC measurements, 2 functions are available to
get and set the formFactor.

To calibrate the noise level (used for AC measurements), 2 functions are available to
get and set the noise in mV.

The examples show the basic working of the functions.


## Future

- mA_AC blocks 20 ms so might affect task scheduling on a ESP32.  
This needs to be investigated. Probably need a separate thread that wakes up when new analogRead is available.
- **detectFrequency** also blocks pretty long.
- int point2point(float freq) function for AC. Is part of mA_AC() already.  
Needs extra global variables, which are slower than local ones  
Or just cache the last p2p value?
- external analogue read support? separate class?
