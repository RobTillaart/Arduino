
[![Arduino CI](https://github.com/RobTillaart/M5SWITCH8/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/M5SWITCH8/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/M5SWITCH8/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/M5SWITCH8/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/M5SWITCH8/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/M5SWITCH8.svg)](https://github.com/RobTillaart/M5SWITCH8/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/M5SWITCH8/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/M5SWITCH8.svg?maxAge=3600)](https://github.com/RobTillaart/M5SWITCH8/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/M5SWITCH8.svg)](https://registry.platformio.org/libraries/robtillaart/M5SWITCH8)


# M5SWITCH8

Arduino library for the I2C M5 SWITCH8 and BUTTON8 devices.


## Description

This library is to use the M5STACK SWITCH8 and BUTTON8 devices.
These two devices are technical identical, one has 8 switches 
and the other has 8 (momentary) buttons.

The switches switch between 0 and 1.

The buttons read 0 when pressed, and 1 when not pressed.

The switches / buttons can be read individually or all in one byte.
The latter is faster as it needs less I2C communication.

The devices have 9 LEDs, 8 of them (index 0..7) are coupled 1 to 1 
with the switches, where the 9th led (index 8) is more like a "power" LED.

The 8 LEDs can be set manually or automatic. In manual mode the
user has to set the LEDs manually (using 0x00BBGGRR colours).

In automatic mode the user defines the ON and OFF colours per switch and 
the internal processor of the devices automatically follows the switch.
This is faster and saves communication, however the user still has to 
read the switches manually.
The light implies that action is taken immediately, but this does not 
need to be the case.

Feedback as always is welcome.


### Test

The library is (quick) tested with UNO R3.
The devices are labelled as 5.0 V but seem to work at 3.3 V too.

Standby power consumption 9mA@5V


### Related

- https://github.com/RobTillaart/M5ANGLE8
- https://github.com/RobTillaart/M5ROTATE8
- https://github.com/RobTillaart/M5SWITCH8


## I2C

### I2C Address

The M5 SWITCH and M5 BUTTON devices have a configurable address.
This allows one to set 100+ different I2C addresses, implying 
over 800 buttons / switches (in theory).

If one needs more devices there are some options.
- One could use an I2C multiplexer (see below)
- One could use an MCU with multiple I2C buses.
- One could use a (Two-Wire compatible) SW I2C (outside scope of this library).


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

|  Clock     |  time (us)  |  Notes  |
|:----------:|:-----------:|:--------|
|   100 KHz  |             |  default 
|   200 KHz  |             |
|   300 KHz  |             |
|   400 KHz  |             |
|   500 KHz  |             |
|   600 KHz  |             |


TODO: create and run performance sketch


## Interface

```cpp
#include "M5SWITCH8.h"
or
#include "M5BUTTON8.h"
```

### Constructor

- **M5SWITCH8(uint8_t address, TwoWire \*wire = &Wire)** set address, optional select I2C bus.
- **M5BUTTON8(uint8_t address, TwoWire \*wire = &Wire)** set address, optional select I2C bus.
- **bool begin()** Checks if device address can be found on I2C bus.
- **bool isConnected()** Checks if device address can be found on I2C bus.
- **uint8_t getAddress()** Returns the address set in constructor.


### Read

- **uint8_t readAll()** returns 1 byte with the state of the 8 switches / buttons.
- **uint8_t readSwitch(uint8_t sw)** returns the state of switch / button sw, where
sw = 0..7. If sw is out of range the function returns 255.

M5BUTTON8 class only:

- **uint8_t readButton(uint8_t button)** returns the state of button where 
1 = not pressed, and 0 = pressed. 
button = 0..7. If button is out of range the function returns 255.
- **bool isPressed(uint8_t button)** returns the state of button.


### LED brightness

- **void setBrightnessAll(uint8_t value)** idem.
- **void setBrightness(uint8_t led, uint8_t value)** idem.
- **uint8_t getBrightness(uint8_t led)** idem.


### LED mode

- **void setMode(uint8_t mode)** see table below.
- **uint8_t getMode()**

|  Mode  |  description  |
|:------:|:--------------|
|    0   |  manual mode  
|    1   |  automatic / system mode

All non zero modes are mapped upon system mode (1).


### Manual mode

Led 8 is the "power LED" near connector.
Note the colour is in BGR format.

- **void setColor(uint8_t led, uint32_t bgr)** led = 0..8
- **void setColorRGB(uint8_t led, uint8_t R, uint8_t G, uint8_t B)** led = 0..8
- **uint32_t getColor(uint8_t led)** read back.
If led is out of range it returns 0.

Some colours to indicate the BGR colour-scheme

|  colour  |  bgr code  |  notes  |
|:---------|:----------:|:--------|
|  RED     |  0x0000FF  |  other intensities possible 
|  GREEN   |  0x00FF00  |
|  BLUE    |  0xFF0000  |
|  YELLOW  |  0x00FFFF  |
|  WHITE   |  0xFFFFFF  |
|  BLACK   |  0x000000  |

The device support a one byte colour space, which is encoded
as a byte ```BBGGGRRR```

- **void setColor233(uint8_t led, uint8_t value)** led = 0..8
- **uint8_t getColor233(uint8_t led)** read back.
If led is out of range it returns 0.


### Automatic mode

In automatic mode the LEDs follow the switches automatically.
Note that one still has to read the status of the switches.

- **void setOffColor(uint8_t led, uint32_t bgr)** led = 0..7, colours in BGR format.
- **uint32_t getOffColor(uint8_t led)** read back.
- **void setOnColor(uint8_t led, uint32_t bgr)** idem.
- **uint32_t getOnColor(uint8_t led)** idem.


### Interrupts

No documentation about interrupts is found except the existance of a register.
So this function is / can not tested. 
It is unknown how interrupts work with these devices.
Assumption the IRQ might be used internally in the firmware as no IRQ line is 
exposed by the devices.

- **void enableInterrupts()** idem.
- **void disableInterrupts()** idem.
- **uint8_t isEnabled()** idem.


### Miscellaneous

- **void writeToFlash()** write settings to flash (restart defaults)
- **uint8_t getFirmwareVersion()** returns firmware version number.
- **void setAddress(uint8_t address)** set the I2C address, needs writeToflash() and reboot.


### Debug

- **uint8_t getLastError()** returns last error of low level communication.


## Future

#### Must

- improve documentation
- test more platforms.

#### Should

- add RGB233 API (reg 0x50) = faster - smaller colours space.
  - **setColor233(led, value)** and **getolor233(led)**
- investigate interrupts.

#### Could

- add **getColors(LED, &R, &G, &B)**
- add examples
  - BUTTON 8 game, follow the LED (sort SIMON)
  - knight rider LED
  - VU meter LED.
- create unit tests if possible
- add **void setBrightnessAll(uint8_t value)**

#### Wont 

- add **setInvert(bool on)** + **bool getInvert()** for M5BUTTON8 ?
  - solved with **bool isPressed(button)**


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


