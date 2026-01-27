
[![Arduino CI](https://github.com/RobTillaart/BL0942_SPI/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/BL0942_SPI/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/BL0942_SPI/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/BL0942_SPI/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/BL0942_SPI/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/BL0942_SPI.svg)](https://github.com/RobTillaart/BL0942_SPI/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/BL0942_SPI/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/BL0942_SPI.svg?maxAge=3600)](https://github.com/RobTillaart/BL0942_SPI/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/BL0942_SPI.svg)](https://registry.platformio.org/libraries/robtillaart/BL0942_SPI)


# BL0942_SPI

Arduino library for BL0942 energy monitor, SPI interface only.


## Description

**Experimental - Work in progress**

This Arduino library is to use the BL0942 energy monitor 
over the SPI interface.
The BL0942 is a configurable current and voltage sensor. 
It also provides power and energy usage.

The library was requested by Andreas Breitschopp, as alternative for 
the UART library for the BL0942. See related below.
Besides the SPI interface the request also included a callback function
to be used in the Open KNX environment. 
Andreas co-developed and did the testing with hardware 

This library only implements and supports the SPI interface.
To use the SPI interface, the SEL (protocol select) pin of the PL0942 
must be connected to HIGH (3.3V).

The device acts as a SPI slave, which works in half duplex mode,
at a maximum clock rate of 900 kHz. This is a rather low speed and
it is not tested yet if the device works well beyond that speed.
The expectation is that there is not much gain possible.

The device contains a ChipSelect pin (A2_NCS) so it is possible to use
multiple devices. The library implements three constructors, one without
a select pin (single device) one with select pin and a software SPI 
constructor.

Always read the datasheet for the details.

The library is still under test / development with hardware, so use with care.

Feedback as always is welcome. Please open an issue on GitHub.


### Hardware 2 models

Read datasheet for details.

There are two different BL0942 modules, one with 10 pins, and one with
14 pins. The "upper" 10 pins are the same, the 14 pins device has 4 extra.


|    name   |  10 pin  |  14 pin  |  description  |
|:---------:|:--------:|:--------:|:--------------|
|    VDD    |     1    |     1    |  power supply  (3.3V)
|     IP    |     2    |     2    |  current channel
|     IN    |     3    |     3    |  current channel
|     VP    |     4    |     4    |  voltage channel
|    GND    |     5    |     5    |  ground
|    CF1    |     6    |     6    |  output 1 (pulse output)
|    SEL    |     7    |    11    |  LOW = UART  HIGH = SPI
|  CLK/BAUD |     8    |    12    |  SPI clock / BAUD select
|   RX/SDI  |     9    |    13    |  serial data in
|   TX/SDO  |    10    |    14    |  serial data out
|           |          |          |
|    A1     |          |     6    |  address pin, GND in SPI
|  A2_NCS   |          |     7    |  address pin, SELECT in SPI
|   CF2     |          |     8    |  output 2 (pulse output)
|    ZX     |          |     9    |  zero crossing (pulse output)

Note: use pull ups on the serial data / clock lines.


### Multi device

From datasheet section 3.1:

In three wire mode (MISO, MOSI, CLOCK), A1 and A2_NCS must be connected to GND.
There can only be a single device on the SPI bus which is always selected.

In four-wire mode (SELECT, MICO, MOSI, CLOCK), the A1 pin is connected to GND,
and the A2_NCS must be driven LOW for the read or write operation.

If the A2 is held HIGH, the A2 bit in the COMMAND byte (write / read) is set HIGH,
and the device won't recognize the 10101000 (=write) or 01011000 (=read) command.
By pulling the A2_NCS LOW, that device will recognize the command and will
response on the request, either read or write.

In hardware the **select pin** given in the constructor **MUST** be connected to
the **A2_NCS** pin of the devices to implement a proper device select.

Note multi device will ONLY work with the 14 pins BL0942.

Technically it is possible to implement multiplexing with additional hardware 
on the 10 pins devices. E.g. one could use an AND port on the clock input of the 
device. THe inputs of the AND port are the CLOCK pin and an inverted SELECT pin.
(inverted as the library pulls select LOW to select).

Other multiplex solutions might exist (e.g. multiplexer HC4067) but for now 
these are out of the scope of this library.


### Calibration

Call **calibrate(shunt, reductionFactor)** with shunt (typical = 0.001) and
the reduction factor of the voltage divider (e.g. 4000).

The other calibration functions are to manually set the settings, optional adjust
the values derived from **calibrate()** call.


### Warning

_Do not apply this product to safety protection devices or emergency stop equipment,
and any other applications that may cause personal injury due to the product's failure._


### Compatibles

The BL0940 is not compatible, although its internal working is partial similar.
At least it needs other magic numbers, and has some other registers.
Support for the BL0940 is not planned.

BL0937 idem.


## Performance

The device works at maximum 900 kHz which is rather low. NO tests have been done
at higher speeds. 

As all communication involves sending / receiving 6 bytes (48 bit) the calls to
the device are expected to be very similar in time.
48 bits at 900 kHz implies a minimum of 54 microseconds for the transmission of
the bits. 

Indicative figures (in microseconds per call)

|  SPI  |  Function     |  UNO R3  |  ESP32  |  RP2040  |
|:-----:|:-------------:|:--------:|:-------:|:--------:|
|   HW  |  Calibrate    |     4    |         |          |
|   HW  |  RW register  |   116    |         |          |
|   SW  |  Calibrate    |     4    |         |          |
|   SW  |  RW register  |   924    |         |          |


### Related

- https://www.belling.com.cn/product_info.html?id=753  latest datasheet
- https://github.com/RobTillaart/BL0942 this library
- https://github.com/RobTillaart/INA226 I2C current and voltage sensor (one of many INAxxx)
- https://github.com/RobTillaart/printHelpers for exponential notation floats.


UART library for the BL0942
- https://github.com/SanteriLindfors/BL0942


Application notes
- https://www.belling.com.cn/media/file_object/bel_product/BL0942/guide/BL0942%20APP%20Note_V1.04_cn.pdf


### Ohm sign

Alt-234 = Ω (Ohm sign) (Windows).


### Tested

In progress.


## Interface

```cpp
#include "BL0942_SPI.h"
```

### Constructor

- **BL0942_SPI(__SPI_CLASS__ \* mySPI = &SPI)** hardware SPI without select 
pin for single device usage.
- **BL0942_SPI(uint8_t select, __SPI_CLASS__ \* mySPI = &SPI)** hardware SPI
with select pin. For multiple devices usage.
- **BL0942_SPI(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock)** 
software SPI with select pin. 
For single device usage one can set the select pin to 255.
- **bool begin()** initializes internals.

The select pin should be connected to the A2_NCS pin of the device (14 pins model).
When this pin is pulled LOW this device is selected.

Note you typical need one select pin per device. Although other hardware
configurations are possible (e.g. HC4067 multiplexer) these are not
supported by the library.


### Calibration 1

- **void calibrate(float shunt, float reductionFactor = 1.0f)**
calibration of the current measurement based upon the shunt and the
calibration of the voltage based upon the reduction factor (ration)
of an optional voltage divider.

From APP Note BL940: (assumes this math applies to all shunts).

_The shunt size(1mΩ) is selected to maximize the use of the dynamic range on
current channel. However, there are some import considerations when selecting a shunt
for an energy metering application. First, minimize the power dissipation in the shunt. the
maximum rated current can be 35A,therefore the maximum power dissipated in the shunt
is 35A×35A×1mΩ=1.225W. Secondly, the higher power dissipation may make it difficult
to manage the thermal issues. High temperatures may cause significant error at heavy
loads. **So, the maximum rated current@ (1mΩ shunt) should be limited to 16A.**_


Reduction factor of an ```VDD - R1 - R2 - GND``` ladder:
```
RF = (R1 + R2) / R2;  // e.g. R1=200K R2=100 => RF=200100/100 = 2001.
```


### Calibration 2

The following functions set the values per LSB directly for the core measurements registers.
The getter functions allow (run time) adjustments and help to manually calibrate
the device more precise if needed.

The VoltageLSB is the voltage of the LeastSignificantBit, the value one has to 
multiply the raw register value with. Other LSB's idem.
Note: the LSB numbers are the reciprocal of the numbers configured in the UART library.

- **float getVoltageLSB()**
- **void setVoltageLSB(float voltageLSB)**
- **float getCurrentLSB()**
- **void setCurrentLSB(float currentLSB)**
- **float getPowerLSB()**
- **void setPowerLSB(float powerLSB)**
- **float getEnergyLSB()**
- **void setEnergyLSB(float energyLSB)**


### Core

- **float getIWave()** return current in Amperes.
- **float getVWave()** return voltage in Volts.
- **float getIRMS()** return RMS current in Amperes.
- **float getVRMS()** return RMS voltage in Volts.
- **float getIRMSFast()** returns RMS current (faster less exact) in Amperes.
- **float getWatt()** returns power Watt.
- **uint32_t getCFPulseCount()** returns counter (base for energy).
- **float getEnergy()** returns energy in kWh.
- **float getFrequency()** returns frequency ~ 50 or 60 Hz.


### Status

Read datasheet for details.

- **uint16_t getStatus()** returns status byte mask.

|  name                  |  value   |
|:-----------------------|:--------:|
|  BL0942_STAT_CF_REVP   |  0x0001  |
|  BL0942_STAT_CREEP     |  0x0002  |
|  BL0942_STAT_I_ZX_LTH  |  0x0100  |
|  BL0942_STAT_V_ZX_LTH  |  0x0200  |


### RMS offset

- **float getCurrentRMSOffset()** returns set offset.
- **void setCurrentRMSOffset(float offset)** set offset in Amperes.


### Power creep

- **float getPowerCreep()**
- **void setPowerCreep(float watt)**

Creep is defined in Watt. It is the level that is considered noise,
and will not be accounted for as Power and Energy.


### Fast RMS threshold

- **float getFastRMSThreshold()**
- **void setFastRMSThreshold(float threshold)**


### Fast RMS cycles

- **uint8_t getFastRMSCycles()**
- **void setFastRMSCycles(uint8_t cycles)** cycles = 0..7

|  Value   |  Cycles  |  Notes  |
|:--------:|:--------:|:--------|
|  0       |  0.5     |
|  1       |  1       |  default
|  2       |  2       |
|  3       |  4       |
|  4..7    |  8       |
|   > 7    |  8       |  values above 7 => 7


### Frequency cycles

- **uint8_t getFrequencyCycles()**
- **void setFrequencyCycles(uint8_t cycles)** cycles = 0..2

|  Value  |  Cycles  |  Notes  |
|:-------:|:--------:|:--------|
|  0      |   2      |
|  1      |   4      |
|  2      |   8      |
|  3      |  16      |  default
|  > 3    |  16      |  values above 3 => 3


### Output configuration

To set the (pulsed) output of the CF1, CF2 and the ZX pins.

- **uint8_t getOutputConfigMask()**
- **void setOutputConfigMask(uint8_t mask)** mask = 0..63

Register 0x18, mask values should be OR-ed.

|  Name                      |  Value  |  Notes  |
|:---------------------------|:-------:|:--------|
|  BL0942_CF1_ACTIVE_ENERGY  |   0x00  |  default
|  BL0942_CF1_OVER_CURRENT   |   0x01  |
|  BL0942_CF1_ZERO_CROSS_V   |   0x02  |
|  BL0942_CF1_ZERO_CROSS_I   |   0x03  |
|                            |         |
|  BL0942_CF2_ACTIVE_ENERGY  |   0x00  |
|  BL0942_CF2_OVER_CURRENT   |   0x04  |  default
|  BL0942_CF2_ZERO_CROSS_V   |   0x08  |
|  BL0942_CF2_ZERO_CROSS_I   |   0x0C  |
|                            |         |
|  BL0942_ZX_ACTIVE_ENERGY   |   0x00  |
|  BL0942_ZX_OVER_CURRENT    |   0x10  |
|  BL0942_ZX_ZERO_CROSS_V    |   0x20  |  default
|  BL0942_ZX_ZERO_CROSS_I    |   0x30  |


### UserMode

See datasheet for details.

To be able to write to the UserMode register, one must call **setWriteProtect(false)**.
See below.

- **uint16_t getUserMode()**
- **void setUserMode(uint16_t mode)** mode = 0x0000 .. 0x03FF (default 0x087)

Register 0x19, mask values should be OR-ed.

|  Name                            |  Value   |  Notes  |
|:---------------------------------|:--------:|:--------|
|  BL0942_MODE_CF_DISABLE          |  0x0000  |
|  BL0942_MODE_CF_ENABLE           |  0x0004  |  default
|  BL0942_MODE_RMS_UPDATE_400MS    |  0x0000  |
|  BL0942_MODE_RMS_UPDATE_800MS    |  0x0008  |
|  BL0942_MODE_RMS_WAVEFORM_FULL   |  0x0000  |
|  BL0942_MODE_RMS_WAVEFORM_AC     |  0x0010  |
|  BL0942_MODE_AC_FREQUENCY_50HZ   |  0x0000  |
|  BL0942_MODE_AC_FREQUENCY_60HZ   |  0x0020  |
|  BL0942_MODE_CNT_CLR_SEL_DISABLE |  0x0000  |
|  BL0942_MODE_CNT_CLR_SEL_ENABLE  |  0x0040  |
|  BL0942_MODE_ACCU_MODE_ALGEBRAIC |  0x0000  |
|  BL0942_MODE_ACCU_MODE_ABSOLUTE  |  0x0080  |  default
|  BL0942_MODE_UART_4800           |  0x0000  |
|  BL0942_MODE_UART_9600           |  0x0100  |
|  BL0942_MODE_UART_19200          |  0x0200  |
|  BL0942_MODE_UART_38400          |  0x0300  |

Note: The UART settings are not to be used in this SPI library.

Note: bits 0,1 are reserved and default 1. bits 23-10 are default 0.


### Gain

- **uint8_t getCurrentGain()**
- **void setCurrentGain(uint8_t gain)**

Register 0x1A

|  Name            |  Value  |  Gain  |  Notes  |
|:-----------------|:-------:|:------:|:--------|
|  BL0942_GAIN_1   |   0x00  |    1   |
|  BL0942_GAIN_4   |   0x01  |    4   |
|  BL0942_GAIN_16  |   0x02  |   16   |
|  BL0942_GAIN_24  |   0x03  |   24   |


### Reset

Read datasheet for details.

- **void softReset()**


### Write protect

Read datasheet for details.

- **uint8_t getWriteProtect()** returns current write protect status.
- **void setWriteProtect(bool wp)**
  - wp = true => write protected
  - wp = false => write allowed


### SPI

To be used only if one needs a specific speed for hardware SPI.
Has no effect on software SPI.

- **void setSPIspeed(uint32_t speed)** set SPI transfer rate.
- **uint32_t getSPIspeed()** returns SPI transfer rate.
- **bool usesHWSPI()** returns true / false depending on constructor.

_3.1.3 Fault Tolerant Mechanism of SPI Interface_
If MCU send 6 bytes (0xFF), the BL0942 perform a reset function 
on the SPI communication interface.
This might also affect configuration - to be verified!
- **void resetSPI()** not tested.


### Error

- **uint8_t getLastError()** returns last error of low level communication.

|  Value  |  Error                 |  Notes  |
|:-------:|:-----------------------|:--------|
|     0   |  BL0942_OK             |
|    -1   |  BL0942_ERR_WRITE      |  not used
|    -2   |  BL0942_ERR_READ       |  not used
|    -3   |  BL0942_ERR_CHECKSUM   |


----

## Open KNX extra API

Created on request for Open KNX project.

- **void setChannelSelector(ChannelSelector selector)**
To set the channel selector call back function.


## Future

#### Must

- improve documentation
  - elaborate all functions.
- get API functional complete
- verify proper working of all functions (including configuration ones)
- get hardware to test

#### Should

- **resetSPI()** function?  section 3.1.3
- software SPI force under SPI max speed 
  - depending on performance / hard delayMicroseconds() for now.
    (it could measure time for first call and switch on/off delay)
    (#ifdef FCPU ... ?)
  - make it configurable? 

#### Could

- add examples
- improve error handling
- investigate unit tests
- default parameters for simple reset?
- performance measurements

#### Wont
- mA interface? float can easily be converted (also other units).


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


