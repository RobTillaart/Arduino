#pragma once
//
//    FILE: FRAM_MULTILANGUAGE.h
//  AUTHOR: Rob Tillaart
//    DATE: 2023-04-22
// PURPOSE: Arduino library for I2C FRAM based multi language table
//     URL: https://github.com/RobTillaart/FRAM_I2C


#include "FRAM.h"   //   https://github.com/RobTillaart/FRAM_I2C


//  ERROR CODES
#define FRAM_ML_OK                     0
#define FRAM_ML_INDEX_OUT_OF_RANGE     -10
#define FRAM_ML_TEXT_TOO_LONG          -20


class FRAM_ML
{
public:


  //////////////////////////////////////////////////////////////////
  //
  //  CONSTRUCTOR
  //
  FRAM_ML();


  //  fram = pointer to FRAM object
  //  memAddr = start address of the multi-language table starts
  //  languages = number of language tables
  //  strings = number of strings in lookup table
  //  maxLength = length of largest string.   (first design is not memory efficient).
  //  returns uint32_t == first free (next) FRAM location.
  //  to be used when creating an FRAM language table
  uint32_t  begin(FRAM *fram, uint32_t memAddr, uint8_t languages, uint8_t strings, uint8_t maxLength);
  
  //  or fetch parameters from FRAM. (read mode)
  uint32_t  begin(FRAM *fram, uint32_t memAddr);


  //  get configuration.
  int       getMaxLanguage();
  int       getMaxStrings();
  int       getMaxLength();


  //  index = 0..n
  //  language token == max 3 chars e.g. "IRL", "EN", "FR", "P"
  //  https://www.nationsonline.org/oneworld/country_code_list.htm
  int       setLanguageName(uint8_t index, const char * str);
  int       getLanguageName(uint8_t index, char * str);


  //  set the current language to use.
  int       setLanguage(uint8_t index);
  int       getLanguage();
  int       setText(uint8_t index, const char * text);
  int       getText(uint8_t index, char * text);


private:
  //   version of memory layout
  uint8_t  _version   = 1;

  uint8_t  _maxLanguages = 0;
  uint8_t  _maxStrings   = 0;
  uint8_t  _maxLength    = 0;
  uint8_t  _currentLanguage = 0;
  uint32_t _baseAddr     = 0;
  uint32_t _langAddr     = 0;
  FRAM *   _fram;
};


//  -- END OF FILE --

