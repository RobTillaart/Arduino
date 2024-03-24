
[![Arduino CI](https://github.com/RobTillaart/DHTNew/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DHTNew/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DHTNew/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DHTNew/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DHTNew/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DHTNew.svg)](https://github.com/RobTillaart/DHTNew/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DHTNew/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DHTNew.svg?maxAge=3600)](https://github.com/RobTillaart/DHTNew/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DHTNew.svg)](https://registry.platformio.org/libraries/robtillaart/DHTNew)


# DHTNew

Arduino library for DHT11 and DHT22 (and compatible) with automatic sensor type recognition.


## Description

DHTNEW is stable for both ARM and AVR. It is based upon the well tested DHTlib code.
This is the main development library of all my DHT libraries.

Supports DHT11, DHT22, DHT33, DHT44, AM2301, AM2302, AM2303 as these all have the same protocol.
Note there are differences e.g. DHT11 has no negative temperature, no decimals, and a longer wakeup time.

The DHTNew library returns Temperature in degrees Celsius and Humidity in 0.0 - 100.0 %RH.
For converting temperature to Fahrenheit or Kelvin, see https://github.com/RobTillaart/Temperature.


#### Sonoff Si7021

Since 0.4.14 there is **experimental** support for the Sonoff Si7021. 
No hardware yet to test this myself, but it is confirmed to work.
See https://github.com/RobTillaart/DHTNew/issues/79.
Seems the Sonoff Si7021 sensor is very sensitive in the wakeup timing.
This behaviour needs to be investigated in the future. 

To use the library one should call **setType(70)**.

Feedback (both positive and negative) about the Sonoff Si7021 sensors is welcome.


#### AM2320, AM2321 and AM2322

Since 0.4.18 there is **experimental** support for the AM2320, AM2321 and AM2322.
Not tested myself, but AM2320 is confirmed to work, see https://github.com/RobTillaart/AM232X/issues/26
As the AM2321 and AM2322 are quite identical according to the datasheet, those are expected to work too.

To use the library one should call **setType(22)** as the protocol is identical to the DHT22.
If there are differences in operation type (23) will be elaborated.
The value 23 is now mapped upon 22 code.

Feedback (both positive and negative) about the AM232X sensors is welcome.

**Note: check the datasheet how to connect!**


#### Related

- https://github.com/RobTillaart/DHTNew
- https://github.com/RobTillaart/DHTStable
- https://github.com/RobTillaart/DHT_Simulator
- https://www.kandrsmith.org/RJS/Misc/Hygrometers/calib_many.html (interesting)
- https://github.com/RobTillaart/Temperature (conversions, dewPoint, heatindex etc)


## DHT PIN layout from left to right

|  Front  |      |  Description    |
|:--------|:----:|:----------------|
|  pin 1  |      |  VCC            |
|  pin 2  |      |  DATA           |
|  pin 3  |      |  Not Connected  |
|  pin 4  |      |  GND            |

**Note: check the datasheet how to connect!**


## Specification DHT22

|  Model                      |  DHT22                   |  Notes  |
|:----------------------------|:-------------------------|:--------|
|  Power supply               |  3.3 - 6.0 V DC          |
|  Output signal              |  digital signal via single-bus  |
|  Sensing element            |  polymer capacitor       |
|  Operating range            |  humidity 0.0-100.0% RH  |  temperature -40° - 80° Celsius
|  Accuracy humidity          |  ±2% RH(Max ±5% RH)      |  temperature < ±0.5° Celsius
|  Resolution or sensitivity  |  humidity 0.1% RH        |  temperature 0.1° Celsius
|  Repeatability humidity     |  ±1.0% RH                |  temperature ±0.2° Celsius
|  Humidity hysteresis        |  ±0.3% RH                |
|  Long-term Stability        |  ±0.5% RH/year           |
|  Sensing period             |  average: 2 s            |
|  Interchangeability         |  fully interchangeable   |
|  Dimensions                 |  small 14 x 18 x 5.5 mm  |  big 22 x 28 x 5 mm  |


## Interface

```cpp
#include "dhtnew.h"
```

### Constructor

- **DHTNEW(uint8_t pin)** defines the dataPin of the sensor.
- **void reset()** might help to reset a sensor behaving badly. It does reset the library settings to default, 
however it does not reset the sensor in a hardware way. 
- **uint8_t getType()**  0 = unknown, 11 or 22. 
In case of 0, **getType()** will try to determine type.
Since 0.4.14 type 70 is added for **experimental** Sonoff Si7021 support.
- **void setType(uint8_t type = 0)** allows to force the type of the sensor. 

|  Type   |  Sensors        |  Notes  |
|:-------:|:---------------:|:--------|
|   0     |  not defined    |
|   11    |  DHT11          |
|   22    |  DHT22 a.o      |  most others
|   23    |  DHT22 a.o      |  mapped to 22 for now
|   70    |  Sonoff Si7021  |  experimental
|  other  |  sets to 0      |  0.4.20


### Base interface

- **int read()** reads a new temperature (Celsius) and humidity (%RH) from the sensor.
- **uint32_t lastRead()** returns milliseconds since last **read()**
- **float getHumidity()** returns last read humidity = 0.0 - 100.0 %RH.
In case of an error it returns **DHTLIB_INVALID_VALUE** == -999. 
Note this error value can be suppressed by **setSuppressError(bool)**.
- **float getTemperature()** returns last read temperature in Celsius.
Range depends on the sensor.
In case of an error it returns **DHTLIB_INVALID_VALUE** == -999. 
Note this error value can be suppressed by **setSuppressError(bool)**.


### Offset 

Adding offsets works well in normal range however they might introduce 
under- or overflow at the ends of the sensor range.
Humidity is in % RH.
Humidity is constrained to 0.0 - 100.0 % in the code.
Temperature is in degrees Celsius.
For temperature such constrain would be type dependant, so it is not done.

- **void setHumOffset(float offset)** typical < ±5% RH.
- **void setTempOffset(float offset)** typical < ±2°C.
- **float getHumOffset()** idem.
- **float getTempOffset()** idem.


### Control

Functions to adjust the communication with the sensor.

- **void setDisableIRQ(bool b )** allows or suppresses interrupts during core 
read function to keep timing as correct as possible. **Note AVR + MKR1010**
- **bool getDisableIRQ()** returns the above setting. Default **true**.
- **void setWaitForReading(bool b )** flag to enforce a blocking wait. 
- **bool getWaitForReading()** returns the above setting.
- **void setReadDelay(uint16_t rd = 0)** To tune the time it waits before actual read. 
This reduces the blocking time. 
Default depends on type. 1000 ms (dht11) or 2000 ms (dht22). 
set readDelay to 0 will reset to datasheet values AFTER a call to **read()**.
- **uint16_t getReadDelay()** returns the above setting.
- **void powerDown()** pulls dataPin down to reduce power consumption
- **void powerUp()** restarts the sensor, note one must wait up to two seconds.
- **void setSuppressError(bool b)** suppress error values of -999 => 
You need to check the return value of read() instead.  
This is used to keep spikes out of your plotter / graphs / logs. 
- **bool getSuppressError()**  returns the above setting.


## Operation

See examples


#### TIME_OUT

If consistent TIMOUT_C or TIMEOUT_D occur during reading a sensor, 
one could try if allowing interrupts solves the issue **DHT.setDisableIRQ(false)**.

This solved this problem at least on
- AVR boards   - is build into the constructor
- MKR1010 Wifi - see https://github.com/RobTillaart/DHTNew/issues/67
                 (added as comment in the examples)

In version 0.4.10 the TIMEOUT_C is extended from 70-90 us to even suppress the TIMEOUT_C
even more. See discussion and tests in https://github.com/RobTillaart/DHTNew/issues/67.


#### Serial

The MKR1010Wifi board need to wait for Serial at startup if you want to monitor it 
from the IDE. Adding the line ```while(!Serial):``` fixes this. (added to the examples).

There might be more boards that need this line to work properly.


#### DHT22 and ESP8266

- The DHT22 sensor has some problems in combination with specific pins of the ESP8266. See more details
  - https://github.com/RobTillaart/DHTNew/issues/31  (message Jan 3, 2021)
  - https://github.com/arendst/Tasmota/issues/3522


#### Voltage AM2301 and ESP8266

In a test an AM2301 had problems giving no humidity (99.9% overflow) when the
DHTStable library was used with an ESP8266. (Reported by mail, no GH issue).
As this DHTStable library is strongly related to the DHTNew it is mentioned here too.

After days of testing and thinking and more testing the cause was found. 
The AM2301 was powered by a 5V3 power supply which was apparently too high while having the
data handshakes at 3V3. 
When the VCC voltage was lowered to 5V1 it appeared to work as it should. 
(Kudos to Viktor for finding the cause)


## History 

DHTNEW has some new features compared to the DHTlib code.

1. The constructor has a pin number, so the one sensor - one object paradigm is chosen.
   So you can now make a DHTNEW object bathroom(4), kitchen(3), etc.
2. The **read()** function now reads both DHT11 and DHT22 sensors and selects the right 
   math per sensor based upon the bit patterns. 
3. An **offset** can be set for both temperature and humidity to have a first-order linear
   calibration in the class itself. Of course, this introduces a possible risk of
   under- or overflow.
   For a more elaborated or non-linear offset, I refer to my multimap class.
4. **lastRead()** keeps track of the last time the sensor is read. If this is not too long ago 
   one can decide not to read the sensors but use the current values for temperature and humidity.
   This saves up to 20+ milliseconds for a DHT11 or 5+ milliseconds for a DHT22. Note that these sensors 
   should have 1-2 seconds between reads according to specification. 
   In the future, this functionality could be inside the library by setting a time threshold
   (e.g. 1 second by default) to give more stable results.
5. Added **interrupt enable/disable flag** to prevent interrupts disturb timing of DHT protocol.
   Be aware that this may affect other parts of your application.
6. (0.1.7) added an automatic check of lastRead in the read call. If request a read to fast it will just return OK.
7. (0.1.7) added **waitForReading flag** (kudos to Mr-HaleYa) to let the sensor explicitly 
   wait until a new value can be read.
8. (0.2.0) Temperature and humidity are private now, use **getTemperature()** and **getHumidity()**
9. (0.2.1) Adjusted the bit timing threshold to work around issue #11 
10. (0.2.2) added **ERROR_SENSOR_NOT_READY** and differentiated timeout errors.
11. (0.3.0)
removed interrupt flag, now the library always disables interrupts during 
the clocking of the bits.
Added getReadDelay & setReadDelay to tune reading interval. Check the example code.
Adjusted the timing in the wake-up part of the protocol. 
Added more comments to describe the protocol.
12. (0.3.1)
added **powerDown()** and **powerUp()** for low power applications. Note that after **powerUp()**
the user must wait for two seconds before doing a read(). Just like after a (re)boot.  
Note: The lib does not (yet) control the power pin of the sensor. 
Discussion see https://github.com/RobTillaart/DHTNew/issues/13
13. (0.3.2)
Added **setSuppressError()** and **getSuppressError()** so the library will not output -999 
but the last known valid value for temperature and humidity. 
This flag is useful to suppress 'negative spikes' in graphs or logs. 
Default the error values are not suppressed to be backwards compatible.  
Added **#ifndef** around **DHTLIB_INVALID_VALUE** so the default -999 can be overruled
compile time to set another error value e.g. -127 or -1 whatever suits the project.
14. (0.3.3)
Refactored the low level **readSensor()** as the **BIT SHIFT ERROR** issue #29 and issue #11 popped up again.
It was reproduced "efficiently" with an ESP32 and by using long wires.
Fixed with an explicit digitalWrite(dataPin, HIGH) + delayMicroseconds() to have enough time between
pulling the line HIGH and polling for the line LOW.
15. (0.3.4)
Added **waitFor(state, timeout)** to more precisely follow the datasheet in terms of timing.
Reintroduced the **interrupt enable/disable flag** as forced noInterrupts()
could break the timing of the DHT protocol / micros() - seen on AVR.
16. (0.4.0)
Added **DHTLIB_WAITING_FOR_READ** as return value of read => minor break of interface
17. (0.4.1)
Added Arduino-CI support + **gettype()** now tries to determine type if not known.
18. (0.4.2)
Fix negative temperatures. Tested with DHTNew_debug.ino and hex dump in .cpp and a freezer.  
Note: testing in a freezer is not so good for humidity readings.
19. (0.4.3)
Added **reset()** to reset internal variables when a sensor blocks this might help.
Added **lastRead()** to return time the sensor is last read. (in milliseconds).
20. (0.4.4)
DO NOT USE incorrect negative temp.
21. (0.4.5)
Prevent -0.0 when negative temp is 0;
DO NOT USE as it maps every negative temp to zero.
22. (0.4.6) 
Fixed negative temperature (again).
23. (0.4.7)
fix #60 negative temperatures below -25.5°C + readme.md.
24. (0.4.8)
fixes to improve Arduino-lint.
25. (0.4.9)
add optional flag DHTLIB_VALUE_OUT_OF_RANGE.
26. (0.4.10)
updated build-CI to do compile test - UNO, due, zero, Leonardo, m4, esp32, esp8266, mega2560.
updated readme.md - added badges and remarks after testing with MKR1010 Wifi.
updated TIMEOUT_C from 70 -> 90 us to minimize its occurrence - See https://github.com/RobTillaart/DHTNew/issues/67.
added ```while(!Serial);``` in examples to they work for MKR1010 Wifi.
27. (0.4.11)
update library.json, license, minor edits (cleanup), unit tests
28. (0.4.12)
Fix #72, delayMicroseconds() for wakeUp
29. (0.4.13)
Fix #76, disable interrupts for ESP32.
30. (0.4.14)
added experimental support for Si7021.
31. (0.4.15)
Fix #81, recognize DHT22 as type 70. Add minimal wakeup delay.
32. (0.4.16)
Fix #84 correct the reading of type 70 for Sonoff Si7021.
33. (0.4.17)
fix #86, define constants explicit as float.
34. (0.4.18)
Update readme.md and library.\* about support for AM2320/21/22.
35. (0.4.19) 
Update readme.md
36. (0.4.20) 
Update GitHub actions and readme.md


## Future

#### Must

- update documentation

#### Should

- test on more boards
- #if defined(MKR1010)  // TODO find out real define  https://github.com/RobTillaart/DHTNew/issues/67
  ```cpp
  #ifdef ARDUINO_SAMD_MKRWIFI1010
  #error found
  #endif
  ```

#### Could

- test compatibility => table.
- investigate temperature constraining (type dependant)

```cpp
if (type == 11) temp = constrain(temp,   0, 100);
if (type == 22) temp = constrain(temp, -40,  80);
etc.
```


#### Wont

- move all code from .h to .cpp


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

 