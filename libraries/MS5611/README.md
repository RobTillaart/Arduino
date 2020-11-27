# MS5611

Arduino library for MS5611 temperature and pressure sensor

## Description

The MS5611 is a high resolution temperature and pressure sensor.

Temperature is expressed in 1/100 of degrees, so to print it
one has to multiply it by 0.01.

Pressure is expressed in 1/100 of mBar, so to print it one has to multiply it 
by 0.01 too.

This high resolution is made possible by oversampling (many times).

Maybe the values should be fixed in the future to be more "user friendly"
so a float representing Celsius and Bar.

## Disclaimer

The library is experimental. As I have no such sensor the quality is hard to test.
So if you happen to have such a sensor, please give it a try and let me know.

## Operation

See examples
