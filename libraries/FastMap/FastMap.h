//
//    FILE: FastMap.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.7
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

#define FASTMAP_LIB_VERSION (F("0.1.7"))

class FastMap
{
public:
    FastMap();

    void init(const double in_min, const double in_max, const double out_min, const double out_max);

    double inline map (const double value)  { return _base + value * _factor; }
    double inline back (const double value) { return _backbase + value * _backfactor; }

    double constrainedMap(const double value);
    double lowerConstrainedMap(const double value);
    double upperConstrainedMap(const double value);

private:
    double _in_min, _in_max, _out_min, _out_max;
    double _factor, _base;
    double _backfactor, _backbase;
};

#endif
//
// END OF FILE
//