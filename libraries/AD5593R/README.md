
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

The device is **NOT** tested with hardware yet. Feedback welcome.

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

As always, feedback is welcome.


### AD5592 SPI

The AD5592 is an almost identical device with a SPI interface.
The AD5592 has no RESET pin.
This library does **not** support the AD5592 / SPI version.


### Related

- https://github.com/RobTillaart/AD5593R  I2C
- https://www.analog.com/en/products/ad5593r.html (datasheet)

Where to buy (note it not the cheapest device)

- https://nl.aliexpress.com/item/1005005789989970.html
- https://www.digikey.nl/en/products/detail/mikroelektronika/MIKROE-2690/7394022


## Hardware

Connections see datasheet, depends on packaging type.


## I2C

### I2C address

The AD5593R has one address line A0, which allows two addresses 0x08 or 0x09.


### I2C Performance

The AD5593R supports standard mode (100 kHz) and fast mode (400 kHz).

TODO  
First get library verified, then make the measurements with hardware.


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

- **int setADCmode(uint8_t bitMask)** set pins == 1 to ADC mode (12 bit).
- **int setDACmode(uint8_t bitMask)** set pins == 1 to DAC mode (12 bits).
- **int setINPUTmode(uint8_t bitMask)** set pins == 1 to INPUT mode.
- **int setOUTPUTmode(uint8_t bitMask)** set pins == 1 to OUTPUT mode.
- **int setPULLDOWNmode(uint8_t bitMask)** 85 kOhm pull down to GND.


### Digital IO

The pins used must be set in the proper INPUT or OUTPUT mode.  
The user needs to handle the pin administration.

- **uint16_t write1(uint8_t pin, uint8_t value)** write HIGH/LOW to pin.
- **uint16_t write8(uint8_t bitMask)** write bitMask to all pins, 1 == HIGH, 0 == LOW
- **uint16_t read1(uint8_t pin)**
- **uint16_t read8()**


### Analog IO

The pins used must be set in the proper DAC or ADC mode.  
The user needs to handle the pin administration.

- **uint16_t writeDAC(uint8_t pin, uint16_t value)** value must be 0..4095 (12 bit).
- **uint16_t readDAC(uint8_t pin)** returns current value of selected DAC.
- **uint16_t readADC(uint8_t pin)** returns 12 bit value.

TODO: output / input range VREF x 2.


### External reference and power

- **int setExternalReference(bool flag)** selects internal 2.5V or 
external reference voltage.
- **int powerDown()** switches of all functionality, Low power mode.
- **int wakeUp()** switches on all functionality.

### Other

- **int reset()** triggers a power on reset, note the Vref is reset to internal 2.5V.
- **int getTemperature()** dummy for now.  
Should return value between −40 +105 (not accurate)


### Low level

Full control of the registers, read the datasheet for the details.

Might move to protected in the future.

- **int writeRegister(uint8_t reg, uint16_t data)**
- **uint16_t readRegister(uint8_t reg)**


## Future


#### Must

- improve documentation
- buy hardware for testing.
- verify (and fix) basic functions.
- check TODO's in code.

#### Should

- add missing functionality (after basic functions confirmed OK).
- input output range VREF x 2
- **writeNOP()** + **readNOP()** what is the function of NOP register?
- **GEN_CTRL_REG** Page 33
- **LDAC_MODE** Page 24/37 => latch the DAC outputs simultaneously (or not).
- possibly more...

#### Could

- read multiple ADC in one call, page 25.
- continuous ADC conversions.
- add examples
- unit tests? 
- support external reset pin?

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

