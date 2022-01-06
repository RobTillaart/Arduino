#pragma once
//
//    FILE: AM232X.h
//  AUTHOR: Rob Tillaart
// PURPOSE: AM232X library for Arduino
// VERSION: 0.4.0
// HISTORY: See AM232X.cpp
//     URL: https://github.com/RobTillaart/AM232X
//
//  AM232X PIN layout             AM2315 COLOR
//  ============================================
//   bottom view  DESCRIPTION     COLOR
//       +---+
//       |o  |       VDD          RED
//       |o  |       SDA          YELLOW
//       |o  |       GND          BLACK
//       |o  |       SCL          GREY
//       +---+
//
// do not forget pull up resistors between SDA, SCL and VDD.


#include "Arduino.h"
#include "Wire.h"


#define AM232X_LIB_VERSION              (F("0.4.0"))


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
#define AM232X_READ_TOO_FAST            -20


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
    // datasheet 8.2 - wake up is min 800 us max 3000 us
    bool     isConnected(uint16_t timeout = 3000);

    int      read();
    // lastRead is in MilliSeconds since start sketch
    uint32_t lastRead()                    { return _lastRead; };
    // set readDelay to 0 will reset to datasheet values
    uint16_t getReadDelay()                { return _readDelay; };
    void     setReadDelay(uint16_t rd = 0) { _readDelay = rd; };

    int      getModel();
    int      getVersion();
    uint32_t getDeviceID();

    int      getStatus();
    int      getUserRegisterA();
    int      getUserRegisterB();

    int      setStatus(uint8_t value);
    int      setUserRegisterA(int value);
    int      setUserRegisterB(int value);

    float    getHumidity();
    float    getTemperature();

    // adding offsets works well in normal range
    // might introduce under- or overflow at the ends of the sensor range
    void     setHumOffset(float offset)    { _humOffset = offset; };
    void     setTempOffset(float offset)   { _tempOffset = offset; };
    float    getHumOffset()                { return _humOffset; };
    float    getTempOffset()               { return _tempOffset; };

    bool     wakeUp() { return isConnected(); };

private:
    uint8_t  bits[8];
    float    _humidity;
    float    _temperature;
    float    _humOffset;
    float    _tempOffset;
    uint32_t _lastRead;
    uint16_t _readDelay;

    int      _readRegister(uint8_t reg, uint8_t cnt);
    int      _writeRegister(uint8_t reg, uint8_t cnt, int16_t value);
    int      _getData(uint8_t length);

    uint16_t _crc16(uint8_t *ptr, uint8_t len);

    TwoWire* _wire;
};


// -- END OF FILE --

