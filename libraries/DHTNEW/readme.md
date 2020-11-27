# DHTNew

Arduino library for DHT11 and DHT22 with automatic sensortype recognition.

## Description

DHTNEW is stable for both ARM and AVR. 
It is based upon the well tested DHTlib code.

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
   This saves up to 20+ milliseconds for a DHT11 or 5+ millis for a DHT22. Note that these sensors 
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
This flag is usefull to suppress 'negative spikes' in graphs or logs. 
Default the error values are not suppressed to be backwards compaible.  
Added **#ifndef** around **DHTLIB_INVALID_VALUE** so the default -999 can be overruled
compile time to set another error value e.g. -127 or -1 whatever suits the project.
14. (0.3.3)
Refactored the low level **readSensor()** as the **BIT SHIFT ERROR** issue #29 and issue #11 popped up again.
It was reproduced "efficiently" with an ESP32 and by using long wires.
Fixed with an explicit digitalWrite(datapin, HIGH) + delayMicroseconds() to have enough time between
pulling the line HIGH and poiling for the line LOW.
15. (0.3.4)
Added **waitFor(state, timeout)** to more precisely follow the datasheet in terms of timing.
Reintroduced the **interrupt enable/disable flag** as forced noInterrupts()
could break the timing of the DHT protocol / micros() - seen on AVR.


## DHT PIN layout from left to right

| FRONT | | DESCRIPTION  |
|:----|:----:|:----|
| pin 1 | | VCC           |
| pin 2 | | DATA          |
| pin 3 | | Not Connected |
| pin 4 | | GND           |

## Specification DHT22

| | | |
|:----|:----|:----|
| Model | DHT22 |
| Power supply | 3.3 - 6 V DC | 
| Output signal | digital signal via single-bus | 
| Sensing element | Polymer capacitor | 
| Operating range | humidity 0-100% RH | temperature -40~80 Celsius | 
| Accuracy humidity | ±2% RH(Max ±5% RH) | temperature < ±0.5 Celsius | 
| Resolution or sensitivity | humidity 0.1% RH | temperature 0.1 Celsius | 
| Repeatability humidity | ±1% RH | temperature ±0.2 Celsius | 
| Humidity hysteresis | ±0.3% RH | 
| Long-term Stability | ±0.5% RH/year | 
| Sensing period | Average: 2s | 
| Interchangeability |  fully interchangeable | 
| Dimensions | small size 14 x 18 x 5.5 mm;  | big size 22 x 28 x 5 mm | 


## Operation

See examples

If consistent problems occur with reading a sensor, one should allow interrupts 
**DHT.setDisableIRQ(true)**
