# DHTstable

Arduino Library for the DHT temperature and humidity sensor. 

## Description

The DHTstable library is a "frozen" version of the DHTlib.
This version is stable for both ARM and AVR.

0.2.5 is a migration to its own repository.
0.2.6 fixed URL to new repro

The latest developments for the DHT sensors are done in https://github.com/RobTillaart/DHTNEW
which is also tested on an ESP32.
There are some interface differences but these are relative small.

It is adviced to upgrade to the DHTNEW library if one needs new functionality.

## Multiple DHT.h includes

Note that the include file is called dht.h (for compatibily reasons)
this might need a rename in sketch and library if there is a conflict.

## TODO (optional)
* rename it to dhtstable.h + dhtstable.cpp  ( 0.3.0 version some day )

## Operational

See examples.
