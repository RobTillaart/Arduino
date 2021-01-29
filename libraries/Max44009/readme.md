
[![Arduino CI](https://github.com/RobTillaart/MAX44009/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MAX44009/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MAX44009.svg?maxAge=3600)](https://github.com/RobTillaart/MAX44009/releases)

# MAX44009 I2C LUX sensor

Library for MAX44009 / GY-49 I2C lux sensor

## Description
a.k.a. GY-49

The MAX44009 ambient light sensor is an I2C sensor, that has a 22 bit 
dynamic range from 0.045 lux to 188,000 lux.


## Schema breakout max44009 / GY-49


```cpp
//  breakout MAX44009 / GY-49
//
//      +--------+
//  VCC |o       |
//  GND |o       |
//  SCL |o      o| ADDRESS
//  SDA |o      o| -INT
//      +--------+
//
// ADDRESS:
// 0 = 0x4A
// 1 = 0x4B
//
// INT:
// Connect the INT pin to an pull up resistor
// 0 = interrupt
// 1 = no interrupt
// connect to an LED or an interrupt pin of an Arduino
//
```


## Interface

- **enum class Boolean { True, False }** enum class to prevent bool to be implicitly casted to int


### Constructor 
  
- **Max44009(address, dataPin, clockPin)** dataPin, clockPin for ESP32, ESP8266
- **Max44009(address, begin = Boolean::True);
- **Max44009(begin = Boolean::True)**
- **void configure(address, TwoWire \*wire, begin = Boolean::True)** Change I2C interface and address
- **bool isConnected()** device available on I2C bus.


### Basic 

- **float getLux()** read the sensor.
- **int getError()** returns last error.


### Configure thresholds

check datasheet for details

- **void setHighThreshold(float)**
- **float getHighThreshold(void)**
- **void  setLowThreshold(float)**
- **float getLowThreshold(void)**
- **void  setThresholdTimer(uint8_t)** 2 seems practical minimum
- **uint8_t getThresholdTimer()** returns 


### Configure interrupts

check datasheet for details

- **void enableInterrupt()**
- **void disableInterrupt()**
- **bool interruptEnabled()**
- **uint8_t getInterruptStatus()**


### Configure flags

check datasheet for details

- **void setConfiguration(uint8_t)**
- **uint8_t getConfiguration()**


### Configure sample mode

check datasheet for details

- **void setAutomaticMode()** 
- **void setContinuousMode()** uses more power
- **void clrContinuousMode()** uses less power
- **void setManualMode(uint8_t CDR, uint8_t TIM)**
- **int getIntegrationTime()** returns time in milliseconds

```
    CDR = Current Divisor Ratio
    CDR = 1 ==> only 1/8th is measured

    TIM = Time Integration Measurement (table)
    000  800ms
    001  400ms
    010  200ms
    011  100ms
    100   50ms       manual only
    101   25ms       manual only
    110   12.5ms     manual only
    111    6.25ms    manual only
```


## Examples

**Max44009\examples\max44009_test01**
- use for e.g. UNO (use voltage convertor!)

**Max44009\examples\max44009_test02**
- will **not** compile for UNO
- use for e.g. ESP32


## Notes

Please be aware this is a 3.3 Volt device so it should not be connected
to an Arduino or other 5 Volt device directly. Use a level convertor to 
solve this.

Do not forget to connect the address pin as you cannot read the sensor
in a reliable way. As the line will float it will sometimes have the
right address and sometimes not. (been there ;)
