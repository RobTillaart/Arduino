//
//    FILE: LUHN.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2022-12-24
// PURPOSE: Arduino Library for calculating LUHN checksum.
//     URL: https://github.com/RobTillaart/LUHN


#include "LUHN.h"


LUHN::LUHN()
{
  _luhn = 0;
  _count = 0;
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

  for (int i = 0; i < length-1; i++)
  {
    uint8_t x = buffer[i] - '0';
    if (i % 2 == 0) checksum += x;            //  weight 1
    else if (x < 5) checksum += x * 2;        //  weight 2
         else checksum += (x * 2 - 10 + 1);   //  weight 2 + handle overflow.
  }
  uint8_t a = (10000UL - checksum) % 10;
  uint8_t b = buffer[length-1] - '0';
  return a == b;
}


char LUHN::generateChecksum(char * buffer)
{
  uint16_t checksum = 0;
  uint8_t length = strlen(buffer);
  for (int i = 0; i < length; i++)
  {
    uint8_t x = buffer[i] - '0';
    if (i % 2 == 0) checksum += x;            //  weight 1
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
    buffer[i++] = '0' + Marsaglia_mod10();
    buffer[i] = '\0';
  }
  char c = generateChecksum(buffer);
  buffer[i++] = c;
  buffer[i] = '\0';
  return true;
}


char LUHN::add(char c)
{
  uint8_t x = c - '0';
  if (_count % 2 == 0) _luhn += x;
  else if (x < 5)      _luhn += x * 2;
  else                 _luhn += (x * 2 - 10 + 1);
  //  correct
  if (_luhn > 9)       _luhn -= 10;
  _count++;
  return '0' + (10 - _luhn);
}


char LUHN::reset()
{
  uint8_t last = _luhn;
  _luhn = 0;
  _count = 0;
  return '0' + (10 - last);
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
uint8_t LUHN::Marsaglia_mod10()
{
    m_z = 36969L * (m_z & 65535L) + (m_z >> 16);
    m_w = 18000L * (m_w & 65535L) + (m_w >> 16);
    return (m_z ^ m_w) % 10;   //  changed
}


//  -- END OF FILE --

