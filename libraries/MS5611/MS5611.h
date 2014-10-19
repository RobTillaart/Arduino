//
//    FILE: MS5611.h
//  AUTHOR: Rob Tillaart
//          Erni - testing/fixes
// VERSION: 0.1.04
// PURPOSE: MS5611 Temperature & Pressure library for Arduino
//     URL:
//
// HISTORY:
// see MS5611.cpp file
//

#ifndef MS5611_h
#define MS5611_h

#if ARDUINO < 100
#error "VERSION NOT SUPPPORTED"
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

#define MS5611_LIB_VERSION "0.1.04"

#define MS5611_READ_OK  0

class MS5611
{
public:
    MS5611(uint8_t address);

    void init();
    int read(uint8_t bits = 8);
    inline int32_t getTemperature() { return _temperature; };
    inline int32_t getPressure() { return _pressure; };
    inline int getLastResult()  { return _result; };

private:
    void reset();
    void convert(uint8_t ADDR, uint8_t bits);
    uint32_t readADC();
    uint16_t readProm(uint8_t reg);
    void command(uint8_t command);

    uint8_t _address;
    int32_t _temperature;
    int32_t _pressure;
    int _result;
    double C[7];

};
#endif
//
// END OF FILE
//