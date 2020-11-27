# DHT2pin

Arduino library for experimental 2 pin DHT library

## Description

**NOTE: THIS LIB IS NOT TESTED EXTENSIVELY YET SO USE WITH CARE**

This library is an experimental version of the DHT library that uses 2 pins.
One pin for all read actions and one pin for write actions. This way one does
not need to switch a pin between **INPUT** and **OUTPUT**.

Note: It needs a diode in the hardware between the input pin of the MCU 
and the datapin of the DHT sensor. 
The output pin of the MCU is directly connected to the datapin of the DHT sensor. 

It was made after a request which also refered to the links below.

https://communities.intel.com/thread/53869

(this link looks dead)
http://bigdinotech.com/tutorials/galileo-tutorials/using-1-wire-device-with-intel-galileo/


**NOTE: THIS LIB IS NOT TESTED EXTENSIVELY YET SO USE WITH CARE**

## Credits & testing

Maria Emanuella Moura Silva for testing and verifying this experimental 
code on a Galileo.

## Operation

See examples

