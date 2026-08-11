
[![Arduino CI](https://github.com/RobTillaart/DS3502/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DS3502/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DS3502/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DS3502/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DS3502/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DS3502.svg)](https://github.com/RobTillaart/DS3502/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DS3502/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DS3502.svg?maxAge=3600)](https://github.com/RobTillaart/DS3502/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DS3502.svg)](https://registry.platformio.org/libraries/robtillaart/DS3502)


# DS3502

Arduino library for the DS3502, I2C, 7-bit, non-volatile, digital potentiometer.


## Description

**Experimental**

The DS3502 is an I2C 7-bit, non-volatile (NV) digital potentiometer (POT)
of 10 kΩ, featuring an output voltage range of up to 15.5V.
Programming is accomplished by an I2C-compatible interface,
which can operate at speeds of up to 400kHz.
External voltages are applied at the RL and RH inputs to define the
lowest and highest potentiometer outputs.

datasheet: rev 1, march 2009

Feedback is as always welcome.


### Compatibility

The DS3501 is similar device with an internal temperature sensor that can
adjust the potmeter based upon a configurable look up table (LUT).
It has also 2 address pins so 4 devices possible.
The base potmeter seems to be compatible so this library might work
for the DS3501 too. 

The DS3503 is similar device with an internal up / down counter and two 
outputs (RW and Y) and an SYNC input. 
It has no address lines and only supports address 0x28.
The base potmeter (output RW) seems to be compatible so this library might work for the DS3503 too.

Maybe in the future libraries for the DS3501 and DS3503 will be written too.


### Special characters

Ω == Ohm = ALT-234 (Windows)

### Hardware

```
             TOPVIEW DS3502
         +--------------------+
         |                    |
     SDA | 1               10 |  SCL
     GND | 2                9 |  V+
     VCC | 3                8 |  RL
      A1 | 4                7 |  RW
      A2 | 5                6 |  RH
         |                    |
         +--------------------+
```

|  pin  |   name   |  description         |  Notes  |
|:-----:|:--------:|:---------------------|:-------:|
|   1   |  SDA     |  I2C data            |
|   2   |  GND     |  Ground              |
|   3   |  VCC     |  Power +5V           |
|   4   |  A1      |  address bit         |  base address 0x28
|   5   |  A0      |  address bit         |
|   6   |  RH      |  high voltage        |  max 15.5V check datasheet.
|   7   |  RW      |  wiper               |
|   8   |  RL      |  low voltage         |
|   9   |  V+      |  Wiper Bias Voltage  |  V+ > Vcc check datasheet!
|   10  |  SCL     |  I2C clock           |


If voltage RH >= VCC, V+ must be >= RH, (e.g. see datasheet page 10).

Power up delay = 3 milliseconds.


### Related

Adafruit breakout

- https://cdn-learn.adafruit.com/downloads/pdf/ds3502-i2c-potentiometer.pdf

Mainly other digital potentiometers.

- https://github.com/RobTillaart/AD520x
- https://github.com/RobTillaart/AD524X
- https://github.com/RobTillaart/AD5245
- https://github.com/RobTillaart/AD5144A
- https://github.com/RobTillaart/AD5263
- https://github.com/RobTillaart/DS3502 this library
- https://github.com/RobTillaart/MCPPOT MCP41xxx and MCP42xxx SPI digital-pots
- https://github.com/RobTillaart/X9C10X


### Tested

TODO: Test on Arduino UNO and ESP32


## I2C

### I2C Address

The device has a base I2C address of 0x28 (40) and two configurable 
address pin so four sensors per I2C bus can be used.
The device supports 2.5 - 5.5 V so any 3.3 V MCU should be able to connect.
Do not forget to connect appropriate pull up resistors to the I2C SDA and SCL lines.

It is not advised to use the VCC as a chip select as it would restart 
at the last NVRAM position, and it takes ~3 ms to power up every time.
However one could probably use one of the address lines as a chip select.
E.g. keep all devices at address 0x29 and only interact with device 
with the address 0x28 after switching its chip select.
(to be verified).


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

Only test **setValue(value)** as that is the main function.


|  Clock     |  time (us)  |  Notes  |
|:----------:|:-----------:|:--------|
|   100 KHz  |             |  default
|   200 KHz  |             |
|   300 KHz  |             |
|   400 KHz  |             |  max speed datasheet
|   500 KHz  |             |  use at your own risk
|   600 KHz  |             |  use at your own risk


TODO: run performance sketch on hardware.


## Interface

```cpp
#include "DS3502.h"
```

### Constructor

- **DS3502(uint8_t address, TwoWire \*wire = &Wire)** optional select I2C bus.
Note the address range is not checked (0x28 .. 0x2B).
- **bool begin()** checks if device is visible on the I2C bus.
- **bool isConnected()** Checks if device address can be found on I2C bus.
- **uint8_t getAddress()** Returns the address set in the constructor.


### Non volatile RAM

- **bool enableNVRAM(bool nvram)** The next value written
with setValue() will be written to non volatile RAM too.
This is thus a one time flag.
- **bool isEnabledNVRAM()** get the status of the nvram flag.
Will be read from the device, so often it is more efficient to 
set the flag in the needed state.

Note that the NVRAM can be written between 50K and 200K times,
depending on temperature, see datasheet.
Although this seems much, if one calls setValue() once per second
for about 56 hours one exceeds the 200K writes.
Even once per minute will give 200K writes within less than a half year.

Therefore the library has implemented a policy to write only to 
NVRAM once if the flag is explicitly set.


### Cache

Cache can be used to speed up device interaction as the last value written
is cached by the library.
It prevents unneeded writes when the value did not change, and it can return
the last value written from cache.

- **void enableCache(bool cache)** default false;
- **bool isEnabledCache()** returns set value from device.


### SetValue

The range of values is 0..127.

- **bool setValue(uint8_t value)** writes value to wiper register and if
enabled also to non volatile ram.
If the value is the same as last value written, the write is skipped.
- **uint8_t  getValue()** reads the wiper register.
If cache is enabled, the last value written is returned from cache.


### Ohm wrappers around setValue

Based on DS3502_MAX_OHM, default max 10 kΩ.
With 127 steps that implies about 78.74 Ω per step.

- **bool setOhm(uint16_t ohm)** sets the value in ohms, exact value is truncated.
Returns false if out of range.
- **uint16_t getOhm()** calculate the last Ohm value from the actual set value.
Note this will differ from the set value often due to step size.


### Debug

- **int getLastError()** returns last error of low level communication.
Resets after being read.

|  value  |  define                |  notes  |
|:-------:|:-----------------------|:--------|
|   0x00  |  DS3502_OK             |
|   0x01  |  DS3502_READ_ERROR     |
|   0x02  |  DS3502_REQUEST_ERROR  |
|   0x03  |  DS3502_CONNECT_ERROR  |
|   0x04  |  DS3502_VALUE_ERROR    |
|  other  |  low level I2C         |


## Future

#### Must

- improve documentation
- get hardware to test
- do performance measurements.

#### Should

- investigate two DS3502 in series 
  - parallel => risk of shortage
  - series would allow fine tuning resolution.

#### Could

- add examples
- add unit tests (if possible)
- add get/setMaxOhm();  for tuning.
- voltageWrapper
  - setRange(Vrl, Vrh);
  - setVoltage(voltage);
  - getVoltage(); // Vwiper = Vrl + ((Vrh - Vrl) x wr)/127  (page 6)
  - needs cached value

#### Wont (unless)

- write DS3501 derived class?
- write DS3503 derived class?


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


