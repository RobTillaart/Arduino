//
//    FILE: MCP4725.cpp
//  AUTHOR: Rob Tillaart
// PURPOSE: Simple MCP4725 DAC library for Arduino
// VERSION: 1.0.02
// HISTORY: See MCP4725.cpp
//     URL:
//
// HISTORY:
// 0.1.00 - 2013-11-24 initial version
// 0.1.01 - 2013-11-30 added readDAC() & writeDAC (registerwrite)
// 0.1.02 - 2013-12-01 added readEEPROM() & RDY()
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
    
    _lastValue = readDAC();
    // _powerDownMode = readPowerDownMode();
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

int MCP4725::smooth2Value(uint16_t value, uint8_t steps)
{
    // speed optimization
    if (value == _lastValue) return 0;

    if (value > MCP4725_MAXVALUE) return MCP4725_VALUE_ERROR;
    if (steps == 0) steps++;

    uint16_t delta = (value - _lastValue)/steps;
    if (delta > 0)
    {
        uint16_t v = _lastValue;
        for (int i=0; i < steps-1; i++)
        {
            v += delta;
            writeFastMode(v);
        }
    }
    // be sure to get the end value right
    int rv = writeFastMode(value);
    _lastValue = value;
    return rv;
}

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
int MCP4725::writePowerDownMode(uint8_t PDM)
{
    _powerDownMode = PDM;
    return writeDAC(_lastValue, true);
}

// from EEPROM
uint8_t MCP4725::readPowerDownMode()
{
    uint8_t buffer[4];
    readRegister(buffer, 4);
    uint8_t value = (buffer[3] & 0x60) >> 5;
    return value;
}

int MCP4725::powerOnReset()
{
    return command(MCP4725_GENERAL_RESET);
}

int MCP4725::powerOnWakeUp()
{
    return command(MCP4725_GENERAL_WAKEUP);
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
    reg = reg | _powerDownMode;
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
int MCP4725::command(uint8_t cmd)
{
    Wire.beginTransmission(_deviceAddress);
#if defined(ARDUINO) && ARDUINO >= 100
    Wire.write(cmd);
#else
    Wire.send(cmd);
#endif
    return Wire.endTransmission();
}
#endif

// END OF FILE