//
//    FILE: LUHN.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
//    DATE: 2022-12-24
// PURPOSE: Arduino Library for calculating LUHN checksum.
//     URL: https://github.com/RobTillaart/LUHN


#include "LUHN.h"


LUHN::LUHN()
{
  _luhnEven = 0;
  _luhnOdd  = 0;
  _count    = 0;
}


bool LUHN::isValid(const char * buffer)
{
  return isValid((char*)buffer);
}


bool LUHN::isValid(char * buffer)
{
  uint16_t checksum = 0;
  uint8_t length = strlen(buffer);
  if (length == 0) return false;

  uint8_t parity = length & 1;
  for (int i = 0; i < length-1; i++)
  {
    uint8_t x = buffer[i] - '0';
    if (i % 2 != parity) checksum += x;       //  weight 1
    else if (x < 5) checksum += x * 2;        //  weight 2
         else checksum += (x * 2 - 10 + 1);   //  weight 2 + handle overflow.
  }
  uint8_t a = (10000UL - checksum) % 10;
  uint8_t b = buffer[length-1] - '0';
  return a == b;
}


char LUHN::generateChecksum(const char * buffer)
{
  return generateChecksum((char *) buffer);
}


char LUHN::generateChecksum(char * buffer)
{
  uint16_t checksum = 0;
  uint8_t length = strlen(buffer);
  uint8_t parity = length & 1;
  for (int i = 0; i < length; i++)
  {
    uint8_t x = buffer[i] - '0';
    if (i % 2 == parity) checksum += x;       //  weight 1
    else if (x < 5) checksum += x * 2;        //  weight 2
         else checksum += (x * 2 - 10 + 1);   //  weight 2 + handle overflow.
  }
  return '0' + ((10000UL - checksum) % 10);
}


void LUHN::randomize(uint32_t a, uint32_t b)
{
  m_z = a;
  m_w = b;
}


bool LUHN::generate(char * buffer, uint8_t length, char * prefix)
{
  int len = strlen(prefix);
  if (len >= length) return false;
  if (length < 2) return false;
  strcpy(buffer, prefix);
  int i;
  for (i = len; i < length-1;)
  {
    buffer[i++] = '0' + _Marsaglia_mod10();
    buffer[i] = '\0';
  }
  char c = generateChecksum(buffer);
  buffer[i++] = c;
  buffer[i] = '\0';
  return true;
}


//////////////////////////////////////////////////////////////
//
//  STREAM INTERFACE
//
char LUHN::add(char c)
{
  //  as we do not know the final length in advance 
  // both parity's must be calculated.
  uint8_t x = c - '0';
  //  handle even lengths
  if (_count % 2 == 0) _luhnEven += x;
  else if (x < 5)      _luhnEven += x * 2;
  else                 _luhnEven += (x * 2 - 10 + 1);
  //  handle odd lengths
  if (_count % 2 == 1) _luhnOdd += x;
  else if (x < 5)      _luhnOdd += x * 2;
  else                 _luhnOdd += (x * 2 - 10 + 1);
  
  _count++;
  if (_count & 1) return '0' + (100 - _luhnOdd) % 10;
  return '0' + (100 - _luhnEven) % 10;
}


char LUHN::reset()
{
  uint8_t last = _luhnEven;
  if (_count & 1) last = _luhnOdd;
  _luhnEven = 0;
  _luhnOdd  = 0;
  _count    = 0;
  return '0' + (100 - last) % 10;
}


uint32_t LUHN::count()
{
  return _count;
}


///////////////////////////////////////////////////////////////////////////
//
//  PROTECTED
//
///////////////////////////////////////////////////////////////////////////
//
//  An example of a simple pseudo-random number generator is the 
//  Multiply-with-carry method invented by George Marsaglia.
//  it has two initializers (not zero) which can be changed 
//  to seed the generator.
//  this is derived work.
//
uint8_t LUHN::_Marsaglia_mod10()
{
    m_z = 36969L * (m_z & 65535L) + (m_z >> 16);
    m_w = 18000L * (m_w & 65535L) + (m_w >> 16);
    return (m_z ^ m_w) % 10;   //  changed
}


//  EXPERIMENTAL
//  ~8% faster and 58 bytes bigger (UNO)
// uint8_t LUHN::_Marsaglia_mod10()
// {
  // static uint32_t value;
  // static uint8_t  digits = 0;
  // if (digits == 0)
  // {
    // digits = 4;
    // m_z = 36969L * (m_z & 65535L) + (m_z >> 16);
    // m_w = 18000L * (m_w & 65535L) + (m_w >> 16);
    // value = (m_z ^ m_w);
  // }
  // uint8_t rv = value % 10;
  // value >>= 8;
  // digits--;
  // return rv;
// }


//  -- END OF FILE --

