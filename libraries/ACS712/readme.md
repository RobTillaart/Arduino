
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

- **ACS712(analogPin, volts = 5.0, maxADC = 1023, mVperA = 100)** constructor. It defaults a 20 A type sensor, which is defined by the default value of mVperA. See below.
- **mA_AC(freq = 50)** blocks ~21 ms to sample a whole 50 or 60 Hz period. Since version 0.2.2 frequencies other than 50 and 60 are supported, the lower the frequency, the longer the blocking period.
- **mA_DC()** blocks < 1 ms as it just needs one analogue read.


| type sensor  | mVperA | LSB 5V-10bit |
|:-------------|:------:|:------------:|
|  5 A         |  185   |  ~25 mA      |
|  20 A        |  100   |  ~50 mA      |
|  30 A        |  66    |  ~75 mA      |


#### Midpoint

- **setMidPoint(mp)** sets midpoint for the ADC
- **autoMidPoint(uint8_t freq = 50)** Auto midPoint, assuming zero DC current or any AC current. Note it will block for 2 periods. Since version 0.2.2 frequencies other than 50 and 60 are supported.
- **getMidPoint()** read back the value set / determined.
- **incMidPoint()** manual increase midpoint, e.g. useful to manually adjust the midPoint in an interactive application.
- **decMidPoint()** manual decrease midpoint


#### Formfactor 

Also known as crest factor;  affects AC signals only. 

- **setFormFactor(ff = ACS712_FF_SINUS)** manually sets form factor  0.0 .. 1.0, 
- **getFormFactor()** returns current form factor

The library has a number of predefined form factors

|  definition          | value         | approx | notes   |
|:---------------------|:--------------|:------:|:--------|
| ACS712_FF_SINUS      | 1.0 / sqrt(2) | 0.707  | default |
| ACS712_FF_SQUARE     | 1.0           | 1.000  |         |
| ACS712_FF_TRIANGLE   | 1.0 / sqrt(3) | 0.577  |         |
|                      |               |        |         |

It is important to measure the current with a calibrated multimeter
and determine / verify the form factor of the signal. This can help
to improve the quality of your measurements.


#### Noise

Default = 21 mV.

- **setNoisemV(noisemV = 21)** set noise level, is used to determine zero level e.g. in AC measurements.
- **getNoisemV()** returns set value


#### mV per Ampere

Both for AC and DC. Is defined in the constructor and depends on 

- **setmVperAmp(mva)** sets the milliVolt per Ampere measured.
- **getmVperAmp()** returns set value.

Typical values see constructor above.


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
- int point2point(uint8_t freq) function for AC. Is part of mA_AC() already. Needs extra global variables?
- float frequency as parameter? Or detect zero crossing to start?
- external analogue read support? separate class?
