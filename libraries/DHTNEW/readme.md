
[![Arduino CI](https://github.com/RobTillaart/DHTNew/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DHTNew/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DHTNew/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DHTNew/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DHTNew/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DHTNew/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DHTNew.svg?maxAge=3600)](https://github.com/RobTillaart/DHTNew/releases)


# DHTNew

Arduino library for DHT11 and DHT22 (and compatible) with automatic sensor type recognition.


## Description

DHTNEW is stable for both ARM and AVR. It is based upon the well tested DHTlib code.
This is the main development library of all my DHT libraries.

Supports DHT11, DHT22, DHT33, DHT44, AM2301, AM2302, AM2303 as these all have the same protocol.
Note there are differences e.g. DHT11 has no negative temperature, no decimals, and a longer wakeup time.


## DHT PIN layout from left to right

| Front |      | Description   |
|:------|:----:|:--------------|
| pin 1 |      | VCC           |
| pin 2 |      | DATA          |
| pin 3 |      | Not Connected |
| pin 4 |      | GND           |


## Specification DHT22

| Model                     | DHT22                  | Notes |
|:--------------------------|:-----------------------|:------|
| Power supply              | 3.3 - 6 V DC           |
| Output signal             | digital signal via single-bus  |
| Sensing element           | Polymer capacitor      |
| Operating range           | humidity 0-100% RH     | temperature -40° - 80° Celsius
| Accuracy humidity         | ±2% RH(Max ±5% RH)     | temperature < ±0.5° Celsius
| Resolution or sensitivity | humidity 0.1% RH       | temperature 0.1° Celsius
| Repeatability humidity    | ±1% RH                 | temperature ±0.2° Celsius
| Humidity hysteresis       | ±0.3% RH               |
| Long-term Stability       | ±0.5% RH/year          |
| Sensing period            | Average: 2s            |
| Interchangeability        | fully interchangeable  |
| Dimensions                | small 14 x 18 x 5.5 mm | big 22 x 28 x 5 mm |


## Interface


### Constructor

- **DHTNEW(uint8_t pin)** defines the dataPin of the sensor.
- **void reset()** might help to reset a sensor behaving badly. It does reset the library settings to default, 
however it does not reset the sensor in a hardware way. 
- **uint8_t getType()**  0 = unknown, 11 or 22. 
In case of 0, **getType()** will try to determine type.
- **void setType(uint8_t type = 0)** allows to force the type of the sensor. 


### Base interface

- **int read()** reads a new temperature and humidity from the sensor
- **uint32_t lastRead()** returns milliseconds since last **read()**
- **float getHumidity()** returns last read value (float) or -999 in case of error. 
Note this error value can be suppressed by **setSuppressError(bool)**.
- **float getTemperature()** returns last read value (float) or -999 in case of error. Note this error value can be suppressed by **setSuppressError(bool)**.


### Offset 

Adding offsets works well in normal range however they might introduce under- or overflow at the ends of the sensor range.
humidity is constrained to 0..100% in the code. For temperature such constrain would be type dependant, so not done.

- **void setHumOffset(float offset)** typical < ±5% RH.
- **void setTempOffset(float offset)** typical < ±2°C.
- **float getHumOffset()** idem.
- **float getTempOffset()** idem.


### Control

Functions to adjust the communication with the sensor.

- **void setDisableIRQ(bool b )** allows or suppresses interrupts during core read function to keep timing as correct as possible. **Note AVR + MKR1010**
- **bool getDisableIRQ()** returns the above setting. Default **true**.
- **void setWaitForReading(bool b )** flag to enforce a blocking wait. 
- **bool getWaitForReading()** returns the above setting.
- **void setReadDelay(uint16_t rd = 0)** To tune the time it waits before actual read. This reduces the blocking time. 
Default depends on type. 1000 ms (dht11) or 2000 ms (dht22). 
set readDelay to 0 will reset to datasheet values AFTER a call to **read()**.
- **uint16_t getReadDelay()** returns the above setting.
- **void powerDown()** pulls dataPin down to reduce power consumption
- **void powerUp()** restarts the sensor, note one must wait up to two seconds.
- **void setSuppressError(bool b)** suppress error values of -999 => you need to check the return value of read() instead.  
This is used to keep spikes out of your graphs / logs. 
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


#### ESP8266 & DHT22

- The DHT22 sensor has some problems in combination with specific pins of the ESP8266. See more details
  - https://github.com/RobTillaart/DHTNew/issues/31  (message Jan 3, 2021)
  - https://github.com/arendst/Tasmota/issues/3522


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


## Future

- test on more boards
- investigate temperature constraining (type dependant.
- update documentation
- move history to separate release_notes.md file ?
- improve unit test
- fix  DHTLIB_VALUE_OUT_OF_RANGE  code
- #if defined(MKR1010)  // TODO find out real define 
- 


 