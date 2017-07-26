//
//    FILE: Max44009.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.6
// PURPOSE: library for MAX44009 lux sensor Arduino
//     URL:
//
// Released to the public domain
//
// 0.1.6  - 2017-07-26 revert double to float 
// 0.1.5  - updated history
// 0.1.4  - added setAutomaticMode() to max44009.h (thanks debsahu)
// 0.1.03 - added configuration
// 0.1.02 - added threshold code
// 0.1.01 - added interrupt code
// 0.1.00 - initial version

#include "Max44009.h"

Max44009::Max44009(const uint8_t address)
{
    _address = address;
    Wire.begin();
    // TWBR = 12; // 400KHz
    _data = 0;
    _error = 0;
}

float Max44009::getLux(void)
{
    uint16_t data = read(MAX44009_LUX_READING, 2);
    uint8_t e = (data & 0xF000) >> 12;
    uint32_t m = ((data & 0x0F00) >> 4) + (data & 0x000F);
    m <<= e;
    float val = m * 0.045;
    return val;
}

int Max44009::getError()
{
    int e = _error;
    _error = 0;
    return e;
}

void Max44009::setHighThreshold(const float value)
{
    setThreshold(MAX44009_THRESHOLD_HIGH, value);
}

float Max44009::getHighThreshold(void)
{
    return getThreshold(MAX44009_THRESHOLD_HIGH);
}

void Max44009::setLowThreshold(const float value)
{
    setThreshold(MAX44009_THRESHOLD_LOW, value);
}

float Max44009::getLowThreshold(void)
{
    return getThreshold(MAX44009_THRESHOLD_LOW);
}

void Max44009::setThresholdTimer(const uint8_t value)
{
    write(MAX44009_THRESHOLD_TIMER, value);
}

uint8_t Max44009::getThresholdTimer()
{
    return read(MAX44009_THRESHOLD_TIMER, 1);
}

void Max44009::setConfiguration(const uint8_t value)
{
    write(MAX44009_CONFIGURATION, value);
}

uint8_t Max44009::getConfiguration()
{
    return read(MAX44009_CONFIGURATION, 1);
}

void Max44009::setAutomaticMode()
{
    uint8_t config = read(MAX44009_CONFIGURATION);
    config &= ~MAX44009_CFG_CONTINUOUS; // off
    config &= ~MAX44009_CFG_MANUAL;     // off
    write(MAX44009_CONFIGURATION, config);
}

void Max44009::setContinuousMode()
{
    uint8_t config = read(MAX44009_CONFIGURATION);
    config |= MAX44009_CFG_CONTINUOUS; // on
    config &= ~MAX44009_CFG_MANUAL;    // off
    write(MAX44009_CONFIGURATION, config);
}

void Max44009::setManualMode(uint8_t CDR, uint8_t TIM)
{
    if (CDR !=0) CDR = 1;
    if (TIM > 7) TIM = 7;
    uint8_t config = read(MAX44009_CONFIGURATION);
    config &= ~MAX44009_CFG_CONTINUOUS; // off
    config |= MAX44009_CFG_MANUAL;      // on
    config &= 0xF0; // clear CDR & TIM bits
    config |= CDR << 3 | TIM;
    write(MAX44009_CONFIGURATION, config);
}

///////////////////////////////////////////////////////////
//
// PRIVATE
//
void Max44009::setThreshold(const uint8_t reg, const float value)
{
    // TODO CHECK RANGE
    uint32_t m = round(value / 0.045);
    uint8_t e = 0;
    while (m > 255)
    {
        m >>= 1;
        e++;
    };
    m = (m >> 4) & 0x0F;
    e <<= 4;
    write(reg, e | m);
}

float Max44009::getThreshold(uint8_t reg)
{
    uint16_t data = read(reg, 1);
    uint8_t e = (data & 0xF0) >> 4;
    uint32_t m = ((data & 0x0F) << 4) + 0x0F;
    m <<= e;
    float val = m * 0.045;
    return val;
}

// bytes is 1 or 2
uint16_t Max44009::read(uint8_t reg, uint8_t bytes)
{
    Wire.beginTransmission(_address);
    Wire.write(reg);
    _error = Wire.endTransmission();
    if (_error != 0)
    {
        return _data; // last value
    }
    if (Wire.requestFrom(_address, (uint8_t) bytes) != bytes)
    {
        _error = 10;
        return _data; // last value
    }
#if (ARDUINO <  100)
    _data = Wire.receive();
    if (bytes == 2) _data = _data * 256 + Wire.receive();
#else
    _data = Wire.read();
    if (bytes == 2) _data = _data * 256 + Wire.read();
#endif
    return _data;
}

void Max44009::write(uint8_t reg, uint8_t value)
{
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.write(value);
    _error = Wire.endTransmission();
}

// --- END OF FILE ---