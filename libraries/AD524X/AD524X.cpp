//
//    FILE: AD524X.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: digital PotentioMeter AD5241 AD5242
//    DATE: 2013-10-12
//     URL:
//
// Released to the public domain
//

#include "AD524X.h"

#define AS524X_RDAC0    0x00
#define AS524X_RDAC1    0x80
#define AS524X_RESET    0x40
#define AS524X_SHUTDOWN 0x20
#define AS524X_O1_HIGH  0x10
#define AS524X_O2_HIGH  0x08

AD524X::AD524X(uint8_t address)
{
    // address: 0x01011xx = 0x2C - 0x2F
    _address = address;
    _lastValue[0] = _lastValue[1] = 0;
    _O1 = 0;
    _O2 = 0;
}

uint8_t AD524X::write(uint8_t RDAC, uint8_t value)
{
    if (RDAC > 1) return AS524X_ERROR;
    uint8_t cmd = (RDAC == 0) ? AS524X_RDAC0 : AS524X_RDAC1;
    // remember the O masks
    cmd = cmd | _O1 | _O2;
    _lastValue[RDAC] = value;
    return send(cmd, value);
}

uint8_t AD524X::write(uint8_t RDAC, uint8_t value, uint8_t O1, uint8_t O2)
{
    if (RDAC > 1) return AS524X_ERROR;
    uint8_t cmd = (RDAC == 0) ? AS524X_RDAC0 : AS524X_RDAC1;
    // remember the O masks
    cmd = cmd | _O1 | _O2;

    _O1 = (O1 == LOW) ? 0 : AS524X_O1_HIGH;
    _O2 = (O2 == LOW) ? 0 : AS524X_O2_HIGH;

    cmd = cmd | _O1 | _O2;
    _lastValue[RDAC] = value;
    return send(cmd, value);
}

uint8_t AD524X::setO1(uint8_t v)
{
    _O1 = (v == LOW) ? 0 : AS524X_O1_HIGH;
    uint8_t cmd = AS524X_RDAC0 | _O1 | _O2;
    return send(cmd, _lastValue[0]);
}

uint8_t AD524X::setO2(uint8_t v)
{
    _O2 = (v == LOW) ? 0: AS524X_O2_HIGH;
    uint8_t cmd = AS524X_RDAC0 | _O1 | _O2;
    return send(cmd, _lastValue[0]);
}

uint8_t AD524X::read(uint8_t RDAC)
{
    return _lastValue[RDAC];
}

uint8_t AD524X::midScaleReset(uint8_t RDAC)
{
    if (RDAC > 1) return AS524X_ERROR;
    uint8_t cmd = AS524X_RESET;
    if (RDAC == 1) cmd |= AS524X_RDAC1;
    cmd = cmd | _O1 | _O2;
    _lastValue[RDAC] = 127;
    return send(cmd, _lastValue[RDAC]);
}

// TODO read datasheet
// uint8_t AD524X::shutDown()
// {
//  uint8_t cmd = AS524X_SHUTDOWN;
//  sendCommand(cmd, 0)
// }

//////////////////////////////////////////////////////////
//
// PRIVATE
//
uint8_t AD524X::send(uint8_t cmd, uint8_t value)
{
    Wire.beginTransmission(_address);
    Wire.write(cmd);
    Wire.write(value);
    return Wire.endTransmission();
}

// -- END OF FILE --