#pragma once
//
//    FILE: I2C_SCANNER.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
//    DATE: 2022-08-29
// PURPOSE: I2C scanner class
//

#include "Arduino.h"
#include "Wire.h"

#define I2C_SCANNER_LIB_VERSION        (F("0.1.2"))


class I2C_SCANNER
{
public:
  
  I2C_SCANNER(TwoWire *wire = &Wire);

  //  CONFIGURATION
  bool     begin();
#if defined (ESP8266) || defined(ESP32)
  bool     begin(int sda, int scl);
#endif

  //  I2C PORT
  uint8_t  getWirePortCount();
  bool     setWire(TwoWire *wire = &Wire);
  //  0 == Wire, 1 = Wire1 etc. easy for iteration.
  bool     setWire(uint8_t n = 0);
  TwoWire* getWire();

  //  valid methods 0 and 1.
  int      softwareReset(uint8_t method = 0);

  //  TIMING
  bool     setClock(uint32_t clockFrequency = 100000UL);
#if defined(ESP32)
  uint32_t getClock();
#endif


  //  SCANNING FUNCTIONS
  bool     ping(uint8_t address);
  int      diag(uint8_t address);
  int32_t  pingTime(uint8_t address);
  uint8_t  count(uint8_t start = 0, uint8_t end = 127);

private:
  int      _init();
  int      _wirePortCount;
  TwoWire* _wire;
};


// -- END OF FILE --

