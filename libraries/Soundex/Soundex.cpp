//
//    FILE: Soundex.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2022-02-05
// PURPOSE: Arduino Library for calculating Soundex hash
//     URL: https://github.com/RobTillaart/Soundex


#include "Soundex.h"


Soundex::Soundex()
{
  _buffer[0] = '\0';
  _length = 4;
}


void Soundex::setLength(uint32_t length)
{
  _length = length;
  if (_length > (SOUNDEX_MAX_LENGTH - 1))
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


// -- END OF FILE -- 


