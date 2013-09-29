#ifndef Histogram_h
#define Histogram_h
// 
//    FILE: Histogram.h
//  AUTHOR: Rob dot Tillaart at gmail dot com  
// PURPOSE: Histogram library for Arduino
// HISTORY: See Histogram.cpp
//
// Released to the public domain
//

#include <stdlib.h>
#include <math.h>
#include <inttypes.h>

#define HISTOGRAM_LIB_VERSION "0.1.1"

class Histogram 
{
	public:
	Histogram(uint8_t len, float *bounds);
	~Histogram();
	void clear();
	void add(float val);
	void sub(float val);
	uint8_t size();
	unsigned long count();
	long bucket(uint8_t idx);
	float frequency(uint8_t idx);
	float PMF(uint8_t idx);
	float CDF(uint8_t idx);
	uint8_t find(float f);
	// void strategy();

protected:
	float * _bounds;
	long * _data;
	uint8_t _len;
	unsigned long _cnt;
};

#endif
// END OF FILE