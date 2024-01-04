#pragma once
//
//    FILE: MathHelpers.h
//  AUTHOR: Rob Tillaart
//    DATE: 2018-01-21
// VERSION: 0.1.2
// PURPOSE: misc functions for math and time
//
//  replaced by printHelpers and datetimeHelpers.h
//
//  0.1.2 - 2024-01-04 minor refactor


#define MATHHELPERS_VERSION (F("0.1.2"))

// global buffer used by all functions
// so we do not need a static buffer in every function
// not usable in multi-threading environments
// results need to be printed/copied asap
char __mathHelperBuffer[17];


//////////////////////////////////////////////////
//
// FLOAT REPRESENTATION HELPERS
//
char * sci(double number, int digits)
{
  int exponent = 0;
  int pos = 0;

  // Handling these costs 13 bytes RAM
  // shorten them with N, I, -I ?
  if (isnan(number)) 
  {
    strcpy(__mathHelperBuffer, "nan");
    return __mathHelperBuffer;
  }
  if (isinf(number))
  {
    if (number < 0) strcpy(__mathHelperBuffer, "-inf");
    strcpy(__mathHelperBuffer, "inf");
    return __mathHelperBuffer;
  }

  // Handle negative numbers
  bool neg = (number < 0.0);
  if (neg)
  {
    __mathHelperBuffer[pos++] = '-';
    number = -number;
  }

  while (number >= 10.0)
  {
    number /= 10;
    exponent++;
  }
  while (number < 1 && number != 0.0)
  {
    number *= 10;
    exponent--;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i = 0; i < digits; ++i)
  {
    rounding *= 0.1;
  }
  number += rounding;
  if (number >= 10)
  {
    exponent++;
    number /= 10;
  }


  // Extract the integer part of the number and print it
  uint8_t d = (uint8_t)number;
  double remainder = number - d;
  __mathHelperBuffer[pos++] = d + '0';   // 1 digit before decimal point
  if (digits > 0)
  {
    __mathHelperBuffer[pos++] = '.';  // decimal point TODO:rvdt CONFIG?
  }


  // Extract digits from the remainder one at a time to prevent missing leading zero's
  while (digits-- > 0)
  {
    remainder *= 10.0;
    d = (uint8_t)remainder;
    __mathHelperBuffer[pos++] = d + '0';
    remainder -= d;
  }


  // print exponent
  __mathHelperBuffer[pos++] = 'E';
  neg = exponent < 0;
  if (neg)
  {
    __mathHelperBuffer[pos++] = '-';
    exponent = -exponent;
  }
  else __mathHelperBuffer[pos++] = '+';


  // 3 digits for exponent;           // needed for double
  // d = exponent / 100;
  // __mathHelperBuffer[pos++] = d + '0';
  // exponent -= d * 100;

  // 2 digits for exponent
  d = exponent / 10;
  __mathHelperBuffer[pos++] = d + '0';
  d = exponent - d*10;
  __mathHelperBuffer[pos++] = d + '0';

  __mathHelperBuffer[pos] = '\0';

  return __mathHelperBuffer;
}


void sci(Stream &str, float f, uint8_t digits)
{
  str.print(sci(f, digits));
}


//////////////////////////////////////////////////
//
// TIME HELPERS
//

// (true)   00:00:00 .. 23:59:59 
// (false)  00:00 ..    23:59
char * seconds2clock(uint32_t seconds, bool displaySeconds=false)
{
  uint16_t days = seconds / 86400UL;  // strips the days
  seconds -= (days * 86400UL);
  uint8_t hours = seconds / 3600UL;
  seconds -= (hours * 3600UL);
  uint8_t minutes = seconds / 60UL;
  seconds -= (minutes * 60UL);

  uint8_t pos = 0;
  __mathHelperBuffer[pos++] = hours/10 + '0';
  __mathHelperBuffer[pos++] = hours%10 + '0';
  __mathHelperBuffer[pos++]  = ':';
  
  __mathHelperBuffer[pos++] = minutes/10 + '0';
  __mathHelperBuffer[pos++] = minutes%10 + '0';
  if (displaySeconds)
  {
    __mathHelperBuffer[pos++]  = ':';
    __mathHelperBuffer[pos++] = seconds/10 + '0';
    __mathHelperBuffer[pos++] = seconds%10 + '0';
  }
  __mathHelperBuffer[pos]  = '\0';
  
  return __mathHelperBuffer;
}


char * millis2clock(uint32_t millis)
{
  uint32_t t = millis/1000;
  seconds2clock(t, true);
  uint16_t m = millis - t*1000;

  __mathHelperBuffer[8]  = '.';
  uint8_t pos = 9;
  uint8_t d = m/100;
  __mathHelperBuffer[pos++] = d + '0';
  m = m - d * 100;
  d = m/10;
  __mathHelperBuffer[pos++] = d + '0';
  d = m - d * 10;
  __mathHelperBuffer[pos++] = d + '0';
  __mathHelperBuffer[pos]  = '\0';

  return __mathHelperBuffer;
}

float weeks(uint32_t seconds)
{
  return seconds * 1.653439153439e-6;  //  /604800
}

float days(uint32_t seconds)
{
  return seconds * 1.157407407407e-5;  //  /86400
}

float hours(uint32_t seconds)
{
  return seconds * 2.777777777778e-4;  //  /3600
}

float minutes(uint32_t seconds)
{
  return seconds * 1.666666666667e-2;  //  /60
}


//////////////////////////////////////////////////
//
// HEX BIN HELPERS
//
// notes:
// - d should not exceed 16 otherwise __mathHelperBuffer overflows...
// - no 64 bit support

char * hex(uint32_t value, uint8_t d = 8)
{
	if (d > 16) d = 16;
	__mathHelperBuffer[d] = '\0';
	while (d > 0)
	{
		uint8_t v = value & 0x0F;
		value >>= 4;
		__mathHelperBuffer[--d] = (v < 10) ? '0' + v : 'A' - 10 + v;
	}
	return __mathHelperBuffer;
}


char * bin(uint32_t value, uint8_t d = 8)
{
    if (d > 16) d = 16;
	__mathHelperBuffer[d] = '\0';
	while (d > 0)
	{
		uint8_t v = value & 0x01;
		value >>= 1;
		__mathHelperBuffer[--d] = '0' + v;
	}
	return __mathHelperBuffer;
}


// -- END OF FILE -- 

