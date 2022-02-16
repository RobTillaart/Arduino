//
//    FILE: X9C10X.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
// PURPOSE: Arduino Library for X9C10X series digital potentiometer.
//
// HISTORY
//  0.1.0  2022-01-26  initial version
//  0.1.1  2022-02-15  improve conditional delay
//  0.1.2  2022-02-16  improve performance, add sweeper example
//                     rounding in getOhm(), documentation


#include "X9C10X.h"

//  minimum pulse width CLOCK = ? us (datasheet);
//  digitalWrite takes enough time on UNO / AVR so clock_delay == 0
//  Note that if clock pulses are long enough the data pulses are too.
#ifdef __AVR__
#define X9C10X_DELAY_MICROS         0
#else
#define X9C10X_DELAY_MICROS         1
#endif

#define X9C10X_UP                   HIGH
#define X9C10X_DOWN                 LOW


X9C10X::X9C10X(uint32_t maxOhm)
{
  _maxOhm = maxOhm;
}


void X9C10X::begin(uint8_t pulsePin, uint8_t directionPin, uint8_t selectPin, uint8_t position)
{
  _pulsePin     = pulsePin;
  _directionPin = directionPin;
  _selectPin    = selectPin;

  pinMode(_pulsePin, OUTPUT);
  pinMode(_directionPin, OUTPUT);
  pinMode(_selectPin, OUTPUT);

  digitalWrite(_pulsePin,     HIGH);
  digitalWrite(_directionPin, HIGH);
  digitalWrite(_selectPin,    HIGH);

  //  wiper power up time. Page 5.
  delayMicroseconds(500);

  //  reset defined position.
  _position = position;
}


//  initial implementation, to be optimized.
void X9C10X::setPosition(uint8_t position)
{
  if (position > 99) position = 99;
  // reference 0.1.0
  // while (position > _position) incr();
  // while (position < _position) decr();
  if (position > _position)
  {
    _move(X9C10X_UP, position - _position);
  }
  if (position < _position)
  {
    _move(X9C10X_DOWN, _position - position);
  }
  _position = position;
}


void X9C10X::incr()
{
  if (_position >= 99) return;
  _position++;
  _move(X9C10X_UP);
}


void X9C10X::decr()
{
  if (_position == 0) return;
  _position--;
  _move(X9C10X_DOWN);
}


uint8_t X9C10X::store()
{
  //  _pulsePin starts default HIGH
  digitalWrite(_selectPin, LOW);
  #if X9C10X_DELAY_MICROS > 0
  delayMicroseconds(X9C10X_DELAY_MICROS);
  #endif
  digitalWrite(_selectPin, HIGH);
  delay(20);    //  Tcph  page 5
  return _position;
}


////////////////////////////////////////////////////////////////////
//
//  PRIVATE
//
void X9C10X::_move(uint8_t direction, uint8_t steps)
{
  digitalWrite(_directionPin, direction);
  delayMicroseconds(3);  // Tdi  (page 5)

  //  _pulsePin starts default HIGH
  digitalWrite(_selectPin, LOW);
  while (steps--)
  {
    digitalWrite(_pulsePin, HIGH);
    #if X9C10X_DELAY_MICROS > 0
    delayMicroseconds(X9C10X_DELAY_MICROS);
    #endif

    digitalWrite(_pulsePin, LOW);
    #if X9C10X_DELAY_MICROS > 0
    delayMicroseconds(X9C10X_DELAY_MICROS);
    #endif
  }
  //  _pulsePin == LOW, (No Store, page 7)
  digitalWrite(_selectPin, HIGH);
  // reset _pulsePin to default.
  digitalWrite(_pulsePin, HIGH);
}



/////////////////////////////////////////////////////////
//
// DERIVED
//
X9C102::X9C102(uint32_t ohm) : X9C10X(ohm)
{
  _type = 102;
}

X9C103::X9C103(uint32_t ohm) : X9C10X(ohm)
{
  _type = 103;
}

X9C104::X9C104(uint32_t ohm) : X9C10X(ohm)
{
  _type = 104;
}

X9C503::X9C503(uint32_t ohm) : X9C10X(ohm)
{
  _type = 503;
}


// -- END OF FILE --


