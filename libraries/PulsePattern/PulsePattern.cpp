//
//    FILE: PulsePattern.cpp
//  AUTHOR: Rob dot Tillaart at gmail dot com
// VERSION: see PULSEPATTERN_LIB_VERSION in .h
// PURPOSE: PulsePattern library for Arduino
//
// HISTORY:
// 0.0.1 - 2012-11-23 initial version
// 0.0.2 - 2012-11-23 adapted a static PPO
// 0.0.3 - 2012-12-27 renamed to PulsePattern
// 0.0.4 - 2012-12-27 code stable(?) enough to publish
// 0.0.5 - 2012-12-27 code cleanup+comment
// 0.0.6 - 2015-04-18 completed the state machine
// 0.0.7 - 2017-07-16 refactor & review
//
// Released to the public domain
//
// TODO
// - fast function iso array to return the next period?
//   more adaptive to e.g. sensor values. (investigate)
// - test PRE 1.0 backwards compatibility
// - move code to .h file so compiler can inline?
// - optimize timer code
// - adjust timing to more accurate values -> setTimer()
// - worker should be private - how???
// - test invalid array periods
// - start en stop index ipv size?
// - pulsepattern recorder
//

#include "PulsePattern.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// Predefined generator (singleton)
PulsePattern PPGenerator;

ISR(TIMER1_COMPA_vect)
{
  PPGenerator.worker();
}

PulsePattern::PulsePattern()
{
  _size = 0;
  _state = NOTINIT;
  _ar = NULL;
  _cnt = 0;
  _level = LOW;
  _prescaler = 0;
  _pin = 0;
}

void PulsePattern::init(uint8_t pin, uint16_t * ar, uint8_t size,
uint8_t level, uint8_t prescaler)
{
  _pin = pin;
  pinMode(_pin, OUTPUT);
  stop();

  _ar = ar;
  _size = size;
  // TODO: run over the array to test invalid values?
  // constrain them 10-4095?
  _level = constrain(level, LOW, HIGH);
  _prescaler = constrain(prescaler, PRESCALE_1, PRESCALE_1024);
  _cnt = 0;

  digitalWrite(_pin, _level);
  _state = STOPPED;
}

void PulsePattern::start()
{
  if (_size == 0) return;         // no pattern
  if (_state == RUNNING) return;  // no restart
  setTimer(1);                    // start asap
  _state = RUNNING;
}

void PulsePattern::stop()
{
  stopTimer();
  _state = STOPPED;
  _level = LOW;
  digitalWrite(_pin, _level);
}

void PulsePattern::worker()
{
  if (_state != RUNNING) return;
  // set next period & flip signal
  _level = !_level;
  // direct port faster
  digitalWrite(_pin, _level);
  // TODO: adjustment needed for code overhead when micros?;
  // + 5.2 usec for digitalWrite
  // + 3 usec for settimer call
  OCR1A = (_ar[_cnt]) * (F_CPU/1000000L);
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
void PulsePattern::setTimer(const uint16_t cc) const
{
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;      		      // reset counter
  OCR1A = cc * 16;	        // compare A register value;
  // * 16 makes max period 4095
  // min period 12?

  // 4: CTC mode, top = OCR1A
  TCCR1A = _BV (COM1A1);  	// clear on compare
  TCCR1B = _BV (WGM12) | _prescaler;
  TIFR1 |= _BV (OCF1A);     // clear interrupt flag
  TIMSK1 = _BV (OCIE1A);    // interrupt on Compare A Match
}

// END OF FILE