
[![Arduino CI](https://github.com/RobTillaart/AD985X/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AD985X/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AD985X.svg?maxAge=3600)](https://github.com/RobTillaart/AD985X/releases)

# AD985X

Arduino library for AD9850 and AD9851 function generators.


## Description

Library for the AD9850 and AD9851 function generators.
The library has a AD9850 base class that implements the commonalities.
The AD9851 is derived and has its own **setFrequency()** methods.
Furthermore the AD9851 also has function to select the reference clock,
a feature the AD9850 does not have.

**Warning**
The library is not suitable for AD9852 as that is a function generator with
way more functionality.


## Connection


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
  P    = potmeter => for duty cycle square wave

```

### Multidevice 

**Warning**: this setup needs to be confirmed as it is not actually tested by me yet.

Discussed in detail here - https://github.com/RobTillaart/AD985X/issues/13 

The AD985X board can be connected with a SPI bus like interface. 
However there is **no Chip Select pin (CS)** so one must take other measures to control multiple AD985X devices.


#### Trivial solution

The trivial implementation is to give each device a set of unique pins. 
If you have pins to spare this is the perfect solution.


#### Shared line solution

A more common SPI solution is to share the data and clock lines.
However that would typical set all AD985X devices simultaneously.
So extra hardware is needed to prevent this.

A possible solution is to put all needed lines behind an AND port that allows only
communication when the **SELECT** is HIGH.


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


TODO - picture.

**Note** Other multiplexing solutions are possible of course.


### FQ_UD note

It might be possible to connect a single FQ_UD line to multiple AD985X devices directly.
The FQ_UD pulse would update the frequency and as this register is not changed, the FQ_UD 
pulse might just have no changing effect. To be investigated to confirm this.

If confirmed this would change the above Shared line solution a bit. 

If the FQ_UD line can be shared directly it offers a way to start / change multiple
devices at the same time. 



## Interface

### Constructors

- **AD9850()** 40 MHz signal generator
- **AD9851()** 70 MHz signal generator, derived from AD9850 with some extra options.


### Common interface

- **begin(selectPin, resetPin, FQUDPin, dataOut = 0, clock = 0)**  
For hardware SPI only use the first three parameters, 
for SW SPI you need to define the data and clock pin too.
  - selectPin = chip select. The library uses HIGH as active and LOW as not selected.  
  - resetPin = reset
  - FQUD = Frequency UpDate Pin
- **reset()** resets the function generator.
- **powerDown()** idem
- **powerUp()** idem
- **setFrequency(uint32_t freq)** SetFrequency sets the frequency and is limited by the 
MaxFrequency of the class used. For the AD9850 => 40 MHz, for the AD9851 => 70 MHz. 
  - Note that the quality of the signal gets less at higher frequencies. 
  - Note setFrequency is affected by the autoUpdateFlag.
- **setFrequencyF(float freq)** SetFrequencyF sets the frequency with a float with a maximum of **two** decimals. 
  - Note that a float only has a mantisse of 6-7 digits so above ~1.000.000 decimals are lost.
  - Note setFrequencyF is affected by the autoUpdateFlag.
- **getMaxFrequency()** returns the maximum frequency setable. For the AD9850 this is 20 MHz.
For the AD9851 this is 70 MHz.
- **getFrequency()** returns the frequency set. As it returns a float it might loose some accuracy at higher frequencies.
- **setPhase(uint8_t phase = 0)** set the phase in units of 11.25°  0..31 allowed. 
Default it sets the phase to 0.
- **getPhase()** returns the phase set, 0 by default.


### Calibration

**Warning:** use with care.

- **void setCalibrationOffset(int32_t offset = 0)** sets an offset to calibrate the frequency.
- **uint32_t getCalibrationOffset()** reads back the offset set.
- **uint32_t getFactor()** internal factor, for debugging

Note: reset() resets the offset to 0..
Note: setting the offset reduces the range of frequencies (at the ends of scale).


### Auto update / manual update

(new since 0.2.2)

**Warning:** use with care.

- **void setAutoUpdate(bool update)** sets the autoUpdate flag, default it is true.
- **bool getAutoUpdate()** reads the autoUpdate flag.
- **void update()** manually toggle the FQ_UD flag to update the frequency.

Manual updating allows one to prepare the frequency, and actually apply 
it at a later moment.

The default of the flag is true, and will be reset to true by the **reset()** call.



### AD9850 specific

The AD9850 has no specific functions.

### AD9851 specific

- **setRefClockHigh()** set reference clock to 180 Mhz.
- **setRefClockLow()**  set reference clock to 30 Mhz.
- **getRefClock()** returns 30 or 180.
- **setAutoRefClock(bool arc)** sets a flag so the library switches automatically
to the reference clock of 180 MHz when the frequency is set above 10 MHz and 
to 30 MHz when the frequency is set to 10 MHz or lower.
The initial value is **false** == OFF for backwards compatibility. 
- **getAutoRefClock()** returns true is automode is set. 
- **void setARCCutOffFreq(uint32_t Hz = 10000000UL )** set cut off frequency 
for the auto reference clock. max value is 30 MHz, typical 10MHz
- **uint32_t getARCCutOffFreq()** returns cut off frequency set.


- Note: the autoRefClock mode does **NOT** automatically adjust the calibration offset.
- Note: **reset()** does **NOT** reset the autoRefClock flag.


## Operation

See examples


### Operational notes

- The quality of the signal becomes less at higher frequencies.
Switch the refclock to find your optimal quality.
- If the calibration offset is not 0, it needs to be set by the user after every startup, 
and after switching the reference clock. 
The user is also responsible to store it e.g. in EEPROM to make it persistent.
- Experimental parts may change or removed in the future.

