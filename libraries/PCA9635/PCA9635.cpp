//
//    FILE: PCA9635.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 23-apr-2016
// VERSION: 0.1.2
// PURPOSE: I2C PCA9635 library for Arduino
//     URL:
//
// HISTORY:
// 0.1.2 fix for PCA9635_MODE1
// 0.1.01 set autoincr in constructor
// 0.1.00 initial BETA version
//

#include "PCA9635.h"

#include <Wire.h>

PCA9635::PCA9635(const uint8_t deviceAddress)
{
    _address = deviceAddress;
    Wire.begin();
    // TWBR = 12; // 400KHz
    _data = 0;
    _error = 0;
    writeReg(PCA9635_MODE1, 0x81);  //  AUTOINCR | NOSLEEP | ALLADRR
}

// write value to single PWM registers
void PCA9635::write1(uint8_t channel, uint8_t value)
{
    writeN(channel, &value, 1);
}

// write three values in consecutive PWM registers
// typically for RGB values
void PCA9635::write3(uint8_t channel, uint8_t R, uint8_t G, uint8_t B)
{
    uint8_t arr[3] = { R, G, B };
    writeN(channel, arr, 3);
}

// write count values in consecutive PWM registers
void PCA9635::writeN(uint8_t channel, uint8_t* arr, uint8_t count)
{
    uint8_t base = PCA9635_PWM(channel);
    Wire.beginTransmission(_address);
    Wire.write(base);
    for(uint8_t i = 0; i < count; i++)
    {
        Wire.write(arr[i]);
    }
    _error = Wire.endTransmission();
}

//
void PCA9635::writeMode(uint8_t reg, uint8_t value)
{
    if (reg == PCA9635_MODE1 || reg == PCA9635_MODE2)
    {
        writeReg(reg, value);
    }
}

//
uint8_t PCA9635::readMode(uint8_t reg)
{
    if ((reg == PCA9635_MODE1) || (reg == PCA9635_MODE2))
    {
        uint8_t value = readReg(reg);
        return value;
    }
    return PCA9635_ERROR;
}

//
void PCA9635::setLedDriverMode(uint8_t channel, uint8_t mode)
{
    if (channel <= 15 && mode <= 3)
    {
        uint8_t reg = PCA9635_LEDOUT_BASE + (channel >> 2);
        // some bit magic
        uint8_t shift = (channel & 0x03) * 2;  // 0,2,4,6 places
        uint8_t setmask = mode << shift;
        uint8_t clrmask = ~(0x03 << shift);
        uint8_t value = (readReg(reg) & clrmask) | setmask;
        writeReg(reg, value);
    }
}

//
uint8_t PCA9635::getLedDriverMode(uint8_t channel)
{
    if (channel <= 15)
    {
        uint8_t reg = PCA9635_LEDOUT_BASE + (channel >> 2);
        uint8_t shift = (channel & 0x03) * 2;  // 0,2,4,6 places
        return (readReg(reg) >> shift ) & 0x03;
    }
    return PCA9635_ERROR;
}

//
int PCA9635::lastError()
{
    int e = _error;
    _error = 0;
    return e;
}

void PCA9635::writeReg(uint8_t reg, uint8_t value)
{
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.write(value);
    _error = Wire.endTransmission();
}

uint8_t PCA9635::readReg(uint8_t reg)
{
    Wire.beginTransmission(_address);
    Wire.write(reg);
    _error = Wire.endTransmission();
    if (Wire.requestFrom(_address, (uint8_t)1) != 1)
    {
        _error = PCA9635_ERROR;
        return 0;
    }
    _data = Wire.read();
    return _data;
}

//
// END OF FILE
//