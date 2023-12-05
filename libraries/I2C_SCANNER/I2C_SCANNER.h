#pragma once
//
//    FILE: I2C_SCANNER.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
//    DATE: 2022-08-29
// PURPOSE: Arduino class to implement an I2C scanner.


#include "Arduino.h"
#include "Wire.h"

#define I2C_SCANNER_LIB_VERSION        (F("0.3.0"))


class I2C_SCANNER
{
public:

  I2C_SCANNER(TwoWire *wire = &Wire);

  //  CONFIGURATION
  bool     begin();

  //  I2C PORT
  uint8_t  getWirePortCount();
  //  0 == Wire, 1 = Wire1 ... 5 = Wire5 (if supported)
  //  to be used for iteration over the I2C interfaces.
  bool     setWire(uint8_t n = 0);
  bool     setWire(TwoWire *wire = &Wire);
  TwoWire* getWire();

  //  valid methods 0 and 1.
  int      softwareReset(uint8_t method = 0);

  //  TIMING
  bool     setClock(uint32_t clockFrequency = 100000UL);
#if defined(ESP32)
  uint32_t getClock();
#endif

  //  SCANNING FUNCTIONS
  uint16_t ping(uint8_t address, uint16_t count = 1);
  int      diag(uint8_t address);
  int32_t  pingTime(uint8_t address);
  uint8_t  count(uint8_t start = 0, uint8_t end = 127);


  //  EXPERIMENTAL.
  //  not all platforms support this function.
  //  patch .cpp file to get this working for your platform.
  bool     setWireTimeout(uint32_t timeOut);
  uint32_t getWireTimeout();


private:
  int      _init();
  int      _wirePortCount;
  TwoWire* _wire;

  uint32_t _timeout = 0;
};


//  -- END OF FILE --

