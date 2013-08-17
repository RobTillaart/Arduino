#ifndef RunningAverage_h
#define RunningAverage_h
// 
//    FILE: RunningAverage.h
//  AUTHOR: Rob dot Tillaart at gmail dot com
// PURPOSE: RunningAverage library for Arduino
//     URL: http://arduino.cc/playground/Main/RunningAverage
// HISTORY: See RunningAverage.cpp
//
// Released to the public domain
//

// backwards compatibility
// clr() clear()
// add(x) addValue(x)
// avg() getAverage()

#define RUNNINGAVERAGE_LIB_VERSION "0.2.02"

class RunningAverage 
{
	public:
	RunningAverage(void);
	RunningAverage(int);
	~RunningAverage();
	void clear();
	void addValue(float);
	float getAverage();
	void fillValue(float, int);

protected:
	int _size;
	int _cnt;
	int _idx;
	float _sum;
	float * _ar;
};

#endif
// END OF FILE