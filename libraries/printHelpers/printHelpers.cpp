//
//    FILE: printHelpers.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2018-01-21
// VERSION: 0.2.4
// PUPROSE: Arduino library to help formatting for printing.
//     URL: https://github.com/RobTillaart/printHelpers


#include "printHelpers.h"


// global buffer used by all functions so no static buffer in every function
// is needed ==> results need to be printed/copied asap
// not usable in multi-threading environments (use with care)
//
// 24 is a pretty safe minimum
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

char * print64(int64_t value, uint8_t base)
{
  char * buffer = __printbuffer;
  uint8_t i = 0;
  uint8_t j = 0;

  buffer[0] = 0;
  // small base need bigger buffer
  if ((base < 10) && (PRINTBUFFERSIZE <= 22)) return buffer;
  // handle special case
  if (value == 0)
  {
    buffer[0] = '0';
    buffer[1] = 0;
    return buffer;
  }

  // PREFIX NEGATIVE
  // handle negative values (for all bases for now)
  if ((value < 0) && (base != 16))
  {
    value = -value;
    buffer[0] = '-';
    i++;
    j++;
  }

  // PREFIX HEX
  if (base == 16)
  {
    buffer[0] = '0';
    buffer[1] = 'x';
    buffer[2] = 0;
    i = 2;
    j = 2;
  }
  // create one digit per loop
  while (value > 0)
  {
    int64_t temp = value / base;
    uint8_t digit = value - temp * base;
    buffer[i++] = (digit < 10) ? '0' + digit : ('A' - 10) + digit;
    value = temp;
  }
  buffer[i] = 0;
  // reverse buffer
  --i;
  while ( i > j)
  {
    uint8_t temp = buffer[i];
    buffer[i]    = buffer[j];
    buffer[j]    = temp;
    i--;
    j++;
  }
  return buffer;
}


char * print64(uint64_t value, uint8_t base)
{
  char * buffer = __printbuffer;
  uint8_t i = 0;
  uint8_t j = 0;

  buffer[0] = 0;
  // small base need bigger buffer
  if ((base < 10) && (PRINTBUFFERSIZE <= 22)) return buffer;
  // handle special case
  if (value == 0)
  {
    buffer[0] = '0';
    buffer[1] = 0;
    return buffer;
  }
  // create one digit per iteration
  while (value > 0)
  {
    uint64_t temp = value / base;
    uint8_t  digit = value - temp * base;
    buffer[i++] = (digit < 10) ? '0' + digit : ('A' - 10) + digit;
    value = temp;
  }
  buffer[i] = 0;
  // reverse buffer
  --i;
  while (i > j)
  {
    uint8_t temp = buffer[i];
    buffer[i]    = buffer[j];
    buffer[j]    = temp;
    i--;
    j++;
  }
  return buffer;
}


////////////////////////////////////////////////////////////
//
// SCIENTIFIC NOTATIION
//

// typical buffer size for 8 byte double is 22 bytes
// 15 bytes mantissa, sign dot E-xxx
//  em = exponentMultiple.
char * scieng(double value, uint8_t decimals, uint8_t em)
{
  char * buffer = __printbuffer;
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
  if (isnan(value))
  {
    strcpy(buffer, "nan");
    return buffer;
  }
  if (isinf(value))
  {
    if (value < 0) strcpy(buffer, "-inf");
    strcpy(buffer, "inf");
    return buffer;
  }

  // Handle negative numbers
  if (value < 0.0)
  {
    buffer[pos++] = '-';
    value = -value;
  }

  // Scale exponent to multiple of em
  // TODO: can we remove loop to reduce rounding errors
  while (value >= e1)
  {
    value *= e2;
    exponent += em;
  }
  // TODO: can we remove loop to reduce rounding errors
  while (value < 1 && value != 0.0)
  {
    value *= e1;
    exponent -= em;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  // TODO: can we remove loop to reduce rounding errors
  for (uint8_t i = 0; i < decimals; ++i)
  {
    rounding *= 0.1;
  }
  value += rounding;
  if (value >= e1)
  {
    exponent += em;
    value *= e2;
  }

  // Split whole part and remainder
  uint32_t d = (uint32_t)value;
  double remainder = value - d;

  // print whole part
  itoa(d, &buffer[pos], 10);
  pos = strlen(buffer);

  // print remainder part
  if (decimals > 0)
  {
    buffer[pos++] = '.';    // decimal point
  }

  // Extract decimals from the remainder one at a time
  // to prevent missing leading zero's
  // TODO: can we remove loop to reduce rounding errors
  while (decimals-- > 0)
  {
    remainder *= 10;
    d = (uint8_t)remainder;
    buffer[pos++] = d + '0';
    remainder -= d;
  }

  // print exponent
  buffer[pos++] = 'E';
  if (exponent < 0)
  {
    buffer[pos++] = '-';
    exponent = -exponent;
  }
  else buffer[pos++] = '+';

  itoa(exponent, &buffer[pos], 10);
  return buffer;
}


char * eng(double value, uint8_t decimals)
{
  return scieng(value, decimals, 3);
}


char * sci(double value, uint8_t decimals)
{
  return scieng(value, decimals, 1);
}


void sci(Stream &str, double value, uint8_t decimals)
{
  str.print(sci(value, decimals));
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
// so code wise difficult and as it is seldom used, support stops there.
//
// To have some support the code uses lowercase for the next 8 levels
// treda sorta rinta quexa pepta ocha nena minga luma (1024 ^21 ~~ 10^63)
char * toBytes(double value, uint8_t decimals)
{
  static char buffer[12];
  char  t[] = " KMGTPEZYXWVUtsrqponml";
  uint8_t i = 0;    // i is index of the array == powers of 1024.
  if (isinf(value))
  {
    strcpy(buffer, "<inf>");
    return buffer;
  }

  while(value >= 1024)
  {
    value /= 1024;
    i++;
  }
  if (i == 0) decimals = 0;
  if (decimals > 3) decimals = 3;

  // WHOLE PART iv
  int integerPart = value;
  itoa(integerPart, &buffer[0], 10);

  // DECIMALS
  value -= integerPart;
  uint8_t pos = strlen(buffer);
  if (decimals > 0)
  {
    buffer[pos++] = '.';
    while (decimals-- > 0)
    {
      value = value * 10;
      buffer[pos++] = '0' + int(value);
      value -= int(value);
    }
  }

  // UNITS
  if (i <= strlen(t))
  {
    if (i > 0) buffer[pos++] = ' ';
    buffer[pos++] = t[i];
    buffer[pos++] = 'B';
    buffer[pos]   = 0;
  }
  else
  {
    // TODO   e.g. E99 B
  }
  return buffer;
}


// -- END OF FILE --



