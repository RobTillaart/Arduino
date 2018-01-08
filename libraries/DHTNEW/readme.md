
This is the 0.1.3 version of the DHTNEW. 
This version is stable for both ARM and AVR.

DHTNEW has some new features compared to my DHTlib.

1) the constructor has a pin number, so the one sensor - one object paradigm is chosen.
   So you can now make a DHTNEW bathroom(4), kitchen(3) etc.

2) The read() function now reads both DHT11 and DHT22 sensors and do the right 
   math per sensor. This is very much based upon the well tested DHTlib code.

3) An offset can be set for both temperature and humidity to have a first order
   calibration in the class itself. Of course this introduces a possible risk of
   under- or overflow.
   For a more elaborated or non-linear offset I refer to my multimap class.
   
4) lastRead() keeps track of the last time the sensor is read. If this is not too long ago 
   one can decide not to read the sensors but use the current values for Temperature and humidity.
   This saves up to 20+ milliseconds for a DHT11 or 5+ millis for a DHT22. Note that these sensors 
   should have 1-2 seconds between reads according to specification. 
   In the future this functionality could be inside the library by setting a time threshold
   (e.g. 1 second by default) to give more stable results.

