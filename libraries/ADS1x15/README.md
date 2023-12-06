
[![Arduino CI](https://github.com/RobTillaart/ADS1X15/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/ADS1X15/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/ADS1X15/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/ADS1X15/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/ADS1X15/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/ADS1X15.svg)](https://github.com/RobTillaart/ADS1X15/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/ADS1X15/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/ADS1X15.svg?maxAge=3600)](https://github.com/RobTillaart/ADS1X15/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/ADS1X15.svg)](https://registry.platformio.org/libraries/robtillaart/ADS1X15)


# ADS1X15

Arduino library for I2C ADC ADS1015, ADS1115, and similar.

For using I2C ADC with Raspberry pi or other SBC with Linux OS,
you can check similar library [here](https://github.com/chandrawi/ADS1x15-ADC).


## Description

This library should work for the devices mentioned below,
although not all sensors support all functionality.

|  Device   |  Channels  |  Resolution  |  Max sps  |  Comparator  |  ProgGainAMP  |  Notes   |
|:---------:|:----------:|:------------:|:---------:|:------------:|:-------------:|:---------|
|  ADS1013  |      1     |       12     |    3300   |       N      |        N      |          |
|  ADS1014  |      1     |       12     |    3300   |       Y      |        Y      |          |
|  ADS1015  |      4     |       12     |    3300   |       Y      |        Y      |          |
|  ADS1113  |      1     |       16     |    860    |       N      |        N      |          |
|  ADS1114  |      1     |       16     |    860    |       Y      |        Y      |          |
|  ADS1115  |      4     |       16     |    860    |       Y      |        Y      |  Tested  |


As the ADS1015 and the ADS1115 are both 4 channels these are the most
interesting from functionality point of view as these can also do
differential measurements.


#### 0.4.0 Breaking change

Version 0.4.0 introduced a breaking change.
You cannot set the pins in **begin()** any more.
This reduces the dependency of processor dependent Wire implementations.
The user has to call **Wire.begin()** and can optionally set the Wire pins 
before calling **begin()**.


#### Related

- https://github.com/RobTillaart/MCP_ADC  (10 & 12 bit ADC, SPI, fast)
- https://github.com/RobTillaart/PCF8591  (8 bit ADC + 1 bit DAC)


## I2C Address

The address of the ADS1113/4/5 is determined by to which pin the **ADDR**
is connected to:

|  ADDR pin connected to  |  Address  |  Notes    |
|:-----------------------:|:---------:|:---------:|
|        GND              |   0x48    |  default  |
|        VDD              |   0x49    |           |
|        SDA              |   0x4A    |           |
|        SCL              |   0x4B    |           |


## Interface

```cpp
#include "ADS1X15.h"
```

#### Initializing

To initialize the library you must call a constructor as described below.

- **ADS1x15()** base constructor, should not be used.
- **ADS1013(uint8_t address, TwoWire \*wire = &Wire)** Constructor with device address,
and optional the Wire interface as parameter.
- **ADS1014(uint8_t address, TwoWire \*wire = &Wire)** Constructor with device address,
and optional the Wire interface as parameter.
- **ADS1015(uint8_t address, TwoWire \*wire = &Wire)** Constructor with device address,
and optional the Wire interface as parameter.
- **ADS1113(uint8_t address, TwoWire \*wire = &Wire)** Constructor with device address,
and optional the Wire interface as parameter.
- **ADS1114(uint8_t address, TwoWire \*wire = &Wire)** Constructor with device address,
and optional the Wire interface as parameter.
- **ADS1115(uint8_t address, TwoWire \*wire = &Wire)** Constructor with device address,
and optional the Wire interface as parameter.


After construction the **ADS.begin()** need to be called. This will return false
if an invalid address is used.
The function **bool isConnected()** can be used to verify the reading of the ADS.
The function **void reset()** is sets the parameters to their initial value as
in the constructor.

For example.

```cpp
#include "ADS1X15.h"

// initialize ADS1115 on I2C bus 1 with default address 0x48
ADS1115 ADS(0x48);

void begin() {
  if (!ADS.isConnected()) {
    // error ADS1115 not connected
  }
}
```


#### I2C clock speed

The function **void setWireClock(uint32_t speed = 100000)** is used to set the clock speed
in Hz of the used I2C interface. typical value is 100 KHz.

The function **uint32_t getWireClock()** is a prototype.
It returns the value set by setWireClock().
This is not necessary the actual value.
When no value is set **getWireClock()** returns 0.
Need to implement a read / calculate from low level I2C code (e.g. TWBR on AVR),
better the Arduino Wire lib should support this call (ESP32 does).

See - https://github.com/arduino/Arduino/issues/11457

Question: Should this functionality be in this library?


#### Programmable Gain

- **void setGain(uint8_t gain)** set the gain value, indicating the maxVoltage that can be measured
Adjusting the gain allowing to make more precise measurements.
Note: the gain is not set in the device until an explicit read/request of the ADC (any read call will do).
See table below.
- **uint8_t getGain()** returns the gain value (index).

|  PGA value  |  Max Voltage  |   Notes   |
|:-----------:|:-------------:|:---------:|
|      0      |    ±6.144V    |  default  |
|      1      |    ±4.096V    |           |
|      2      |    ±2.048V    |           |
|      4      |    ±1.024V    |           |
|      8      |    ±0.512V    |           |
|      16     |    ±0.256V    |           |


- **float getMaxVoltage()** returns the max voltage with the current gain.
- **float toVoltage(int16_t raw = 1)** converts a raw measurement to a voltage.
Can be used for normal and differential measurements.
The default value of 1 returns the conversion factor for any raw number.

The voltage factor can also be used to set HIGH and LOW threshold registers
with a voltage in the comparator mode.
Check the [examples](https://github.com/RobTillaart/ADS1X15/blob/master/examples/ADS_read_comparator_1/ADS_read_comparator_1.ino).

```cpp
  float f = ADS.toVoltage();
  ADS.setComparatorThresholdLow( 3.0 / f );
  ADS.setComparatorThresholdLow( 4.3 / f );
```


#### Operational mode

The ADS sensor can operate in single shot or continuous mode.
Depending on how often conversions needed you can tune the mode.
- **void setMode(uint8_t mode)** 0 = CONTINUOUS, 1 = SINGLE (default)
Note: the mode is not set in the device until an explicit read/request of the ADC (any read call will do).
- **uint8_t getMode()** returns current mode 0 or 1, or ADS1X15_INVALID_MODE = 0xFE.


#### Data rate

- **void setDataRate(uint8_t dataRate)** Data rate depends on type of device.
For all devices the index 0..7 can be used, see table below.
Values above 7 ==> will be set to the default 4.
Note: the data rate is not set in the device until an explicit read/request of the ADC (any read call will do).
- **uint8_t getDataRate()** returns the current data rate (index).

The library has no means to convert this index to the actual numbers
as that would take 32 bytes.

Data rate in samples per second, based on datasheet is described on table below.

|  data rate  |  ADS101x  |  ADS111x  |   Notes   |
|:-----------:|----------:|----------:|:---------:|
|     0       |   128     |    8      |  slowest  |
|     1       |   250     |    16     |           |
|     2       |   490     |    32     |           |
|     3       |   920     |    64     |           |
|     4       |   1600    |    128    |  default  |
|     5       |   2400    |    250    |           |
|     6       |   3300    |    475    |           |
|     7       |   3300    |    860    |  fastest  |


#### ReadADC Single mode

Reading the ADC is very straightforward, the **readADC()** function handles all in one call.
Under the hood it uses the asynchronous calls.
- **int16_t readADC(uint8_t pin = 0)** normal ADC functionality, pin = 0..3.
If the pin number is out of range, this function will return 0.
Default pin = 0 as this is convenient for 1 channel devices.

```cpp
// read ADC in pin 2
ADS.readADC(2);

// read ADC in pin 0 - two ways
ADS.readADC();
ADS.readADC(0);
```

See [examples](https://github.com/RobTillaart/ADS1X15/blob/master/examples/ADS_minimum/ADS_minimum.ino).

To read the ADC in an asynchronous way (e.g. to minimize blocking) you need call three functions:
- **void requestADC(uint8_t pin = 0)**  Start the conversion. pin = 0..3.
Default pin = 0 as this is convenient for 1 channel devices.
- **bool isBusy()** Is the conversion not ready yet? Works only in SINGLE mode!
- **bool isReady()** Is the conversion ready? Works only in SINGLE mode!  (= wrapper around **isBusy()** )
- **int16_t getValue()** Read the result of the conversion.


in terms of code
```cpp
  void setup()
  {
    // other setup things here
    ADS.setMode(1);               // SINGLE SHOT MODE
    ADS.requestADC(pin);
  }

  void loop()
  {
    if (ADS.isReady())
    {
      value = ADS.getValue();
      ADS.requestADC(pin);       // request new conversion
    }
    // do other things here
  }
```
See [examples](https://github.com/RobTillaart/ADS1X15/blob/master/examples/ADS_read_async/ADS_read_async.ino).


#### ReadADC Differential

For reading the ADC in a differential way there are 4 calls possible.

- **int16_t readADC_Differential_0_1()** returns the difference between 2 ADC pins.
- **int16_t readADC_Differential_0_3()** ADS1x15 only
- **int16_t readADC_Differential_1_3()** ADS1x15 only
- **int16_t readADC_Differential_2_3()** ADS1x15 only
- **int16_t readADC_Differential_0_2()** ADS1x15 only - in software (no async equivalent)
- **int16_t readADC_Differential_1_2()** ADS1x15 only - in software (no async equivalent)

```cpp
// read differential ADC between pin 0 and 1
ADS.readADC_Differential_0_1(0);
```

The differential reading of the ADC can also be done with asynchronous calls.

- **void requestADC_Differential_0_1()** starts conversion for differential reading
- **void requestADC_Differential_0_3()** ADS1x15 only
- **void requestADC_Differential_1_3()** ADS1x15 only
- **void requestADC_Differential_2_3()** ADS1x15 only

After one of these calls you need to call
- **int16_t getValue()** Read the result of the last conversion.

See [examples](https://github.com/RobTillaart/ADS1X15/blob/master/examples/ADS_differential/ADS_differential.ino).


#### lastRequestMode

Since 0.3.12 the library tracks the last request mode, single pin or differential.
This variable is set at the moment of request, and keeps its value until a new 
request is made. This implies that the value / request can be quite old.

Values >= 0x10 are differential, values < 0x10 are single pin. 

- **uint8_t lastRequest()** returns one of the values below.

|  Value  |  Description                 |  Notes  |
|:-------:|:-----------------------------|:--------|
|  0xFF   |  no (invalid) request made   |  after call constructor.
|  0x00   |  single pin 0                |
|  0x01   |  single pin 1                |
|  0x02   |  single pin 2                |
|  0x03   |  single pin 3                |
|  0x10   |  differential pin 1 0        |
|  0x30   |  differential pin 3 0        |
|  0x31   |  differential pin 3 1        |
|  0x32   |  differential pin 3 2        |


Please note that (for now) the function does not support a descriptive return value
for the following two requests:
- **readADC_Differential_0_2()** ADS1x15 only - in software (no async equivalent)
- **readADC_Differential_1_2()** ADS1x15 only - in software (no async equivalent)

As these are emulated in software by two single pin calls, the state would be 
one of the two single pin values.


#### ReadADC continuous mode

To use the continuous mode you need call three functions:
- **void setMode(0)** 0 = CONTINUOUS, 1 = SINGLE (default).
Note: the mode is not set in the device until an explicit read/request of the ADC (any read call will do).
- **int16_t readADC(uint8_t pin)** or **void requestADC(uint8_t pin)** to get the continuous mode started.
- **int16_t getValue()** to return the last value read by the device.
Note this can be a different pin, so be warned.
Calling this over and over again can give the same value multiple times.

```cpp
void setup() {
  // configuration things here
  ADS.setMode(ADS.MODE_CONTINUOUS);
  ADS.requestADC(0);              // request on pin 0
}

void loop() {
  value = ADS.getValue()
  sleep(1)
}
```

See [examples](https://github.com/RobTillaart/ADS1X15/blob/master/examples/ADS_continuous/ADS_continuous.ino)
.
By using **bool isBusy()** or **bool isReady()** one can wait until new data is available.
Note this only works in the SINGLE_SHOT modus.

In continuous mode, you can't use **isBusy()** or **isReady()** functions to wait until new data available.
Instead you can configure the threshold registers to allow the **ALERT/RDY**
pin to trigger an interrupt signal when conversion data ready.


#### Switching mode or channel during continuous mode

When switching the operating mode or the ADC channel in continuous mode, be aware that 
the device will always finish the running conversion.
This implies that after switching the mode or channel the first sample you get is probably 
the last sample with the previous settings, e.g. channel.
This might be a problem for your project as this value can be in an "unexpected" range (outlier).

The robust way to change mode or channel therefore seems to be:

1. stop continuous mode,
1. wait for running conversion to be ready,
1. reject the last conversion or process it "under old settings",
1. change the settings,
1. restart (continuous mode) with the new settings.

This explicit stop takes extra time, however it should prevent "incorrect" readings.

(need to be verified with different models)


#### Threshold registers

If the thresholdHigh is set to 0x0100 and the thresholdLow to 0x0000
the **ALERT/RDY** pin is triggered when a conversion is ready.

- **void setComparatorThresholdLow(int16_t lo)** writes value to device directly.
- **void setComparatorThresholdHigh(int16_t hi)** writes value to device directly.
- **int16_t getComparatorThresholdLow()** reads value from device.
- **int16_t getComparatorThresholdHigh()** reads value from device.

See [examples](https://github.com/RobTillaart/ADS1X15/blob/master/examples/ADS_read_RDY/ADS_read_RDY.ino).


#### Comparator

Please read Page 15 of the datasheet as the behaviour of the
comparator is not trivial.

NOTE: all comparator settings are copied to the device only after calling
**readADC()** or **requestADC()** functions.


#### Comparator Mode

When configured as a **TRADITIONAL** comparator, the **ALERT/RDY** pin asserts
(active low by default) when conversion data exceed the limit set in the
high threshold register. The comparator then de-asserts when the input
signal falls below the low threshold register value.

- **void setComparatorMode(uint8_t mode)** value 0 = TRADITIONAL 1 = WINDOW,
- **uint8_t getComparatorMode()** returns value set.


If the comparator **LATCH** is set, the **ALERT/RDY** pin asserts and it will be
reset after reading the sensor (conversion register) again.
*An SMB alert command (00011001) on the I2C bus will also reset the alert state.*
*Not implemented in the library (yet)*

In **WINDOW** comparator mode, the **ALERT/RDY** pin asserts if conversion data exceeds
the high threshold register or falls below the low threshold register.
In this mode the alert is held if the **LATCH** is set. This is similar as above.


#### Polarity

Default state of the **ALERT/RDY** pin is **LOW**, can be to set **HIGH**.

- **void setComparatorPolarity(uint8_t pol)**
Flag is only explicitly set after a **readADC()** or a **requestADC()**
- **uint8_t getComparatorPolarity()** returns value set.


#### Latch

Holds the **ALERT/RDY** to **HIGH** (or **LOW** depending on polarity) after triggered
even if actual value has been 'restored to normal' value.

- **void setComparatorLatch(uint8_t latch)** 0 = NO LATCH, not 0 = LATCH
- **uint8_t getComparatorLatch()** returns value set.


#### QueConvert

Set the number of conversions before trigger activates.
The **void setComparatorQueConvert(uint8_t mode)** is used to set the number of
conversions that exceed the threshold before the **ALERT/RDY** pin is set **HIGH**.
A value of 3 (or above) effectively disables the comparator. See table below. 
To enable the conversion-ready function of the ALERT/RDY pin, it is necessary to set the MSB of the Hi_thresh register to 1 and the MSB of the Lo_thresh register to 0.

See [examples](https://github.com/RobTillaart/ADS1X15/blob/master/examples/ADS_continuous_differential/ADS_continuous_differential.ino).

- **void setComparatorQueConvert(uint8_t mode)** See table below.
- **uint8_t getComparatorQueConvert()**  returns value set.

|  value  |  meaning                            |  Notes    |
|:-------:|:------------------------------------|:----------|
|    0    |  trigger alert after 1 conversion   |           |
|    1    |  trigger alert after 2 conversions  |           |
|    2    |  trigger alert after 4 conversions  |           |
|    3    |  Disable comparator                 |  default  |


#### Threshold registers comparator mode

Depending on the comparator mode **TRADITIONAL** or **WINDOW** the thresholds registers
mean something different see - Comparator Mode above or datasheet.

- **void setComparatorThresholdLow(int16_t lo)** set the low threshold; take care the hi >= lo.
- **void setComparatorThresholdHigh(int16_t hi)**  set the high threshold; take care the hi >= lo.
- **int16_t getComparatorThresholdLow()** reads value from device.
- **int16_t getComparatorThresholdHigh()** reads value from device.


## Future ideas & improvements

#### Must

- Improve documentation (always)

#### Should


#### Could

- More examples
- SMB alert command (00011001) on I2C bus?
- sync order .h / .cpp


#### Wont (unless requested)

- type flag?
- constructor for ADS1X15? No as all types are supported.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

