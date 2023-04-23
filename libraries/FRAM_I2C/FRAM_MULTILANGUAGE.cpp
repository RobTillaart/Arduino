//
//    FILE: FRAM_MULTILANGUAGE.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-04-22
// PURPOSE: Arduino library for I2C FRAM based multi language table
//     URL: https://github.com/RobTillaart/FRAM_I2C
//


#include "FRAM_MULTILANGUAGE.h"   //   https://github.com/RobTillaart/FRAM_I2C


//  CONFIG
#define FML_MAX_LANGUAGES          5
#define FML_MAX_COUNTRY_CODE       3

//  OFFSETS
#define FML_VERSION                0
#define FML_LANGUAGES              10
#define FML_STRINGS                11
#define FML_LENGTH                 12
#define FML_LANGCODE               20
#define FML_TABLES                 40


FRAM_ML::FRAM_ML()
{
}


uint32_t FRAM_ML::begin(FRAM *fram, uint32_t memAddr, uint8_t languages, uint8_t strings, uint8_t maxLength)
{
  _fram         = fram;
  _baseAddr     = memAddr;
  _maxLanguages = languages;
  if (_maxLanguages > FML_MAX_LANGUAGES)
  {
    _maxLanguages = FML_MAX_LANGUAGES;
  }
  _maxStrings = strings;
  _maxLength  = maxLength;

  //  write configuration to FRAM.
  _fram->write8(_baseAddr + FML_VERSION,   _version);
  _fram->write8(_baseAddr + FML_LANGUAGES, _maxLanguages);
  _fram->write8(_baseAddr + FML_STRINGS,   _maxStrings);
  _fram->write8(_baseAddr + FML_LENGTH,    _maxLength);

  setLanguage(0);

  return _baseAddr + _maxLanguages * _maxStrings * _maxLength + FML_TABLES;
}


uint32_t FRAM_ML::begin(FRAM *fram, uint32_t memAddr)
{
  _fram      = fram;
  _baseAddr  = memAddr;

  _maxLanguages = _fram->read8(_baseAddr + FML_LANGUAGES);
  _maxStrings   = _fram->read8(_baseAddr + FML_STRINGS);
  _maxLength    = _fram->read8(_baseAddr + FML_LENGTH);

  setLanguage(0);

  return _baseAddr + _maxLanguages * _maxStrings * _maxLength + FML_TABLES;
}


int FRAM_ML::getMaxLanguage()
{
  return _maxLanguages;
}


int FRAM_ML::getMaxStrings()
{
  return _maxStrings;
}


int FRAM_ML::getMaxLength()
{
  return _maxLength;
}


/////////////////////////////////////////////////////////////////////
//
//
//
int FRAM_ML::setLanguageName(uint8_t index, const char * str)
{
  if (index >= _maxLanguages) return FRAM_ML_INDEX_OUT_OF_RANGE;
  uint8_t len = strlen(str);
  if (len > FML_MAX_COUNTRY_CODE) return FRAM_ML_TEXT_TOO_LONG;
  _fram->write(_baseAddr + FML_LANGCODE + index * (FML_MAX_COUNTRY_CODE + 1), (uint8_t*) str, len);
  //  add separator.
  _fram->write8(_baseAddr + FML_LANGCODE + index * (FML_MAX_COUNTRY_CODE + 1) + len, '\n');
  return FRAM_ML_OK;
}


int FRAM_ML::getLanguageName(uint8_t index, char * str)
{
  if (index >= _maxLanguages) return FRAM_ML_INDEX_OUT_OF_RANGE;
  _fram->readUntil(_baseAddr + FML_LANGCODE + index * (FML_MAX_COUNTRY_CODE + 1), str, (FML_MAX_COUNTRY_CODE + 1), '\n');
  return FRAM_ML_OK;
}


/////////////////////////////////////////////////////////////////////
//
//
//
int FRAM_ML::setLanguage(uint8_t index)
{
  if (index >= _maxLanguages) return FRAM_ML_INDEX_OUT_OF_RANGE;
  _currentLanguage = index;
  //  set language address too.
  _langAddr = _baseAddr + FML_TABLES + _currentLanguage * _maxStrings * _maxLength;
  return FRAM_ML_OK;
}


int FRAM_ML::getLanguage()
{
  return _currentLanguage;
}


/////////////////////////////////////////////////////////////////////
//
//  TEXT TABLES
//
int FRAM_ML::setText(uint8_t index, const char * text)
{
  if (index >= _maxStrings) return FRAM_ML_INDEX_OUT_OF_RANGE;
  uint8_t len = strlen(text);
  if (len >= _maxLength) return FRAM_ML_TEXT_TOO_LONG;

  _fram->write(_langAddr + index * _maxLength, (uint8_t*) text, len);
  //  add separator.
  _fram->write8(_langAddr + index * _maxLength + len, '\n');
  return FRAM_ML_OK;
}


int FRAM_ML::getText(uint8_t index, char * text)
{
  if (index >= _maxStrings) return FRAM_ML_INDEX_OUT_OF_RANGE;
  _fram->readUntil(_langAddr + index * _maxLength, text, _maxLength, '\n');
  return FRAM_ML_OK;
}


//  -- END OF FILE --

