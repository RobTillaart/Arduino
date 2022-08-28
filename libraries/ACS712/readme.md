
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
There are 3 core functions:

- **int mA_DC(cycles = 1)**
- **int mA_AC(frequency = 50, cycles = 1)** The frequency can be set to any 
value but typically to 50 or 60 Hz.
- **float mA_AC_sampling(frequency = 50, cycles = 1)** 

The parameter cycles is used to do measure multiple cycles and average them.

To measure DC current a single **analogRead()** with conversion math is 
sufficient to get a value. 
To stabilize the signal **analogRead()** is called at least twice.

To measure AC current **a blocking loop for 20 milliseconds** (50 Hz, 1 cycle) 
is run to determine the peak to peak value which is converted to the RMS value. 
To convert the peak2peak value to RMS one need the so called crest or form factor. 
This factor depends heavily on the signal form, hence its name.
For a perfect sinus the value is sqrt(2)/2 == 1/sqrt(2).
See **Form factor** below.

Note to make precise measurements, the power of both the ACS712 and the ADC of 
the processor should be as stable as possible.
That would improve the stability of the midpoint and minimizes the noise.


#### Compatibles

To investigate.

Robodyn has breakout for ACS758 - 50A,

Allegromicro offer a lot of different ones, that might be compatible.

https://www.allegromicro.com/en/products/sense/current-sensor-ics/current-sensors-innovations

If you have tested a compatible sensor, please share your experiences.
(can be done by opening an issue to update documentation)


#### Tests

The library is at least confirmed to work with the following boards:

| Device       | Voltage | ADC steps |  Notes  |
|:-------------|:-------:|:---------:|:--------|
| Arduino UNO  |  5.0V   |   1024    | tested with RobotDyn ACS712 20 A breakout.
| Arduino NANO |  5.0V   |   1024    | #18
| ESP32        |  3.3V   |   4096    | #15
| Promicro     |  5.0V   |   1024    | #15 

Please let me know of other working platforms / processors.


## Interface

#### Base

- **ACS712(uint8_t analogPin, float volts = 5.0, uint16_t maxADC = 1023, float mVperAmpere = 100)** constructor. 
It defaults a 20 A type sensor, which is defined by the default value of mVperAmpere. See table below.
Volts is the voltage used by the (Arduino) internal ADC. maxADC is the maximum output of the internal ADC.
The defaults are based upon an Arduino UNO, 10 bits ADC.
These two ADC parameters are needed to calculate the voltage output of the ACS712 sensor.
- **int mA_AC(float frequency = 50, uint16_t cycles = 1)** blocks ~21 ms to sample a whole 50 or 60 Hz period.
Note that a lower frequency, or more cycles, will increase the blocking period.
The function returns the AC current in mA.
Its working is based upon multiplying the peak2peak value by the FormFactor.
  - 0.2.2 frequencies other integer values than 50 and 60 are supported.
  - 0.2.3 floating point frequencies are supported to tune even better.
  - 0.2.8 the parameter cycles allow to average over a number of cycles.
- **float mA_AC_sampling(float frequency = 50, uint16_t cycles = 1)** blocks ~21 ms to sample a whole period.
The function returns the AC current in mA. (Note it returns a float).
Its working is based upon sampling a full period and take the square root of the average sumSquared.
This function is intended for signals with unknown Form Factor.
  - 0.2.8 the parameter cycles allow to average over a number of cycles.
- **int mA_DC(uint16_t cycles = 1)** blocks < 1 ms (Arduino UNO) as it calls **analogRead()** twice.
A negative value indicates the current flows in the opposite direction.
  - 0.2.8 the parameter cycles allow to average over a number of cycles.


#### Resolution ACS712

|  Sensor  |  mVperA  |  LSB 10bit  |  LSB 12bit  |  LSB 16bit  |
|:---------|:--------:|:-----------:|:-----------:|:-----------:|
|  5 A     |  185     |   ~25 mA    |  ~06.25 mA  |  ~0.38 mA   |
|  20 A    |  100     |  ~100 mA    |  ~25.00 mA  |  ~1.54 mA   |
|  30 A    |  66      |  ~150 mA    |  ~37.50 mA  |  ~2.31 mA   |


#### Midpoint

- **void setMidPoint(uint16_t midPoint)** sets midpoint for the ADC conversion.
- **void autoMidPoint(float frequency = 50, uint16_t cycles = 1)** Auto midPoint, 
assuming zero DC current or any AC current. 
Note the function blocks for at least 2 periods. 
By increase the number of cycles it averages multiple measurements, possibly getting a better midPoint.
This function is mandatory for measuring AC.
  - 0.2.2 frequencies other than 50 and 60 are supported.
  - 0.2.8 the parameter cycles allow to average over a number of cycles.
- **uint16_t getMidPoint()** read the value set / determined.
- **void incMidPoint()** manual increase midpoint, e.g. useful in an interactive application.
- **void decMidPoint()** manual decrease midpoint.


#### Form factor 

Also known as crest factor. Only used for signals measured with **mA_AC()**.

- **void setFormFactor(float formFactor = ACS712_FF_SINUS)** manually sets form factor.
Must typical be between 0.0 and 1.0, see constants below.
- **float getFormFactor()** returns current form factor. 

The library has a number of predefined form factors:

|  definition          | value         | approx | notes   |
|:---------------------|:--------------|:------:|:--------|
| ACS712_FF_SQUARE     | 1.0           | 1.000  |         |
| ACS712_FF_SINUS      | 1.0 / sqrt(2) | 0.707  | default |
| ACS712_FF_TRIANGLE   | 1.0 / sqrt(3) | 0.577  |         |
| ACS712_FF_SAWTOOTH   | 1.0 / sqrt(3) | 0.577  |         |

It is important to measure the current with a calibrated multimeter
and determine / verify the form factor of the signal. 
This can help to improve the quality of your measurements.

Please let me know if other crest factors need to be added.


#### Noise

Default = 21 mV.

- **void setNoisemV(uint8_t noisemV = 21)** set noise level, 
is used to determine zero level e.g. in the AC measurements with **mA_AC()**.
- **uint8_t getNoisemV()** returns the set value.


#### mV per Ampere

Used for both for AC and DC measurements. 
Its value is defined in the constructor and depends on type sensor used.
These functions allow to adjust this setting run-time.

- **void setmVperAmp(float mVperAmpere)** sets the milliVolt per Ampere measured.
- **float getmVperAmp()** returns the set value.

Typical values see "Resolution" section above, and the "voltage divider" section below.


#### Frequency detection

Experimental functionality for AC signal only!

- **float detectFrequency(float minimalFrequency = 40)** Detect the frequency of the AC signal.
- **void setMicrosAdjust(float factor = 1.0)** adjusts the timing of micros in **detectFrequency()**.
Values are typical around 1.0 ± 1%
- **float getMicrosAdjust()** returns the set factor. 

The minimum frequency of 40 Hz is used to sample for enough time to find the minimum and maximum
for 50 and 60 Hz signals. 
Thereafter the signal is sampled 10 cycles to minimize the variation of the frequency.

The **microsAdjust()** is to adjust the timing of **micros()**. 
This function is only useful if one has a good reference source like a calibrated function generator 
to find the factor to adjust. 
Testing with my UNO I got a factor 0.9986.

Current version is experimental and not performance optimized. 


## Voltage divider

As per issue #15 in which an ACS712 was connected via a voltage divider to the ADC of an ESP32.

Schema
```
ACS712 ----[ R1 ]----o----[ R2 ]---- GND
                     |
                     |
                ADC of processor
```

The voltage divider gave an error of about a factor 2 as all voltages were divided, 
including the "offset" from the **midPoint** zero current level.

By adjusting the mV per Ampere with **setmVperAmp(float mva)** the readings can be corrected 
for this "voltage divider effect".


#### Examples:

For a 20 A type sensor, 100 mV/A would be the normal value. 
After using a voltage divider one need to adjust the mVperAmp.

| R1 (ACS) | R2 (GND)  | voltage factor                  |  mVperAmp corrected     |
|:--------:|:---------:|:-------------------------------:|:-----------------------:|
|  10200   |  4745     |  4745 / (10200 + 4745) = 0.3175 |  100 \* 0.3175 = 31.75  |
|  4745    |  10200    | 10200 / (10200 + 4745) = 0.6825 |  100 \* 0.6825 = 68.25  |
|  10200   |  9800     |  9800 / (10200 + 9800) = 0.4900 |  100 \* 0.4900 = 49.00  |


**Note:** setting the midPoint correctly is also needed when using a voltage divider.


## Operation

With the constructor the parameters **volts** and **maxADC (== steps-1)** of the ADC are set
together with the **milliVolt per Ampere** value. 
The last parameter can be adjusted afterwards, e.g. to calibrate this value runtime. 
Note this parameter affects both AC and DC measurements.

To calibrate the zero level for DC measurements, 5 functions are available to
adjust the midPoint.

To calibrate the RMS value for AC measurements, 2 functions are available to
get and set the formFactor.

To calibrate the noise level (used for AC measurements), 2 functions are available to
get and set the noise in mV.

The examples show the basic working of the functions.


## Future

#### Should - 0.3.x

- fix Form Factor in **mA_AC()**
  - the value set in **setFormFactor()** is not used!
- return types
  - float for **mA_AC()** and **mA_DC()**
  - actual value for **midPoint()** functions instead of void.
- midPoint need to be a float so it can be set more exact.
- **autoMidPoint()** should have cycles parameter too.
- investigate blocking calls:
  - **mA_AC()** blocks for about 20 ms at 50 Hz.
  This might affect task scheduling on a ESP32. Needs to be investigated. 
  Probably need a separate thread that wakes up when new analogRead is available?
  - RTOS specific class?
  - **detectFrequency(float)** blocks pretty long.
- pre-calculate **\_AmperePerStep** to remove expensive float division.
  - should mA per step be more efficient?
- more testing.
- add count parameter to **mA_DC(uint8_t count = 1)** to takes multiple
  readings instead of just one. 
  When **mA_DC()** returns a float this could improve accuracy a (small) bit.
- investigate noise suppression
- update readme.md file
- should cycles be an uint8_t ?


#### Could

- do we need a **int peak2peak(float frequency)** function for AC. 
  - Is technically a part of mA_AC() already.  
  - Needs extra global variables, which are slower than local ones  
  - Or just cache the last p2p value?
  - function **measure_AC()** + getters?   
  - ==> breaking interface ==> 0.4.0 ?.
- int **getMax()** idem
- int **getMin()** idem
- ACS712X class with external ADC ( 16 or even 24 bit)
  - keep interface alike?
- external history file = changelog.md
- Should the FormFactor not be just a parameter of **mA_AC()**
  it is the only function using it.

#### Won't

- external analogue read support? separate class!
  - after this one stabilized.
- investigate support for micro-Amperes. **ACS.uA_DC()**
  - need a very stable voltage 
  - needs a 24 bit ADC 
  - default noise is already ~21mV...
  - => not feasible in normal setup.

