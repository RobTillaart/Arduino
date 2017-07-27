//
//    FILE: FastMap.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.8
// PURPOSE: class with fast map function - library for Arduino
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

#define FASTMAP_LIB_VERSION (F("0.1.8"))

class FastMap
{
public:
    FastMap();

    void init(const float in_min, const float in_max, const float out_min, const float out_max);

    float inline map (const float value)  { return _base + value * _factor; }
    float inline back (const float value) { return _backbase + value * _backfactor; }

    float constrainedMap(const float value);
    float lowerConstrainedMap(const float value);
    float upperConstrainedMap(const float value);

private:
    float _in_min, _in_max, _out_min, _out_max;
    float _factor, _base;
    float _backfactor, _backbase;
};

#endif

// END OF FILE