
[![Arduino CI](https://github.com/RobTillaart/DS18B20_INT/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DS18B20_INT/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DS18B20_INT.svg?maxAge=3600)](https://github.com/RobTillaart/DS18B20_INT/releases)

# DS18B20_INT

Minimalistic library for the DS18B20 temperature sensor.

## Description

This DS18B20 library is a minimalistic library for a DS18B20 sensor.
It will give only temperatures in whole degrees C.
Goal is to minimize footprint.

If you need more functions or control over the DS18B20 family I refer to the library
of Miles Burton - https://github.com/milesburton/Arduino-Temperature-Control-Library
or to 

## Interface

This DS18B20_INT library supports only the DS18B20, only one sensor per pin, no parasite 
mode, no Fahrenheit and no alarm functions. The only feature the class supports is 
the asynchronous reading of the temperature by means of three core functions:

- **DS18B20_INT(onewire)** constructor needs a reference to OneWire object.
- **begin()** resets oneWire and set resolution to 9 bit.  
returns true if all is OK.
- **requestTemperatures()** trigger temperature comversion
- **isConversionComplete()** check if conversion is complete
- **int16_t readTempC()** returns temperature in whole degrees only. -55..125  
-127 = DEVICE_DISCONNECTED  


## Operation

This library supports only one DS18B20 per Arduino/ MCU pin.
```
    //  BOTTOM VIEW
    //
    //          PIN  MEANING
    //   /---+
    //  /  o |  1    GND
    //  |  o |  2    DATA
    //  \  o |  3    VCC
    //   \---+
    //
```

Connect a pull-up resistor 4.7 KOhm between pin3 and pin2. 
When the wires are longer this resistor needs to be smaller.

Check examples.

## Credits

Miles Burton who originally developed the Arduino Temperature Control Library.
and all people who contributed to that lib.

