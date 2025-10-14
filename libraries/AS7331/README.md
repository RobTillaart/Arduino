
[![Arduino CI](https://github.com/RobTillaart/AS7331/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AS7331/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AS7331/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AS7331/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AS7331/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AS7331.svg)](https://github.com/RobTillaart/AS7331/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AS7331/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AS7331.svg?maxAge=3600)](https://github.com/RobTillaart/AS7331/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AS7331.svg)](https://registry.platformio.org/libraries/robtillaart/AS7331)


# AS7331

Arduino library for the I2C AS7331 UV sensor. UV-A, UV-B, UV-C 


## Warnings

**Always take precautions as UV radiation can cause sunburn, eye damage and other severe problems**.

Do not expose yourself to the sun or any other UV source too long.

When working with UV light, natural or artificial (TL LED laser a.o.) use appropriate shielding. Do not look right into UV light sources (e.g. the sun). Do not expose yourself to any UV source too long.

### Datasheet warning:

_Do not apply this product to safety protection devices or emergency stop equipment,
and any other applications that may cause personal injury due to the product's failure._


## Description

**Experimental**

This Arduino library is for the I2C AS7331 UV sensor.
The AS7331 is a device that measures UV-A, UV-B and UV-C and internal temperature (Celsius) simultaneously.

|  Channel  |  Peak wavelength  |  Range            |
|:---------:|:-----------------:|:------------------|
|    UVC    |  λ = 260 nm       |  240 nm – 280 nm  |
|    UVB    |  λ = 300 nm       |  280 nm – 315 nm  |
|    UVA    |  λ = 360 nm       |  315 nm – 410 nm  |

See datasheet for detailed sensitivity graphs.

The library allows the user to set the **gain** from 1 to 2048 and a **conversion time** 
from 1 millisecond up to 16384 milliseconds (16+ seconds).
The sensor can be used in a **MANUAL** or **CONTINUOUS** mode and has a **RDY** pin that can be used
for an interrupt to indicate conversion is ready. Polling mode is also supported.
In MANUAL mode one needs to restart a measurement manually.

Feedback as always is welcome.

Note: The library is not verified against a calibrated UV source, so use with care. 

Datasheet used: v4-00, 2023-Mar-24.


### Disclaimer

In version 0.3.0 access to the "missing" registers of the AS7331 is implemented, 
however proper working of these registers are not tested. So use them with care.

Also the SYND mode is not tested (my choice / priority), so if you do, please 
provide feedback about what works and what not.  

In short, the library is still work in progress.


### Breaking change 0.2.0

The 0.1.0 version is obsolete as it just did not work. 
Version 0.2.0 has been verified to work in MANUAL, CONTINUOUS and SYNS mode.
Examples have been added to show the operation of the library.


### Angle sensitivity

Angle of incidence is +-10 degrees, so Cosine law is not really needed (imho).
Search for Lambert’s Cosine Law on Wikipedia for details.


### Special chars.

µ = ALT-230,
λ = ALT-955,
Via emoji tab: WIN .  => Ω tab => search for λ)


### Related

UV related

- https://en.wikipedia.org/wiki/Ultraviolet
- https://en.wikipedia.org/wiki/Ultraviolet_index
- https://github.com/RobTillaart/AnalogUVSensor 
- https://github.com/RobTillaart/AS7331 - profi UVA, UVB, UVC sensor.
- https://github.com/RobTillaart/LTR390_DFR  (DF Robotics variant)
- https://github.com/RobTillaart/LTR390_RT   (native LTR390)
- https://github.com/RobTillaart/ML8511

Other

- https://github.com/RobTillaart/map2colour - for a continuous colour scale
- https://github.com/RobTillaart/Temperature - conversions.


### Tested

This library is partially tested with hardware Arduino UNO R3.
As there is no board specific code, it is expected to work on other boards too.
Examples work but not all functions of the library are verified (or calibrated).
See also disclaimer.

As said before, feedback is welcome.


## I2C

If the library does not work with your board, you should check the INIT_IDX
section (far) below. Check the datasheet for the details.

### I2C Performance

The datasheet states that the device support up to 400 kHz fast mode.
(not verified the actual range)
As the exposure time "blocks the device" quite some time, the most relevant 
function to test seems to be **conversionReady()** as that can be called 
multiple times in a project. 
A small performance sketch shows that **getUVA_uW()** performs similar, which
is logical as it also fetches 2 bytes (0.2.0 version).

|  Clock     |  time (us)  |  Notes  |
|:----------:|:-----------:|:--------|
|   100 kHz  |     548     |  default
|   200 kHz  |     320     |
|   300 kHz  |     232     |
|   400 kHz  |     196     |  max datasheet
|   500 kHz  |     176     |
|   600 kHz  |     160     |
|   700 kHz  |     148     |
|   800 kHz  |     140     |

Conclusion, running at 400 kHz (max datasheet) is more than 2.5 times faster.
Going beyond the 400 kHz could save another ~25% but it is not known how 
this affect the quality of the measurements and/or the lifetime of the device.


### I2C address

The device has two address lines allowing for up to four I2C addresses,
on one I2C bus.

|  A0  |  A1  |  Address  |
|:----:|:----:|:---------:|
|   0  |   0  |    0x74   |
|   1  |   0  |    0x75   |
|   0  |   1  |    0x76   |
|   1  |   1  |    0x77   |

In a small test it became evident that the sensor under test did not appreciate
runtime changing of the address pins. 
So this trick cannot be used to "multiplex" multiple devices.


### I2C multiplexing

Sometimes you need to control more devices than possible with the default
address range the device provides.
This is possible with an I2C multiplexer e.g. TCA9548 which creates up
to eight channels (think of it as I2C subnets) which can use the complete
address range of the device.

Drawback of using a multiplexer is that it takes more administration in
your code e.g. which device is on which channel.
This will slow down the access, which must be taken into account when
deciding which devices are on which channel.
Also note that switching between channels will slow down other devices
too if they are behind the multiplexer.

- https://github.com/RobTillaart/TCA9548


## Interface

```cpp
#include "AS7331.h"
```

### Constructor

- **AS7331(uint8_t address, TwoWire \*wire = &Wire)** set the I2C address to use and optional select an I2C bus.
- **bool begin()** resets the device to the default configuration.
Returns true if the device address can be found on I2C bus.
  - **AS7331_MODE_MANUAL**
  - **AS7331_GAIN_2x**
  - **AS7331_CONV_064**
- **bool isConnected()** Returns true if the device address can be found on I2C bus.
- **uint8_t getAddress()** Returns the device address set in the constructor.
- **void softwareReset()** reset to initial state.


### Mode

Note: these functions only work in CONFIGURATION MODE.

- **void setMode(uint8_t mode = AS7331_MODE_MANUAL)** idem. Manual mode is default.
- **uint8_t getMode()** returns the set mode from device.

|  Mode                    |  value  |  Notes  |
|:-------------------------|:-------:|:--------|
|  AS7331_MODE_CONTINUOUS  |   0x00  |
|  AS7331_MODE_MANUAL      |   0x01  |
|  AS7331_MODE_SYNS        |   0x02  |  not supported / tested yet
|  AS7331_MODE_SYND        |   0x03  |  not supported / tested yet


### Standby and PowerDown

For temporary saving of energy one can put the device in a standby mode.
Standby works in MEASUREMENT MODE only.

Read the datasheet for the details, e.g. page 20 figure 14.

- **void setStandByOn()** idem. (set Standby)
- **void setStandByOff()** idem. (Idle, or convert or ..)
- **uint8_t getStandByMode()** returns 0 == StandBy, 1 == Idle, Convert ...

Maximum saving of energy can be reached with powerDown.
These power functions works in both CONFIGURATION and MEASUREMENT MODE

- **void powerDown()** idem.
- **void powerUp()** idem.

Table power usage indication, from datasheet page 10.

|  State              |   Usage  |  Notes  |
|:--------------------|---------:|:--------|
|  PowerDown          |    1 uA  |
|  StandBy            |  970 uA  |
|  Configuration      |    ?     |  same as Measurement ?
|  Measurement (run)  |    2 mA  |
|  Measurement (idle) |    ?     |  same as Measurement ?


### Gain

Note: these functions only work in CONFIGURATION MODE.

The gain parameter is 0..11, which goes from 2048x down to 1x in powers of 2.
Note the factors decrease while the gain value increases.
See table below.
  
- **bool setGain(uint8_t gain)** sets the gain, if value > 11 the
function returns false.
- **uint8_t getGain()** returns the set value from device.

|  Define             |  Value  |  Notes  |
|:--------------------|:-------:|:--------|
|  AS7331_GAIN_1x     |   11    |
|  AS7331_GAIN_2x     |   10    |  default, not with 8 MHz
|  AS7331_GAIN_4x     |    9    |  
|  AS7331_GAIN_8x     |    8    |
|  AS7331_GAIN_16x    |    7    |
|  AS7331_GAIN_32x    |    6    |
|  AS7331_GAIN_64x    |    5    |
|  AS7331_GAIN_128x   |    4    |
|  AS7331_GAIN_256x   |    3    |
|  AS7331_GAIN_512x   |    2    |
|  AS7331_GAIN_1024x  |    1    |
|  AS7331_GAIN_2048x  |    0    |

See also section Internal Clock Frequency below.

Read the datasheet for details (7.4 Transfer function).


### Timing conversion (Tconv)

Note: these functions only work in CONFIGURATION MODE.

The convTime parameter (exposure time) is 0..15, which goes from 1 millisecond
up to 16384 millisecond (~16 seconds). See table below.

Note value 15 is 1 millisecond like value 0 and in fact currently uses value 0 (overruled).
The difference between value 15 and 0 needs to be investigated.

- **void setConversionTime(uint8_t convTime)** set conversion time (table below), 
if the value > 15 the function returns false.
- **uint8_t getConversionTime()** returns set value.

The number in the define indicates the milliseconds of the conversion / exposure.

Resolutions above 16 bit need to be investigated how to read them properly.

|  Define             |   msec  |  Value  |  Bits   |  Notes  |
|:--------------------|:-------:|:-------:|:-------:|:--------|
|  AS7331_CONV_001    |      1  |    0    |   10    |
|  AS7331_CONV_002    |      2  |    1    |   11    |
|  AS7331_CONV_004    |      4  |    2    |   12    |
|  AS7331_CONV_008    |      8  |    3    |   13    |
|  AS7331_CONV_016    |     16  |    4    |   14    |
|  AS7331_CONV_032    |     32  |    5    |   15    |
|  AS7331_CONV_064    |     64  |    6    |   16    |  default
|  AS7331_CONV_128    |    128  |    7    |   17    |  Not supported.
|  AS7331_CONV_256    |    256  |    8    |   18    |  Not supported.
|  AS7331_CONV_512    |    512  |    9    |   19    |  Not supported.
|  AS7331_CONV_1024   |   1024  |   10    |   20    |  Not supported.
|  AS7331_CONV_2048   |   2048  |   11    |   21    |  Not supported.
|  AS7331_CONV_4096   |   4096  |   12    |   22    |  Not supported.
|  AS7331_CONV_8192   |   8192  |   13    |   23    |  Not supported.
|  AS7331_CONV_16384  |  16384  |   14    |   24    |  Not supported.
|  AS7331_CONV_001xx  |      1  |   15    |   10    |  1 millisecond (not supported yet).


Read the datasheet for details (7.4 Transfer function).


### DeviceID

- **uint8_t getDeviceID()** expect to return 0x21.
Can be used to test reading from device (debug).


### Mode control and start measurements

- **void startMeasurement()** starts a new measurement, by explicitly setting 
the MEASUREMENT MODE and trigger the Start bit.
- **void stopMeasurement()** idem. (to be tested).
- **void setConfigurationMode()** forces the mode to CONFIGURATION MODE. 
Needed to set parameters like gain and conversion time as these cannot be 
set in MEASUREMENT MODE.
- **void setMeasurementMode()** forces the mode to MEASUREMENT MODE.
Needed to make and read the measurements.
- **uint8_t readOSR()** read the OSR register (CONFIGURATION MODE) to see bits.
(mostly for debugging).


### RDY ready pin

When the AS7331 is converting the **READY** pin is LOW,
when the conversion is done the READY pin goes HIGH (short/long?).
This can be used to trigger an interrupt (RISING). 
See e.g. the **AS7331_continuous_IRQ.ino** example.

This end of conversion info is also available in the status register 
in the NDATA (New DATA) field, and can be checked with:
- **bool conversionReady()**

The RDY pin can be configured in two modi: (not tested)

- **void setRDYOpenDrain()**
- **void setRDYPushPull()** default

Read the datasheet for details.


### Internal Clock Frequency

Datasheet figure 33, page 39.

The functions affect the performance and measurement, but the parameter 
CLOCK is not yet included in the radiation math. The table below shows which gain values cannot be used. See Figure 33 Page 39 datasheet for details.

The CCLK parameter is 0..3, Note that the maximum gain (2048x) can only be used
when the CCLK == 0, the default. See datasheet page 38 for details.

- **bool setClockFrequency(uint8_t CCLK = 0)** set 0..3.
- **uint8_t getClockFrequency()**

|  Define            |  CCLK  |  Frequency  |  Notes  |
|:-------------------|:------:|:-----------:|:--------|
|  AS7331_CCLK_1024  |    0   |  1.024 MHz  |  default
|  AS7331_CCLK_2048  |    1   |  2.048 MHz  |  gain value 0 not useable
|  AS7331_CCLK_4096  |    2   |  4.096 MHz  |  gain value 0,1 not usable
|  AS7331_CCLK_8192  |    3   |  8.192 MHz  |  gain value 0,1,2,4,6,8,10 not usable


Read the datasheet for details (7.4 Transfer function).


### Read measurements

Note: these functions only work in MEASUREMENT MODE. (8.2.9)

- **float getUVA_uW()** returns in microWatts / cm2
- **float getUVB_uW()** returns in microWatts / cm2
- **float getUVC_uW()** returns in microWatts / cm2
- **float getCelsius()** returns temperature in Celsius.


#### Convenience wrappers

- **float getUVA_mW()** returns in milliWatts / cm2
- **float getUVB_mW()** returns in milliWatts / cm2
- **float getUVC_mW()** returns in milliWatts / cm2
- **float getUVA_Wm2()** returns Watt / meter2
- **float getUVB_Wm2()** returns Watt / meter2
- **float getUVC_Wm2()** returns Watt / meter2

https://en.wikipedia.org/wiki/Ultraviolet_index


### Break time

The break time is used to set a pause to the next conversion start.
This is needed to allow to fetch the data over I2C without disturbing
the actual measurements. 
This is especially useful in CONTINUOUS and SYNS mode.

The break time is defined in steps of 8 microseconds, so the range of 0..255
maps to 0 to 2048 microseconds max.

- **void setBreakTime(uint8_t breakTime)**
- **uint8_t getBreakTime()**


### Status

Note: these status functions only work in MEASUREMENT MODE. (8.2.9)

- **uint16_t readStatus()** get status back, see table below.
- **bool conversionReady()** uses NDATA status field.

Status table, see AS7331.h for defines, or datasheet for details.

|  bit   |  name          |  test  |  meaning  |
|:------:|:---------------|:------:|:----------|
|   15   |  OUTCONVOF     |    N   |  overflow 24 bit
|   14   |  MRESOF        |    N   |  overflow of one of the UV registers
|   13   |  ADCOF         |    N   |  internal overflow
|   12   |  LDATA         |    N   |  data overwritten
|   11   |  NDATA         |    Y   |  new data available - used by conversionReady().
|   10   |  NOTREADY      |    N   |  0 = ready, 1 = busy, inverted RDY pin.
|    9   |  STANDBYSTATE  |    N   |  1 = stand by
|    8   |  POWERSTATE    |    N   |  1 = power down

Only NDATA is tested / used yet as it is the most important one (imho).


### SYN pin

The SYN pin can be used in two modi:

- SYNS Mode: synchronization of start via the control signal at pin SYN.
- SYND Mode: synchronization of start and stop of measuring cycles via control signal at pin SYN.

Read the datasheet for details.

### SYNS

In the SYNS mode the SYN pin is used as an external trigger to start a measurement.
This has two advantages above the start via an I2C command.
- the command is much faster than I2C 
- it allows to start multiple sensors simultaneously.

The pulse length to start a measurement is 3 us @ 1 MHz internal clock.
The SYN pin should be drawn to GND, so do not forget the pull up resistor!

### SYND

The SYND mode is not tested, needs investigation.

In the SYND mode temperature measurement is not possible.

Read the datasheet for details.

(page 53)
- **void enableTemperature()** enable temperature
- **void disableTemperature()** disable temperature
- **bool isEnabledTemperature()** returns current status.

(page 56)
_The register EDGES becomes operative in SYND mode. After a measurement was started in SYND
mode, it defines the necessary number of additional falling edges at input SYN until the conversion is
terminated. The value EDGES = “0” is not allowed and results in the initial value “1”._

- **void setEdges(uint8_t edges)** edges = 1..255 (0 is mapped unto 1).
- **uint8_t getEdges()** returns set value.


### Divider

The Divider is not tested, needs investigation.

Read the datasheet for details (page54).

_The bit CREG2:EN_DIV enables the internal pre-scaler, which could be interesting for conversion
times more than 16-bits (CREG1:TIME ≥ 0111b) and if SYND mode is used._

- **void enableDivider()** enable divider
- **void disableDivider()** disable divider
- **bool isEnabledDivider()** returns current status


### I2C-INIT_IDX

Only to be used if I2C of the board does not work (esp reading)
Read the datasheet for details (Page 58).

- **void setInitIdx()** sets the INIT_IDX flag
- **void clrInitIdx()** clears the INIT_IDX flag


### Debug

- **uint8_t getLastError()** returns last error of low level communication.


### OUTCONV

OUTCONV = Time reference, result of conversion time measurement.

Read the datasheet for details (see chapter 7.6).

- **uint32_t getOUTCONV()** read the **OUTCONV** registers and merge them into
a single 24 bit value.



## Future

#### Must

- improve documentation
  - reorder sections
- check calibration.

#### Should

- investigate 17-24 bits measurements?
- test SYND mode (uses external timing, other math needed?)
- test different configurations (gain + Tconv)
- add functions around status bits
- add return values functions (error not in right MODE?) iso void()

#### Could

- reorganize code
- check handle Tconv == 15 case (last column) correctly.
- mention VEML6070 ?
- write documentation (code) from state machine pov?
- Split status en OSR? Yes/No?
  - not clear benefit / usage / performance ?
- extend unit tests
- add SYN pin as part of the library, parameter begin().


#### Wont

- add UV Index table => See Wikipedia.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


