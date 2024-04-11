//
//    FILE: currency.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.9
// PURPOSE: Currency library for Arduino
//     URL: https://github.com/RobTillaart/Currency


#include "currency.h"


char * currency(int32_t value, int decimals, char decimalSeparator, char thousandSeparator, char symbol)
{
  static char tmp[16];
  uint8_t index = 0;

  int32_t v = value;
  bool negative = v < 0;
  if (negative) v = -v;

  int pos = -decimals;  //  decimal places

  while ((pos < 1) || (v > 0))
  {
    //  separators
    if ((pos == 0) && (decimals > 0) ) tmp[index++] = decimalSeparator;
    if ((pos > 0)  && (pos % 3 == 0) ) tmp[index++] = thousandSeparator;
    pos++;

    tmp[index++] = (v % 10) + '0';
    v /= 10;
  }
  if (negative) tmp[index++] = '-';
  else          tmp[index++] = ' ';
  tmp[index++] = symbol;
  tmp[index]   = '\0';

  //  reverse string
  for (uint8_t i = 0, j = index - 1; i < index / 2; i++, j--)
  {
    char c = tmp[i];
    tmp[i] = tmp[j];
    tmp[j] = c;
  }
  return tmp;
}


char * currency64(int64_t value, int decimals, char decimalSeparator, char thousandSeparator, char symbol)
{
  static char tmp[32];
  int index = 0;

  int64_t v = value;
  bool negative = v < 0;
  if (negative) v = -v;

  int pos = -decimals;  //  decimal places

  while ((pos < 1) || (v > 0))
  {
    // separators
    if ((pos == 0) && (decimals > 0) ) tmp[index++] = decimalSeparator;
    if ((pos > 0)  && (pos % 3 == 0) ) tmp[index++] = thousandSeparator;
    pos++;

    tmp[index++] = (v % 10) + '0';
    v /= 10;
  }
  if (negative) tmp[index++] = '-';
  else          tmp[index++] = ' ';
  tmp[index++] = symbol;
  tmp[index]   = '\0';

  //  reverse string
  for (uint8_t i = 0, j = index - 1; i < index / 2; i++, j--)
  {
    char c = tmp[i];
    tmp[i] = tmp[j];
    tmp[j] = c;
  }
  return tmp;
}


//
//  DERIVED FUNCTIONS
//
char * bitcoin(int32_t value)   { return currency(value, 6,  '.',  ',',  'B'); }  
char * dollar(int32_t value)    { return currency(value, 2,  '.',  ',',  '$'); }
char * euro(int32_t value)      { return currency(value, 2,  ',',  '.',  'E'); }
char * pound(int32_t value)     { return currency(value, 2,  ',',  '.',  'L'); }
char * roubles(int32_t value)   { return currency(value, 2,  ',',  '.',  'P'); }
char * yen(int32_t value)       { return currency(value, 2,  '.',  ',',  'Y'); }
char * yuan(int32_t value)      { return currency(value, 2,  '.',  ',',  'R'); }

char * bitcoin64(int64_t value) { return currency64(value, 6,  '.',  ',',  'B'); }  
char * dollar64(int64_t value)  { return currency64(value, 2,  '.',  ',',  '$'); }
char * euro64(int64_t value)    { return currency64(value, 2,  ',',  '.',  'E'); }
char * pound64(int64_t value)   { return currency64(value, 2,  ',',  '.',  'L'); }
char * roubles64(int64_t value) { return currency64(value, 2,  ',',  '.',  'P'); }
char * yen64(int64_t value)     { return currency64(value, 2,  '.',  ',',  'Y'); }
char * yuan64(int64_t value)    { return currency64(value, 2,  '.',  ',',  'R'); }

char * bitcoinf(double value)   { return currency64(round(value * 1000000), 6,  '.',  ',',  'B'); }  
char * dollarf(double value)    { return currency64(round(value * 100), 2,  '.',  ',',  '$'); }
char * eurof(double value)      { return currency64(round(value * 100), 2,  ',',  '.',  'E'); }
char * poundf(double value)     { return currency64(round(value * 100), 2,  ',',  '.',  'L'); }
char * roublesf(double value)   { return currency64(round(value * 100), 2,  ',',  '.',  'P'); }
char * yenf(double value)       { return currency64(round(value * 100), 2,  '.',  ',',  'Y'); }
char * yuanf(double value)      { return currency64(round(value * 100), 2,  '.',  ',',  'R'); }


//  -- END OF FILE --
