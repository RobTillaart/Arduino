#pragma once
//
//    FILE: DS2401.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Library for the DS2401 1-wire unique identification chip.
// VERSION: 0.1.2
//     URL: https://github.com/RobTillaart/DS2401


#include "Arduino.h"
#include "OneWire.h"


#define DS2401_LIB_VERSION            (F("0.1.2"))


class DS2401
{
public:
  explicit DS2401(OneWire * ow)
  {
    _oneWire = ow;
  }

  bool begin()
  {
    //  reset address
    for (int i = 0; i < 8; i++)
    {
      _address[i] = 0x00;
    }

    _oneWire->reset();
    _oneWire->reset_search();
    _oneWire->search(_address);
    //  ds2401 has an family ID of 0x01 but this way 
    //  all one-wire devices can be used as UID.
    return (_address[0] != 0x00) && (_oneWire->crc8(_address, 7) == _address[7]);
  }


  void getUID(uint8_t * buffer)
  {
    memcpy(buffer, _address, 8);
  }


  bool compareUID(uint8_t * buffer)
  {
    return !memcmp(buffer, _address, 8);
  }


  void getUID6(uint8_t * buffer)
  {
    memcpy(buffer, &_address[1], 6);
  }


  bool compareUID6(uint8_t * buffer)
  {
    return !memcmp(buffer, &_address[1], 6);
  }


  void getUID4(uint32_t * buffer)
  {
    memcpy(buffer, &_address[1], 4);
  }


  bool compareUID4(uint32_t * buffer)
  {
    return !memcmp(buffer, &_address[1], 4);
  }


private:
  OneWire * _oneWire;
  uint8_t   _address[8];
};


//  -- END OF FILE --

