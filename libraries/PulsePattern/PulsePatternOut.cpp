//
//    FILE: PulsePattern.cpp
//  AUTHOR: Rob dot Tillaart at gmail dot com  
// VERSION: see PULSEPATTERN_LIB_VERSION in .h
// PURPOSE: PulsePatternOut library for Arduino
//
// HISTORY:
// 0.0.1 - 2012-11-23 initial version
// 0.0.2 - 2012-11-23 adapted a static PPO
// 0.0.3 - 2012-12-27 renamed to PulsePattern
//
// Released to the public domain
//
// TODO 
// - PRE 1.0 backwards compatibility
// - move code to .h file so compiler can inline?
// - optimize timer code
// - adjust timing to more accurate values -> setTimer()
//

#include "PulsePattern.h"

#include "Arduino.h"

enum { NO_CLOCK, PRESCALE_1, PRESCALE_8, PRESCALE_64, PRESCALE_256, PRESCALE_1024 };

PulsePattern PPO;

ISR(TIMER1_COMPA_vect)
{
  PPO::worker();
}

PulsePattern::PulsePattern()
{
	_size = 0;
	_state = NOTINIT;
}

void PulsePattern::init(uint8_t pin, uint16_t * ar, uint8_t size, uint8_t level)
{ 
	stop();
	_pin = pin;
	_ar = ar;
	_size = size;
	_level = level;
	_cnt = 0;

	pinMode(_pin, OUTPUT);
	digitalWrite(_pin, _level);
}

void PulsePattern::start()
{
	if (_size == 0) return;  
	if (_state == RUNNING) return;  // no restart
	setTimer(1);  // start asap
	_state = RUNNING;
}

void PulsePattern::stop()
{
	stopTimer();
	_state = STOPPED;
	_level = LOW;
	digitalWrite(_pin, _level);
}

bool PulsePattern::isRunning()
{
	return (_state == RUNNING);
}

void PulsePattern::worker()
{
	if (_state != RUNNING) return;
	// set next period & flip signal
	_level = !_level;
	digitalWrite(_pin, _level);
	// TODO small adjustment needed for code overhead?; inline iso call?
	// for now
	// + 5.2 usec for digitalWrite
	// + 3 usec for settimer call
	setTimer(_ar[_cnt]-8);
	
	_cnt++;
	if (_cnt >= _size) _cnt = 0;  // repeat
}

// TIMER code based upon - http://www.gammon.com.au/forum/?id=11504
void PulsePattern::stopTimer()
{
	TCCR1A = 0;        // reset timer 1
	TCCR1B = 0;
}

// TODO: can be optimized?
void PulsePattern::setTimer(uint16_t cc)
{
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;      	// reset counter
    OCR1A = cc*2;		// compare A register value;  
						// *2 because of 8 prescaler @16mhz;
	
	// 4: CTC mode, top = OCR1A
	TCCR1A = _BV (COM1A1);  	// clear on compare
	TCCR1B = _BV (WGM12) | PRESCALE_1024;  // should be PRESCALE_8 now for testing
	TIFR1 |= _BV (OCF1A);    // clear interrupt flag
	TIMSK1 = _BV (OCIE1A);   // interrupt on Compare A Match   
}

// END OF FILE