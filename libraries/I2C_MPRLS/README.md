
[![Arduino CI](https://github.com/RobTillaart/I2C_MPRLS/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/I2C_MPRLS/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/I2C_MPRLS/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/I2C_MPRLS/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/I2C_MPRLS/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/I2C_MPRLS.svg)](https://github.com/RobTillaart/I2C_MPRLS/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/I2C_MPRLS/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/I2C_MPRLS.svg?maxAge=3600)](https://github.com/RobTillaart/I2C_MPRLS/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/I2C_MPRLS.svg)](https://registry.platformio.org/libraries/robtillaart/I2C_MPRLS)


# I2C_MPRLS

Arduino library for MPRLS pressure sensors. (Honeywell).


## Description

The MPRLS sensor of Honeywell exists in many variations and ranges.
In the "sensor type" section below these variations are explained a bit.
Check the datasheet of your type for all the details.

The I2C_MPRLS library can read the sensor over I2C and returns the pressure 
in the same unit as used in the **begin()** function. 
There is no conversion.
Typical units to use are Bar, mBar, KPa or PSI, depending on the sensor used,
(see datasheet figure 2).
although one may convert the sensors specified unit to any other of course.
E.g. use a PSI sensor an configure it as a mBar sensor.

The MPRLS sensor comes with different transfer functions. 
The pressure is measured in 24 bit but only a part of the full range is used.
This can be 20-80%, 10-90% or 2.5-22.5%, depending on the transfer function.
Default transfer function is A but the library allows to set B or C.

The MPR series are relative low pressure sensors, for higher pressure 
ranges you might check e.g. the Honeywell ABP series.

Feedback, as always, is welcome.


### Hardware connection

Always check datasheet for the exact pins. 
(Figure 3. I2C Circuit Diagram)

```
        MPRLS              ARDUINO
    +----------+        +----------+
    |          |        |          |
    |     GND o|--------|o GND     |
    |     VCC o|--------|o VCC     |
    |     SDA o|--------|o SDA     |
    |     SCL o|--------|o SCL     |
    |          |        |          |
    |     EOC o|------->|o GPIO    |
    |     RES o|<-------|o GPIO    |
    |          |        |          |
    +----------+        +----------+
    
```

|  pin  |  name    |  description        |  Notes  |
|:-----:|:--------:|:--------------------|:-------:|
|  10   |  GND     |  Ground             |
|  12   |  VCC     |  Power              |
|   8   |  EOC     |  End Of Conversion  |  not supported yet.
|   9   |  RES     |  RESET              |  not supported yet.
|   2   |  SDA     |  I2C data           |
|   3   |  SCL     |  I2C clock          |   max 400 kHz.
| other |  NC      |  not connected      |


Note: SPI is not supported in this library, maybe in the future.  
The connections for SPI in datasheet miss pull up resistors.


### Sensor type

Detailed information see Figure 2. Product Nomenclature

The MPR sensor has a full product type string like 
```
MPRLS0025PA00001A 
split in fields:

MPR  L  S  0025  P  A  0000   1  A
```

|  part  |   description  |
|:-------|:---------------|
|  MPR   |  Series, Micro Pressure (R unknown)
|  L     |  model: L = Long
|  S     |  Silicone gel
|  0025  |  max pressure = 25 units
|  P     |  unit: P (Psi) or B(bar), M(mbar), K(kPa) ...
|  A     |  A=Absolute, G=Gage
|  0000  |  min pressure = 0 units
|  1     |  IO: S=SPI, digit = I2C address => 0xN8 (e.g. 1 => 0x18)
|  A     |  transfer function: A,B or C  

The last character A is the transfer function to be used to
calculate the pressure from the raw pressure count.
The library supports A B and C and raw pressure count.


### Related

Pressure sensors:
- https://github.com/RobTillaart/I2C_ABP2 (I2C) pressure sensor
- https://github.com/RobTillaart/I2C_ASDX (I2C) pressure + conversions 
- https://github.com/RobTillaart/I2C_MPRLS (I2C) pressure
- https://github.com/RobTillaart/MS4525DO (I2C) temperature pressure sensor 
- https://github.com/RobTillaart/MS5837 (I2C) temperature pressure sensor  (including pressure to altitude)
- https://github.com/RobTillaart/MS5611 (I2C) temperature pressure sensor  (including pressure to altitude)
- https://github.com/RobTillaart/MSP300 (I2C) industrial pressure transducer

Other:
- https://github.com/RobTillaart/pressure pressure conversions
- https://github.com/RobTillaart/Temperature temperature conversions 
- https://github.com/RobTillaart/printHelpers scientific notation, units. 
- https://swharden.com/blog/2017-04-29-precision-pressure-meter-project/


## I2C

### I2C address

Datasheet figure 2.
The address is hard coded in the sensor, so order the right type.

|  HEX  |  DEC  |   |  HEX  |  DEC  |
|:-----:|:-----:|:-:|:-----:|:-----:|
| 0x08  |    8  |   | 0x48  |   72  |
| 0x18  |   24  |   | 0x58  |   88  |
| 0x28  |   40  |   | 0x68  |  104  |
| 0x38  |   56  |   | 0x78  |  120  |


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

The sensor supports up to 400 kHz for I2C-bus (datasheet).

TODO: run performance sketch with hardware.

Only test **read()** as that is the main function.

|  Clock     |  time (us)  |  Notes  |
|:----------:|:-----------:|:--------|
|   100 kHz  |             |  default 
|   200 kHz  |             |
|   300 kHz  |             |
|   400 kHz  |             |  maximum datasheet


## Interface

```cpp
#include "I2C_MPRLS.h"
```


### Constructor

- **I2C_MPRLS(uint8_t address, TwoWire \*wire = &Wire)** Constructor,
I2C address and optional the wire interface can be defined.
- **bool begin(float maxPressure)** initializes range as 0..maxPressure.
- **bool begin(float minPressure, float maxPressure)** initializes range.
Note: all sensors have a range starting at zero, however one might 
set minPressure to be non zero to adjust (calibrate) the range.
The pressure is in arbitrary units, can be PSI, mBar, KPa etc.
The function **getPressure()** returns the same units. 
Returns true if the address can be found on the I2C bus.
- **void reset()** resets internal variables, including pressure.
- **bool isConnected()** tests if the address can be found on the I2C bus.
- **uint8_t getAddress()** returns the I2C address configured in the 
constructor. Mainly for debug message.


### Transfer function

The MPR sensors come with three different transfer functions,
named 'A', 'B' or 'C'. 
This function defines how the raw counter is converted to pressure.
The library defaults to 'A' but the other transfer functions to be set.

- **void setTransferFunction(char tff)** idem.
Parameter tff == 'A', 'B' or 'C'. Default = 'A'.
The tff is case sensitive as it is the last character of the 
sensor type code.
- **char getTransferFunction()** return set value or default 'A'.

There is no validity check on the TFF parameter, to allow to add 
additional (proprietary) transfer functions in the library.
This can be used to have other conversion of the raw pressure count
(rpc) to pressure. Or one could just pass through the rpc.
If TFF is not supported, the default 'A' is used.


### Read ASYNC

- **int request()** request new pressure conversion.
Returns **I2C_MPRLS_OK** or an error code.
- **bool conversionReady()** returns true if state byte indicates not busy.
Can set an error code.
- **int getData()** reads the status and pressure data, checks for errors,
calculates the pressure and set the lastRead time stamp.
Returns **I2C_MPRLS_OK** or an error code.


### Read, getPressure

Before any call to **getPressure()** one need to call **read()** 
unless one wants the last value read.

- **int read()** actually reads the status and pressure, checks for errors,
calculates the pressure and set the lastRead time stamp.
The read() call blocks for at least 5 milliseconds.
Returns **I2C_MPRLS_OK** or an error code.
- **int getPressure()** returns pressure in units as defined in **begin()**.
Multiple calls give the same value until a new call to read() is made.

Check related library: https://github.com/RobTillaart/pressure for conversions.

In the future an ASYNC API for read will be implemented. 
First need the working be validated with hardware.


### State

- **uint32_t lastRead()** time in milliseconds of last successful read of the sensor.
- **uint8_t getState()** returns last known state fetched by **read()** or **getData()**.

|  state              |  bit mask  |  meaning             |
|:--------------------|:----------:|:---------------------|
|  I2C_MPRLS_POWER    |    0x40    |  1 = device powered  |
|  I2C_MPRLS_BUSY     |    0x20    |  1 = device busy     |
|  I2C_MPRLS_MEMTEST  |    0x04    |  1 = integrity fail  |
|  I2C_MPRLS_MATH     |    0x01    |  1 = math saturation |
|  other fields       |    0x00    |  always 0


### Error 

- **uint16_t errorCount()** total counter for the number of errors occurred.
Internal counter wraps after 65535.
- **int getLastError()** returns last error and resets error flag.

|  error                    |  meaning             |
|:--------------------------|:---------------------|
|  I2C_MPRLS_OK             |  no error            |
|  I2C_MPRLS_INIT           |  begin() not called  |
|  I2C_MPRLS_READ_ERROR     |  I2C error           |
|  I2C_MPRLS_WRITE_ERROR    |  I2C error           |
|  I2C_MPRLS_CONNECT_ERROR  |  I2C error           |


### Debugging

Raw counter API, for debugging or your own conversion.

- **int rawPressureCount()** idem.
- **float getMinPressure()** idem.
- **float getMaxPressure()** idem.


## Testing

The library is not tested with hardware yet.

Your feedback is welcome.


## Future

#### Must

- update documentation
- verify with hardware
- keep in sync with I2C_ASDX if possible

#### Should

#### Could

- improve performance of pressure math
  - first need verification they work
- add lastRequest timeStamp for more efficient async
  - no need to poll state before e.g. 5 ms
  - implement conversionReady() based upon millis() and lastRequest
  - implement isBusy() upon state field.
  - lastRequest > lastRead fails when wrapping occurs. 
  - lastRequest ==> 0 after read?
- add examples
  - derived 
- check datasheet if SPI bus is faster?
- support EOC pin
- support RES (reset) pin


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

