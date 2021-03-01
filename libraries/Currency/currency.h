#pragma once

//
//    FILE: currency.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Currency library for Arduino
//     URL: https://github.com/RobTillaart/Currency

//  HISTORY
//  0.1.0   2021-02-27  initial version


#include "Arduino.h"


#define CURRENCY_VERSION        (F("0.1.0"))


// TODO 
// optimize this 99% same code currency - currency64  
// print to string and "merge" with formatters?
//
// ALT-0165 = ¥
// ALT-0128 = €
// U+20BF   = Bitcoin


char * currency(int32_t value, int decimals, char dsep, char tsep, char sym)
{
  static char tmp[16];
  int idx = 0;

  int32_t v = value;
  bool neg = v < 0;
  if (neg) v = -v;

  int p = -decimals; // decimal places

  while ((p < 1) || ( v > 0))
  {
    // separators
    if ((p == 0) && (decimals > 0) ) tmp[idx++] = dsep;
    if ((p > 0) && (p % 3 == 0) && (v > 0)) tmp[idx++] = tsep;

    int d = (v % 10) + '0';
    v /= 10;
    tmp[idx++] = d;
    p++;
  }
  if (neg) tmp[idx++] = '-';
  else     tmp[idx++] = ' ';
  tmp[idx++] = sym;
  tmp[idx] = 0;

  // reverse string
  int len = strlen(tmp);
  for (int i = 0; i < len / 2; i++)
  {
    char c = tmp[i];
    tmp[i] = tmp[len - i - 1];
    tmp[len - i - 1] = c;
  }
  return tmp;
}


char * currency64(int64_t value, int decimals, char dsep, char tsep, char sym)
{
  static char tmp[32];
  int idx = 0;

  int64_t v = value;
  bool neg = v < 0;
  if (neg) v = -v;

  int p = -decimals; // decimal places

  while ((p < 1) || ( v > 0))
  {
    // separators
    if ((p == 0) && (decimals > 0) ) tmp[idx++] = dsep;
    if ((p > 0) && (p % 3 == 0) && (v > 0)) tmp[idx++] = tsep;

    int d = (v % 10) + '0';
    v /= 10;
    tmp[idx++] = d;
    p++;
  }
  if (neg) tmp[idx++] = '-';
  else     tmp[idx++] = ' ';
  tmp[idx++] = sym;
  tmp[idx] = 0;

  // reverse string
  int len = strlen(tmp);
  for (int i = 0; i < len / 2; i++)
  {
    char c = tmp[i];
    tmp[i] = tmp[len - i - 1];
    tmp[len - i - 1] = c;
  }
  return tmp;
}


//
//  DERIVED FUNCTIONS
//
char * bitcoin(int32_t value)   { return currency(value, 6,  '.',  ',',  'B'); }  
char * dollar(int32_t value)    { return currency(value, 2,  '.',  ',',  '$'); }
char * euro(int32_t value)      { return currency(value, 2,  ',',  '.',  'E'); }
char * roebel(int32_t value)    { return currency(value, 2,  ',',  '.',  'P'); }
char * yen(int32_t value)       { return currency(value, 2,  '.',  ',',  'Y'); }
char * yuan(int32_t value)      { return currency(value, 2,  '.',  ',',  'R'); }

char * bitcoin64(int64_t value) { return currency64(value, 6,  '.',  ',',  'B'); }  
char * dollar64(int64_t value)  { return currency64(value, 2,  '.',  ',',  '$'); }
char * euro64(int64_t value)    { return currency64(value, 2,  ',',  '.',  'E'); }
char * roebel64(int64_t value)  { return currency64(value, 2,  ',',  '.',  'P'); }
char * yen64(int64_t value)     { return currency64(value, 2,  '.',  ',',  'Y'); }
char * yuan64(int64_t value)    { return currency64(value, 2,  '.',  ',',  'R'); }

char * bitcoinf(double value)   { return currency64(round(value * 1000000), 6,  '.',  ',',  'B'); }  
char * dollarf(double value)    { return currency64(round(value * 100), 2,  '.',  ',',  '$'); }
char * eurof(double value)      { return currency64(round(value * 100), 2,  ',',  '.',  'E'); }
char * roebelf(double value)    { return currency64(round(value * 100), 2,  ',',  '.',  'P'); }
char * yenf(double value)       { return currency64(round(value * 100), 2,  '.',  ',',  'Y'); }
char * yuanf(double value)      { return currency64(round(value * 100), 2,  '.',  ',',  'R'); }


// -- END OF FILE --
