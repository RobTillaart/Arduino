#pragma once
//
//    FILE: MAX31850.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.4
//    DATE: 2021-06-03
// PURPOSE: Arduino library for the MAX31850 thermocouple temperature sensor.
//     URL: https://github.com/RobTillaart/MAX31850


#define MAX31850_LIB_VERSION     (F("0.1.4"))

#include "Arduino.h"
#include "OneWire.h"


//  ERROR CODES
#define MAX31850_OK                   0
#define MAX31850_ERR_SHORT_OPEN       1
#define MAX31850_ERR_SHORT_GND        2
#define MAX31850_ERR_SHORT_VDD        4



typedef uint8_t DeviceAddress[8];
typedef uint8_t ScratchPad[9];


class MAX31850
{
public:
  explicit  MAX31850(OneWire * oneWire);
  bool      begin(uint8_t retries = 3);
  bool      getAddress(uint8_t * buffer);

  void      requestTemperatures(void);
  bool      isConversionComplete(void);

  //  call read to get new measurement.
  float     read(void);
  //        Call read first!!
  float     getTempTC(void);
  float     getTempInternal(void);

  uint8_t   getErrorCode();
  //  TODO
  uint8_t   getAddressPins();

  //  type is a char from  E J K N R S T  (lowercase will be converted)
  bool      setTypeTC(char typeTC = 'K');  //  K is most used
  char      getTypeTC();


protected:
  void      readScratchPad(uint8_t *, uint8_t);
  uint8_t   _deviceAddress[8];
  OneWire*  _oneWire;
  bool      _addresFound;
  char      _typeTC;

  float     _TCTemp;
  float     _internalTemp;
  uint8_t   _errorBits;
  bool      _failFlag;
  uint8_t   _addrBits;
};


class MAX31851 : public MAX31850
{
public:
  MAX31851(OneWire * onewire);
};


//  -- END OF FILE --

