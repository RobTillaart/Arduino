

[![Arduino CI](https://github.com/RobTillaart/MultiSpeedI2CScanner/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MultiSpeedI2CScanner/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MultiSpeedI2CScanner/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MultiSpeedI2CScanner/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MultiSpeedI2CScanner/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MultiSpeedI2CScanner.svg)](https://github.com/RobTillaart/MultiSpeedI2CScanner/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MultiSpeedI2CScanner/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MultiSpeedI2CScanner.svg?maxAge=3600)](https://github.com/RobTillaart/MultiSpeedI2CScanner/releases)

```
not used.
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MultiSpeedI2CScanner.svg)](https://registry.platformio.org/libraries/robtillaart/MultiSpeedI2CScanner)
```


# Arduino MultiSpeed I2C Scanner


## Version: 0.1.17


## Description

MultiSpeedI2CScanner is a menu driven I2C scanner, see below.
The scanner is tested on an UNO and an ESP32.

The scanner provides an overview of which addresses can be found 
at which speed. This allows one to optimize the I2C performance of
many devices above the standard 100KHz speed.

#### Related

build your own I2C scanner with:
- https://github.com/RobTillaart/I2C_SCANNER


## Menu dialog

```
<speeds = 50 100 150 200 250 300 350 400 >

Arduino MultiSpeed I2C Scanner - 0.1.15

I2C ports: 1  Current: Wire0
	@ = toggle Wire - Wire1 - Wire2 [TEENSY 3.5 or Arduino Due]
Scan mode:
	s = single scan
	c = continuous scan - 1 second delay
	q = quit continuous scan
	d = toggle latency delay between successful tests. 0 - 5 ms
	i = toggle enable/disable interrupts
Output:
	p = toggle printAll - printFound.
	h = toggle header - noHeader.
	a = toggle address range, 0..127 - 8..119 (default)
Speeds:
	0 = 100..800 KHz - step 100  (warning - can block!!)
	1 = 100 KHz
	2 = 200 KHz
	4 = 400 KHz
	9 = 50..400 KHz - step 50     < DEFAULT >

	!! HIGH SPEEDS - WARNING - can block - not applicable for UNO
	8 =  800 KHz
	M = 1000 KHz
	N = 3400 KHz
	O = 5000 KHz
	P =  100 400 1000 3400 5000 KHz (standards)

	r = reset to startup defaults.
	? = help - this page
```


## Functions

### I2C ports

**@** selects through the different Wire ports. 
Note that the current Wire port is given after I2C ports: count
Wire0 is just Wire but it was easier to program.

### Scan mode

**s** selects single scan mode, think of it as manual.

**c** selects continuous scanning, think of it as automatic.

**q** quits the continuous scan mode.

**d** toggles the latency between successful scans. 
Only needed sometimes.

**i** toggles disable/enable interrupts, use with care.


### Output selection

**p** toggles printAll and  printFound. 
PrintAll will print also the addresses where nothing is found.
PrintFound will only generate a line if an I2C device is found on that address.

**h** toggles the printing of a header.

**a** toggles the range of addresses scanned, default the range 8 .. 119 is scanned,
but one can extend this range to 0 .. 127. **Note:** some addresses are reserved.


### Speeds

All options here select a single speed or a range of speeds.

Since 0.1.10 version experimental speeds of 1000, 3400 and 5000 are added as
these are part of the I2C standards.  
http://i2c.info/i2c-bus-specification

NOTE: not all processors will support these higher speeds. 
This can show up as blocking or it can even look like it is working.
Check your datasheet to see which speeds are applicable for the processor in use.


## Future

#### Must

- update documentation
- test on RP2040

#### Should

#### Could

- add watchdog reset (at least AVR - 8 seconds 0.2.0 )
- non-AVR command behind a ```#ifdef``` ?
- rename releaseNotes.md to changelog.md (in line with libraries)
- I2C GENERIC RESET address 0x00 CMD 0x06

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

