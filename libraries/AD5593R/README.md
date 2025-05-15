
[![Arduino CI](https://github.com/RobTillaart/AD5593R/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AD5593R/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AD5593R/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AD5593R/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AD5593R/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AD5593R.svg)](https://github.com/RobTillaart/AD5593R/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AD5593R/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AD5593R.svg?maxAge=3600)](https://github.com/RobTillaart/AD5593R/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AD5593R.svg)](https://registry.platformio.org/libraries/robtillaart/AD5593R)


# AD5593R

Arduino library for AD5593R, I2C, 8 channel ADC / DAC / GPIO device.


## Description

**Experimental**

The AD5593R is an IO device with 8 channels that can be configured as ADC
DAC or GPIO.
In that sense it is one of the most flexible IO expanders on the market.

Both the ADC and DAC are 12 bit, giving 4096 steps, from 0 to 4095.
The ADC unit is multiplexed over different channels/pins and is rated
with a conversion time of 2 us. _Note: this is not confirmed yet_.

From datasheet

_On power-up, the I/O pins are configured as 85 kΩ resistors
connected to GND. The I/O channels of the AD5593R can be
configured to operate as DAC outputs, ADC inputs, digital outputs,
digital inputs, three-state, or connected to GND with 85 kΩ pull-down
resistors. When configured as digital outputs, the pins have
the additional option of being configured as push/pull or open-drain._

The AD5593R is a relative expensive IO expander ($40-$50 range).

The DAC can use an internal reference (2.5 V, default option) or
an external reference.
The datasheet mentions a number of suitable external references which 
include the AD780, AD1582, ADR431, REF193, and ADR391.

Feedback as always is welcome. Please open an issue on GitHub or open an PR.

Also if there is functionality missing, please open an issue on GitHub.


### AD5592 SPI

The AD5592 is an almost identical device with a SPI interface.
The AD5592 has no RESET pin.
This library does **not** support the AD5592 / SPI version.  
(If this AD5593R works well, I might investigate the SPI version)


### Related

- https://github.com/RobTillaart/AD5593R  I2C
- https://www.analog.com/en/products/ad5593r.html (datasheet)
- https://github.com/RobTillaart/ADS1x15 12 & 16 bit ADC, I2C, slow
- https://github.com/RobTillaart/MCP_ADC 10-12 bit, 1,2,4,8 channel ADC
- https://github.com/RobTillaart/MCP_DAC 10-12 bit, 1,2,4,8 channel ADC
- https://github.com/RobTillaart/PCF8591 8 bit ADC + 1 bit DAC

Where to buy

- https://nl.aliexpress.com/item/1005005789989970.html
- https://www.digikey.nl/en/products/detail/mikroelektronika/MIKROE-2690/7394022


## Hardware

Connections see datasheet, depends on packaging type.


## Testing

The library is tested (most parts) with an Arduino UNO and an IOMOD module (V1.0)
from SuperHouse Automation Pty (Thanks!). See also issue #2.

- https://github.com/SuperHouse/IOMOD


## I2C

### I2C address

The AD5593R has one address line A0, which allows two addresses 0x10 or 0x11.

It is possible to use the A0 line as a CS (chip select) line and configure all
devices as 0x11. 
By setting a single A0 line HIGH the related AD5593R device will be selected. 
This works if you have enough IO pins. Alternative is I2C multiplexing see below.

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


### I2C Performance

The AD5593R supports standard mode (100 kHz) and fast mode (400 kHz).

Not tested.


## Interface

```cpp
#include "AD5593R.h"
```

### Constructors

- **AD5593R(const uint8_t deviceAddress, TwoWire \* wire = &Wire)** constructor.
- **bool begin()** no actions for now. Returns true if device address is seen on I2C bus.
- **bool isConnected()** returns true if device address is seen on I2C bus.
- **uint8_t getAddress()** returns address as set in constructor (0x08 or 0x09).

### Mode

From datasheet, page 23.

_In the event that the bit for an I/O channel is set in multiple configuration
registers, the I/O channel adopts the function dictated by the last
write operation.
The exceptions to this rule are that an I/Ox pin can be set as both
a DAC and ADC or as a digital input and output. When an I/Ox pin
is configured as a DAC and ADC, the primary function is as a DAC
and the ADC can be used to measure the voltage being provided
by the DAC.
When a pin is configured as both a general-purpose input and output,
the primary function is as an output pin._

There is no check if a pin is already set in a different mode.  
The user needs to handle the pin administration.

The pinMode must be set before one can do IO.

- **int setMode(char config[9])** simple configuration by means of a char array.
A=ADC, D=DAC, I=INPUT, O=OUTPUT, T=THREEState 
e.g. **setMode("AADDIIOT")** configures all eight pins with an unique function.
The char array must be 8 characters long, other characters set that pin as not configured.
The char array is not case sensitive.
- **int setADCmode(uint8_t bitMask)** set pins == 1 to ADC mode (12 bits).
- **int setDACmode(uint8_t bitMask)** set pins == 1 to DAC mode (12 bits).
- **int setINPUTmode(uint8_t bitMask)** set pins == 1 to INPUT mode.
- **int setOUTPUTmode(uint8_t bitMask)** set pins == 1 to OUTPUT mode.
- **int setTHREESTATEmode(uint8_t bitMask)** set pins == 1 to Three State Output mode

Configure detailed pin behaviour.

- **int setPULLDOWNmode(uint8_t bitMask)** 85 kOhm pull down to GND.
- **int setLDACmode(uint8_t mode)** See table below. 
Must be set after the **setExternalReference()**.
- **int setOpenDrainMode(uint8_t bitMask)** see datasheet page 26.

|  mode  |  meaning  |
|:------:|:----------|
|   0    |  COPY input register direct to DAC. (default)
|   1    |  HOLD in input registers.
|   2    |  RELEASE all input registers to DAC simultaneously.


### Digital IO

The pins used must be set in the proper INPUT or OUTPUT mode.  
The user needs to handle the pin administration.

- **uint16_t write1(uint8_t pin, uint8_t value)** write HIGH/LOW to an OUTPUT pin.
- **uint16_t write8(uint8_t bitMask)** write bitMask to all pins, 1 == HIGH, 0 == LOW.
This is faster than writing the individual pins.
- **uint16_t read1(uint8_t pin)** read a single pin, returns HIGH (1) or LOW (0).
- **uint16_t read8()** reads all INPUT pins at once, returns a bit mask with the
value of the individual pins.


### Vref Voltage reference

- **int setExternalReference(bool flag, float Vref)** true = external reference,
false = internal reference of 2.5 Volts. The Vref parameter has no meaning when 
internal reference is selected.
- **float getVref()** returns the current reference voltage.
- **int setADCRange2x(bool flag)** Configures the ADC range 1x or 2x the Vref.
- **int setDACRange2x(bool flag)** Configures the DAC range 1x or 2x the Vref.


### General Control register

See datasheet page 33 + 34 (not tested)

- ** int enableADCBufferPreCharge(bool flag)**
- ** int enableADCBuffer(bool flag)**
- ** int enableIOLock(bool flag)**
- ** int writeAllDacs(bool flag)**


### Analog IO

The pins 0..7 used must be set in the proper DAC or ADC mode.  
The user needs to handle the pin administration.

- **uint16_t writeDAC(uint8_t pin, uint16_t value)** value must be 0..4095 (12 bit). 
Values above 4095 will be clipped to 4095.
- **uint16_t readDAC(uint8_t pin)** returns current value of selected DAC.
- **uint16_t readADC(uint8_t pin)** returns 12 bit value.
- **uint16_t readTemperature()** Accuracy 3C over 5 samples averaged according datasheet.
Returns value in Celsius between −40 and +125 C.

Note: readADC(8) returns the RAW temperature reading, which is only 2 bytes.
Can be converted to (integer) temperature by mapping. 

```cpp
//  note depends on ADC _gain = 1x or 2x
int Celsius = map(raw, 645, 1084, -40, 125);
int Fahrenheit = map(raw, 645, 1084, -40, 257);
```


### Power

- **int powerDown()** switches off all functionality, Low power mode.
- **int wakeUp()** switches on all functionality.
- **int powerDownDac(uint8_t pin)** disable a single DAC.
- **int wakeUpDac(uint8_t pin)** enable a single DAC.


### Reset

- **int reset()** triggers a power on reset.
Note the Vref is reset to internal 2.5V and gain is set to 1x.


### Low level

Full control of the registers, read the datasheet for the details.

Will move to protected in the future.

- **int writeRegister(uint8_t reg, uint16_t data)**
- **uint16_t readIORegister(uint8_t reg)**
- **uint16_t readConfigRegister(uint8_t reg)**

See datasheet or top of the AD5593R.cpp file for overview of 
IO registers and CONFIG registers.


## Future


#### Must

- improve documentation.
- verify and fix all functions.

#### Should

- add missing functionality upon request.
- does **setMode()** needs **G** flag for Ground via 85 kΩ?
- **writeNOP()** + **readNOP()** what is the function of NOP register?
- fix TODO's in code


#### Could

- add examples
  - example with A0 line as ChipSelect.
  - example LDAC hold / release.
  - example performance measurements
  - example reset
- voltage interfaces
  - **float getADCVoltage(uint8_t pin)**
  - **int setDACVoltage(uint8_tpin, float value)**
  - **float getDacVoltage(uint8_t pin)**
- logical group functionality (code / readme.md).
- error handling
  - **int getLastError()**
- investigate **int getMode(char config[])** needed?
  - **uint8_t getADCmode()**, returns bitMask
  - getDACmode(), getINPUTMode(), getOUTPUTmode() getTSmode() idem.
- investigate read multiple ADC in one call, page 25.
  - readADCmask(uint8_t mask, uint16_t array8);
  - need to know how many are configured 
  - array with 8 values?
- continuous ADC conversions?
- name the magic numbers / masks in code.

#### Wont (for now).

- extend unit tests - needs mock-up device.
- **int writeDACVoltage(pin, voltage)** - depends on Vref.
- **float readADCVoltage()** - depends on Vref.
- support external reset pin - user can do this relative easy.
  - effect on internals of library?

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

