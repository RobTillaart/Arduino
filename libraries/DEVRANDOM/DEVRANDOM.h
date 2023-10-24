#pragma once
//
//    FILE: DEVRANDOM.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.2
// PURPOSE: Arduino library for a /dev/random stream - useful for testing
//     URL: https://github.com/RobTillaart/DEVRANDOM


#include "Arduino.h"


#define  DEVRANDOM_LIB_VERSION      (F("0.2.2"))


#define  DEVRANDOM_MODE_RANDOM       0
#define  DEVRANDOM_MODE_DIGITALREAD  1
#define  DEVRANDOM_MODE_ANALOGREAD   2
#define  DEVRANDOM_MODE_MARSAGLIA    3


class DEVRANDOM : public Stream
{
public:
  DEVRANDOM();
  DEVRANDOM(const char * str);
  DEVRANDOM(const uint32_t value);
  DEVRANDOM(const float value);

  int     available();
  int     peek();
  int     read();

  //      keep CI happy as parent class flush is virtual.
  void    flush();

  //      for reseeding, including via print() and println().
  size_t  write(const uint8_t data);
  size_t  write(const uint8_t * buffer, size_t size);

  //      build in random is the default mode.
  void    useRandom();
  void    useDigitalRead(uint8_t pin);
  void    useAnalogRead(uint8_t pin);
  void    useMarsaglia();

  uint8_t getMode();


  //  OBSOLETE
  //  void    useAR(uint8_t pin) { useAnalogRead(pin);  };
  //  void    useHW(uint8_t pin) { useDigitalRead(pin); };
  //  void    useSW()            { useRandom();         };


private:
  uint8_t  _next = 0;
  uint32_t _seed = 0;
  uint8_t  _mode = 0;
  uint8_t  _pin  = 0;

  //  Marsaglia 'constants'
  uint32_t _m_w  = 1;
  uint32_t _m_z  = 2;

  int      _rnd();
  int      _digitalRead();
  int      _analogRead();
  uint32_t _marsaglia();

};


//  -- END OF FILE --

