
This library is for the Adafruit 4x 7segment display with HT16K33 driver,
http://www.adafruit.com/products/1002

This library is functionally less capable than Adafruits e.g. it has no support for negative numbers. However it is faster for writing an int / hex to the display.

Test on UNO, I2C.setClock(100000);
0-9999 integers       3.960 sec
0-65535 hexadecimal  23.685 sec

Test on UNO, I2C.setClock(800000);
0-9999 integers       1.223 sec
0-65535 hexadecimal   6.350 sec

Substantial part of this performance gain is due to an internal cache of the digits displayed, so other tests and real live usage may result in different gain.
