//
//    FILE: printHelpers.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2018-01-21
// VERSION: 0.5.0
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
  if ((base < 10) && (PRINTBUFFERSIZE <= 66))
  {
    buffer[0] = 'E';  // Error
    buffer[1] = 0;
    return buffer;
  }
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
  if ((base < 10) && (PRINTBUFFERSIZE <= 66))
  {
    buffer[0] = 'E';  // Error
    buffer[1] = 0;
    return buffer;
  }
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
//  Scientific + Engineering notation
//
//  typical buffer size for 8 byte double is 22 bytes (max 15 decimals)
//  15 bytes mantissa, sign dot E-xxx
//  em = exponentMultiple == step size exponent.
char * scieng(double value, uint8_t decimals, uint8_t em)
{
  char *  buffer   = __printbuffer;
  int     exponent = 0;
  uint8_t pos = 0;
  double  e1 = 10;     //  exponent step > 1
  double  e2 = 0.1;    //  exponent step < 1

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
  //  loop can be removed by using pow and log however
  //  in small tests it was not faster or more accurate
  while (value >= e1)
  {
    value *= e2;
    exponent += em;
  }
  while (value < 1 && value != 0.0)
  {
    value *= e1;
    exponent -= em;
  }

  //  Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  //  TODO: can optimize loop to reduce rounding errors?
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
//  toBytes()
//
//  official support to UDA == 1024^12
//  kilo mega giga tera peta exa (1024^6)
//  zetta yotta xona weka vunda uda (1024^12)
//
//  (treda Byte == TDB is the next one and it is 2 char
//  so code wise difficult and as it is seldom used, support stops there.
//
//  To have some support the code uses lowercase for the next 8 levels
//  treda sorta rinta quexa pepta ocha nena minga luma
//  (1024 ^13 .... 1024 ^21 (~10^63)
//
char * toBytes(double value, uint8_t decimals)
{
  char * buffer = __printbuffer;
  //  to enable full range uncomment the following line
  //  char  units[] = " KMGTPEZYXWVUtsrqponml";

  char  units[] = " KMGTPEZYXWVU";
  uint8_t i = 0;    //  i is index of the unit array == powers of 1024.

  if (isnan(value))
  {
    strcpy(buffer, "nan");
    return buffer;
  }
  if (isinf(value))
  {
    strcpy(buffer, "inf");
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
//  hex()
//
//  always leading zero's - no prefix - no separators
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
//  always leading zero's - no prefix - no separators
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
//  toRoman()
//
//  value should be in range 1..9999
//  values 10K-100M are experimental in lower case (see readme.md)
char * toRoman(int32_t value)
{
  char * buffer     = __printbuffer;
  int32_t       val = value;
  uint16_t    n[13] = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
  char roman[13][3] = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };

  buffer[0] = 0;
  int idx = 0;
  if (val == 0)
  {
    strcat(buffer, "N");  //  NULL
    return buffer;
  }
  //  handle negative values
  if (val < 0)
  {
    strcat(buffer, "-");
    val = -val;
  }
  if (val > 100000000L)
  {
    strcat(buffer, "OVF");  //  overflow
    return buffer;
  }

  if (val >= 10000L)
  {
    //  10K units
    while(val >= 10000L)
    {
      while (val >= (10000L * n[idx]))
      {
        strcat(buffer, roman[idx]);
        val -= (10000L * n[idx]);
      };
      idx++;
    }
    //  set chars to lower
    for (uint16_t i = 0; i < strlen(buffer); i++)
    {
      buffer[i] = tolower(buffer[i]);
    }
  }
  //  reset index
  idx = 0;
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
//
//  step == 2,4,8,16,32,64,128,256 (default 16)
char * printInch(float inch, uint16_t step)
{
  char * buffer = __printbuffer;
  if (inch < 0)
  {
    //  cannot handle negative numbers.
    strcpy(buffer, "E-NEG");
    return buffer;
  }
  uint32_t whole = inch;
  uint8_t num = round((inch - whole) * step);
  if (num == step)
  {
    whole++;
    num = 0;
  }
  uint8_t den = step;
  //  reduce factors 2
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
  if (feet < 0)
  {
    //  cannot handle negative numbers.
    strcpy(buffer, "E-NEG");
    return buffer;
  }
  uint32_t ft = feet;
  uint8_t inch = round((feet - ft) * 12);
  if (inch == 12)
  {
    ft++;
    inch = 0;
  }
#if defined(ESP32)
  //  ESP32 does not support %ld  or ltoa()
  sprintf(buffer, "%d\'%d\"", ft, inch);
#else
  sprintf(buffer, "%ld\'%d\"", ft, inch);
#endif
  return buffer;
}


////////////////////////////////////////////////////////////
//
//  Comma Separated Integers
//  Experimental
//
//  - merge if possible 64-32  signed-unsigned
//  - performance (use divmod10?)
//
char * csi(int64_t value, char separator)
{
  char * buffer = __printbuffer;
  int64_t val = value;
  int index = 0;
  bool negative = (val < 0);
  if (negative)
  {
    val = -val;
  }
  int threeCount = 0;
  while (val > 0)
  {
    buffer[index++] = '0' +  val % 10;
    val /= 10;
    threeCount++;
    if ((threeCount == 3) && (val > 0))
    {
      threeCount = 0;
      buffer[index++] = separator;
    }
  }
  if (negative)
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

char * csi(int32_t value, char separator)
{
  int32_t val = value;
  char * buffer = __printbuffer;
  int index = 0;
  bool negative = (val < 0);
  if (negative)
  {
    val = -val;
  }
  int threeCount = 0;
  while (val > 0)
  {
    buffer[index++] = '0' +  val % 10;
    val /= 10;
    threeCount++;
    if ((threeCount == 3) && (val > 0))
    {
      threeCount = 0;
      buffer[index++] = separator;
    }
  }
  if (negative)
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

char * csi(int16_t value, char separator)
{
  return csi((int32_t)value, separator);
}

char * csi(int8_t value, char separator)
{
  return csi((int32_t)value, separator);
}


char * csi(uint64_t value, char separator)
{
  char * buffer = __printbuffer;
  uint64_t val = value;
  int index = 0;
  int threeCount = 0;
  while (val > 0)
  {
    buffer[index++] = '0' +  val % 10;
    val /= 10;
    threeCount++;
    if ((threeCount == 3) && (val > 0))
    {
      threeCount = 0;
      buffer[index++] = separator;
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

char * csi(uint32_t value, char separator)
{
  char * buffer = __printbuffer;
  uint64_t val = value;
  int index = 0;
  int threeCount = 0;
  while (val > 0)
  {
    buffer[index++] = '0' +  val % 10;
    val /= 10;
    threeCount++;
    if ((threeCount == 3) && (val > 0))
    {
      threeCount = 0;
      buffer[index++] = separator;
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

char * csi(uint16_t value, char separator)
{
  return csi((uint32_t)value, separator);
}

char * csi(uint8_t value, char separator)
{
  return csi((uint32_t)value, separator);
}


////////////////////////////////////////////////////////////
//
//  Fraction
//  Experimental
//  Based upon Fraction library -> fractionize()
//
char * fraction(double value)
{
  static char buffer[20];
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
  bool negative = false;
  if (value < 0)
  {
    negative = true;
    value = -value;
  }

  float whole = 0;
  if (value > 1)
  {
    whole = (uint32_t)value;
    value -= whole;
  }

  //  find nearest fraction
  float Precision = 0.000001;

  //  low = (0,1), high = (1,1)
  int32_t lowN = 0;
  int32_t lowD = 1;
  int32_t highN = 1;
  int32_t highD = 1;

  //  max 100 iterations
  for (int i = 0; i < 100; ++i)
  {
    float testLow = lowD * value - lowN;
    float testHigh = highN - highD * value;
    if (testHigh < Precision * highD)
      break;  //  high is answer

    if (testLow < Precision * lowD)
    { //  low is answer
      highD = lowD;
      highN = lowN;
      break;
    }
    if (i & 1)
    { //  odd step: add multiple of low to high
      float test = testHigh / testLow;
      int32_t count = (int32_t)test;    //  "N"
      int32_t n = (count + 1) * lowN + highN;
      int32_t d = (count + 1) * lowD + highD;
      if ((n > 0x8000) || (d > 0x10000))   //   0x8000 0x10000
        break;
      highN = n - lowN;
      highD = d - lowD;
      lowN = n;
      lowD = d;
    }
    else
    { //  even step: add multiple of high to low
      float test = testLow / testHigh;
      int32_t count = (int32_t)test;     //  "N"
      int32_t n = lowN + (count + 1) * highN;
      int32_t d = lowD + (count + 1) * highD;
      if ((n > 0x10000) || (d > 0x10000))   //   0x10000 0x10000
        break;
      lowN = n - highN;
      lowD = d - highD;
      highN = n;
      highD = d;
    }
  }

  //  produce the string
  if (whole > 0) highN += whole * highD;
  if (negative)
  {
    #if defined(ESP32)
    //  ESP32 does not support %ld  or ltoa()
    sprintf(buffer, "-%d/%d", highN, highD);
    #else
    sprintf(buffer, "-%ld/%ld", highN, highD);
    #endif
  }
  else
  {
    #if defined(ESP32)
    //  ESP32 does not support %ld  or ltoa()
    sprintf(buffer, "%d/%d", highN, highD);
    #else
    sprintf(buffer, "%ld/%ld", highN, highD);
    #endif
  }
  return buffer;
}


char * fraction(double value, uint32_t denominator)
{
  static char buffer[20];
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
  bool negative = false;
  if (value < 0)
  {
    negative = true;
    value = -value;
  }

  float whole = 0;
  if (value > 1)
  {
    whole = (uint32_t)value;
    value -= whole;
  }

  uint32_t numerator = round(value * denominator);
  //  find GCD
  uint32_t a = numerator;
  uint32_t b = denominator;
  while ( a != 0 )
  {
    uint32_t c = a;
    a = b % a;
    b = c;
  }
  //  simplify
  denominator /= b;
  numerator /= b;

  //  produce the string
  if (whole > 0)
  {
    numerator += whole * denominator;
  }
  if (negative)
  {
    #if defined(ESP32)
    //  ESP32 does not support %ld  or ltoa()
    sprintf(buffer, "-%d/%d", numerator, denominator);
    #else
    sprintf(buffer, "-%ld/%ld", numerator, denominator);
    #endif
  }
  else
  {
    #if defined(ESP32)
    //  ESP32 does not support %ld  or ltoa()
    sprintf(buffer, "%d/%d", numerator, denominator);
    #else
    sprintf(buffer, "%ld/%ld", numerator, denominator);
    #endif
  }
  return buffer;
}


//  -- END OF FILE --

