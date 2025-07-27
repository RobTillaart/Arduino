
[![Arduino CI](https://github.com/RobTillaart/INA228/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/INA228/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/INA228/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/INA228/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/INA228/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/INA228.svg)](https://github.com/RobTillaart/INA228/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/INA228/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/INA228.svg?maxAge=3600)](https://github.com/RobTillaart/INA228/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/INA228.svg)](https://registry.platformio.org/libraries/robtillaart/INA228)


# INA228

Arduino library for the INA228 power sensor.


## Description

**Experimental**

This library controls the INA228, a device that measures voltage,
current, power, temperature and more.

The INA228 sensor differs from the better known INA226.
Most important difference is that the INA228 has a 20 bit ADC.
This should result in higher precision however this is expected to only
be visible with stable loads and low noise.

An important difference is that the INA228 works up to 85 Volts,
which is more than twice the 36 volt of the INA226.
The INA228 has a build in temperature sensor (±1°C) to be used for
monitoring and temperature compensation.

Finally the INA228 has an **energy** and **charge** register.
These are values accumulated over time, and only work in continuous mode.
(to be investigated what those mean ).

The INA228 also provides an **ALERT** line, to generate an interrupt
in case a predefined threshold has been met.
This can be an under- or over-voltage, temperature or power limit.
The library does not handle these interrupts.

The library is limited tested and verified with hardware.

==> **USE WITH CARE**

Feedback as always is welcome.


### Breaking change 0.3.0

The function **getCharge()** is updated as the value can be negative too.
The previous versions assumed it could only be positive. See #22.
0.3.0 fixed the **getEnergy()** which only can have positive values
and was broken in 0.2.0. Versions before 0.3.0 are obsolete now.


### Details

The INA228 is a voltage, current and power measurement device.
A few important data, Read the datasheet for the details, 
Section 7, Page 12++.


|  description   |  value      |  notes  |
|:---------------|:-----------:|:--------|
|  bus voltage   |  85 Volt    |  unclear for how long.
|  ADC           |  20 bit     |
|  alert timing  |  75 µs.     |


Two breakout boards are known, with completely different maximum current.
This max current depends on the width of the traces on the PCB and the 
shunt used. See the links below for more details.


|  supplier  |  Shunt Ω |  Current  |  Shunt V  |  URL  |
|:----------:|:--------:|:---------:|:---------:|:------|
|  Adafruit  |  0.015   |   10 Amp  |   150 mV  |  https://www.adafruit.com/product/5832
|  Mateksys  |  0.0002  |  204 Amp  |    41 mV  |  https://www.mateksys.com/?portfolio=i2c-ina-bm


Both are verified to work but not the full range. (See #10)


### Calibrating

Note the power and the current are not meaningful without calibrating the sensor.
Also the values are not meaningful if there is no shunt connected.


### Schema LOW SIDE


```
         GND                           VCC
          |                             |
          |                             |
          |            +----[ LOAD ]----+
          |            |                |
          |            |                |
      /-------------------------------------\
      |  VIN-         VIN+             VBUS |
      |                                     |
      |                                     |
      |         INA 228 BREAKOUT            |
      |                                     |
      |                                     |
      \-------------------------------------/

```

_Tested_


### Schema HIGH SIDE


```
         GND                          VCC
          |                            |
          |                            |
          +---[ LOAD ]---+        +----+
                         |        |    |
                         |        |    |
      /-------------------------------------\
      |                 VIN-     VIN+  VBUS |
      |                                     |
      |                                     |
      |         INA 228 BREAKOUT            |
      |                                     |
      |                                     |
      \-------------------------------------/

```

_Tested_


### Special characters

- Ω == Ohm = ALT-234 (Windows)
- µ == micro = ALT-0181 (Windows)
- ° == degree = ALT-0176 (Windows)
- ± == plus minus = ALT-0177 (Windows)


### Related

- https://www.ti.com/product/INA228#tech-docs
- https://www.ti.com/product/INA228#params
- https://www.ti.com/document-viewer/INA228/datasheet
- https://github.com/RobTillaart/INA219  26 Volt, I2C, 12 bit
- https://github.com/RobTillaart/INA226  36 Volt, I2C, 16 bit
- https://github.com/RobTillaart/INA228  85 Volt, I2C, 20 bit
- https://github.com/RobTillaart/INA236  48 Volt, I2C, 16 bit
- https://github.com/RobTillaart/INA229  85 Volt, SPI, 20 bit
- https://github.com/RobTillaart/INA239  85 Volt, SPI, 16 bit
- https://github.com/RobTillaart/INA3221_RT  26 Volt, I2C, 13 bits (3 channel)
- https://www.adafruit.com/product/5832
- https://www.mateksys.com/?portfolio=i2c-ina-bm
- https://github.com/RobTillaart/printHelpers  (for scientific notation)


## I2C

### Address

The sensor can have 16 different I2C addresses,
which depends on how the A0 and A1 address lines
are connected to the SCL, SDA, GND and VCC pins.

See table - from datasheet table 7-2, page 19.

|  A1   |  A0   |  Addr  |  HEX   |   |  A1   |  A0   |  Addr  |  HEX   |
|:-----:|:-----:|:------:|:------:|:-:|:-----:|:-----:|:------:|:------:|
|  GND  |  GND  |   64   |  0x40  |   |  SDA  |  GND  |   72   |  0x48  |
|  GND  |  VCC  |   65   |  0x41  |   |  SDA  |  VCC  |   73   |  0x49  |
|  GND  |  SDA  |   66   |  0x42  |   |  SDA  |  SDA  |   74   |  0x4A  |
|  GND  |  SCL  |   67   |  0x43  |   |  SDA  |  SCL  |   75   |  0x4B  |
|  VCC  |  GND  |   68   |  0x44  |   |  SCL  |  GND  |   76   |  0x4C  |
|  VCC  |  VCC  |   69   |  0x45  |   |  SCL  |  VCC  |   77   |  0x4D  |
|  VCC  |  SDA  |   70   |  0x46  |   |  SCL  |  SDA  |   78   |  0x4E  |
|  VCC  |  SCL  |   71   |  0x47  |   |  SCL  |  SCL  |   79   |  0x4F  |


Note this might differ per breakout board.


### Performance

Run **INA228_performance.ino** sketch to get a first indication.
Numbers below are based upon tests with the Adafruit board.

Time in micros, I2C speed in kHz.

|  I2C  |  function         |  time  |  notes  |
|:-----:|:------------------|:------:|:-------:|
|  100  |  getBusVoltage    |   684  |  100%
|  100  |  getShuntVoltage  |  1248  |
|  100  |  getCurrent       |   684  |
|  100  |  getPower         |   684  |
|  100  |  getTemperature   |   580  |
|  100  |  getEnergy        |   940  |
|  100  |  getCharge        |   960  |
|       |                   |        |  other functions similar gain.
|  200  |  getBusVoltage    |   404  |   60%
|  400  |  getBusVoltage    |   252  |   37%
|  800  |  getBusVoltage    |   184  |   27%


Most non core functions are as fast as **getTemperature()**


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
#include "INA228.h"
```

### Constructor

- **INA228(const uint8_t address, TwoWire \*wire = Wire)** Constructor to set
the address and optional Wire interface.
- **bool begin()** initializes the class.
Returns true if the INA228 address is on the I2C bus.
  - Note: one needs to set **Wire.begin()** before calling **begin()**.
  - Note: call **setMaxCurrentShunt(maxCurrent, shunt)** to calibrate your INA228
- **bool isConnected()** returns true if the INA228 address is on the I2C bus.
- **uint8_t getAddress()** returns the address set in the constructor.

### BUS VOLTAGE

Main function + wrappers.

- **float getBusVoltage()** idem. Returns value in volts. Max 85 Volt.
This value is always positive.
- **float getBusVolt()**
- **float getBusMilliVolt()**
- **float getBusMicroVolt()**

### SHUNT VOLTAGE

- **float getShuntVoltage()** idem, Returns value in volts.
Note the value can be positive or negative as the INA228 is bidirectional.
- **float getShuntVolt()**
- **float getShuntMilliVolt()**
- **float getShuntMicroVolt()**
- **int32_t getShuntVoltageRAW()**

### SHUNT CURRENT

- **float getCurrent()** returns the current through the shunt in Ampere.
Note this value can be positive or negative as the INA228 is bidirectional.
- **float getAmpere()**
- **float getMilliAmpere()**
- **float getMicroAmpere()**

### TEMPERATURE

- **float getTemperature()** returns the temperature in Celsius.

### POWER

- **float getPower()** returns the current x BusVoltage in Watt.
- **float getWatt()**
- **float getMilliWatt()**
- **float getMicroWatt()**
- **float getKiloWatt()**

### ENERGY

See page 13++, page 32, 8.1.2

The **getEnergy()** only has meaning in continuous mode.
This is an accumulation register and can be reset to zero by **setAccumulation(1)**.
Note this function resets other accumulation registers too.

The accuracy of **getEnergy()** is 1.0% full scale (maximum).

- **double getEnergy()** return Joule (elaborate).
- **double getJoule()**
- **double getMegaJoule()**
- **double getKiloJoule()**
- **double getMilliJoule()**
- **double getMicroJoule()**
- **double getWattHour()**
- **double getKiloWattHour()**

### CHARGE

The **getCharge()** only has meaning in continuous mode.
This is an accumulation register and can be reset to zero by **setAccumulation(1)**.
Note this function resets other accumulation registers too.

The accuracy of **getCharge()** is 1.0% full scale (maximum).

- **double getCharge()** return Coulomb (elaborate).
- **double getCoulomb()**
- **double getMilliCoulomb()**
- **double getMicroCoulomb()**


### Configuration

Read datasheet for details, section 7.6.1.1, page 22

- **void reset()** Resets the device, be aware that you need to calibrate the sensor
(shunt register) again ==> call **setMaxCurrentShunt()** and more.
- **bool setAccumulation(uint8_t value)** value: 0 == normal operation,  
1 = clear Energy and Charge accumulation registers.
- **bool getAccumulation()** return set value. (TODO check).
- **void setConversionDelay(uint8_t steps)**  Conversion delay in 0..255 steps of 2 ms
- **uint8_t getConversionDelay()** return set value.
- **void setTemperatureCompensation(bool on)** see Shunt temperature coefficient below.
- **bool getTemperatureCompensation()** return set value.
- **bool setADCRange(bool flag)** flag = false => 164 mV, true => 41 mV
Since 0.3.1 setADCRange() calls setMaxCurrentShunt() to update the internal LSB values.
- **bool getADCRange()** return set value.

TODO: wrapper + better name for setAccumulation().  resetEnergyCharge() { setAccumulation(true) }

TODO: examples to show the effect of the ADC configuration.


### ADC mode

Read datasheet for details, section 7.6.1.2, page 22++

- **bool setMode(uint8_t mode = INA228_MODE_CONT_TEMP_BUS_SHUNT)** default all on.
- **uint8_t getMode()** return set value.

|  MODE                           |  value  |  notes  |
|:--------------------------------|:-------:|:--------|
| INA228_MODE_SHUTDOWN            |   0x00  |  See 0x08.
| INA228_MODE_TRIG_BUS            |   0x01  |
| INA228_MODE_TRIG_SHUNT          |   0x02  |
| INA228_MODE_TRIG_BUS_SHUNT      |   0x03  |
| INA228_MODE_TRIG_TEMP           |   0x04  |
| INA228_MODE_TRIG_TEMP_BUS       |   0x05  |
| INA228_MODE_TRIG_TEMP_SHUNT     |   0x06  |
| INA228_MODE_TRIG_TEMP_BUS_SHUNT |   0x07  |
| INA228_MODE_SHUTDOWN2           |   0x08  |  There are two shutdowns.
| INA228_MODE_CONT_BUS            |   0x09  |
| INA228_MODE_CONT_SHUNT          |   0x0A  |
| INA228_MODE_CONT_BUS_SHUNT      |   0x0B  |
| INA228_MODE_CONT_TEMP           |   0x0C  |
| INA228_MODE_CONT_TEMP_BUS       |   0x0D  |
| INA228_MODE_CONT_TEMP_SHUNT     |   0x0E  |
| INA228_MODE_CONT_TEMP_BUS_SHUNT |   0x0F  |


### ADC conversion time

- **bool setBusVoltageConversionTime(uint8_t bvct = INA226_1052_us)**
- **uint8_t getBusVoltageConversionTime()** return set value.
- **bool setShuntVoltageConversionTime(uint8_t svct = INA226_1052_us)**
- **uint8_t getShuntVoltageConversionTime()** return set value.
- **bool setTemperatureConversionTime(uint8_t tct = INA226_1052_us)**
- **uint8_t getTemperatureConversionTime()** return set value.

|  TIMING             |  value  |  notes  |
|:--------------------|:-------:|:--------|
| INA228_50_us        |    0    |
| INA228_84_us        |    1    |
| INA228_150_us       |    2    |
| INA228_280_us       |    3    |
| INA228_540_us       |    4    |
| INA228_1052_us      |    5    |
| INA228_2074_us      |    6    |
| INA228_4120_us      |    7    |


- **bool setAverage(uint8_t avg = INA228_1_SAMPLE)**
- **uint8_t getAverage()** return set value.

|  AVERAGE            |  value  |  notes  |
|:--------------------|:-------:|:--------|
| INA228_1_SAMPLE     |    0    |
| INA228_4_SAMPLES    |    1    |
| INA228_16_SAMPLES   |    2    |
| INA228_64_SAMPLES   |    3    |
| INA228_128_SAMPLES  |    4    |
| INA228_256_SAMPLES  |    5    |
| INA228_512_SAMPLES  |    6    |
| INA228_1024_SAMPLES |    7    |


### Shunt Calibration

To elaborate, read datasheet for details.

Note: **setMaxCurrentShunt()** must be called to calibrate your sensor.
Otherwise several functions will return zero or incorrect data.

- **int setMaxCurrentShunt(float maxCurrent, float shunt)** The maxCurrent 
depends on breakout used, See section above. 
The shunt should be 0.0001 Ω and up.
  - returns 0 if OK.
  - returns -2 if shunt < 0.0001 Ohm. ( Mateksys == 0.0002 Ω )
- **bool isCalibrated()** is valid calibration value. The currentLSB > 0.
- **float getMaxCurrent()** return set value.
- **float getShunt()** return set value.
- **float getCurrentLSB()** return actual currenLSB. 0.0 means not calibrated.


### Shunt temperature coefficient

Read datasheet for details, page 16.

The INA228 can compensate for shunt temperature variance to increase accuracy.
The reference temperature is 25°C.
- Enter the coefficient with **setShuntTemperatureCoefficent(uint16_t ppm)**.
- Enable the function with **setTemperatureCompensation(true)**.

In formula:
```
Radjusted = Rnominal + (Rnominal x (temperature - 25) x PPM) * 10e-6;
```

- **bool setShuntTemperatureCoefficent(uint16_t ppm = 0)** ppm = 0..16383 ppm/°C.
Default 0 for easy reset.
Returns false if ppm is out of range.
- **uint16_t getShuntTemperatureCoefficent()** returns the set value (default 0).


### Diagnose alert

Read datasheet for details, section 7.6.1.12, page 26++.

- **void setDiagnoseAlert(uint16_t flags)** set all flags as bit mask.
- **uint16_t getDiagnoseAlert()** return all flags as bit mask.

INA228.h has an enum for the bit fields.

- **void setDiagnoseAlertBit(uint8_t bit)** set individual bit.
- **void clearDiagnoseAlertBit(uint8_t bit)** clear individual bit.
- **uint16_t getDiagnoseAlertBit(uint8_t bit)** return individual bit.


### Threshold and Limits

Read datasheet for details, section 7.3.7, page 16++

Note: the implementation of this part is rather minimalistic and 
might be changed / extended in the future.

#### Shunt

- **void setShuntOvervoltageTH(uint16_t threshold)**
- **uint16_t getShuntOvervoltageTH()**
- **void setShuntUndervoltageTH(uint16_t threshold)**
- **uint16_t getShuntUndervoltageTH()**

#### Bus

- **void setBusOvervoltageTH(uint16_t threshold)**
- **uint16_t getBusOvervoltageTH()**
- **void setBusUndervoltageTH(uint16_t threshold)**
- **uint16_t getBusUndervoltageTH()**

#### Temperature

- **void setTemperatureOverLimitTH(uint16_t threshold)**
- **uint16_t getTemperatureOverLimitTH()**

#### Power

- **void setPowerOverLimitTH(uint16_t threshold)**
- **uint16_t getPowerOverLimitTH()**


### Manufacturer and ID

- **bool getManufacturer()** Returns 0x5449, can be used to check right sensor.
- **uint16_t getDieID()** Returns 0x228, can be used to check right sensor.
- **uint16_t getRevision()** Returns revision, probably 0x01.


## Future


#### Must

- update documentation.
- test and verify.
- DiagnoseAlertBit functions
  - redo API (0.2.0)

#### Should

- TODO's in code and docs.
- add error handling.
- keep in sync with INA226 where possible.
- how to detect nothing connected?
  - vshunt >  maxVShunt (new variable)
  - current > maxCurrent

#### Could

- write examples, (please share yours).
- improve unit tests
- clean up magic numbers in the code

#### Won't

- cache registers for performance
  - first get library working / tested.
  - reset should reread all cached values...


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

