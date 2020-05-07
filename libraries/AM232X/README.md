# AM232X

Arduino library for AM2320 AM2321 and AM2322 I2C temperature and humidity sensor

## Description

AM232X is a sensor similar to the DHT12 with an I2C interface. 
Although in theory this could enable multiple sensors on one bus
the AM232X has a fixed address 0x5C.

## Operation

In setup() you have to call the **begin()** to initialize 
the Wire library and do an initial **read()** to fill the 
variables temperature and humidity. 
To access these values one must use **getTemperature()** and **getHhumidity()**. 


## Planned changes

Fix several TODO's in the code.

## Warning
The library has several open ends so it is not suitable yet for
any serious application. 

See also LICENCE
