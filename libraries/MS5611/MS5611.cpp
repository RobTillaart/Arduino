//
//    FILE: MS5611.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.01
// PURPOSE: MS5611 Temperature & Humidity library for Arduino
//     URL:
//
// HISTORY:
// 0.1.01 small refactoring
// 0.1.00 added temperature and Pressure code
// 0.0.00 initial version by Rob Tillaart (15-okt-2014)
//
// Released to the public domain
//

#include "MS5611.h"

#include <Wire.h>

/////////////////////////////////////////////////////
//
// PUBLIC
//
MS5611::MS5611(uint8_t address)
{
    _address = address;
    Wire.begin();
}

void MS5611::init()
{
    reset();
    for (int reg = 0; reg < 8; reg++)
    {
        C[reg] = readProm(reg);
        delay(10);
    }
}

int MS5611::read(uint8_t bits)
{
    convertD1(bits);
    if (_result) return _result;
    delay(10);
    int32_t D1 = readADC();
    if (_result) return _result;
    delay(10);
    convertD2(8);
    if (_result) return _result;
    delay(10);
    int32_t D2 = readADC();
    if (_result) return _result;
    delay(10);

    // PAGE 7/20 of the datasheet
    int32_t dT = D2 - C[5] * 256L;
    temperature = 2000 + (dT * C[6])/8388608L;

    int64_t offset = C[2] * 65536L + (C[4] * dT ) / 128L;
    int64_t sens = C[1] * 32768L + (C[3] * dT ) / 256L;
    pressure = ((D1 * sens)/2097152L - offset) / 32768L;
}

int MS5611::getLastResult()
{
    return _result;
}

/////////////////////////////////////////////////////
//
// PRIVATE
//
void MS5611::reset()
{
    command(0x1E);
}

void MS5611::convertD1(uint8_t bits)
{
    bits = constrain(bits, 8, 12);
    int offset = (bits - 8) * 2;
    command(0x40 + offset);
}

void MS5611::convertD2(uint8_t bits)
{
    bits = constrain(bits, 8, 12);
    int offset = (bits - 8) * 2;
    command(0x50 + offset);
}

uint16_t MS5611::readProm(uint8_t reg)
{
    reg = constrain(reg, 0, 7);
    reg = reg * 2;
    command(0xA0 + reg);
    if (_result == 0)
    {
        int nr = Wire.requestFrom(_address, (uint8_t)2);
        if (nr >= 2)
        {
            uint16_t val = Wire.read() * 256;
            val += Wire.read();
            return val;
        }
        return 0;
    }
    return 0;
}

int32_t MS5611::readADC()
{
    command(0x00);
    if (_result == 0)
    {
        int nr = Wire.requestFrom(_address, (uint8_t)3);
        if (nr >= 3)
        {
            uint32_t val = Wire.read() * 65536L;
            val += Wire.read() * 256L;
            val += Wire.read();
            return val;
        }
        return 0L;
    }
    return 0L;
}

void MS5611::command(uint8_t command)
{
    Wire.beginTransmission(_address);
    Wire.write(command);
    _result = Wire.endTransmission();
}
//
// END OF FILE
//