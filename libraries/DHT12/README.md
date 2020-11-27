# DHT12

Arduino library for I2C DHT12 temperature and humidity sensor.

## Description

The library should be initiated by calling the **begin()** function, 
optionally with datapin and clockpin for **ESP** and other platforms.

Thereafter one has to call the **read()** function to do the actual reading,
and with **getTemperature()** and **getHumidity()** to get the read values.
Calling these latter again will return the same values until a new **read()** is called.

### note
The two members **temperature** and **humidity** will become private in the future.

## Operation

See examples
