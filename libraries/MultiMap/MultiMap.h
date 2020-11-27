#pragma once
//
//    FILE: multimap.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
//    DATE: 2011-01-26
// PURPOSE: Arduino library for fast non-linear mapping or interpolation of values
//     URL: https://github.com/RobTillaart/MultiMap
//     URL: http://playground.arduino.cc/Main/MultiMap
//
// HISTORY:
// 0.0.1    2011-01-26 initial version (see forum)
// .....
// 0.1.0    2015-03-29
// 0.1.1    2020-04-09
// 0.1.2    2020-06-19 fix library.json
//
//

#define MULTIMAP_LIB_VERSION "0.1.2"

#include <Arduino.h>

// note: the in array should have increasing values
template<typename T>
T multiMap(T val, T* _in, T* _out, uint8_t size)
{
    // take care the value is within range
    // val = constrain(val, _in[0], _in[size-1]);
    if (val <= _in[0]) return _out[0];
    if (val >= _in[size-1]) return _out[size-1];

    // search right interval
    uint8_t pos = 1;  // _in[0] allready tested
    while(val > _in[pos]) pos++;

    // this will handle all exact "points" in the _in array
    if (val == _in[pos]) return _out[pos];

    // interpolate in the right segment for the rest
    return (val - _in[pos-1]) * (_out[pos] - _out[pos-1]) / (_in[pos] - _in[pos-1]) + _out[pos-1];
}


/*
 * speed optimized version if inputs do not change often e.g.  2 2 2 2 2 3 3 3 3 5 5 5 5 5 5 8 8 8 8 5 5 5 5 5 
 * 
// note: the in array should have increasing values
template<typename T>
T multiMap(T val, T* _in, T* _out, uint8_t size)
{
    
    static T lastvalue = -1;
    static T cache = -1;	
	
	if (val == lastvalue) return cache;
	lastvalue = val;

    // take care the value is within range
    // val = constrain(val, _in[0], _in[size-1]);
    if (val <= _in[0])
	{
		cache = _out[0];
	}
    else if (val >= _in[size-1])
	{
		cache = _out[size-1];
	}
    else
	{
        // search right interval; index 0 _in[0] already tested
        uint8_t pos = 1;  
        while(val > _in[pos]) pos++;
	    
        // this will handle all exact "points" in the _in array
        if (val == _in[pos]) 
        {
		    cache = _out[pos];
        }
		else
		{
		    // interpolate in the right segment for the rest
            cache = (val - _in[pos-1]) * (_out[pos] - _out[pos-1]) / (_in[pos] - _in[pos-1]) + _out[pos-1];
		}
	}
	return cache;
}
*/

// -- END OF FILE --
