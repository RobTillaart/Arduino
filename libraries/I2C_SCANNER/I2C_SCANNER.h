#pragma once
//
//    FILE: I2C_SCANNER.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2022-08-29
// PURPOSE: I2C scanner class
//

#include "Arduino.h"
#include "Wire.h"

#define I2C_SCANNER_LIB_VERSION        (F("0.1.0"))


class I2C_SCANNER
{
  public:
  
  I2C_SCANNER(TwoWire *wire = &Wire);
  
#if defined (ESP8266) || defined(ESP32)
  bool    begin(int sda, int scl);
#endif
  bool    begin();

  bool    ping(uint8_t address);

  bool    setClock(uint32_t clockFrequency = 100000UL);



  private:
    uint8_t   _devices[16];  //  cache ?
    TwoWire*  _wire;

};


/*
 * ideas 
 *
- set Wire
- detect Wirecount

- set output stream

- set speed, re
- 

*/

// -- END OF FILE --

