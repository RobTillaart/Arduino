# ML8511 Library

## Description

ML8511 - UV sensor - library for Arduino UNO. 

## Breakout

```
//      +-------+--+
//  VIN |o      +-+| mounting hole
//  3V3 |o      +-+|
//  GND |o         |
//  OUT |o         |
//   EN |o       S |  Sensor
//      +----------+
```

## Operational

As the sensor / breakout is 3V3 one need to connect to Arduino 3V3.
The library converts the analogRead to voltages, and it uses a
reference of 5.0 Volt == 1023 steps as default.

If one wants to use other ratio e.g. 3.3 volts == 4095 steps, one
can set those with setVoltagePerStep()

```
    ML8511 light(A0, 7);
    light.setVoltagePerStep(3.3, 4095);
```

It is possible to always enable the sensor by connecting the EN to 3V3.
The value of the enablePin in the constructor should then be ommitted 
or set to a negative value;

When connecting to an Arduino UNO one can use the 3V3 of the Arduino to power
the sensor. However it is not possible to connect the enablepin directly to the 
sensor. Use a voltage divider (10K + 20K) to convert the 5 Volts to ~3.3 Volts.

## Sensor sensitivity

Indoors there is very little UV light so use a known UV source like 
a blacklight or go outside in the sun.

The formula to convert the ADC reading to mW m^2 is based upon the graph 
shown in the datasheet. As I have no reference source to calibrate the library
its accuracy is limited.

## Notes
* 3V3 Sensor so do not connect to 5V directly.
* do not forget to connect the EN to either an enablePIN or to 3V3 (constantly enabled).
* library does not work with an external ADC 
