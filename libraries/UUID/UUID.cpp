//
//    FILE: UUID.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.6
//    DATE: 2022-06-14
// PURPOSE: Arduino Library for generating UUID's
//     URL: https://github.com/RobTillaart/UUID
//          https://en.wikipedia.org/wiki/Universally_unique_identifier


#include "UUID.h"


UUID::UUID()
{
  seed(1, 2);
  setVariant4Mode();
  generate();
}


void UUID::seed(uint32_t s1, uint32_t s2)
{
  //  set Marsaglia constants, prevent 0 as value
  if (s1 == 0) s1 = 1;
  if (s2 == 0) s2 = 2;
  _m_w = s1;
  _m_z = s2;
}


//  check version 0.1.1 for more readable code
void UUID::generate()
{
  uint32_t ar[4];
  for (uint8_t i = 0; i < 4; i++)
  {
    ar[i] = _random();
    //  store binary version globally ?
    //  _ar[i] = ar[i];
  }
  //  Conforming to RFC 4122 Specification
  //  - byte 7: four most significant bits ==> 0100  --> always 4
  //  - byte 9: two  most significant bits ==> 10    --> always {8, 9, A, B}.
  //
  //  patch bits for version 1 and variant 4 here
  if (_mode == UUID_MODE_VARIANT4)
  {
    ar[1] &= 0xFFF0FFFF;   //  remove 4 bits.
    ar[1] |= 0x00040000;   //  variant 4
    ar[2] &= 0xFFFFFFF3;   //  remove 2 bits
    ar[2] |= 0x00000008;   //  version 1
  }

  //  process 16 bytes build up the char array.
  for (uint8_t i = 0, j = 0; i < 16; i++)
  {
    //  multiples of 4 between 8 and 20 get a -.
    //  note we are processing 2 digits in one loop.
    if ((i & 0x1) == 0)
    {
      if ((4 <= i) && (i <= 10))
      {
        _buffer[j++] = '-';
      }
    }

    //  process one byte at the time instead of a nibble
    uint8_t nr   = i / 4;
    uint8_t xx   = ar[nr];
    uint8_t ch   = xx & 0x0F;
    _buffer[j++] = (ch < 10) ? '0' + ch : ('a' - 10) + ch;

    ch = (xx >> 4) & 0x0F;
    ar[nr] >>= 8;
    _buffer[j++] = (ch < 10) ? '0' + ch : ('a' - 10) + ch;
  }

  //  if (_upperCase)
  //  {
  //    for (int i = 0; i < 37; i++)
  //    {
  //      _buffer[i] = toUpper(_buffer[i]);
  //    }
  //  }
  _buffer[36] = 0;
}


char * UUID::toCharArray()
{
  //  if (_upperCase)
  //  {
  //    for (int i = 0; i < 37; i++)
  //    {
  //      _buffer[i] = toLower(_buffer[i]);
  //    }
  //  }
  //  else
  //  {
  //    for (int i = 0; i < 37; i++)
  //    {
  //      _buffer[i] = toLower(_buffer[i]);
  //    }
  //  }
  return _buffer;
}


//////////////////////////////////////////////////
//
//  MODE
//
void UUID::setVariant4Mode()
{
  _mode = UUID_MODE_VARIANT4;
}


void UUID::setRandomMode()
{
  _mode = UUID_MODE_RANDOM;
}


uint8_t UUID::getMode()
{
  return _mode;
}


//////////////////////////////////////////////////
//
//  PRINTING
//
size_t UUID::printTo(Print& p) const
{
  return p.print(_buffer);
}


//////////////////////////////////////////////////
//
//  CASE
//
//  void UUID::setLowerCase()
//  {
//    _upperCase = false;
//  }
//
//
//  void UUID::setUpperCase()
//  {
//    _upperCase = true;
//  }


//////////////////////////////////////////////////
//
//  PRIVATE
//



//////////////////////////////////////////////////
//
//  RANDOM GENERATOR MARSAGLIA
//
//  An example of a simple pseudo-random number generator is the
//  Multiply-with-carry method invented by George Marsaglia.
//  two initializers (not null)
uint32_t UUID::_random()
{
  _m_z = 36969L * (_m_z & 65535L) + (_m_z >> 16);
  _m_w = 18000L * (_m_w & 65535L) + (_m_w >> 16);
  return (_m_z << 16) + _m_w;  //   32-bit result
}


//  -- END OF FILE --

