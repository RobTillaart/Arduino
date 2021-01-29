//
//    FILE: PulsePattern.cpp
//  AUTHOR: Rob dot Tillaart at gmail dot com
// VERSION: 0.1.3
//    DATE: 2012-11-23
// PURPOSE: Arduino Library to generate repeating pulse patterns
//
//  HISTORY:
//  0.0.1   2012-11-23  initial version
//  0.0.2   2012-11-23  adapted a static PPO
//  0.0.3   2012-12-27  renamed to PulsePattern
//  0.0.4   2012-12-27  code stable(?) enough to publish
//  0.0.5   2012-12-27  code cleanup+comment
//  0.0.6   2015-04-18  completed the state machine
//  0.0.7   2017-07-16  refactor & review
//  0.0.8   2018-12-13  refactor -> remove some warnings
//  0.1.0   2020-06-19  #pragma once; remove pre 1.0 support; refactor
//  0.1.1   2020-07-04  add continue function, fix spaces.
//  0.1.2   2020-08-07  speed up toggle pin + get/setFactor()
//  0.1.3   2021-01-06  arduino-ci (no unit test)


#include "PulsePattern.h"


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

void PulsePattern::init(const uint8_t pin, const uint16_t * ar, const uint8_t size,
const uint8_t level, const uint8_t prescaler)
{
  _pin = pin;
  pinMode(_pin, OUTPUT);
  stop();

  _ar = (uint16_t *) ar;
  _size = size;
  _level = level ? LOW : HIGH;
  _prescaler = constrain(prescaler, PRESCALE_1, PRESCALE_1024);
  _cnt = 0;

  digitalWrite(_pin, _level);
  _state = STOPPED;

  // fast low level AVR ports
  uint8_t _pinport   = digitalPinToPort(_pin);
  _pinout = portOutputRegister(_pinport);
  _pinbit = digitalPinToBitMask(_pin);
}

void PulsePattern::start()
{
  if (_state == RUNNING) return;  // no restart
  _cnt = 0;                       // start from begin
  cont();
}

void PulsePattern::cont()
{
  if (_state == RUNNING) return;  // no continue
  if (_size == 0) return;         // no pattern
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
  // digitalWrite(_pin, _level);
  // direct port much faster
  if (_level == 0) *_pinout &= ~_pinbit;
  else *_pinout |= _pinbit;

  if (_factor != 4096)
  {
    OCR1A = _ar[_cnt] * _factor * (F_CPU/1000000UL) / 4096;
  }
  else
  {
    OCR1A = _ar[_cnt] * (F_CPU/1000000UL);
  }
  _cnt++;
  if (_cnt >= _size) _cnt = 0;  // repeat pattern
}

// TIMER code based upon - http://www.gammon.com.au/forum/?id=11504
void PulsePattern::stopTimer()
{
  TCCR1A = 0;        // reset timer 1
  TCCR1B = 0;
}

void PulsePattern::setTimer(const uint16_t cc) const
{
  TCCR1A = 0;               // stop timer first
  TCCR1B = 0;
  TCNT1 = 0;                // reset counter
  OCR1A = cc * 16;          // compare A register value;
  // * 16 makes max period 4095
  // min period 12?

  // 4: CTC mode, top = OCR1A
  TCCR1A = _BV (COM1A1);    // clear on compare
  TCCR1B = _BV (WGM12) | _prescaler;
  TIFR1 |= _BV (OCF1A);     // clear interrupt flag
  TIMSK1 = _BV (OCIE1A);    // interrupt on Compare A Match
}

// -- END OF FILE --
