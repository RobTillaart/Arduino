#pragma once
//
//    FILE: AM232X.h
//  AUTHOR: Rob Tillaart
// PURPOSE: AM232X library for Arduino
// VERSION: 0.3.1
// HISTORY: See AM232X.cpp
//     URL: https://github.com/RobTillaart/AM232X
//

//  Bottom view
//       +---+
//  VDD  |o  |
//  SDA  |o  |
//  GND  |o  |
//  SCL  |o  |
//       +---+


#include "Arduino.h"
#include "Wire.h"


#define AM232X_LIB_VERSION              (F("0.3.1"))



#define AM232X_OK                        0
#define AM232X_ERROR_UNKNOWN            -10
#define AM232X_ERROR_CONNECT            -11
#define AM232X_ERROR_FUNCTION           -12
#define AM232X_ERROR_ADDRESS            -13
#define AM232X_ERROR_REGISTER           -14
#define AM232X_ERROR_CRC_1              -15
#define AM232X_ERROR_CRC_2              -16
#define AM232X_ERROR_WRITE_DISABLED     -17
#define AM232X_ERROR_WRITE_COUNT        -18
#define AM232X_MISSING_BYTES            -19


/*
   from datasheet
   0x80: not support function code
   0x81: Read an illegal address
   0x82: write data beyond the scope
   0x83: CRC checksum error
   0x84: Write disabled
*/

class AM232X
{
  public:
    explicit AM232X(TwoWire *wire = &Wire);

#if defined (ESP8266) || defined(ESP32)
    bool     begin(uint8_t sda, uint8_t scl);
#endif
    bool     begin();
    bool     isConnected();

    int      read();
    int      getModel();
    int      getVersion();
    uint32_t getDeviceID();

    int      getStatus();
    int      getUserRegisterA();
    int      getUserRegisterB();

    int      setStatus(uint8_t value);
    int      setUserRegisterA(int value);
    int      setUserRegisterB(int value);

    inline float getHumidity()    { return humidity; };
    inline float getTemperature() { return temperature; };

  private:
    uint8_t   bits[8];
    float     humidity;
    float     temperature;

    int      _readRegister(uint8_t reg, uint8_t cnt);
    int      _writeRegister(uint8_t reg, uint8_t cnt, int16_t value);
    bool     _wakeup();
    int      _getData(uint8_t length);

    uint16_t _crc16(uint8_t *ptr, uint8_t len);

    TwoWire*  _wire;
};

// -- END OF FILE --
