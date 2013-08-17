#ifndef RunningMedian_h
#define RunningMedian_h
// 
//    FILE: RunningMedian.h
//  AUTHOR: Rob dot Tillaart at gmail dot com  
// PURPOSE: RunningMedian library for Arduino
// VERSION: 0.1.02
//     URL: http://arduino.cc/playground/Main/RunningMedian
// HISTORY: See RunningMedian.cpp
//
// Released to the public domain
//

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <inttypes.h>

#define RUNNINGMEDIANVERSION "0.1.02"
// should at least be 5 to be practical
#define MEDIAN_MIN 1
#define MEDIAN_MAX 19
#define MEDIAN_DEFAULT 5

class RunningMedian 
{
	public:
	RunningMedian(uint8_t);
	RunningMedian();
	void clear();
	void add(float);
	float getMedian();

	float getAverage();
	float getHighest();
	float getLowest();

	protected:
	uint8_t _size;
	uint8_t _cnt;
	uint8_t _idx;
	float _ar[MEDIAN_MAX];
	float _as[MEDIAN_MAX];
	void sort();
};

#endif
// END OF FILE