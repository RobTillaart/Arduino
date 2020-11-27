# ACS712

Current Sensor - 5A, 20A, 30A

## Description

The ACS712 is a chip to measure current, both AC or DC. The chip has an
analog output that provides a voltage that is lineair with the current.
The ACS712 library supports only a built in ADC by means of analogRead().
There are 2 core functions:

* **int mA_DC()**
* **int mA_AC()**

To measure DC current a single analogRead() with some conversion math is sufficient to get
a value. To stabilize the signal analogRead() is called twice.

To measure AC current **a blocking loop for 20 millis** is run to determine the
peak to peak value which is converted to the RMS value. To convert the peak2peak
value to RMS one need the so called crest or form factor. This factor depends heavily
on the signal form. For a perfect sinus the value is sqrt(2)/2.

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
