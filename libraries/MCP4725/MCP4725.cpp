//
//    FILE: MCP4725.cpp
//  AUTHOR: Rob Tillaart
// PURPOSE: Simple MCP4725 DAC library for Arduino
// VERSION: 1.0.04
// HISTORY: See MCP4725.cpp
//     URL:
//
// HISTORY:
// 0.1.00 - 2013-11-24 initial version
// 0.1.01 - 2013-11-30 added readDAC() & writeDAC (registerwrite)
// 0.1.02 - 2013-12-01 added readEEPROM() & RDY()
// 0.1.03 - 2013-12-01 added powerDownMode code
// 0.1.04 - 2013-12-04 improved the generalCall code (still experimental)
//
// Released to the public domain
//

#include "MCP4725.h"

MCP4725::MCP4725(uint8_t device)
{
    _deviceAddress = device;
    _lastValue = 0;
    _powerDownMode = 0;
}

void MCP4725::begin()
{
    Wire.begin();
    TWBR = 72;
    // 0=1000 1=888 2=800 8=500
    // 12=400KHz  24=250 32=200  72=100  152=50
    // F_CPU/16+(2*TWBR) // TWBR is a uint8_t

    #ifdef MCP4725_EXTENDED
    _lastValue = readDAC();
    #else
    _lastValue = 0;
    #endif

    #ifdef MCP4725_POWERDOWNMODE
    _powerDownMode = readPowerDownModeDAC();
    #else
    _powerDownMode = 0;
    #endif
}

int MCP4725::setValue(uint16_t value)
{
    if (value == _lastValue) return 0;
    if (value > MCP4725_MAXVALUE) return MCP4725_VALUE_ERROR;
    int rv = writeFastMode(value);
    if (rv == 0) _lastValue = value;
    return rv;
}

uint16_t MCP4725::getValue()
{
    return _lastValue;
}

#ifdef MCP4725_EXTENDED

// unfortunately it is not possible to write a different value
// to the DAC and EEPROM simultaneously or write EEPROM only.
int MCP4725::writeDAC(uint16_t value, bool EEPROM)
{
    if (value > MCP4725_MAXVALUE) return MCP4725_VALUE_ERROR;
    while(!RDY());
    int rv = writeRegisterMode(value, EEPROM ? MCP4725_DACEEPROM : MCP4725_DAC);
    if (rv == 0) _lastValue = value;
    return rv;
}

uint16_t MCP4725::readDAC()
{
    uint8_t buffer[3];
    readRegister(buffer, 3);
    uint16_t value = buffer[1];
    value = value << 4;
    value = value + (buffer[2] >> 4);
    return value;
}

uint16_t MCP4725::readEEPROM()
{
    while(!RDY());
    uint8_t buffer[5];
    readRegister(buffer, 5);
    uint16_t value = buffer[3] & 0x0F;
    value = value << 8;
    value = value + buffer[4];
    return value;
}

#endif

#ifdef MCP4725_POWERDOWNMODE
//
// depending on bool EEPROM the value of PDM is written to
// (false) DAC or
// (true) DAC & EEPROM,
int MCP4725::writePowerDownMode(uint8_t PDM, bool EEPROM)
{
    _powerDownMode = (PDM & 0x03); // mask pdm bits only
    return writeDAC(_lastValue, EEPROM);
}

uint8_t MCP4725::readPowerDownModeEEPROM()
{
    while(!RDY());
    uint8_t buffer[4];
    readRegister(buffer, 4);
    uint8_t value = (buffer[3] >> 5) & 0x03;
    return value;
}

uint8_t MCP4725::readPowerDownModeDAC()
{
    while(!RDY());
    uint8_t buffer[1];
    readRegister(buffer, 1);
    uint8_t value = (buffer[0] >> 1) & 0x03;
    return value;
}

// PAGE 22 - experimental
// DAC value is reset to EEPROM value
// need to reflect this in cached value
int MCP4725::powerOnReset()
{
    int rv = generalCall(MCP4725_GC_RESET);
    _lastValue = readDAC(); // update cache to actual value;
    return rv;
}

// PAGE 22 - experimental
// _powerDownMode DAC resets to 0 -- pdm EEPROM stays same !!!
// need to reflect this in cached value
int MCP4725::powerOnWakeUp()
{
    int rv = generalCall(MCP4725_GC_WAKEUP);
    _powerDownMode = readPowerDownModeDAC();  // update to actual value;
    return rv;
}
#endif

////////////////////////////////////////////////////////////////////
//
// PRIVATE
//

// PAGE 18 DATASHEET
int MCP4725::writeFastMode(uint16_t value)
{
    Wire.beginTransmission(_deviceAddress);
    uint8_t h = ((value / 256) & 0x0F);  // set C0 = C1 = 0, no PDmode
    h = h | (_powerDownMode << 4);
    uint8_t l = value & 0xFF;
#if defined(ARDUINO) && ARDUINO >= 100
    Wire.write(h);
    Wire.write(l);
#else
    Wire.send(h);
    Wire.send(l);
#endif
    return Wire.endTransmission();
}

#ifdef MCP4725_EXTENDED

// RDY checks if the last write to EEPROM has been written.
// until RDY all writes to the MCP4725 are ignored!
bool MCP4725::RDY()
{
    uint8_t buffer[1];
    readRegister(buffer, 1);
    return ((buffer[0] & 0x80) > 0);
}

// PAGE 19 DATASHEET
// reg = MCP4725_DAC | MCP4725_EEPROM
int MCP4725::writeRegisterMode(uint16_t value, uint8_t reg)
{
    uint8_t h = (value / 16);
    uint8_t l = (value & 0x0F) << 4;
    Wire.beginTransmission(_deviceAddress);
    reg = reg | (_powerDownMode << 1);
#if defined(ARDUINO) && ARDUINO >= 100
    Wire.write(reg);
    Wire.write(h);
    Wire.write(l);
#else
    Wire.send(reg);
    Wire.send(h);
    Wire.send(l);
#endif
    return Wire.endTransmission();
}

// PAGE 20 DATASHEET
// typical 3 or 5 bytes
uint8_t MCP4725::readRegister(uint8_t* buffer, uint8_t length)
{
    Wire.beginTransmission(_deviceAddress);
    int rv = Wire.endTransmission();
    if (rv != 0) return 0;  // error

    Wire.requestFrom(_deviceAddress, length);
    uint8_t cnt = 0;
    uint32_t before = millis();
    while ((cnt < length) && ((millis() - before) < MCP4725_TIMEOUT))
    {
#if defined(ARDUINO) && ARDUINO >= 100
        if (Wire.available()) buffer[cnt++] = Wire.read();
#else
        if (Wire.available()) buffer[cnt++] = Wire.receive();
#endif
    }
    return cnt;
}
#endif

#ifdef MCP4725_POWERDOWNMODE
int MCP4725::generalCall(uint8_t gc)
{
    Wire.beginTransmission(0);
#if defined(ARDUINO) && ARDUINO >= 100
    Wire.write(gc);
#else
    Wire.send(gc);
#endif
    return Wire.endTransmission();
}
#endif

// END OF FILE