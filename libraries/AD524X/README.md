# AD524X

I2C digital potentiometer AD5241 AD5242

## Description

The AD5241 and AD5242 are two digital potentiometers.
The AD5241 has one, the AD5242 has two potentiometers.
Both types have two outputlines O1 and O2.

These digital potentiometers come in 10K, 100K and 1M
and can be set in 256 steps.

An important property of the devices is that they defaults
to their mid position at startup.

## I2C address
The AD524X has two address lines to configure the I2C address.

The range is: 0x01011**YX** = 0x2C - 0x2F 

Where **AD0 = X** and **AD1 = Y** 

## Operation

The library has a number of functions which are all quite straightforward.
One can set the value of (both) the potentiometer(s), and the O1 and O2 lines.

* **uint8_t write(rdac, value);** value 0..255
* **uint8_t write(rdac, value, O1, O2);**
* **uint8_t setO1(value);** value = HIGH or LOW
* **uint8_t setO2(value);**

Also one can read the current values

* **uint8_t read(rdac);**
* **uint8_t getO1();**
* **uint8_t getO2();**

Note: the class does not distinguish between AD5241 and AD5242. 
The developer is responsible for handling this correctly.

The examples show the basic working of the functions.
