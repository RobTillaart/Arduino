
[![Arduino CI](https://github.com/RobTillaart/I2C_MPRLS/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/I2C_MPRLS/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/I2C_MPRLS/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/I2C_MPRLS/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/I2C_MPRLS/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/I2C_MPRLS.svg)](https://github.com/RobTillaart/I2C_MPRLS/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/I2C_MPRLS/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MPRLS.svg?maxAge=3600)](https://github.com/RobTillaart/I2C_MPRLS/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MPRLS.svg)](https://registry.platformio.org/libraries/robtillaart/MPRLS)


# I2C_MPRLS

Arduino library for MPRLS pressure sensors. (Honeywell).


## Description

The MPRLS sensor of Honeywell exists in many variations.
Check the datasheet of your type for all the details.

The I2C_MPRLS library can read the sensor over I2C and returns the pressure 
in the same unit as used in the **begin(maxPresseure, minPressure)** function. 
There is no conversion.
Typical units to use are Bar, mBar, KPa or PSI, depending on the sensor used,
(see datasheet figure 2).
although one may convert the sensors specified unit to any other of course.
E.g. use a PSI sensor an configure it as a mBar sensor.

The MPRLS sensor comes with different transfer functions. 
The pressure is measured in 24 bit but only a part of the full range is used.
This can be 20-80%, 10-90% or 2.5-22.5%, depending on the transfer function.
Default transfer function is A but the library allows to set B or C.

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

The MPR sensor has a full product type like 
```
MPR  L  S  0025  P  A  0000   1  A
```

The first character A means Absolute.

The last character A is the transfer function to be used to
calculate the pressure from the raw pressure count.


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

The sensor supports up to 400 kHz.

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
set minPressure to be non zero to adjust the range.
The pressure is in arbitrary units, can be PSI, mBar, KPa etc.
The function **getPressure()** returns the same units. 
Returns true if address can be found  on I2C bus.
- **void reset()** resets internal variables, including pressure.
- **bool isConnected()** tests if address can be found on I2C bus.
- **uint8_t getAddress()** returns I2C address used.
Mainly for debug message.


### Transfer function

The MPR sensor comes with three different transfer functions,
named A, B or C. The library defaults to A but allows the other
transfer functions to be chosen.

- **void setTransferFunction(char tff)** idem.
Parameter tff == 'A', 'B' or 'C'. Default = 'A'.
The tff is case sensitive as it is the last character of the 
sensor type code.
- **char getTransferFunction()** return set value or default 'A'.

There is no validity check on the TFF parameter, to allow to add 
additional transfer functions in the library.
If TFF is not supported, the default 'A' is used.
This can be used to have other conversion of the raw pressure count
(rpc) to pressure. Or one could just pass through the rpc.
  

### Read, getPressure

Before any call to **getPressure()** one need to call **read()** 
unless one wants the last value read.

- **int read()** actually reads the sensor, checks for errors,
calculates the pressure and set the lastRead time stamp.
The read call blocks for at least 5 milliseconds.
Returns **I2C_MPRLS_OK** or an error code.
- **int getPressure()** returns pressure in units as defined in **begin()**.
Multiple calls give the same value until a new call to read() is made.

Check related library: https://github.com/RobTillaart/pressure for conversions.

In the future an ASYNC API for read will be implemented. 
First need the working be validated with hardware.


### State

- **uint32_t lastRead()** time in milliseconds of last successful read of the sensor.
- **int state()** last known state from **read()**, bit masks.

|  state              |  value  |  meaning             |
|:--------------------|:-------:|:---------------------|
|  I2C_MPRLS_POWER    |  0x40   |  no error            |
|  I2C_MPRLS_BUSY     |  0x20   |  begin() not called  |
|  I2C_MPRLS_MEMTEST  |  0x04   |  I2C error           |
|  I2C_MPRLS_MATH     |  0x01   |  I2C error           |


### Error 

- **uint16_t errorCount()** total counter for the number of errors occurred.
Internal counter wraps after 65535.
- **int getLastError()** returns last error and resets.

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

- update documentation.
- keep in sync with I2C_ASDX if possible.

#### Should

- async API
  - int request();
  - bool isReady();
  - int readAsync();
- elaborate sensor type section.

#### Could

- improve performance of pressure math.
  - first need verification they work.
- add examples

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

