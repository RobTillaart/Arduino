//
//    FILE: fastMap.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.02
// PURPOSE: class implementation of map function - library for Arduino
//     URL: http://forum.arduino.cc/index.php?topic=276194
//
// HISTORY:
// see fastMap.cpp file
//

#ifndef fastMap_h
#define fastMap_h

#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

#define FASTMAP_LIB_VERSION "0.1.02"

#define USE_CONSTRAINED_MAP

class fastmap
{
public:
    void init(float in_min, float in_max, float out_min, float out_max);

    float inline map(float value) { return _base + value * _factor; }
    float constrainedMap(float value);
    float lowerConstrainedMap(float value);
    float upperConstrainedMap(float value);

private:
    float _in_min, _in_max, _out_min, _out_max;
    float _factor, _base;
};

#endif
//
// END OF FILE
//