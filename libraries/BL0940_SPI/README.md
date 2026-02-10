
[![Arduino CI](https://github.com/RobTillaart/BL0940_SPI/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/BL0940_SPI/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/BL0940_SPI/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/BL0940_SPI/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/BL0940_SPI/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/BL0940_SPI.svg)](https://github.com/RobTillaart/BL0940_SPI/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/BL0940_SPI/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/BL0940_SPI.svg?maxAge=3600)](https://github.com/RobTillaart/BL0940_SPI/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/BL0940_SPI.svg)](https://registry.platformio.org/libraries/robtillaart/BL0940_SPI)


# BL0940_SPI

Arduino library for BL0940 energy monitor, SPI interface only.


## Description

**Experimental - Work in progress**

This library is not tested with hardware yet.
(it is based upon datasheet + app note).
If you have hardware and can test with SPI, please let me know (open an issue).

The BL0940 is a configurable current and voltage sensor. 
It also provides power, energy usage and more.
This Arduino library is to use the BL0940 energy monitor 
over the SPI interface.

The library was made as a spin-off off of the BL0942 library as they
are sort of similar but definitely not compatible.

There exist Serial libraries that support the reading of the base registers.
This library gives access to all registers over SPI (it does not support Serial).
To use the SPI interface, the SEL (== protocol select) pin of the BL0940 
must be connected to HIGH (3.3V).

The device acts as a SPI slave, which works in half duplex mode,
at a maximum clock rate of 900 kHz. This is a rather low speed and
it is not tested yet if the device works well beyond that speed.
The expectation is that there is not much gain possible.

Always read the datasheet for the details.

The library is still under test / development with hardware, so use with care.

Feedback as always is welcome. Please open an issue on GitHub.


### Hardware

Read datasheet for details.

The BL0940 module has 14 pins.

|    name   |  14 pin  |  description  |
|:---------:|:--------:|:--------------|
|    VDD    |     1    |  power supply - 3.3V
|     VT    |     2    |  external temperature
|    IP1    |     3    |  current channel - max 50 mV (35 RMS)
|    IN1    |     4    |  current channel
|     VP    |     5    |  voltage channel - max 100 mV (70 RMS)
|     VN    |     6    |  voltage channel
|    GND    |     7    |  Ground
|     ZX    |     8    |  Zero crossing
|     CF    |     9    |  Energy Pulse
|    SEL    |    10    |  Protocol Select (0 = UART, 1 = SPI)
|   SCLK    |    11    |  SPI clock
|  RX/SDI   |    12    |  data input (RX for UART)
|  TX/SDO   |    13    |  data output (TX for UART)
|   VPP     |    14    |  reserved


Note: use pull ups on the SDI / SDO / clock lines.


### Multi device

The BL0940 does not support a SPI-CS (Chip Select) pin. Therefore one cannot use
multiple devices on a SPI bus by pulling one Chip Select line LOW/HIGH.

There are several ways to support multiple BL0940 devices, which one
works for you depends on your requirements.
The following methods are NOT tested (so feedback is welcome).

1. Use different pins per device. As each device uses 3 wires (CLK, IN, OUT),
the number of wires used adds up, **n devices use 3n pins**.
This method is robust and needs no additional coding.
1. Use clock pin as Chip Select too. SPI devices will not act if they see 
no clock signal (AFAIK). So by giving every device an unique clock pin and
share the IN OUT pins the number of pins needed is reduced. 
**n devices use n+2 pins**.
1. Use an HC4067 1x16 multiplexer to multiplex the clock pin.
It needs up to four lines to "Chip Select" one of sixteen devices.
For less than 9 devices one can make one of the four lines fixed etc.
**1..16 devices use 4..7 pins** 
With every 4 pins extra one can add 16 devices.

The latter two need extra handling of the Chip Select by additional code.

(feedback welcome)

### Calibration

Call **calibrate(float shunt, float reductionFactor)** with shunt (typical = 0.001) and
the reduction factor of the voltage divider (e.g. 4000).

The other calibration functions are to manually set the settings, optional adjust
the values derived from **calibrate()** call.


### Warning

_Do not apply this product to safety protection devices or emergency stop equipment,
and any other applications that may cause personal injury due to the product's failure._


### Compatibles

The BL0940 and BL0942 are not compatible, although their internal working is partial similar.

The BL0937 needs investigation (no library planned yet)


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
|   HW  |  RW register  |   120    |         |          |
|   SW  |  Calibrate    |     4    |         |          |
|   SW  |  RW register  |   928    |         |          |


### Related

- https://www.belling.com.cn/product_info.html?id=753  latest datasheet
- https://github.com/RobTillaart/BL0940 this library
- https://github.com/RobTillaart/BL0942 related library
- https://github.com/RobTillaart/INA226 I2C current and voltage sensor (one of many INAxxx)
- https://github.com/RobTillaart/printHelpers for exponential notation floats.


UART libraries for the BL0940
- https://github.com/mcmchris/mcm-bl0940-lib
- https://github.com/ArtronShop/ArtronShop_BL0940


Application notes
- https://www.belling.com.cn/product_info.html?id=369


### Ohm sign

Alt-234 = Ω (Ohm sign) (Windows).

## Interface

```cpp
#include "BL0940_SPI.h"
```

### Constructor

- **BL0940_SPI(__SPI_CLASS__ \* mySPI = &SPI)** hardware SPI without Chip Select 
pin for single device usage.  No Chip Select pin supported (See #2).
- **BL0940_SPI(uint8_t dataIn, uint8_t dataOut, uint8_t clock)** 
software SPI. No Chip Select pin supported (See #2).
- **bool begin()** initializes internals.


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

From the calibration data the maxima can be derived.

- **float getMaxCurrent()** idem
- **float getMaxVoltage()** idem
- **float getMaxCurrentRMS()** idem
- **float getMaxVoltageRMS()** idem


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

Register 0x00-0x0F.

- **float getIRMSFast()** returns RMS current (faster less exact) in Amperes.
- **float getIWave()** return current in Amperes.
- **float getVWave()** return voltage in Volts.
- **float getIRMS()** return RMS current in Amperes.
- **float getVRMS()** return RMS voltage in Volts.

- **float getWatt()** returns power in Watt.
- **uint32_t getCFPulseCount()** returns counter (base for energy).
- **float getEnergy()** returns energy in kWh.
- **float getPhaseAngle()**
- **float getIntTemperature()**
- **float getExtTemperature()**


### RMS

Register 0x10, 0x12.
- **uint16_t getFastRMSControl()**
- **void setFastRMSControl(uint16_t ctrl, bool half = false)**
- **float getCurrentRMSOffset()** returns set offset.
- **void setCurrentRMSOffset(float offset)** set offset in Amperes.


### Power

Register 0x15, 0x17.

- **float getPowerOffset()**
- **void setPowerOffset(float deltaWatt)**
- **float getPowerCreep()**
- **void setPowerCreep(float watt)**

Creep is defined in Watt. It is the level that is considered noise,
and will not be accounted for as Power and Energy.


### UserMode

Register 0x18.

See datasheet for details.

To be able to write to the UserMode register, one must call **setWriteProtect(false)**.
See below.

- **uint16_t getUserMode()**
- **void setUserMode(uint16_t mode)** mode = 0x0000 .. 0x03FF (default 0x087)

Mask values should be OR-ed.

|  Name                            |  Value   |  Notes  |
|:---------------------------------|:--------:|:--------|
|  BL0940_MODE_RMS_UPDATE_400MS    |  0x0000  |  default
|  BL0940_MODE_RMS_UPDATE_800MS    |  0x0100  |
|  BL0940_MODE_AC_FREQUENCY_50HZ   |  0x0000  |  default
|  BL0940_MODE_AC_FREQUENCY_60HZ   |  0x0200  |
|  BL0940_MODE_CF_ENERGY           |  0x0000  |  default
|  BL0940_MODE_CF_ALARM            |  0x1000  |


### Reset

Register 0x1C. Read datasheet for details.

- **void softReset()** idem.


### Write protect

Register 0x1D. Read datasheet for details.

- **uint8_t getWriteProtect()** returns current write protect status.
- **void setWriteProtect(bool wp)**
  - wp = true => write protected
  - wp = false => write allowed


### Temperature control

  //  TODO bit masks? + doc.
- **uint16_t getTemperatureControl()**
- **void setTemperatureControl(uint16_t ctrl)**
  //  TODO bit masks? + doc.
- **uint16_t getExtTempGain()**
- **void setExtTempGain(uint16_t gain)**
  //  TODO bit masks? + doc.
- **uint16_t getExtTempOffset()**
- **void setExtTempOffset(uint16_t offset)**


### SPI

To be used only if one needs a specific speed for hardware SPI.
Has no effect on software SPI.

- **void setSPIspeed(uint32_t speed)** set SPI transfer rate.
- **uint32_t getSPIspeed()** returns SPI transfer rate.
- **bool usesHWSPI()** returns true / false depending on constructor.

From datasheet:

_3.1.3 Fault Tolerant Mechanism of SPI Interface_
If MCU send 6 bytes (0xFF), the BL0940 perform a reset function 
on the SPI communication interface.
This might also affect configuration - to be verified!
- **void resetSPI()** not tested yet.


### Error

- **uint8_t getLastError()** returns last error of low level communication.
- **uint32_t errorCount()** counter for CRC errors in readRegister. Not resettable.

|  Value  |  Error                 |  Notes  |
|:-------:|:-----------------------|:--------|
|     0   |  BL0940_OK             |
|    -1   |  BL0940_ERR_WRITE      |  not used
|    -2   |  BL0940_ERR_READ       |  not used
|    -3   |  BL0940_ERR_CHECKSUM   |


----

## Open KNX extra API

Created on request for Open KNX project.

- **void setChannelSelector(ChannelSelector selector)**
To set the channel selector call back function.


## Future

#### Must

- improve documentation
  - elaborate all functions.
- get hardware to test
- verify proper working of all functions (including configuration ones)

#### Should

- software SPI force under SPI max speed 
  - depending on performance / hard delayMicroseconds() for now.
    (it could measure time for first call and switch on/off delay)
    (#ifdef FCPU ... ?)
  - make it configurable? 

#### Could

- add examples
- improve error handling
  - e.g. setters return bool if out of range.
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


