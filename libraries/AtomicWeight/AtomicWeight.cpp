//
//    FILE: AtomicWeight.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-03-09
// VERSION: 0.2.1
// PURPOSE: Arduino library for atomic weights
//     URL: https://github.com/RobTillaart/AtomicWeight


#include "AtomicWeight.h"
#include "elements_uint16.h"


PTOE::PTOE(const uint8_t size)
{
  _size  = size;
  _found = 0;
}


////////////////////////////////////////////////////////////////
//
//  BASIC
//
uint8_t PTOE::size()
{
  return _size;
}


char * PTOE::name(const uint8_t el)
{
  //  catch out of range.
  if (el > _size) return NULL;
  return elements[el].name;
}


uint8_t PTOE::find(const char * abbrev)
{
  //  case insensitive?
  //  caching?
  //  param check?
  //  uint8_t len = strlen(abbrev);
  //  if ((len == 1) || (len == 2))
  //  {
  for (uint8_t i = 0; i < _size; i++)
  {
    if (strcmp(elements[i].name, abbrev) == 0) return i;
  }
  // }
  return 255;
}


uint8_t PTOE::electrons(const uint8_t el)
{
  return el;
}


uint8_t PTOE::neutrons(const uint8_t el)
{
  return round(weight(el)) - el;
}


uint8_t PTOE::protons(const uint8_t el)
{
  return el;
}


////////////////////////////////////////////////////////////////
//
//  WEIGHT
//
float PTOE::weight(const uint8_t el)
{
  if (el > _size) return 0;  //  catch out of range.
  return elements[el].weight * ATOMIC_WEIGHT_FACTOR;
}


float PTOE::weight(const char * formula, const char * abbrev)
{
  p = (char *)formula;
  return _weight('\0', abbrev);
}


float PTOE::massPercentage(const char * formula, const char * abbrev)
{
  float total = weight(formula);
  if (total == 0) return 0;
  p = (char *)formula;
  return 100.0 * _weight('\0', abbrev) / total;
}



////////////////////////////////////////////////////////////////
//
//  CONVERSION
//
float PTOE::moles2grams(const char * formula, float moles)
{
  return moles * weight(formula);
}


float PTOE::grams2moles(const char * formula, float grams)
{
  return grams / weight(formula);
}


////////////////////////////////////////////////////////////////
//
//  SPLIT FORMULA IN ELEMENTS
//
uint8_t PTOE::splitElements(const char * formula)
{
  uint8_t count = 0;
  char elem[3] = { 0, 0, 0 };

  char * p = (char *) formula;
  while (*p != '\0')
  {
    //  SKIP non element info
    if (*p == '(')
    {
      p++;   //  skip '('
      continue;
    }
    if (*p == ')')
    {
      p++;   //  skip ')'
      continue;
    }
    if (isdigit(*p))
    {
      p++;   //  skip digit
      continue;
    }

    //  GET ELEMENT := [ Upper | Upper,lower ]
    elem[0] = 0;
    elem[1] = 0;
    if (! isupper(*p)) return 0;  //  fail
    elem[0] = *p;
    p++;
    if (islower(*p))
    {
      elem[1] = *p;
      p++;
    }
    //  FIND INDEX OF ELEMENT
    int z = find(elem);
    if (z == 255)
    {
      return 0;  //  fail
    }

    //  DO WE HAVE IDENTIFIED IT ALREADY?
    bool found = false;
    for (int i = 0; i < count; i++)
    {
      if (_splitList[i] == z)
      {
        found = true;
      }
    }
    if ((found == false) && (count < ATOMIC_WEIGHT_MAX_SPLIT_LIST))
    {
      _splitList[count] = z;
      count++;
    }
  }

  // //  DEBUG
  // for (int i = 0; i < count; i++)
  // {
  // Serial.print(i);
  // Serial.print('\t');
  // Serial.print(_splitList[i]);
  // Serial.print('\t');
  // Serial.println(name(_splitList[i]));
  // }

  _found = count;
  return count;
}


uint8_t PTOE::element(uint8_t el)
{
  if (el >= _found) return 255;
  return _splitList[el];
}


////////////////////////////////////////////////////////////////
//
//  COUNT
//
uint32_t PTOE::count(const char * formula, const char * el)
{
  p = (char *)formula;
  return _count('\0', el);
}


float PTOE::atomPercentage(const char * formula, const char * el)
{
  float total = count(formula);
  if (total == 0) return 0;
  p = (char *)formula;
  return 100.0 * _count('\0', el) / total;
}


////////////////////////////////////////////////////////////////
//
//  DEBUG
//
float PTOE::weightFactor()
{
  return ATOMIC_WEIGHT_FACTOR;
}


////////////////////////////////////////////////////////////////
//
//  PRIVATE
//
float PTOE::_weight(const char sep, const char * abbrev)
{
  float sum = 0;
  float w   = 0;
  char elem[3] = { 0, 0, 0 };
  uint32_t count = 0;

  while (*p != sep)
  {
    w = 0;
    //  HANDLE GROUP  (...)
    if (*p == '(')
    {
      p++;   //  skip '('
      w = _weight(')', abbrev);
      p++;   //  skip ')'
    }
    else
    {
      //  GET ELEMENT := [ Upper | Upper,lower ]
      elem[1] = 0;
      if (! isupper(*p)) return 0;  //  fail
      elem[0] = *p;
      p++;
      if (islower(*p))
      {
        elem[1] = *p;
        p++;
      }
      //  can be optimized?
      if ((abbrev == NULL) || (strcmp(elem, abbrev) == 0))
      {
        int z = find(elem);
        if (z == 255) return 0;  //  fail
        w = weight(z);
      }
    }

    count = 0;
    //  get optional digits
    while (isdigit(*p))
    {
      count = count * 10 + (*p - '0');
      p++;
    }
    //  correct for no digits
    if (count == 0) count = 1;

    //  DEBUG
    // Serial.println(w);
    // Serial.println(count);
    sum += (w * count);
  }
  return sum;
}


uint32_t PTOE::_count(const char sep, const char * abbrev)
{
  uint32_t sum = 0;
  char elem[3] = { 0, 0, 0 };
  uint32_t count = 0;
  int w = 0;

  while (*p != sep)
  {
    //  HANDLE GROUP  (...)
    if (*p == '(')
    {
      p++;   //  skip '('
      w = _count(')', abbrev);
      p++;   //  skip ')'
    }
    else
    {
      w = 0;
      //  GET ELEMENT := [ Upper | Upper,lower ]
      elem[1] = 0;
      if (! isupper(*p)) return 0;  //  fail
      elem[0] = *p;
      p++;
      if (islower(*p))
      {
        elem[1] = *p;
        p++;
      }
      //  can be optimized
      if ((abbrev == NULL) || (strcmp(elem, abbrev) == 0))
      {
        int z = find(elem);
        if (z == 255) return 0;  //  fail
        w = 1;
      }
    }

    count = 0;
    //  get optional digits
    while (isdigit(*p))
    {
      count = count * 10 + (*p - '0');
      p++;
    }
    //  correct for no digits
    if (count == 0) count = 1;

    //  DEBUG
    // Serial.println(w);
    // Serial.println(count);

    sum += w * count;
  }
  return sum;
}


//  -- END OF FILE --

