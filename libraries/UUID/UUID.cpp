//
//    FILE: UUID.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
//    DATE: 2022-06-14
// PURPOSE: Arduino Library for generating UUID's
//     URL: https://github.com/RobTillaart/UUID
//          https://en.wikipedia.org/wiki/Universally_unique_identifier


#include "UUID.h"


UUID::UUID()
{
  //  seed - differs per construction on compile time constants
  //         and multiplication with micros().
  //  TODO investigate how to differ better at runtime.
  uint32_t s2 = _hash(__TIME__) * micros();
  uint32_t s1 = s2 ^ _hash(__DATE__);
           s2 = s2 ^ _hash(__FILE__);
  seed(s1, s2);
  setVersion4Mode();
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


// void UUID::autoSeed()
// {
  // static uint32_t lastMicros = 0;
  // uint32_t now = micros();
  // _m_w ^= now;
  // if (_m_w == 0) _m_w = 1
  // _m_z ^= (now - lastMicros);
  // if (_m_z == 0) _m_z = _m_w * 2;
  // lastMicros = now;
// }


//  check version 0.1.1 for more readable code
void UUID::generate()
{
  uint32_t ar[4];
  for (int i = 0; i < 4; i++)
  {
    ar[i] = _random();
  }
  //  Conforming to RFC 4122 Specification, version 4, variant 1
  //  - byte 7: four most significant bits ==> 0100  --> always 4
  //  - byte 9: two  most significant bits ==> 10    --> always {8, 9, A, B}.
  //
  //  patch bits for version 4 and variant 1 here
  if (_mode == UUID_MODE_VERSION4)
  {
    ar[1] &= 0xFFF0FFFF;   //  remove 4 bits.
    ar[1] |= 0x00040000;   //  variant 4
    ar[2] &= 0xFFFFFFF3;   //  remove 2 bits
    ar[2] |= 0x00000008;   //  version 1
  }
  //  store binary version globally ?
  //  _ar[i] = ar[i];

  //  process 16 bytes build up the char array.
  for (int i = 0, j = 0; i < 16; i++)
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

  _buffer[36] = 0;
}


char * UUID::toCharArray()
{
  return _buffer;
}


//////////////////////////////////////////////////
//
//  MODE
//
int UUID::getMode()
{
  return _mode;
}

void UUID::setRandomMode()
{
  _mode = UUID_MODE_RANDOM;
}

void UUID::setVersion4Mode()
{
  _mode = UUID_MODE_VERSION4;
}

// void UUID::setVersion8Mode(uint8_t nodeId[6])
// {
//   //  TODO  store node ID in lib.
//   _mode = UUID_MODE_VERSION8;
// }


//  OBSOLETE in 0.3.0
void UUID::setVariant4Mode()
{
  _mode = UUID_MODE_VERSION4;
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


uint32_t UUID::_hash(const char * str)
{
  //  very simple hash function.
  uint32_t hash = strlen(str);
  for (char *p = (char *) str; *p != 0; p++)
  {
    //  use a big prime as magic number.
    hash = hash * 2000099957 + (uint8_t) *p;
  }
  return hash;
}


//////////////////////////////////////////////////
//
//  DERIVED CLASS GUID
//
GUID::GUID() : UUID()
{
}


//////////////////////////////////////////////////
//
//  DERIVED CLASS ? - TODO
//



//  -- END OF FILE --

