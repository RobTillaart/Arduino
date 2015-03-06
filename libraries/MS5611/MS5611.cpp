//
//    FILE: MS5611.cpp
//  AUTHOR: Rob Tillaart
//          Erni - testing/fixes
// VERSION: 0.1.05
// PURPOSE: MS5611 Temperature & Humidity library for Arduino
//     URL:
//
// HISTORY:
// 0.1.05 moved 6 float multiplies to init  [adds ~70 bytes !!!]
//        moved the MS5611_LIB_VERSION to PROGMEM
// 0.1.04 changed float to double (for platforms which support it)
//        changed divisions in multiplications
//        fixed uint32_t readADC()
//        reduced size of C array by 1 float
//        added second order temperature compensation
// 0.1.03 changed math to float [test version]
// 0.1.02 fixed bug return value read()
//        fixed bug #bits D2
//        added MS5611_READ_OK
//        added inline getters for temp & pres & lastresult.
//        adjusted delay's based on datasheet
//        merged convert functions
//        fixed offset in readProm()
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
MS5611::MS5611(uint8_t deviceAddress)
{
    _address = deviceAddress;
    Wire.begin();
}

void MS5611::init()
{
    reset();

    C[0] = 1;
    C[1] = 32768L;
    C[2] = 65536L;
    C[3] = 3.90625E-3;
    C[4] = 7.8125E-3;
    C[5] = 256;
    C[6] = 1.1920928955E-7;
    for (uint8_t reg = 0; reg < 7; reg++)
    {
        // C[0] not used; this way indices match datasheet.
        // C[7] == CRC skipped.
        C[reg] *= readProm(reg);
    }
}

int MS5611::read(uint8_t bits)
{
    // VARIABLES NAMES BASED ON DATASHEET
    convert(0x40, bits);
    if (_result) return _result;
    uint32_t D1 = readADC();
    if (_result) return _result;

    convert(0x50, bits);
    if (_result) return _result;
    uint32_t D2 = readADC();
    if (_result) return _result;

    // TODO the multiplications of these constants can be done in init()
    // but first they need to be verified.
    
    // TEMP & PRESS MATH - PAGE 7/20
    double dT = D2 - C[5];
    _temperature = 2000 + dT * C[6];

    double offset =  C[2] + dT * C[4];
    double sens = C[1] + dT * C[3];

    // SECOND ORDER COMPENSATION - PAGE 8/20
    // COMMENT OUT < 20 CORRECTION IF NOT NEEDED
    if (_temperature < 20)
    {
        double T2 = dT * dT * 4.6566128731E-10;
        double t = _temperature - 2000;
        double offset2 = 2.5 * t * t;
        double sens2 = 1.25 * t * t * t;
        // COMMENT OUT < -15 CORRECTION IF NOT NEEDED
        if (_temperature < -15)
        {
            t = _temperature + 1500;
            t = t * t;
            offset2 += 7 * t;
            sens2 += 5.5 * t;
        }
        _temperature -= T2;
        offset -= offset2;
        sens -= sens2;
    }
    // END SECOND ORDER COMPENSATION

    _pressure = (D1 * sens * 4.76837158205E-7 - offset) * 3.051757813E-5;

    return 0;
}


/////////////////////////////////////////////////////
//
// PRIVATE
//
void MS5611::reset()
{
    command(0x1E);
    delay(3);
}

void MS5611::convert(uint8_t addr, uint8_t bits)
{
    uint8_t del[5] = {1,2,3,5,10};
    bits = constrain(bits, 8, 12);
    uint8_t offset = (bits - 8) * 2;
    command(addr + offset);
    delay(del[offset/2]);
}

uint16_t MS5611::readProm(uint8_t reg)
{
    reg = constrain(reg, 0, 7);
    uint8_t offset = reg * 2;
    command(0xA0 + offset);
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

uint32_t MS5611::readADC()
{
    command(0x00);
    if (_result == 0)
    {
        int nr = Wire.requestFrom(_address, (uint8_t)3);
        if (nr >= 3)
        {
            uint32_t val = Wire.read() * 65536UL;
            val += Wire.read() * 256UL;
            val += Wire.read();
            return val;
        }
        return 0UL;
    }
    return 0UL;
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