//
//    FILE: PulsePatternOut.cpp
//  AUTHOR: Rob dot Tillaart at gmail dot com  
// VERSION: see PULSEPATTERNOUT_LIB_VERSION in .h
// PURPOSE: PulsePatternOut library for Arduino
//
// HISTORY:
// 0.0.1 - 2012-11-23 initial version
//
// Released to the public domain
//

#include "PulsePatternOut.h"
// TODO PRE 1.0 backwards compat
#include "Arduino.h"

enum { NO_CLOCK, PRESCALE_1, PRESCALE_8, PRESCALE_64, PRESCALE_256, PRESCALE_1024 };

PulsePatternOut::PulsePatternOut(uint8_t pin)
{
	_pin = pin;
	pinMode(_pin, OUTPUT);
	digitalWrite(_pin, LOW);
	_size = 0;
	_cnt = 0;
	_state = STOPPED;
}

PulsePatternOut::~PulsePatternOut()
{
}

void PulsePatternOut::init(uint16_t * ar, uint8_t size, uint8_t level = LOW)
{ 
	_ar = ar;
	_size = size;
	_level = level;
	_cnt = 0;
	_state = STOPPED;
}

void PulsePatternOut::start()
{
	if (_size == 0) return;
	if (_state == RUNNING) return;
	setTimer(1);  // start asap
	_state = RUNNING;
}

void PulsePatternOut::stop()
{
	stopTimer();
	_state = STOPPED;
}

bool PulsePatternOut::isRunning()
{
	return (_state == RUNNING);
}

void PulsePatternOut::worker()
{
	if (_cnt == _size || _state == STOPPED) 
	{
		_state = STOPPED;
		_cnt = 0;
		stopTimer();
		return;
	}

	_level = !_level;
	// improve - absorb digitalwrite details here
	digitalWrite(_pin, _level);

	setTimer(_ar[_cnt]);
	_cnt++;
}

// TIMER code based upon - http://www.gammon.com.au/forum/?id=11504

void PulsePatternOut::stopTimer()
{
	TCCR1A = 0;        // reset timer 1
	TCCR1B = 0;
}

void PulsePatternOut::setTimer(uint16_t cc)
{
	TCCR1A = 0;			// reset timer 1
	TCCR1B = 0;
	TCNT1 = 0;      	// reset counter
    OCR1A = cc*2;		// compare A register value; 
	// 4: CTC mode, top = OCR1A
	TCCR1A = _BV (COM1A1);  	// clear on compare
	TCCR1B = _BV (WGM12) | PRESCALE_1024;  // should be PRESCALE_8
	TIFR1 |= _BV (OCF1A);    // clear interrupt flag
	TIMSK1 = _BV (OCIE1A);   // interrupt on Compare A Match   
}

// END OF FILE