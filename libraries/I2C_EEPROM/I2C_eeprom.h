#ifndef I2C_EEPROM_H
#define I2C_EEPROM_H
//
//    FILE: I2C_eeprom.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Simple I2C_eeprom library for Arduino with EEPROM 24LC256 et al.
// VERSION: 1.0.02
// HISTORY: See I2C_eeprom.cpp
//     URL: http://arduino.cc/playground/Main/LibraryForI2CEEPROM
//
// Released to the public domain
//

#include <Wire.h>

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#include "Wstring.h"
#include "Wiring.h"
#endif

#define I2C_EEPROM_VERSION "1.0.02"

// I2C_EEPROM_PAGESIZE must be multiple of 2 e.g. 16, 32 or 64
// 24LC256 -> 64 bytes
#define I2C_EEPROM_PAGESIZE 64

// TWI buffer needs 2 bytes for address
#define I2C_TWIBUFFERSIZE  30

// to break blocking read/write
#define I2C_EEPROM_TIMEOUT  1000

class I2C_eeprom
{
public:
    I2C_eeprom(uint8_t deviceAddress);

    void writeByte(uint16_t address, uint8_t value);
    void writeBlock(uint16_t address, uint8_t* buffer, uint16_t length);
    void setBlock(uint16_t address, uint8_t value, uint16_t length);

    uint8_t readByte(uint16_t address);
    void readBlock(uint16_t address, uint8_t* buffer, uint16_t length);

private:
    uint8_t _deviceAddress;

    void _pageBlock(uint16_t address, uint8_t* buffer, uint16_t length, bool incrBuffer);

    int _WriteBlock(uint16_t address, uint8_t* buffer, uint8_t length);
    int _ReadBlock(uint16_t address, uint8_t* buffer, uint8_t length);
};

#endif
// END OF FILE