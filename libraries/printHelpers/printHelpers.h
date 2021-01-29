#pragma once
//
//    FILE: printHelpers.h
//  AUTHOR: Rob Tillaart
//    DATE: 2018-01-21
// VERSION: 0.2.0
// PUPROSE: Arduino library to help formatting for printing. 
//     URL: https://github.com/RobTillaart/printHelpers


#include "Arduino.h"
#include "stdlib.h"


#define PRINTHELPERS_VERSION      (F("0.2.0"))

// 24 is a pretty safe minimum

#ifndef PRINTBUFFERSIZE
#define PRINTBUFFERSIZE       66
#endif

// global buffer used by all functions so no static buffer in every function
// is needed ==> results need to be printed/copied asap
// not usable in multi-threading environments (use with care)

char __printbuffer[PRINTBUFFERSIZE];


////////////////////////////////////////////////////////////
//
// PRINT 64 BIT 
//

// print64 note
// buffer size 66 will work for base 2 -36
// buffer size 34 will work for base 4 -36
// buffer size 24 will work for base 8 -36
// buffer size 22 will work for base 10 - 36

char * print64(int64_t n, uint8_t base = 10)
{
  char * buf = __printbuffer;
  uint8_t i = 0;
  uint8_t j = 0;

  buf[0] = 0;
  // small base need bigger buffer
  if ((base < 10) && (PRINTBUFFERSIZE <= 22)) return buf;
  // handle special case
  if (n == 0)
  {
    buf[0] = '0';
    buf[1] = 0;
    return buf;
  }

  // PREFIX NEGATIVE
  // handle negative values (for all bases for now)
  if ((n < 0) && (base != 16))
  {
    n = -n;
    buf[0] = '-';
    i++;
    j++;
  }

  // PREFIX HEX
  if (base == 16)
  {
    buf[0] = '0';
    buf[1] = 'x';
    buf[2] = 0;
    i = 2;
    j = 2;
  }
  // create one digit per loop
  while (n > 0)
  {
    int64_t t = n / base;
    uint8_t p = n - t * base;
    buf[i++] = (p < 10) ? '0' + p : ('A' - 10) + p;
    n = t;
  }
  buf[i] = 0;
  // reverse buffer
  --i;
  while ( i > j)
  {
    uint8_t t = buf[i];
    buf[i] = buf[j];
    buf[j] = t;
    i--;
    j++;
  }
  return buf;
}


char * print64(uint64_t n, uint8_t base = 10)
{
  char * buf = __printbuffer;
  uint8_t i = 0;
  uint8_t j = 0;

  buf[0] = 0;
  // small base need bigger buffer
  if ((base < 10) && (PRINTBUFFERSIZE <= 22)) return buf;
  // handle special case
  if (n == 0)
  {
    buf[0] = '0';
    buf[1] = 0;
    return buf;
  }
  // create one digit per loop
  while (n > 0)
  {
    uint64_t t = n / base;
    uint8_t p = n - t * base;
    buf[i++] = (p < 10) ? '0' + p : ('A' - 10) + p;
    n = t;
  }
  buf[i] = 0;
  // reverse buf
  --i;
  while (i > j)
  {
    uint8_t t = buf[i];
    buf[i] = buf[j];
    buf[j] = t;
    i--;
    j++;
  }
  return buf;
}


////////////////////////////////////////////////////////////
//
// SCIENTIFIC NOTATIION
//

// typical buffer size for 8 byte double is 22 bytes 
// 15 bytes mantissa, sign dot E-xxx
char * scieng(double number, uint8_t digits, uint8_t em)
{
  char * buf = __printbuffer;
  int exponent = 0;
  int pos = 0;
  double e1 = 10;
  double e2 = 0.1;
  for (int i = 1; i < em; i++)
  {
    e1 *= 10;
    e2 *= 0.1;
  }

  // Handling these costs 13 bytes RAM
  // shorten them with N, I, -I ?
  if (isnan(number)) 
  {
    strcpy(buf, "nan");
    return buf;
  }
  if (isinf(number))
  {
    if (number < 0) strcpy(buf, "-inf");
    strcpy(buf, "inf");
    return buf;
  }

  // Handle negative numbers
  if (number < 0.0)
  {
    buf[pos++] = '-';
    number = -number;
  }

  // Scale exponent to multiple of em  
  // TODO: can we remove loop to reduce rounding errors
  while (number >= e1)
  {
    number *= e2;
    exponent += em;
  }
  // TODO: can we remove loop to reduce rounding errors
  while (number < 1 && number != 0.0)
  {
    number *= e1;
    exponent -= em;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  // TODO: can we remove loop to reduce rounding errors
  for (uint8_t i = 0; i < digits; ++i)
  {
    rounding *= 0.1;
  }
  number += rounding;
  if (number >= e1)
  {
    exponent += em;
    number *= e2;
  }

  // Split whole part and remainder
  uint32_t d = (uint32_t)number;
  double remainder = number - d;

  // print whole part
  itoa(d, &buf[pos], 10);
  pos = strlen(buf);

  // print remainder part
  if (digits > 0)
  {
    buf[pos++] = '.';    // decimal point
  }

  // Extract digits from the remainder one at a time 
  // to prevent missing leading zero's
  // TODO: can we remove loop to reduce rounding errors
  while (digits-- > 0)
  {
    remainder *= 10;
    d = (uint8_t)remainder;
    buf[pos++] = d + '0';
    remainder -= d;
  }

  // print exponent
  buf[pos++] = 'E';
  if (exponent < 0)
  {
    buf[pos++] = '-';
    exponent = -exponent;
  }
  else buf[pos++] = '+';

  itoa(exponent, &buf[pos], 10);
  return buf;
}


char * eng(double number, uint8_t digits)
{
  return scieng(number, digits, 3);
}


char * sci(double number, uint8_t digits)
{
  return scieng(number, digits, 1);
}


void sci(Stream &str, double f, uint8_t digits)
{
  str.print(sci(f, digits));
}

////////////////////////////////////////////////////////////
//
// toBytes 
//

// official support to UDA == 1024^12
// kilo mega giga tera peta exa (1024^6)
// zetta yotta xona weka vunda uda (1024^12)
//
// (treda Byte == TDB is the next one and it is 2 char 
// so codewise difficult and as it is seldom used, support stops there.
// 
// To have some support the code uses lowercase for the next 8 levels
// treda sorta rinta quexa pepta ocha nena minga luma (1024 ^21 ~~ 10^63)
char * toBytes(double val, uint8_t decimals = 2)
{
  static char buf[12];
  char t[] = " KMGTPEZYXWVUtsrqponml";
  uint8_t i = 0;
  if (isinf(val)) 
  {
    strcpy(buf, "<inf>");
    return buf;
  }

  while(val >= 1024)
  {
    val /= 1024;
    i++;
  }
  if (i == 0) decimals = 0;
  if (decimals > 3) decimals = 3;

  // WHOLE PART
  int iv = val;
  itoa(iv, &buf[0], 10);
  
  // DECIMALS
  val -= iv;
  uint8_t pos = strlen(buf);
  if (decimals > 0)
  {
    buf[pos++] = '.';
    while (decimals-- > 0)
    {
      val = val * 10;
      buf[pos++] = '0' + int(val);
      val -= int(val);
    }
  }
  
  // UNITS
  if (i <= strlen(t))
  {
    if (i > 0) buf[pos++] = ' ';
    buf[pos++] = t[i];
    buf[pos++] = 'B';
    buf[pos] = 0;
  }
  else
  {
    // TODO   e.g. E99 B
  }
  return buf;
}


// -- END OF FILE --
