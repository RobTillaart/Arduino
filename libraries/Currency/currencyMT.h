#pragma once
//
//    FILE: currencyMT.h
//  AUTHOR: Rob Tillaart
//    DATE: 2026-07-23
// VERSION: See currency.h
// PURPOSE: Arduino library to help formatting currency for printing.
//     URL: https://github.com/RobTillaart/currency

//
//  EXPERIMENTAL  WORK IN PROGRESS
//

//  Class implementations of the currency.h functions.
//  code is similar, except for symbol which is a TLA. (BREAKING)
//  These should be thread safe.
//  To be verified.

//  support add sub mul and div and ratio?


#include "Arduino.h"


#ifndef CURRENCY_LIB_VERSION
#define CURRENCY_LIB_VERSION  (F("0.2.1"))
#endif


class currency
{
  protected:
    char buffer[16];

  public:
    currency(int32_t value, int decimals, char decimalSeparator, char thousandSeparator, const char * symbol )
    {
      uint8_t index = 0;

      int32_t v = value;
      bool negative = v < 0;
      if (negative) v = -v;

      int pos = -decimals;  //  decimal places

      while ((pos < 1) || (v > 0))
      {
        //  separators
        if ((pos == 0) && (decimals > 0) ) buffer[index++] = decimalSeparator;
        if ((pos > 0)  && (pos % 3 == 0) ) buffer[index++] = thousandSeparator;
        pos++;

        buffer[index++] = (v % 10) + '0';
        v /= 10;
      }
      if (negative) buffer[index++] = '-';
      else          buffer[index++] = ' ';

      //  reverse numeric part
      for (uint8_t i = 0, j = index - 1; i < index / 2; i++, j--)
      {
        char c = buffer[i];
        buffer[i] = buffer[j];
        buffer[j] = c;
      }
      buffer[index++] = ' ';
      buffer[index++] = symbol[0];
      buffer[index++] = symbol[1];
      buffer[index++] = symbol[2];
      buffer[index]   = '\0';
    }

    //  implicit cast
    inline operator char *()  __attribute__((always_inline)) {
      return buffer;
    }

    //  see issue #32, alternative option.
    //  inline char * c_str() { return buffer; }
};


class currency64
{
  protected:
    char buffer[32];

  public:
    currency64(int64_t value, int decimals, char decimalSeparator, char thousandSeparator, const char * symbol )
    {
      int index = 0;

      int64_t v = value;
      bool negative = v < 0;
      if (negative) v = -v;

      int pos = -decimals;  //  decimal places

      while ((pos < 1) || (v > 0))
      {
        //  separators
        if ((pos == 0) && (decimals > 0) ) buffer[index++] = decimalSeparator;
        if ((pos > 0)  && (pos % 3 == 0) ) buffer[index++] = thousandSeparator;
        pos++;

        buffer[index++] = (v % 10) + '0';
        v /= 10;
      }
      if (negative) buffer[index++] = '-';
      else          buffer[index++] = ' ';

      //  reverse numeric part
      for (uint8_t i = 0, j = index - 1; i < index / 2; i++, j--)
      {
        char c = buffer[i];
        buffer[i] = buffer[j];
        buffer[j] = c;
      }
      buffer[index++] = ' ';
      buffer[index++] = symbol[0];
      buffer[index++] = symbol[1];
      buffer[index++] = symbol[2];
      buffer[index]   = '\0';
    }

    //  implicit cast
    inline operator char *()  __attribute__((always_inline)) {
      return buffer;
    }

    //  see issue #32, alternative option.
    //  inline char * c_str() { return buffer; }
};


//////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//
//  TODO test, other derived, 64 bit, ...
//  should the separator parameters be removed? always same?
//  nr of decimals can be more as precission might be needed?
//
class EUR : public currency
{
  public:
    EUR(int32_t value, int decimals = 2, char decimalSeparator = '.', char thousandSeparator = ',') 
      : currency(value, decimals, decimalSeparator, thousandSeparator, "EUR")
    {
    }

    inline operator char *() __attribute__((always_inline)) {
      return buffer;
    }
};


//  -- END OF FILE --


