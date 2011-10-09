#ifndef RunningMedian_h
#define RunningMedian_h
// 
//    FILE: RunningMedian.h
//  AUTHOR: Rob dot Tillaart at gmail dot com  
// PURPOSE: RunningMedian library for Arduino
// VERSION: 0.1.01
//     URL: http://arduino.cc/playground/Main/RunningMedian
// HISTORY: See RunningMedian.cpp
//
// Released to the public domain
//

#include <inttypes.h>

#define RUNNINGMEDIANVERSION "1.0"
// should at least be 5 and odd.
#define MEDIAN_SIZE 5

class RunningMedian 
{
	public:
	RunningMedian();
	void clear();
	void add(long);
	long getMedian();

protected:
	uint8_t _cnt;
	uint8_t _idx;
	long _ar[MEDIAN_SIZE];
	long _as[MEDIAN_SIZE];
	void sort();
};

#endif
// END OF FILE