//
//    FILE: printHelpers.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2018-01-21
// VERSION: 0.4.4
// PURPOSE: Arduino library to help formatting for printing.
//     URL: https://github.com/RobTillaart/printHelpers


#include "printHelpers.h"


//  global buffer used by all functions so no static buffer in every function
//  is needed ==> results need to be printed/copied asap
//  not usable in multi-threading environments (use with care)
//
//  24 is a pretty safe minimum
char __printbuffer[PRINTBUFFERSIZE];


////////////////////////////////////////////////////////////
//
//  PRINT 64 BIT
//

//  print64 note
//  buffer size 66 will work for base 2 -36
//  buffer size 34 will work for base 4 -36
//  buffer size 24 will work for base 8 -36
//  buffer size 22 will work for base 10 - 36

char * print64(int64_t value, uint8_t base)
{
  char * buffer = __printbuffer;
  uint8_t i = 0;
  uint8_t j = 0;

  buffer[0] = 0;
  //  small base need bigger buffer
  if ((base < 10) && (PRINTBUFFERSIZE <= 22)) return buffer;
  //  handle special case
  if (value == 0)
  {
    buffer[0] = '0';
    buffer[1] = 0;
    return buffer;
  }

  //  PREFIX NEGATIVE
  //  handle negative values (for all bases for now)
  if ((value < 0) && (base != 16))
  {
    value = -value;
    buffer[0] = '-';
    i++;
    j++;
  }

  //  PREFIX HEX
  if (base == 16)
  {
    buffer[0] = '0';
    buffer[1] = 'x';
    buffer[2] = 0;
    i = 2;
    j = 2;
  }
  //  create one digit per loop
  while (value > 0)
  {
    int64_t temp = value / base;
    uint8_t digit = value - temp * base;
    buffer[i++] = (digit < 10) ? '0' + digit : ('A' - 10) + digit;
    value = temp;
  }
  buffer[i] = 0;
  //  reverse buffer
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
  //  small base need bigger buffer
  if ((base < 10) && (PRINTBUFFERSIZE <= 22)) return buffer;
  //  handle special case
  if (value == 0)
  {
    buffer[0] = '0';
    buffer[1] = 0;
    return buffer;
  }
  //  create one digit per iteration
  while (value > 0)
  {
    uint64_t temp = value / base;
    uint8_t  digit = value - temp * base;
    buffer[i++] = (digit < 10) ? '0' + digit : ('A' - 10) + digit;
    value = temp;
  }
  buffer[i] = 0;
  //  reverse buffer
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
//  SCIENTIFIC NOTATIION
//

//  typical buffer size for 8 byte double is 22 bytes
//  15 bytes mantissa, sign dot E-xxx
//  em = exponentMultiple.
char * scieng(double value, uint8_t decimals, uint8_t em)
{
  char *  buffer   = __printbuffer;
  int     exponent = 0;
  uint8_t pos = 0;
  double  e1 = 10;
  double  e2 = 0.1;

  //  scale to multiples of em.
  for (uint8_t i = 1; i < em; i++)
  {
    e1 *= 10;
    e2 *= 0.1;
  }

  //  Handling these costs 13 bytes RAM
  //  shorten them with N, I, -I ?
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

  //  Handle negative numbers
  if (value < 0.0)
  {
    buffer[pos++] = '-';
    value = -value;
  }

  //  Scale exponent to multiple of em
  //  TODO: can we remove loop to reduce rounding errors
  while (value >= e1)
  {
    value *= e2;
    exponent += em;
  }
  //  TODO: can we remove loop to reduce rounding errors
  while (value < 1 && value != 0.0)
  {
    value *= e1;
    exponent -= em;
  }

  //  Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  //  TODO: can we remove loop to reduce rounding errors?
  //        additional loop that steps per 1000?
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

  //  Split whole part and remainder
  uint32_t d = (uint32_t)value;
  double remainder = value - d;


  //  print whole part
#if defined(ESP32)
  //  ESP32 does not support %ld  or ltoa()
  itoa(d, &buffer[pos], 10);
#else
  sprintf(&buffer[pos], "%ld", d);
#endif
  pos = strlen(buffer);


  //  print remainder part
  if (decimals > 0)
  {
    buffer[pos++] = '.';    //  decimal point
  }

  //  Extract decimals from the remainder one at a time
  //  to prevent missing leading zero's
  while (decimals-- > 0)
  {
    remainder *= 10;
    d = (uint8_t)remainder;
    buffer[pos++] = d + '0';
    remainder -= d;
  }

  //  print exponent
  buffer[pos++] = 'E';
  if (exponent < 0)
  {
    buffer[pos++] = '-';
    exponent = -exponent;
  }
  else buffer[pos++] = '+';

  if (exponent < 10) buffer[pos++] = '0';
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


size_t sci(Stream &str, double value, uint8_t decimals)
{
  return str.print(sci(value, decimals));
}


////////////////////////////////////////////////////////////
//
//  toBytes
//

//  official support to UDA == 1024^12
//  kilo mega giga tera peta exa (1024^6)
//  zetta yotta xona weka vunda uda (1024^12)
//
//  (treda Byte == TDB is the next one and it is 2 char
//  so code wise difficult and as it is seldom used, support stops there.
//
//  To have some support the code uses lowercase for the next 8 levels
//  treda sorta rinta quexa pepta ocha nena minga luma (1024 ^13 ~~ 1024^21)
//
char * toBytes(double value, uint8_t decimals)
{
  char * buffer = __printbuffer;
  //  to enable full range uncomment the following line
  //  char  units[] = " KMGTPEZYXWVUtsrqponml";

  char  units[] = " KMGTPEZYXWVU";
  uint8_t i = 0;    //  i is index of the unit array == powers of 1024.

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

  //  WHOLE PART iv
  int integerPart = value;
  itoa(integerPart, &buffer[0], 10);

  //  DECIMALS
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

  //  UNITS
  if (i <= strlen(units))
  {
    if (i > 0) buffer[pos++] = ' ';
    buffer[pos++] = units[i];
    buffer[pos++] = 'B';
    buffer[pos]   = 0;
  }
  else
  {
    //  no units available
  }
  return buffer;
}


////////////////////////////////////////////////////////////
//
//  HEX
//
//  always leading zero's - no prefix - no separator
char * hex(uint64_t value, uint8_t digits)
{
  uint64_t val = value;
  char * buffer = __printbuffer;
  buffer[digits] = '\0';
  while (digits > 0)
  {
    uint8_t v = val & 0x0F;
    val >>= 4;
    digits--;
    buffer[digits] = (v < 10) ? '0' + v : ('A' - 10) + v;
  }
  return buffer;
}

//  faster than 64 bit.
char * hex(uint32_t value, uint8_t digits)
{
  uint32_t val = value;
  char * buffer = __printbuffer;
  buffer[digits] = '\0';
  while (digits > 0)
  {
    uint8_t v = val & 0x0F;
    val >>= 4;
    digits--;
    buffer[digits] = (v < 10) ? '0' + v : ('A' - 10) + v;
  }
  return buffer;
}

char * hex(uint16_t value, uint8_t digits) { return hex((uint32_t) value, digits); };
char * hex(uint8_t value, uint8_t digits)  { return hex((uint32_t) value, digits); };


////////////////////////////////////////////////////////////
//
//  BIN
//
//  always leading zero's - no prefix - no separator
char * bin(uint64_t value, uint8_t digits)
{
  uint64_t val = value;
  char * buffer = __printbuffer;
  buffer[digits] = '\0';
  while (digits > 0)
  {
    digits--;
    buffer[digits] = '0' + (val & 1);
    val >>= 1;
  }
  return buffer;
}

//  faster than 64 bit.
char * bin(uint32_t value, uint8_t digits)
{
  uint64_t val = value;
  char * buffer = __printbuffer;
  buffer[digits] = '\0';
  while (digits > 0)
  {
    digits--;
    buffer[digits] = '0' + (val & 1);
    val >>= 1;
  }
  return buffer;
}

char * bin(uint16_t value, uint8_t digits) { return bin((uint32_t) value, digits); };
char * bin(uint8_t value, uint8_t digits)  { return bin((uint32_t) value, digits); };


////////////////////////////////////////////////////////////
//
//  toRoman
//
//  extended with 10K units generated with the same but lower case chars.
//  would expect a special char for 5000?
//  need investigation.
char * toRoman(uint32_t value)
{
  char * buffer = __printbuffer;
  uint32_t      val = value;
  uint16_t    n[13] = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
  char roman[13][3] = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };

  buffer[0] = 0;
  int idx = 0;
  if (value == 0)
  {
    strcat(buffer, "N");  //  NULL
    return buffer;
  }

  if (value > 100000000UL)
  {
    strcat(buffer, "OVF");  //  overflow
    return buffer;
  }

  if (val >= 10000UL)
  {
    //  10K units
    while(val >= 10000UL)
    {
      while (val >= (10000UL * n[idx]))
      {
        strcat(buffer, roman[idx]);
        val -= (10000UL * n[idx]);
      };
      idx++;
    }
    //  set chars to lower
    for (uint16_t i = 0; i < strlen(buffer); i++)
    {
      buffer[i] = tolower(buffer[i]);
    }
  }

  //  Official part UPPER case letters
  while(val > 0)
  {
    while (val >= n[idx])
    {
      strcat(buffer, roman[idx]);
      val -= n[idx];
    };
    idx++;
  }

  return buffer;
}


////////////////////////////////////////////////////////////
//
//  Distances
//  Experimental

//  step == 2,4,8,16,32,64,128,256 (default 16)
char * printInch(float inch, uint16_t step)
{
  char * buffer = __printbuffer;
  uint32_t whole = inch;
  uint8_t num = round((inch - whole) * step);
  if (num == step)
  {
    whole++;
    num = 0;
  }
  uint8_t den = step;
  //  optional reduce
  while ((num > 0) && ((num & 1) == 0))
  {
    num >>= 1;
    den >>= 1;
  }

#if defined(ESP32)
  //  ESP32 does not support %ld  or ltoa()
  sprintf(buffer, "%d %d/%d", whole, num, den);
#else
  sprintf(buffer, "%ld %d/%d", whole, num, den);
#endif
  return buffer;
}


char * printFeet(float feet)
{
  char * buffer = __printbuffer;
  uint32_t ft = feet;
  uint8_t inch = round((feet - ft) * 12);
  if (inch == 12)
  {
    ft++;
    inch = 0;
  }
#if defined(ESP32)
  //  ESP32 does not support %ld  or ltoa()
  sprintf(buffer, "%d\"%d\'", ft, inch);
#else
  sprintf(buffer, "%ld\"%d\'", ft, inch);
#endif
  return buffer;
}


////////////////////////////////////////////////////////////
//
//  Comma Separated Integers
//  Experimental
//
//  TODO 
//  - merge if possible 64-32  signed-unsigned
//  - performance (use divmod10?)
//
char * csi(int64_t value)
{
  char * buffer = __printbuffer;
  int index = 0;
  bool neg = (value < 0);
  if (neg)
  {
    value = -value;
  }
  int threeCount = 0;
  while (value > 0)
  {
    buffer[index++] = '0' +  value % 10;
    value /= 10;
    threeCount++;
    if ((threeCount == 3) && (value > 0))
    {
      threeCount = 0;
      buffer[index++] = ',';
    }
  }
  if (neg)
  {
    buffer[index++] = '-';
  }
  buffer[index--] = 0;
  for (int i = 0, j = index; i < j; i++, j--)
  {
    char t = buffer[j];
    buffer[j] = buffer[i];
    buffer[i] = t;
  }
  return buffer;
}

char * csi(int32_t value)
{
  char * buffer = __printbuffer;
  int index = 0;
  bool neg = (value < 0);
  if (neg)
  {
    value = -value;
  }
  int threeCount = 0;
  while (value > 0)
  {
    buffer[index++] = '0' +  value % 10;
    value /= 10;
    threeCount++;
    if ((threeCount == 3) && (value > 0))
    {
      threeCount = 0;
      buffer[index++] = ',';
    }
  }
  if (neg)
  {
    buffer[index++] = '-';
  }
  buffer[index--] = 0;
  for (int i = 0, j = index; i < j; i++, j--)
  {
    char t = buffer[j];
    buffer[j] = buffer[i];
    buffer[i] = t;
  }
  return buffer;
}

char * csi(int16_t value)
{
  return csi((int32_t)value);
}

char * csi(int8_t value)
{
  return csi((int32_t)value);
}


char * csi(uint64_t value)
{
  char * buffer = __printbuffer;
  int index = 0;
  int threeCount = 0;
  while (value > 0)
  {
    buffer[index++] = '0' +  value % 10;
    value /= 10;
    threeCount++;
    if ((threeCount == 3) && (value > 0))
    {
      threeCount = 0;
      buffer[index++] = ',';
    }
  }
  buffer[index--] = 0;
  for (int i = 0, j = index; i < j; i++, j--)
  {
    char t = buffer[j];
    buffer[j] = buffer[i];
    buffer[i] = t;
  }
  return buffer;
}

char * csi(uint32_t value)
{
  char * buffer = __printbuffer;
  int index = 0;
  int threeCount = 0;
  while (value > 0)
  {
    buffer[index++] = '0' +  value % 10;
    value /= 10;
    threeCount++;
    if ((threeCount == 3) && (value > 0))
    {
      threeCount = 0;
      buffer[index++] = ',';
    }
  }
  buffer[index--] = 0;
  for (int i = 0, j = index; i < j; i++, j--)
  {
    char t = buffer[j];
    buffer[j] = buffer[i];
    buffer[i] = t;
  }
  return buffer;
}

char * csi(uint16_t value)
{
  return csi((uint32_t)value);
}


char * csi(uint8_t value)
{
  return csi((uint32_t)value);
}



//  -- END OF FILE --



