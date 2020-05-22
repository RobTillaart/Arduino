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
5. Added **interrupt enable / disable flag** to prevent interrupts disturb timing of DHT protocol.
   Be aware that this may affect other parts of your application.

6. (0.1.7) added an automatic check of lastRead in the read call. If request a read to fast it will just return OK.
7. (0.1.7) added **waitForReading flag** (kudos to Mr-HaleYa) to let the sensor explicitly 
   wait until a new value can be read.

8. (0.2.0) Temperature and humidity are private now, use **getTemperature()** and **getHumidity()**

## Operation

See examples
