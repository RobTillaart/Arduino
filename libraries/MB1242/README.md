
[![Arduino CI](https://github.com/RobTillaart/MB1242/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MB1242/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MB1242/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MB1242/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MB1242/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MB1242.svg)](https://github.com/RobTillaart/MB1242/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MB1242/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MB1242.svg?maxAge=3600)](https://github.com/RobTillaart/MB1242/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MB1242.svg)](https://registry.platformio.org/libraries/robtillaart/MB1242)


# MB1242

Arduino library for the MaxBotix I2C MB1242 distance sensor.


## Description

**Experimental - work in progress**

This library is to use the MaxBotix I2C MB1242 and compatible distance
sensors MB1202, MB1212, MB1222 and MB1232.

Note: the library is not tested with hardware yet.

If you have the hardware, please test and provide feedback if the library
works or not so the library can mature.


_Came across this sensor and found it interesting as
it supports a range up to 7.5 meters.
To understand the working of the device I wrote this library for it.
So consider the current version "work in progress"._


TODO: elaborate description.

|  property     |       |
|:--------------|:------|
|  Range        |  20/25 cm up to 7.5 meters
|  Voltage      |  3.0 - 5.5 V, should work with ESP32 and AVR.
|  Temperature  |  0°C - 65°C == 32°F - 149°F
|  Sample rate  |  10 Hz up to 40 Hz (need statusPin, see below).
|  Start time   |  operational after ~115 ms


Feedback as always is welcome.


### Correction for speed of sound.

The library or sensor does not compensate the speed of sound for
temperature or humidity.
Please look at the SRF05 library for a function to calculate the
speed of sound for different T and H.

TODO: add function to calculate correction factor.


### Datasheet warning

_Do not apply this product to safety protection devices or emergency stop equipment,
and any other applications that may cause personal injury due to the product's failure._


### Hardware

```
            Top view MB12X2
         +--------------------+
   pin 7 | o  GND             |
   pin 6 | o  VCC             |
   pin 5 | o  SCL             |
   pin 4 | o  SDA             |
   pin 3 | o  not used        |
   pin 2 | o  status          |
   pin 1 | o  address select  |
         +--------------------+
```

|  pin  |  description  |
|:-----:|:--------------|
|   7   |  Ground
|   6   |  VCC - 3.0-5.5 Volt
|   5   |  SCL - I2C clock
|   4   |  SDA - I2C data
|   3   |  not used
|   2   |  status + (not in library) address announce
|   1   |  address select


Pin 2 is HIGH during distance measurement, and LOW when IDLE.
This can be used to detect when a measurement is done.
During power up pin 2 "sends" a HIGH pulse indicating its 8 bit address.
100 us per unit, so address 224 gives a pulse of 22.400 micros.
One can measure this with digitalRead() or pulseIn() if you can
control the startup. The library does not support this function.

Using the statusPin can speed up the detection that the device is ready,
and thus the reading of the device.

If pin 1 is HIGH or unconnected the device will use the internal I2C
address set with changeAddress().
If pulled LOW it will use factory default address.
The library does not support this function.
Advice is to hardwire this pin with a switch to GND in your project.


### Compatibles

Datasheet (ds) mentions:

|  device  |  min range    |  ds  |   beam   |  notes  |
|:---------|:-------------:|:----:|:--------:|:--------|
|  MB1202  |  20 cm /  8"  |  09  |   wide   |  people, high sensitivity
|  MB1212  |  20 cm /  8"  |  10  |  medium  |  best balance
|  MB1222  |  25 cm / 10"  |  11  |  medium  |  best balance
|  MB1232  |  25 cm / 10"  |  12  |  narrow  |  large targets
|  MB1242  |  25 cm / 10"  |  13  |  narrow  |  very large targets


### Related

Distance sensors
- https://github.com/RobTillaart/A02YYUW - Serial distance sensor.
- https://github.com/RobTillaart/MB1242 - I2C distance sensor.
- https://github.com/RobTillaart/SRF05 - distance sensor with SOS calibration.
- https://github.com/RobTillaart/US500 - US500 + US4000 underwater distance sensor.

Other
- https://maxbotix.com/ - company that makes the MB1242
- https://github.com/RobTillaart/lengthConverter - idem
- https://github.com/RobTillaart/printHelpers - print inches and feet
- https://github.com/RobTillaart/map2colour - colour mapping of distance
- https://github.com/stoduk/PingSerial  Serial IO with distance sensors e.g. US-100


### Tested

TODO: Test with hardware on Arduino UNO and ESP32.


## I2C

### I2C Address

The default address is 0x70 (112).
The address can be changed with **changeAddress(uint8_t address)**.
Invalid addresses reported in the datasheet are 0, 80, 164, 170.
ChangeAddress() will return false if these are used.

It is not clear if a restart is needed when the address is changed.

TODO: Test with hardware.


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

Datasheet states it only works at 20 - 100 kHz.

TODO: Test with hardware.


## Interface

```cpp
#include "MB1242.h"
```

### Constructor

- **MB1202(uint8_t address, TwoWire \*wire = &Wire)** set address, optional select I2C bus.
- **MB1212(uint8_t address, TwoWire \*wire = &Wire)** set address, optional select I2C bus.
- **MB1222(uint8_t address, TwoWire \*wire = &Wire)** set address, optional select I2C bus.
- **MB1232(uint8_t address, TwoWire \*wire = &Wire)** set address, optional select I2C bus.
- **MB1242(uint8_t address, TwoWire \*wire = &Wire)** set address, optional select I2C bus.
- **bool begin()** resets internal variables and checks if device address is
visible on the I2C bus.
- **bool isConnected()** Checks if device address can be found on I2C bus.
- **uint8_t getAddress()** Returns the device address, default 0x70 (112).


### Async Request

- **bool requestDistance()** request a new distance measurement.
One can poll with ready() when the request is done.
- **bool requestInProgress()** idem.
- **uint32_t lastRequest()** returns timestamp of last request.
Allows low level tracking.
- **void setStatusPin(uint8_t statusPin)** option to connect pin 2
to the library so ready() can detect measurement ready much faster.
It is possible to use an IRQ pin as statusPin and set a flag
in the IRQ.
- **bool ready()** returns true if either the statusPin indicates ready or
when 100 milliseconds after a request was made.
The function will return false if no request was made.
If the statusPin is set, it will read the statusPin instead of
waiting hard for 100 millis.

When using the statusPin, sampling can be up to 40 Hz, "blocking" wait
for 100 ms will limit the sample rate to 10 Hz.

### Async Read

- **int16_t readCM()** read the measurement from the device.
Returns range in centimeter.
Should return a value between 20 and 750.
Value 0 indicates an error.
- **float readMeter()** wrapper around readCM(), converts to meters.
- **float readInch()** wrapper around readCM(), converts to inches.
- **float readFeet()** wrapper around readCM(), converts to feet.
Note decimal part are 'decimals', 0.5 feet == 6 inch.
- **uint32_t lastRead()** returns timestamp of last read.

The printHelpers library can help to pretty print inch and feet.


### Address

- **bool changeAddress(uint8_t address)** changes the address of the device.
Invalid addresses 0, 80, 164, 170 are checked and return false.


### Debug

- **uint8_t getLastError()** returns last error of low level communication.
Reading resets the error flag, so you might need to copy its value.

|  value  |  meaning  |
|:-------:|:----------|
|    00   |  MB1242_OK
|  1..15  |  low level I2C errors
|    16   |  MB1242_NOT_READY
|    17   |  MB1242_REQUEST_ERROR
|    18   |  MB1242_NO_REQUEST_PENDING
|    19   |  MB1242_INVALID_ADDRESS


## Future

#### Must

- improve documentation
- get hardware to test
- fix TODO's in code and documentation.

#### Should

- SOS calibration for temperature and humidity.

#### Could

- add examples
  - sketch to read startup pulse?
- elaborate derived classes? needed?

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


