//
//    FILE: MS5611.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.01
// PURPOSE: MS5611 Temperature & Pressure library for Arduino
//     URL:
//
// HISTORY:
// see MS5611.cpp file
//

#ifndef MS5611_h
#define MS5611_h

#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

#define MS5611_LIB_VERSION "0.1.01"

class MS5611
{
public:
    MS5611(uint8_t address);

    void init();
    int read(uint8_t bits = 8);
    int32_t temperature;
    int32_t pressure;
    int getLastResult();

private:
    void reset();
    void convertD1(uint8_t bits);
    void convertD2(uint8_t bits);
    int32_t  readADC();
    uint16_t readProm(uint8_t reg);
    void command(uint8_t command);

    uint8_t _address;
    int _result;
    uint16_t C[8];
};
#endif
//
// END OF FILE
//