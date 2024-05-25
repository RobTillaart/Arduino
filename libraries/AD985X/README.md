
[![Arduino CI](https://github.com/RobTillaart/AD985X/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AD985X/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AD985X/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AD985X/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AD985X/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AD985X.svg)](https://github.com/RobTillaart/AD985X/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AD985X/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AD985X.svg?maxAge=3600)](https://github.com/RobTillaart/AD985X/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AD985X.svg)](https://registry.platformio.org/libraries/robtillaart/AD985X)


# AD985X

Arduino library for AD9850 and AD9851 function generators.


## Description

Library for the AD9850 and AD9851 function generators.
These devices can produce a square and a sine wave 

|   type   | max freq |  phase (step size)  |  Notes  |
|:--------:|:--------:|:-------------------:|:--------|
|  AD9850  |  40 MHz  |     0..31 x 11.25°  |
|  AD9851  |  70 MHz  |     0..31 x 11.25°  | has more options.


Note that at the max frequency the devices do not give a nice sine any more.
You need to check what is acceptable for your project.

The library has a AD9850 as base class that implements the commonalities.
The AD9851 is derived and has its own **setFrequency()** methods.
Furthermore the AD9851 also has function to select the reference clock,
a feature the AD9850 does not have. 
This feature improves the tuning for both low and high frequencies.

**Warning**
The library is not suitable for AD9852 as that is a function generator with
way more functionality.

Note: mainly tested on Arduino UNO.


#### 0.5.0 Breaking change

Version 0.5.0 introduced a breaking change to improve handling the SPI dependency.
The user has to call **SPI.begin()** or equivalent before calling **AD.begin()**.
Optionally the user can provide parameters to the **SPI.begin(...)**


#### 0.4.0 Breaking change

The version 0.4.0 has breaking changes in the interface. 
The essence is removal of ESP32 specific code from the library. 
Furthermore it moved parameters from **begin()** to the constructor.
Finally made a specific constructor for HW SPI and SW SPI.
This makes it possible to support the ESP32-S3 and other processors in the future. 
Also it makes the library a bit simpler to maintain.


## Connection

Schema break-out

```
          TOP VIEW
        +-----------+
        |   X-TAL   |
        |         L |
    VCC | o       o | VCC
    CLK | o       o | D0
   PUFD | o       o | D1
   DATA | o       o | D2
  RESET | o       o | D3
    GND | o CCC   o | D4
  QOUT1 | o CCC   o | D5
  QOUT2 | o       o | D6
  ZOUT1 | o       o | D7 ----- SELECT SERIAL LOW
  ZOUT2 | o  PP   o | GND
        |    PP     |
        +-----------+

  XTAL = crystal
  L    = LED
  C    = chip
  P    = potentiometer => for duty cycle square wave
```


#### Related

- https://github.com/RobTillaart/AD9833
- https://github.com/RobTillaart/AD985X
- https://github.com/RobTillaart/functionGenerator  software waveform generator
- https://pages.mtu.edu/~suits/notefreqs.html  frequency table for notes.


### Multi device 

See **Multi_AD985X_devices.pdf**

Discussion leading to the document see - https://github.com/RobTillaart/AD985X/issues/13 

The AD985X board can be connected with a SPI bus like interface. 
However there is **no Chip Select pin (CS)** so one must take 
other measures to control multiple AD985X devices.


#### Trivial solution

The trivial implementation is to give each device a set of unique pins. 
If you have pins to spare this is the perfect solution.


#### Shared line solution

A more common SPI solution is to share the data and clock lines.
However that would typical set all AD985X devices simultaneously.
So extra hardware is needed to prevent this.

A possible solution is to put all needed lines behind an AND port that allows only
communication when the **SELECT** is HIGH.

```
     Arduino        AND           AD985X
--------------------------------------------------
 
                +--------+
     SELECT ----| A      |
                |      Y |------- DATA
     DATA  -----| B      |
                +--------+
  
                +--------+
     SELECT ----| A      |
                |      Y |------- CLOCK
     CLOCK  ----| B      |
                +--------+
 
                +--------+
     SELECT ----| A      |
                |      Y |------- FQ_UD
     FQ_UD  ----| B      |
                +--------+
 
                +--------+
     SELECT ----| A      |
                |      Y |------- RESET
     RESET  ----| B      |
                +--------+

```


The **DATA** line of the device is connected to the output of an **AND** port.  
The inputs if the **AND** port are (a) the SPI bus **DATA** line and (b) the **SELECT** pin.  
Strictly for the **DATA** this is not needed as data will only clock in if there is a **CLOCK**.

The **CLOCK** pin of the device is connected to the output of an **AND** port.  
The inputs if the **AND** port are (a) the SPI bus **CLOCK** line and (b) the **SELECT** pin.

The **FQ_UD** pin of the device is connected to the output of an **AND** port.  
The inputs if the **AND** port are (a) the MCU **FQ_UD** line and (b) the **SELECT** pin.
See FQ_UD note below.

The **RESET** pin of the device is connected to the output of an **AND** port.  
The inputs if the **AND** port are (a) the MCU **RESET** line and (b) the **SELECT** pin.

A typical IC to use is the **74HC08** which has 4 AND ports in it.


In short this setup makes the lines 'switchable' pass through, with the **SELECT** line.
It allows to have multiple AD985X devices, and even to share the SPI bus **DATA** and **CLOCK** 
lines with other SPI devices.


### FQ_UD note

It might be possible to connect a single FQ_UD line to multiple AD985X devices directly.
The FQ_UD pulse would update the frequency and as this register is not changed, the FQ_UD 
pulse might just have no changing effect. To be investigated to confirm this.

If confirmed this would change the above Shared line solution a bit. 

If the FQ_UD line can be shared directly it offers a way to start / change multiple
devices at the same time. 


## Interface

```cpp
#include "AD985X.h"
```

#### Constructors

- **AD9850(uint8_t slaveSelect, uint8_t resetPin, uint8_t FQUDPin, SPIClassRP2040 \* mySPI, uint8_t spiClock)** hardware SPI constructor RP2040
- **AD9850(uint8_t slaveSelect, uint8_t resetPin, uint8_t FQUDPin, SPIClass \* mySPI, uint8_t spiClock)** hardware SPI constructor 
- **AD9850(uint8_t slaveSelect, uint8_t resetPin, uint8_t FQUDPin, uint8_t spiData, uint8_t spiClock)**
  - slaveSelect = chip select. The library uses HIGH as active and LOW as not selected.  
  - resetPin = reset
  - FQUDPin = Frequency UpDate Pin
- **AD9851(...)** constructors with same interface as AD9850


#### Common interface

- **void begin()** initializes library internals.
- **void reset()** resets the function generator.
- **void powerDown()** idem.
- **void powerUp()** idem.
- **bool setFrequency(uint32_t freq)** SetFrequency sets the frequency and is limited by the 
MaxFrequency of the class used.
Returns false if limited. 
For the AD9850 => 40 MHz, for the AD9851 => 70 MHz. 
  - Note that the quality of the signal gets less at higher frequencies. 
  - Note setFrequency is affected by the autoUpdateFlag.
- **bool setFrequencyF(float freq)** SetFrequencyF sets the frequency with a float with a maximum of **two** decimals. 
  - Note that a float only has a mantissa of 6-7 digits so for frequencies above above ~1.000.000 = 1MHz all decimals are lost.
  - Note setFrequencyF is affected by the autoUpdateFlag.
The frequency is limited by the MaxFrequency of the class used.
Returns false if limited. 
- **uint32_t getMaxFrequency()** returns the maximum frequency that can be set. 
  - For the AD9850 this is 20 MHz.
  - For the AD9851 this is 70 MHz.
- **float getFrequency()** returns the frequency set. 
As it returns a float it might loose some accuracy at higher frequencies.
- **bool setPhase(uint8_t phase = 0)** set the phase in units of 11.25°  0..31 allowed. 
Default it sets the phase to 0.
Returns false if phase > 31, no change to phase in that case.
- **uint8_t getPhase()** returns the phase set, 0 by default. 
  - multiply by 11.25° to get the actual phase angle in degrees.
  - multiply by (PI \* 0.0625) to get actual phase angle in radians.


#### Calibration

**Warning:** use with care.

- **void setCalibrationOffset(int32_t offset = 0)** sets an offset to calibrate the frequency.
- **uint32_t getCalibrationOffset()** reads back the offset set.
- **uint32_t getFactor()** internal factor, for debugging

Note: **reset()** resets the offset to 0..
Note: setting the offset reduces the range of frequencies (at the ends of scale).


#### Auto update / manual update

(new since 0.2.2)

**Warning:** use with care.

- **void setAutoUpdate(bool update)** sets the autoUpdate flag, default set to true.
- **bool getAutoUpdate()** reads the autoUpdate flag.
- **void update()** manually toggle the FQ_UD flag to update the frequency.

Manual updating allows one to prepare the frequency, and actually apply 
it at a later moment.

Note: The default of the autoUpdate flag is true.  
Note: **reset()** resets the autoUpdateFlag to true.


#### Hardware SPI

To be used only if one needs a specific speed.

- **void setSPIspeed(uint32_t speed)** set SPI transfer rate.
- **uint32_t getSPIspeed()** returns SPI transfer rate.
- **bool usesHWSPI()** returns true if HW SPI is used.


## AD9851 additional

- **void setRefClockHigh()** set reference clock to 180 Mhz.
- **void setRefClockLow()** set reference clock to 30 Mhz.
- **uint8_t getRefClock()** returns 30 or 180.
- **void setAutoRefClock(bool arc)** sets a flag so the library switches automatically
to the reference clock of 180 MHz when the frequency is set above 10 MHz and 
to 30 MHz when the frequency is set to 10 MHz or lower.
The initial value is **false** == OFF for backwards compatibility. 
- **bool getAutoRefClock()** returns true if autoRefClock is set. 
- **void setARCCutOffFreq(uint32_t Hz = 10000000UL )** set cut off frequency 
for the auto reference clock. 
Maximum value is 30 MHz, typical is 10 MHz.
- **uint32_t getARCCutOffFreq()** returns cut off frequency set.


- Note: the autoRefClock mode does **NOT** automatically adjust the calibration offset.
- Note: **reset()** does **NOT** reset the autoRefClock flag.


## Operation

See examples.


#### Operational notes

- The quality of the signal becomes less at higher frequencies.
Switch the reference clock to find your optimal quality.
- If the calibration offset is not 0, it needs to be set by the user after every startup, 
and after switching the reference clock. 
The user is also responsible to store it e.g. in EEPROM to make it persistent.
- Experimental parts may change or removed in the future.


## Future

#### Must

- improve documentation

#### Should

- test on ESP32
- test on RP2040

#### Could

- performance measurements
- move code to .cpp
- create defines for MAGIC numbers (defaults)

#### Wont

- **bool setARCCutOffFreq()** no need
- should **setSPIspeed(uint32_t speed)** return bool?
  - out of range?
- wave quality measurements


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

