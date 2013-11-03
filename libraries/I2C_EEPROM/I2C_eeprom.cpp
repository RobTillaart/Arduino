//
//    FILE: I2C_eeprom.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 1.0.02
// PURPOSE: Simple I2C_eeprom library for Arduino with EEPROM 24LC256 et al.
//
// HISTORY:
// 0.1.00 - 2011-01-21 initial version
// 0.1.01 - 2011-02-07 added setBlock function
// 0.2.00 - 2011-02-11 fixed 64 bit boundary bug
// 0.2.01 - 2011-08-13 _readBlock made more robust + return value
// 1.0.00 - 2013-06-09 support for Arduino 1.0.x
// 1.0.01 - 2013-11-01 fixed writeBlock bug, refactor
// 1.0.02 - 2013-11-03 optimize internal buffers, refactor
//
// Released to the public domain
//

#include <I2C_eeprom.h>

////////////////////////////////////////////////////////////////////
//
// PUBLIC
//

I2C_eeprom::I2C_eeprom(uint8_t device)
{
    _deviceAddress = device;
    Wire.begin();
    //TWBR = 12;          // 12 = 400Khz  72 = 100    FCPU/16+(2*TWBR)
}


void I2C_eeprom::writeByte(uint16_t address, uint8_t data)
{
    _WriteBlock(address, &data, 1);
}


void I2C_eeprom::setBlock(uint16_t address, uint8_t data, uint16_t length)
{
    uint8_t buffer[I2C_TWIBUFFERSIZE];
    for (uint8_t i =0; i< I2C_TWIBUFFERSIZE; i++) buffer[i] = data;

    _pageBlock(address, buffer, length, false);
}


void I2C_eeprom::writeBlock(uint16_t address, uint8_t* buffer, uint16_t length)
{
    _pageBlock(address, buffer, length, true);
}


uint8_t I2C_eeprom::readByte(uint16_t address)
{
    uint8_t rdata;
    _ReadBlock(address, &rdata, 1);  // todo check return value..
    return rdata;
}


// maybe let's not read more than 30 or 32 uint8_ts at a time!
void I2C_eeprom::readBlock(uint16_t address, uint8_t* buffer, uint16_t length)
{
    while (length > 0)
    {
        uint8_t cnt = min(length, I2C_TWIBUFFERSIZE);
        _ReadBlock(address, buffer, cnt);  // todo check return value..
        address += cnt;
        buffer += cnt;
        length -= cnt;
    }
}

////////////////////////////////////////////////////////////////////
//
// PRIVATE
//

// _pageBlock aligns buffer to page boundaries for writing.
// and TWI buffer size
void I2C_eeprom::_pageBlock(uint16_t address, uint8_t* buffer, uint16_t length, bool incrBuffer)
{
    while (length > 0)
    {
        uint8_t bytesUntilPageBoundary = I2C_EEPROM_PAGESIZE - address%I2C_EEPROM_PAGESIZE;
        uint8_t cnt = min(length, bytesUntilPageBoundary);
        cnt = min(cnt, I2C_TWIBUFFERSIZE);

        _WriteBlock(address, buffer, cnt); // todo check return value..
        address += cnt;
        if (incrBuffer) buffer += cnt;
        length -= cnt;
    }
}

// pre: length <= I2C_EEPROM_PAGESIZE  && length <= I2C_TWIBUFFERSIZE;
int I2C_eeprom::_WriteBlock(uint16_t address, uint8_t* buffer, uint8_t length)
{
    Wire.beginTransmission(_deviceAddress);
#if defined(ARDUINO) && ARDUINO >= 100
    Wire.write((int)(address >> 8));
    Wire.write((int)(address & 0xFF));
    for (uint8_t cnt = 0; cnt < length; cnt++)
    Wire.write(buffer[cnt]);
#else
    Wire.send((int)(address >> 8));
    Wire.send((int)(address & 0xFF));
    for (uint8_t cnt = 0; cnt < length; cnt++)
    Wire.send(buffer[cnt]);
#endif
    int rv = Wire.endTransmission();

    delay(5);
    return rv;
}


// pre: buffer is large enough to hold length bytes
int I2C_eeprom::_ReadBlock(uint16_t address, uint8_t* buffer, uint8_t length)
{
    Wire.beginTransmission(_deviceAddress);
#if defined(ARDUINO) && ARDUINO >= 100
    Wire.write((int)(address >> 8));
    Wire.write((int)(address & 0xFF));
#else
    Wire.send((int)(address >> 8));
    Wire.send((int)(address & 0xFF));
#endif
    Wire.endTransmission();

    Wire.requestFrom(_deviceAddress, length);
    int cnt = 0;
    unsigned long before = millis();
    while ((cnt < length) && ((millis() - before) < I2C_EEPROM_TIMEOUT))
    {
#if defined(ARDUINO) && ARDUINO >= 100
        if (Wire.available()) buffer[cnt++] = Wire.read();
#else
        if (Wire.available()) buffer[cnt++] = Wire.receive();
#endif
    }
    return cnt;
}


//
// END OF FILE
//