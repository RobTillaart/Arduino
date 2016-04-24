//
//    FILE: PCA9685.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 24-apr-2016
// VERSION: 0.1.00
// PURPOSE: I2C PCA9685 library for Arduino
//     URL:
//
// HISTORY:
// 0.1.00 initial BETA version
//

#include "PCA9685.h"

#include <Wire.h>

PCA9685::PCA9685(const uint8_t deviceAddress)
{
    _address = deviceAddress;
    Wire.begin();
    // TWBR = 12; // 400KHz
    _error = 0;
    writeReg(PCA9685_MODE1, 0x21);  //  RESTART | AUTOINCR | ALLADRR
}

//
void PCA9685::writeMode(uint8_t reg, uint8_t value)
{
    if (reg != PCA9685_MODE1 && reg != PCA9685_MODE2)
    {
        _error = PCA9685_ERR_MODE;
        return;
    }
    writeReg(reg, value);
}

//
uint8_t PCA9685::readMode(uint8_t reg)
{
    if (reg != PCA9685_MODE1 && reg != PCA9685_MODE2)
    {
        _error = PCA9685_ERR_MODE;
        return 0;
    }
    uint8_t value = readReg(reg);
    return value;
}

// write value to single PWM channel
void PCA9685::setPWM(uint8_t channel, uint16_t onTime, uint16_t offTime)
{
    if (channel > 15)
    {
        _error = PCA9685_ERR_CHANNEL;
        return;
    }
    uint8_t reg = 0x06 + (channel << 2);
    writeReg2(reg, onTime, offTime);
}

// read value from single PWM channel
void PCA9685::getPWM(uint8_t channel, uint16_t* onTime, uint16_t* offTime)
{
    if (channel > 15)
    {
        _error = PCA9685_ERR_CHANNEL;
        return;
    }
    uint8_t reg = 0x06 + (channel << 2);
    Wire.beginTransmission(_address);
    Wire.write(reg);
    _error = Wire.endTransmission();
    if (Wire.requestFrom(_address, (uint8_t)4) != 4)
    {
        _error = PCA9685_ERROR;
        return;
    }
    uint16_t _data = Wire.read();
    *onTime = (Wire.read() * 256) + _data;
    _data = Wire.read();
    *offTime = (Wire.read() * 256) + _data;
}

//
void PCA9685::setON(uint8_t channel)
{
    if (channel > 15)
    {
        _error = PCA9685_ERR_CHANNEL;
        return;
    }
    uint8_t reg = 0x06 + (channel << 2);
    writeReg2(reg, 0x0010, 0x0000);
}

//
void PCA9685::setOFF(uint8_t channel)
{
    if (channel > 15)
    {
        _error = PCA9685_ERR_CHANNEL;
        return;
    }
    uint8_t reg = 0x06 + (channel << 2);
    writeReg2(reg, 0x0000, 0x0010);
}

//
int PCA9685::lastError()
{
    int e = _error;
    _error = 0;
    return e;
}

//
void PCA9685::writeReg(uint8_t reg, uint8_t value)
{
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.write(value);
    _error = Wire.endTransmission();
}

void PCA9685::writeReg2(uint8_t reg, uint16_t a, uint16_t b)
{
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.write(a & 0xFF);
    Wire.write((a >> 8) & 0x0F);
    Wire.write(b & 0xFF);
    Wire.write((b >> 8) & 0x0F);
    _error = Wire.endTransmission();
}

//
uint8_t PCA9685::readReg(uint8_t reg)
{
    Wire.beginTransmission(_address);
    Wire.write(reg);
    _error = Wire.endTransmission();
    if (Wire.requestFrom(_address, (uint8_t)1) != 1)
    {
        _error = PCA9685_ERROR;
        return 0;
    }
    uint8_t _data = Wire.read();
    return _data;
}

//
// END OF FILE
//