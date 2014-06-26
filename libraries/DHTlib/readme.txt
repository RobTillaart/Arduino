The DHT11, 21, 22, 33 and 44 are relative inexpensive sensors for measuring temperature and humidity. 

This library can be used for reading both values from these DHT sensors. 
The DHT11 only returns integers (e.g. 20) and does not support negative values.
The others are quite similar and provide one decimal digit (e.g. 20.2)
The hardware pins of the sensors and handshake are identical so ideal to combine in one lib.

The library is confirmed to work on:

UNO (tested myself)
2009 (tested myself)
MEGA2560
DUE
attiny85 @8MHz
Digistump Digix @ 84 MHz

More information - http://playground.arduino.cc//Main/DHTLib -