# DHT_Simulator

Arduino sketch to simulate a DHT22

## Description

The DHT22 is an often used sensor and many libraries are written for it
including my own DHTNEW library. To better understand the protocol and 
to be able to debug my library I wrote a simulator for the DHT sensors
in 2014.

The simulator can be used to test applications to that use a DHT sensor,
e.g. to get high alarm temp or whatever.

Currently the code uses two analog ports to get some value for temperature
and humidity. Just connect two potmeters to play and simulate increase and 
decrease of the temperature and humidity.

## 0.2.0 version

- added flag for random generation of data
- added flag for debug
- explicit support ESP32 & ESP8266
- added counter # samples generated per second ==> so one sees it still runs
- added error and debug messages // some commented

The simulator is not tested extensively so please report bugs.

## Future

Idea is to use the code of the simulator in combination with a 
Senserion or two separate sensors (DS18B20 + ? ) to provide an 
accurate temperature and humidity. These could then be readable 
with any DHT library with the performance of a DHT (~ 5ms).
(when time permits)

## Operation

- adjust the pins in the head of the program to meet your setup
- compile, connect, run

And have fun.
