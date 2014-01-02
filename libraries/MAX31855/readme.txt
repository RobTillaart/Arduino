
Working is as follows:

first is to instantiate a constructor:

#include "MAX31855.h"

const int doPin = 7;
const int csPin = 6;
const int clPin = 5;

MAX31855 tc(clPin, csPin, doPin);


To get a reading one must call tc.read() 

This is the workhorse, it returns the status of the last read which is 0..7
0 = OK
bit 0 set = thermocouple open circuit
bit 1 set = thermocouple short to GND
bit 2 set = thermocouple short to VCC


After a tc.read() you can do tc.getTemperature() and tc.getInternal().
repeated getTemperature() will give the same value until a new tc.read();

The reason for this is that it allows the object holds its last known temperature.
Now one can do:

float last = tc.getTemperature();
tc.read();
float new = tc.getTemperature();
float delta = new - last;

