//
//    FILE: RunningMedian.cpp
//  AUTHOR: Rob dot Tillaart at gmail dot com  
// VERSION: 0.1
// PURPOSE: RunningMedian library for Arduino
//
// HISTORY:
// 0.1.00 - 2011-02-16 initial version
// 0.1.01 - 2011-02-22 added remarks from CodingBadly
//
// Released to the public domain
//

#include "RunningMedian.h"

RunningMedian::RunningMedian()
{
	// size hardcoded
	clear();
}

// resets all counters
void RunningMedian::clear()
{ 
	_cnt = 0;
	_idx = 0;
}

// adds a new value to the data-set
// or overwrites the oldest if full.
void RunningMedian::add(long value)
{
	_ar[_idx++] = value;
	if ( _idx >= MEDIAN_SIZE ) _idx = 0; // wrap around
	if (_cnt < MEDIAN_SIZE) _cnt++;
	return;
}

long RunningMedian::getMedian()
{
	sort();
	return _as[_cnt/2];
}


void RunningMedian::sort()
{
	// copy
	for (uint8_t i=0; i< _cnt; i++) _as[i] = _ar[i];

	// sort all
	for (uint8_t i=0; i< _cnt-1; i++) 
	{
		uint8_t m = i;
		for (uint8_t j=i+1; j< _cnt; j++)
		{
			if (_as[j] < _as[m]) m = j;
		}
		if (m != i)
		{
			long t = _as[m];
			_as[m] = _as[i];
			_as[i] = t;
		}
	}
}

// END OF FILE