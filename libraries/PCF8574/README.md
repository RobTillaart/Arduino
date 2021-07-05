
[![Arduino CI](https://github.com/RobTillaart/PCF8574/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PCF8574/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PCF8574.svg?maxAge=3600)](https://github.com/RobTillaart/PCF8574/releases)

# PCF8574

Arduino library for PCF8574 - 8 channel I2C IO expander


## Description

Related to the PCF8575 16 channel IO expander library  https://github.com/RobTillaart/PCF8575

This library gives easy control over the 8 pins of a PCF8574 and PCF8574A chip.
These chips are identical in behavior although there are two distinct address ranges.

| TYPE     | ADDRESS-RANGE | notes                    |
|:---------|:-------------:|:------------------------:|
|PCF8574   |  0x20 to 0x27 | same range as PCF8575 !! |
|PCF8574A  |  0x38 to 0x3F |                          |

So you can connect up to 16 PCF8574 on one I2C bus, giving access 
to 16 x 8 = 128 IO lines. To maximize IO lines combine 8 x PCF8575 + 8 x PCF8574A giving
128 + 64 = 192 IO lines. Be sure to have a well dimensioned power supply.

The library allows to read and write both single pins or 8 pins at once.
Furthermore some additional functions are implemented that are 
playful but useful.


## Interface

**PCF8574_INITIAL_VALUE** is a define that can be set compile time or before
the include of "pcf8574.h" to overrule the default value used with the 
**begin()** call.


### Constructor

- **PCF8574(deviceAddress, TwoWire \*wire = &Wire)** Constructor with device address, 
and optional the Wire interface as parameter.
- **bool begin(val = PCF8574_INITIAL_VALUE)** set the initial value for the pins and masks.
- **bool begin(sda, scl, val = PCF8574_INITIAL_VALUE)** idem, for the ESP32 where one can choose the I2C pins.
- **bool isConnected()** checks if the address set in the constructor or by **setAddress()** is visible on the I2C bus.
- **bool setAddress(const uint8_t deviceAddress)** sets the device address after construction. Can be used to switch between PCF8574 modules runtime. Note this corrupts internal buffered values, so one might need to call **read8()** and/or **write8()**. Returns true if address can be found on I2C bus.
- **uint8_t getAddress()** returns the device address.


### Read and Write

- **uint8_t read8()** reads all 8 pins at once. This one does the actual reading.
- **uint8_t read(uint8_t pin)** reads a single pin; pin = 0..7
- **uint8_t value()** returns the last read inputs again, as this information is buffered 
in the class this is faster than reread the pins.
- **void write8(const uint8_t value)** writes all 8 pins at once. This one does the actual reading.
- **uint8_t write(const uint8_t pin, const uint8_t value)** writes a single pin; pin = 0..7; value is HIGH(1) or LOW (0)
- **valueOut()** returns the last written data.


### Button

- **void setButtonMask(const uint8_t mask)** 
- **uint8_t readButton8()**
- **uint8_t readButton8(const uint8_t mask)**
- **uint8_t readButton(const uint8_t pin)**


### Special

- **void toggle(const uint8_t pin)** toggles a single pin
- **void toggleMask(const uint8_t mask = 0xFF)** toggles a selection of pins, 
if you want to invert all pins use 0xFF (default value).
- **void shiftRight(const uint8_t n = 1)** shifts output channels n pins (default 1) pins right (e.g. leds ). 
Fills the higher lines with zero's.
- **void shiftLeft(const uint8_t n = 1)**  shifts output channels n pins (default 1) pins left (e.g. leds ).
Fills the lower lines with zero's.
- **void rotateRight(const uint8_t n = 1)** rotates output channels to right, moving lowest line to highest line.
- **void rotateLeft(const uint8_t n = 1)** rotates output channels to left, moving highest line to lowest line.
- **void reverse()** revers the "bit pattern" of the lines, high to low and vice versa.


### Misc

- **int lastError()** returns the last error from the lib. (see .h file)


## Error codes

| name               | value | description             |
|:-------------------|:-----:|:------------------------|
| PCF8574_OK         |  0x00 | no error                |
| PCF8574_PIN_ERROR  |  0x81 | pin number out of range |
| PCF8574_I2C_ERROR  |  0x82 | I2C communication error |


## Operation

See examples
