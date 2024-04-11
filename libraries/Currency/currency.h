#pragma once
//
//    FILE: currency.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.9
// PURPOSE: Currency library for Arduino
//     URL: https://github.com/RobTillaart/Currency


#include "Arduino.h"


#define CURRENCY_VERSION                        (F("0.1.9"))


//  TODO 
//  optimize this 99% same code currency - currency64  
//  print to string and "merge" with formatters?
//  
//  ALT-0165 = ¥
//  ALT-0128 = €
//  U+20BF   = Bitcoin


char * currency(int32_t value, int decimals, char decimalSeparator, char thousandSeparator, char symbol);

char * currency64(int64_t value, int decimals, char decimalSeparator, char thousandSeparator, char symbol);

//
//  DERIVED FUNCTIONS
//
char * bitcoin(int32_t value);
char * dollar(int32_t value);
char * euro(int32_t value);
char * pound(int32_t value);
char * roubles(int32_t value);
char * yen(int32_t value);
char * yuan(int32_t value);

char * bitcoin64(int64_t value);
char * dollar64(int64_t value);
char * euro64(int64_t value);
char * pound64(int64_t value);
char * roubles64(int64_t value);
char * yen64(int64_t value);
char * yuan64(int64_t value);

char * bitcoinf(double value);
char * dollarf(double value);
char * eurof(double value);
char * poundf(double value);
char * roublesf(double value);
char * yenf(double value);
char * yuanf(double value);


//  -- END OF FILE --

