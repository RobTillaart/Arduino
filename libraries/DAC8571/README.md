
[![Arduino CI](https://github.com/RobTillaart/DAC8571/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DAC8571/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DAC8571/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DAC8571/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DAC8571/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DAC8571.svg)](https://github.com/RobTillaart/DAC8571/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DAC8571/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DAC8571.svg?maxAge=3600)](https://github.com/RobTillaart/DAC8571/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DAC8571.svg)](https://registry.platformio.org/libraries/robtillaart/DAC8571)


# DAC8571

Arduino library for DAC8571 I2C 16 bit DAC.

## Description

**Experimental**

The DAC8571 is a small low-power, 16-bit voltage Power-On Reset to Zero output DAC.

The DAC8571 has one 16 bit DAC. The output value can be set from 0..65535.
This results in a voltage which depends on a reference voltage Vref (datasheet).
At power up it always will start with a value of zero.

The DAC8571 has a temporary register in which a value can be preloaded.
This can be used to change the DAC at a later moment.

**Not supported** is the broadcast function to change multiple DAC8571 
(and compatibles) at the same moment by using this temporary register.

As said the library is experimental need to be tested with hardware.
Feedback is always welcome, please open an issue.


#### Settling time

From datasheet page 24.

Settling time to within the 16-bit accurate range of the DAC8571 is achievable within 
10 μs for a full-scale code change at the input. 
Worst case settling times between consecutive code changes is typically less than 2 μs,
therefore, the update rate is limited by the I2C interface.


## I2C

#### Address

The DAC8571 support 2 addresses by means of an A0 address pin.


|  Address  |   A0   |
|:---------:|:------:|
|   0x4C    |   LOW  |
|   0x4E    |  HIGH  |

It might be possible to connect this address pin to an IO pin
and keep only one HIGH and remaining LOW to support many devices.
This is not tested, feedback welcome.


#### I2C performance

Extend table, use output of **DAC8571_performance.ino**

Time in microseconds.  
array == write(array, length)
Assumption all write modi have similar performance.

Tested on Arduino UNO.

|  Speed   |  function  |  time  |  notes  |
|:--------:|:----------:|:------:|:-------:|
|  100000  |  write()   |        |
|  100000  |  read()    |        |
|  200000  |  write()   |        |
|  200000  |  read()    |        |
|  400000  |  write()   |        |
|  400000  |  read()    |        |


Test ESP32 (Kudos to Paul)

|  Speed   |  write()  |  read()  |  write(array)  |  Notes  |
|:--------:|:---------:|:--------:|:--------------:|:--------|
|  50000   |  800.01   |  800.04  |                |
|  100000  |  439.02   |  441.18  |  2100.01       |  array == 10 elements!
|  200000  |  239.12   |  242.41  |  1090.82       |
|  300000  |  178.05   |  181.81  |   757.57       |
|  400000  |  148.94   |  156.83  |   595.24       |
|  500000  |  131.57   |  142.93  |   497.99       |
|  600000  |  120.68   |  136.35  |   428.59       |
|  700000  |  113.19   |  130.40  |   384.64       |
|  800000  |  108.12   |  128.18  |   351.85       |
|  900000  |   98.21   |  106.67  |   317.45       |
|  1000000 |   94.11   |   94.58  |   296.88       |



#### I2C multiplexing

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


#### Related

- https://github.com/RobTillaart/AD5680 (18 bit DAC)
- https://github.com/RobTillaart/DAC8550
- https://github.com/RobTillaart/DAC8551
- https://github.com/RobTillaart/DAC8552
- https://github.com/RobTillaart/DAC8554
- https://github.com/RobTillaart/DAC8571
- https://github.com/RobTillaart/MCP_DAC
- https://github.com/RobTillaart/MCP_ADC


## Interface

```cpp
#include "DAC8571.h"
```

#### Constructor

- **DAC8571(uint8_t address = 0x4C, TwoWire \*wire = &Wire)** constructor with I2C address.
Default is 0x4C, optional set the WireN I2C bus.
- **bool begin(uint16_t value = 0)** Set initial value for the DAC, typical zero (power on default).
Returns false if address out of range, or if device cannot be seen on the I2C bus.
Returns **true** if successful.
- **bool isConnected()** test to see if address can be reached on the I2C bus.
- **uint8_t getAddress()** returns address set in constructor.


#### Core

The DAC8571 has one 16 bit DAC. The output value can be set from 0..65535.

- **bool write(uint16_t value)** writes a value 0..65535 to the DAC.
NO default, user must explicit set value.
- **uint16_t lastWrite()** get last value written from cache (fast).
- **uint16_t read()** get last written value from device.

Percentage wrappers
- **void setPercentage(float perc)** set 0.00 .. 100.00
- **float getPercentage()** returns 0.0 .. 100.0


#### Write modi

The DAC8571 can be written in different modi (datasheet page 19).
Not all modi are supported yet, these need testing.

- **void setWriteMode(uint8_t mode = DAC8571_MODE_NORMAL)**
- **uint8_t getWriteMode()**


Setting the mode will be applied for all writes until mode is changed.

|  Mode                    |  Meaning  |
|:-------------------------|:----------|
| DAC8571_MODE_STORE_CACHE |  store value in temporary register. Preparation for (2, 3 and 4)
| DAC8571_MODE_NORMAL      |  update DAC with value written. **DEFAULT**.
| DAC8571_MODE_WRITE_CACHE |  writes the temporary register to DAC, ignores new value.
| DAC8571_MODE_BRCAST_0    |  broadcast update. **Not supported yet**. See below.
| DAC8571_MODE_BRCAST_1    |  broadcast update. **Not supported yet**. See below.
| DAC8571_MODE_BRCAST_2    |  broadcast update. **Not supported yet**. See below.
| other                    |  maps onto default **DAC8571_MODE_NORMAL**.


#### Write multiple values - High speed mode.

The maximum length depends on the internal I2C BUFFER of the board.
For Arduino this is typical 32 bytes so it allows 14 values.

- **void write(uint16_t arr[n], uint8_t length)** Writes a buffer with 
max 14 values in one I2C call. 
The last value written will be remembered in **lastWrite()**.


#### Power Down mode

To investigate: Mixes also with broadcast ==> complex API.

- **void powerDown(uint8_t pdMode = 0)** default low power.
- **void wakeUp(uint16_t value = 0)** wake up, DAC value set to zero by default.

See table 6, page 22 datasheet for details.

|  Power Down Mode       |  Meaning  |
|:-----------------------|:----------|
|  DAC8571_PD_LOW_POWER  |  170 uA
|  DAC8571_PD_FAST       |  250 uA
|  DAC8571_PD_1_KOHM     |  200 nA, GND 1 KOhm
|  DAC8571_PD_100_KOHM   |  200 nA, GND 100 KOhm
|  DAC8571_PD_HI_Z       |  200 nA, open circuit, high impedance


#### Broadcast mode

**Not supported**

Different ways possible, need to investigate API. (page 19)

Three broadcast commands exists:

|  Mode                   |  Meaning  |
|:------------------------|:----------|
|  DAC8571_MODE_BRCAST_0  | Load all devices from temporary register
|  DAC8571_MODE_BRCAST_1  | Load all devices with data.
|  DAC8571_MODE_BRCAST_2  | Power down all devices



#### Error codes

- **int lastError()** always check this value after a read() / write() 
to see if it was DAC8571_OK.
After the call to **lastError()** the error value is reset to DAC8571_OK.

|  Error code             |  Value  |  Notes  |
|:------------------------|:-------:|:--------|
|  DAC8571_OK             |  0x00   |
|  DAC8571_I2C_ERROR      |  0x81   |
|  DAC8571_ADDRESS_ERROR  |  0x82   |
|  DAC8571_BUFFER_ERROR   |  0x83   |  write(arr, length) length error


## Future

#### Must

- get hardware to test
- improve documentation
- test different write modi

#### Should

- extend performance table
- replace magic numbers

#### Could

- add examples
- investigate broadcast support
- investigate known compatibles
  - including SPI versions?

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


