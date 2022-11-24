//
//    FILE: Soundex.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.3
//    DATE: 2022-02-05
// PURPOSE: Arduino Library for calculating Soundex hash
//     URL: https://github.com/RobTillaart/Soundex


#include "Soundex.h"


Soundex::Soundex()
{
  _buffer[0] = '\0';
  _length = 4;
}


void Soundex::setLength(uint8_t length)
{
  _length = length;
  if (_length < SOUNDEX_MIN_LENGTH)
  {
    _length = SOUNDEX_MIN_LENGTH;
  }
  else if (_length > (SOUNDEX_MAX_LENGTH - 1))
  {
    _length = SOUNDEX_MAX_LENGTH - 1;
  }
};


char * Soundex::soundex(const char * str)
{
  uint8_t i = 0;  // index for the buffer.

  //  fill buffer with zeros
  for (i = 0; i < _length; i++) _buffer[i] = '0';
  _buffer[_length] = '\0';

  //  find begin of word, skip spaces, digits
  char *p = (char *) &str[0];
  while((*p != 0) && (isalpha(*p) == false)) p++;
  if (*p == 0) return _buffer;

  //  handle first character
  i = 0;
  _buffer[i++] = toupper(*p);
  uint8_t last = sdx[_buffer[0] - 'A'];  // remember last code
  p++;

  //  process the remainder of the string
  while ((*p != 0) && (i < _length))
  {
    if (isalpha(*p))  // skip non ASCII
    {
      uint8_t current = sdx[toupper(*p) - 'A'];
      // new code?
      if (last != current)
      {
        last = current;
        if (last != 0) _buffer[i++] = '0' + last;
      }
    }
    p++;
  }
  return _buffer;
}


//  reference implementation
uint16_t Soundex::soundex16(const char * str)
{
  uint8_t tmp = _length;
  _length = 5;
  char *p = soundex(str);
  _length = tmp;

  uint16_t value = (p[0] - 'A');
  for (uint8_t i = 1; i < 5; i++)
  {
    value *= 7;
    value += (p[i] - '0');
  }
  return value;
}


//  reference implementation
uint32_t Soundex::soundex32(const char * str)
{
  uint8_t tmp = _length;
  _length = 10;
  char *p = soundex(str);
  _length = tmp;

  uint32_t value = (p[0] - 'A');
  for (uint8_t i = 1; i < 10; i++)
  {
    value *= 7;
    value += (p[i] - '0');
  }
  return value;
}


//  -- END OF FILE --

