//
//    FILE: currency.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
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


//
//  DERIVED FUNCTIONS
//
char * bitcoin(int32_t value)   { return currency(value, 6,  '.',  ',',  'B'); }
char * dollar(int32_t value)    { return currency(value, 2,  '.',  ',',  '$'); }
char * euro(int32_t value)      { return currency(value, 2,  ',',  '.',  'E'); }
char * pound(int32_t value)     { return currency(value, 2,  ',',  '.',  'P'); }
char * roubles(int32_t value)   { return currency(value, 2,  ',',  '.',  'R'); }
char * yen(int32_t value)       { return currency(value, 2,  '.',  ',',  'Y'); }
char * yuan(int32_t value)      { return currency(value, 2,  '.',  ',',  'Y'); }

char * bitcoin64(int64_t value) { return currency64(value, 6,  '.',  ',',  'B'); }
char * dollar64(int64_t value)  { return currency64(value, 2,  '.',  ',',  '$'); }
char * euro64(int64_t value)    { return currency64(value, 2,  ',',  '.',  'E'); }
char * pound64(int64_t value)   { return currency64(value, 2,  ',',  '.',  'P'); }
char * roubles64(int64_t value) { return currency64(value, 2,  ',',  '.',  'R'); }
char * yen64(int64_t value)     { return currency64(value, 2,  '.',  ',',  'Y'); }
char * yuan64(int64_t value)    { return currency64(value, 2,  '.',  ',',  'Y'); }

//  deprecated
//  char * bitcoinf(double value)   { return currency64(round(value * 1000000LL), 6,  '.',  ',',  'B'); }
//  char * dollarf(double value)    { return currency64(round(value * 100LL), 2,  '.',  ',',  '$'); }
//  char * eurof(double value)      { return currency64(round(value * 100LL), 2,  ',',  '.',  'E'); }
//  char * poundf(double value)     { return currency64(round(value * 100LL), 2,  ',',  '.',  'P'); }
//  char * roublesf(double value)   { return currency64(round(value * 100LL), 2,  ',',  '.',  'R'); }
//  char * yenf(double value)       { return currency64(round(value * 100LL), 2,  '.',  ',',  'Y'); }
//  char * yuanf(double value)      { return currency64(round(value * 100LL), 2,  '.',  ',',  'Y'); }


//
//  TLA - Three Letter Acronyms
//
char * BTC(int32_t value)       { return currency(value, 6,  '.',  ',',  'B'); }
char * USD(int32_t value)       { return currency(value, 2,  '.',  ',',  '$'); }
char * EUR(int32_t value)       { return currency(value, 2,  ',',  '.',  'E'); }
char * GBP(int32_t value)       { return currency(value, 2,  ',',  '.',  'P'); }
char * RUB(int32_t value)       { return currency(value, 2,  ',',  '.',  'R'); }
char * JPY(int32_t value)       { return currency(value, 2,  '.',  ',',  'Y'); }
char * CNY(int32_t value)       { return currency(value, 2,  '.',  ',',  'Y'); }

char * BTC64(int64_t value)       { return currency64(value, 6,  '.',  ',',  'B'); }
char * USD64(int64_t value)       { return currency64(value, 2,  '.',  ',',  '$'); }
char * EUR64(int64_t value)       { return currency64(value, 2,  ',',  '.',  'E'); }
char * GBP64(int64_t value)       { return currency64(value, 2,  ',',  '.',  'P'); }
char * RUB64(int64_t value)       { return currency64(value, 2,  ',',  '.',  'R'); }
char * JPY64(int64_t value)       { return currency64(value, 2,  '.',  ',',  'Y'); }
char * CNY64(int64_t value)       { return currency64(value, 2,  '.',  ',',  'Y'); }


//  -- END OF FILE --
