#ifndef I2C_EEPROM_H
#define I2C_EEPROM_H
// 
//    FILE: I2C_eeprom.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Simple I2C_eeprom library for Arduino with EEPROM 24LC256 et al.
// HISTORY: See I2C_eeprom.cpp
//
// Released to the public domain
//

#include <Wire.h>

// BLOCKSIZE must be 16
#define BLOCKSIZE 16

#define I2C_EEPROM_VERSION "0.2"

// interface
class I2C_eeprom 
{
	public:
	// (I2C address)
	I2C_eeprom(uint8_t);
	// (mem_address, value)
	void writeByte(unsigned int, uint8_t );
	// (mem_address, buffer, length)
	void writeBlock(unsigned int, uint8_t*, int ); 
	// (mem_address, value, count)
	void setBlock(unsigned int, uint8_t, int ); 
	// (mem_address)
	uint8_t readByte(unsigned int );
	// (mem_address, buffer, length)
	void readBlock(unsigned int, uint8_t*, int );

	private:
	uint8_t _Device;
	// (address)
	int endOfPage(unsigned int);  
	// (mem_address, buffer, length)
	void _WriteBlock(unsigned int, uint8_t*, uint8_t );
	void _ReadBlock(unsigned int, uint8_t*, uint8_t );
};

#endif
// END OF FILE