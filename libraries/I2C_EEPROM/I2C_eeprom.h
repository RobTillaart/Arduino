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

#include <Wire.h> //I2C library

// interface
class I2C_eeprom 
{
	public:
	I2C_eeprom(uint8_t);
	void writeByte(unsigned int , uint8_t );
	void writeBlock(unsigned int, uint8_t* , int ); 
	uint8_t readByte(unsigned int);
	void readBlock(unsigned int , uint8_t* , int );

	private:
	uint8_t _Device;
	void _WriteBlock(unsigned int , uint8_t* , uint8_t);
	void _ReadBlock(unsigned int , uint8_t* , uint8_t);
};

#endif
// END OF FILE