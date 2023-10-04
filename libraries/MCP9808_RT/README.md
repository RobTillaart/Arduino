
[![Arduino CI](https://github.com/RobTillaart/MCP9808_RT/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MCP9808_RT/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MCP9808_RT/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MCP9808_RT/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MCP9808_RT/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MCP9808_RT.svg)](https://github.com/RobTillaart/MCP9808_RT/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MCP9808_RT/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MCP9808_RT.svg?maxAge=3600)](https://github.com/RobTillaart/MCP9808_RT/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MCP9808.svg)](https://registry.platformio.org/libraries/robtillaart/MCP9808)


# MCP9808_RT

Arduino library for I2C MCP9808 temperature sensor.


## Description

The MCP9808 is a temperature sensor that measures typically in 1/16th == 0.0625° Celsius.
What makes this sensor interesting is the **ALERT** pin, which allows triggering of any piece
of electronics if the temperature hits a predefined value or temperature zone.


### MCP9808 breakout board

```
//
//       Adafruit MCP9808 breakout board
//       +----------+
//       |0   ALERT |---------------+--[ 4K7 ]---- +5V
//       |       A2 |---- GND       |
//       |       A1 |---- GND       +--[ LED ]---- GND  // or other electronics.
//       |       A0 |---- GND
//       |      SDA |---- I2C MCU
//       |      SCL |---- I2C MCU
//       |      GND |---- GND MCU
//       |0     VCC |---- +5V
//       +----------+
//
//       address above is 24
//
```


## Interface

```cpp
#include "mcp9808.h"
```

#### Constructor

- **MCP9808(const uint8_t address, TwoWire \*wire = &Wire)** Set the device address.
Option one can set the I2C bus if multiple I2C buses are present.
Default I2C bus is Wire.

**0.4.0 Breaking change**

The user must initialize the I2C bus in **setup()**, the library doesn't do that
since 0.4.0. So one need to call **Wire.begin()** or **Wire.begin(SDA, SCL)**.


#### Address

There are max 8 sensors on one I2C bus.
Normal address = 0011xxx where xxx = A2, A1, A0  

| Address |  HEX   |  A2  |  A1  |  A0  |
|:-------:|:------:|:----:|:----:|:----:|
|    24   |  0x18  |  0   |  0   |  0   |
|    25   |  0x19  |  0   |  0   |  1   |
|    26   |  0x1A  |  0   |  1   |  0   |
|    27   |  0x1B  |  0   |  1   |  1   |
|    28   |  0x1C  |  1   |  0   |  0   |
|    29   |  0x1D  |  1   |  0   |  1   |
|    30   |  0x1E  |  1   |  1   |  0   |
|    31   |  0x1F  |  1   |  1   |  1   |

On request manufacturer will provide 1001xxx as base address 
allowing up to 16 temp sensors on one bus.


#### Temperature and status

- **void setOffset(float offset = 0.0)** set an offset to calibrate or to correct for self heating. 
The value of offset is not validated to keep footprint small.
- **float getOffset()** return value of offset (default 0).
- **float getTemperature()** read the ambient temperature.
- **uint8_t getStatus()** returns the status bits of the last call to **getTemperature()**

The value returned by **getStatus()** is the last value read by the call to **GetTemperature()**.  
There are three bits, see table below. 
A value of 6 == mask == 110 means that TA is above the upper AND above the critical temperature.

|  Bit  |  Mask  |  Description  |  Notes           |
|:-----:|:------:|:--------------|:-----------------|
|   0   |  0x01  |  TA < TLOWER  |  lower           |
|   1   |  0x02  |  TA > TUPPER  |  larger          |
|   2   |  0x04  |  TA ≥ TCRIT   |  larger or equal |


#### Resolution

- **void setResolution(uint8_t resolution = 3)** set the resolution, if resolution > 3, it is not set.
- **uint8_t getResolution()** returns the resolution set.

|  Value  |  Resolution  |  Conversion  |  Samples/s  |  Notes   |
|:-------:|:-------------|:------------:|:-----------:|:--------:|
|    0    |  0.5°C       |     30 ms    |   33        |          |
|    1    |  0.25°C      |     65 ms    |   15        |          |
|    2    |  0.125°C     |    130 ms    |   7         |          |
|    3    |  0.0625°C    |    250 ms    |   4         |  default |


Note: for the same resolution the MCP9808 is about 3x faster than 
the popular DS18B20.


#### Configuration

- **void setConfigRegister(uint16_t configuration)** see table below + read datasheet.
- **uint16_t getConfigRegister()** return set value.

| Bit   | Mask   | Name       | Description     | Value  |
|:-----:|:------:|:-----------|:----------------|:-------|
| 0     | 0x0001 | ALT MOD    | alert mode      | **0 = comparator output**,  1 = interrupt output
| 1     | 0x0002 | ALT POL    | alert polarity  | **0 = active low**,         1 = active high
| 2     | 0x0004 | ALT SEL    | alert select    | **0 = upper+lower+crit**,   1 = critical only
| 3     | 0x0008 | ALT CNT    | alert control   | **0 = OFF**,                1 = ON
| 4     | 0x0010 | ALT STAT   | alert status    | **0 = OFF**,                1 = ON  (read!)
| 5     | 0x0020 | INT CLR    | interrupt clear | **0 = none**,               1 = clear interrupt
| 6     | 0x0040 | WIN LOC    | lock Tup + Tlow | **0 = unlocked**,           1 = Lock
| 7     | 0x0080 | CRT LOC    | lock Tcritical  | **0 = unlocked**,           1 = Lock
| 8     | 0x0100 | SHDN       | shutdown,       | **0 = continuous mode**,    1 = low power
| 9-10  | 0x0600 | Hysteresis | Thysteresis     | **00 = 0°C**,  01 = 1.5°C,  10 = 3°C,  11 = 6°C
| 11-15 |        | always 0   |                 |

Check datasheet for the details...


#### Temperature limits / thresholds

- **void setTupper(float temp)** write upper register, accuracy 0.25°C.
- **float getTupper()** idem.
- **void setTlower(float temp)** write lower register, accuracy 0.25°C.
- **float getTlower()** idem.
- **void setTcritical(float temp)** write critical register, accuracy 0.25°C.
- **float getTcritical()** idem.

The values written in these registers, are the trigger values for the status
read with getStatus. Note that the Hysteresis temperature delta affects the
value of these triggers.

The values set are not validated to keep footprint of the library small.


#### Miscellaneous

- **uint16_t getManufacturerID()** returns 84 (my version).
- **uint8_t getDeviceID()** returns 0 (my version).
- **uint8_t getRevision()** returns 84 (my version).
- **uint16_t getRFU()** returns 29 (my version). Reserved for future use. 


#### Hidden registers

The MCP9808 has hidden registers mentioned only on p.16 of the datasheet.
These are for testing and calibration.
The library prevents reading / writing them to keep sensors working.


## Future

#### Must

- refactor the constructor to include Wire param
- add begin() function.


#### Should

- update documentation
  - compare DS18B20?
- test more
  - negative temperatures
- do unit test
- check for optimizations


#### Could

- add examples 
  - for the **ALERT**
  - multi sensor


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

