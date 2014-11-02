//
//    FILE: FastMap.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.05
// PURPOSE: class implementation of map function - library for Arduino
//     URL: http://forum.arduino.cc/index.php?topic=276194
//
// HISTORY:
// see FastMap.cpp file
//

#ifndef FastMap_h
#define FastMap_h

#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

#define FASTMAP_LIB_VERSION (F("0.1.05"))

class FastMap
{
public:
    void init(float in_min, float in_max, float out_min, float out_max);

    float inline map(float value) { return _base + value * _factor; }
    float inline back(float value) { return _backbase + value * _backfactor; }

    float constrainedMap(float value);
    float lowerConstrainedMap(float value);
    float upperConstrainedMap(float value);

private:
    float _in_min, _in_max, _out_min, _out_max;
    float _factor, _base;
    float _backfactor, _backbase;
};

#endif
//
// END OF FILE
//