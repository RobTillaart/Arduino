//
//    FILE: X9C10X.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
// PURPOSE: Arduino Library for X9C10X series digital potentiometer.
//     URL: https://github.com/RobTillaart/X9C10X
//
// HISTORY
//  0.1.0  2022-01-26  initial version
//  0.1.1  2022-02-15  improve conditional delay
//  0.1.2  2022-02-16  improve performance, add sweeper example
//                     rounding in getOhm(), documentation
//  0.1.3  2022-02-22  add forced parameter to setPosition()
//                     incr() and decr() return bool (made a step)
//  0.2.0  2022-07-09  fix #7 incorrect signal during initialize
//                     remove position parameter from begin()
//                       to make setting position more explicit.
//                     update readme
//                     add uint8_t Ohm2Position()


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


/////////////////////////////////////////////////////////
//
//  MINIMALISTIC BASE CLASS
//
X9C::X9C()
{
}


void X9C::begin(uint8_t pulsePin, uint8_t directionPin, uint8_t selectPin)
{
  _pulsePin     = pulsePin;
  _directionPin = directionPin;
  _selectPin    = selectPin;

  //  #7 order of the initialization does matter
  //     as it might introduce an unwanted STORE pulse.
  //     use of pull ups might be wise.  
  digitalWrite(_selectPin,    HIGH);
  digitalWrite(_pulsePin,     HIGH);
  digitalWrite(_directionPin, HIGH);

  pinMode(_selectPin, OUTPUT);
  pinMode(_pulsePin, OUTPUT);
  pinMode(_directionPin, OUTPUT);

  //  wiper power up time. Page 5.
  delayMicroseconds(500);
}


bool X9C::incr()
{
  _move(X9C10X_UP);
  return true;
}


bool X9C::decr()
{
  _move(X9C10X_DOWN);
  return true;
}


void X9C::store()
{
  //  _pulsePin starts default HIGH
  digitalWrite(_selectPin, LOW);
  #if X9C10X_DELAY_MICROS > 0
  delayMicroseconds(X9C10X_DELAY_MICROS);
  #endif
  digitalWrite(_selectPin, HIGH);
  delay(20);    //  Tcph  page 5
}


/////////////////////////////////////////////////////////
//
//  PROTECTED
//
void X9C::_move(uint8_t direction, uint8_t steps)
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
//  X9C10X  BASE CLASS
//
X9C10X::X9C10X(uint32_t maxOhm) : X9C()
{
  _maxOhm = maxOhm;
}


void X9C10X::setPosition(uint8_t position, bool forced)
{
  if (position > 99) position = 99;
  //  reference 0.1.0
  //  while (position > _position) incr();
  //  while (position < _position) decr();

  //  force to nearest end position first to minimize steps.
  if (forced)  
  {
    if (position < 50)
    {
      _move(X9C10X_DOWN, 99);
      _position = 0;
    }
    else 
    {
      _move(X9C10X_UP, 99);
      _position = 99;
    }
  }
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


bool X9C10X::incr()
{
  if (_position >= 99) return false;
  _position++;
  _move(X9C10X_UP);
  return true;
}


bool X9C10X::decr()
{
  if (_position == 0) return false;
  _position--;
  _move(X9C10X_DOWN);
  return true;
}


uint8_t X9C10X::store()
{
  X9C::store();
  return _position;
}


//  rounding needed!
uint32_t X9C10X::getOhm()
{
  return (_maxOhm * _position + 49) / 99;
};


uint32_t X9C10X::getMaxOhm()
{
  return _maxOhm;
};


//  rounding needed!
uint8_t X9C10X::Ohm2Position(uint32_t value, bool invert)
{
  if (value > _maxOhm) return 99;
  uint8_t val = (99 * value + _maxOhm/2) / _maxOhm;
  if (invert) return 99 - val;
  return val;
}


uint16_t X9C10X::getType()
{
  return _type;
};


/////////////////////////////////////////////////////////
//
//  SPECIFIC DERIVED DEVICE CLASSES
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


