#ifndef RunningAverage_h
#define RunningAverage_h
// 
//    FILE: RunningAverage.h
//  AUTHOR: Rob dot Tillaart at gmail dot com
// PURPOSE: RunningAverage library for Arduino
// VERSION: 0.1.01
//     URL: http://arduino.cc/playground/Main/RunningAverage
// HISTORY: See RunningAverage.cpp
//
// Released to the public domain
//

class RunningAverage 
{
	public:
	RunningAverage(void);
	RunningAverage(int);
	~RunningAverage();
	void clr();
	void add(float);
	float avg();

protected:
	int _size;
	int _cnt;
	int _idx;
	float _sum;
	float * _ar;
};

#endif
// END OF FILE