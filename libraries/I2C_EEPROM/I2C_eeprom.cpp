// 
//    FILE: I2C_eeprom.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: Simple I2C_eeprom library for Arduino with EEPROM 24LC256 et al.
//
// HISTORY: 
// 0.1.00 - 2011-01-21 initial version
// 0.1.01 - 2011-01-04 
// 
// Released to the public domain
//

#include <I2C_eeprom.h>

#include "Wstring.h"
#include "Wiring.h"
#include "ctype.h"

////////////////////////////////////////////////////////////////////
//
// PUBLIC
//

I2C_eeprom::I2C_eeprom(uint8_t device)
{
	_Device = device;
	Wire.begin(); 		// initialise the connection
}

void I2C_eeprom::writeByte(unsigned int address, uint8_t data )
{
	_WriteBlock(address, &data, 1);
}

// WARNING: address is a page address, 6-bit end will wrap around
// also, data can be maximum of about 30 uint8_ts, because the Wire library has a buffer of 32 uint8_ts
void I2C_eeprom::writeBlock(unsigned int address, uint8_t* data, int length)
{
	// TODO while loop that store in blocks of 32 uint8_ts 
	// something like
	// while (length > 0)
	// {
	// 		_WriteBlock(address, data, min(length, 32));
	//		address += 32;
	//		data += 32;
	// 		length -=32;
	// }
	_WriteBlock(address, data, length);
}

uint8_t I2C_eeprom::readByte(unsigned int address)
{
	uint8_t rdata = 0xFF;
	_ReadBlock(address, &rdata, 1);
	return rdata;

}

// maybe let's not read more than 30 or 32 uint8_ts at a time!
void I2C_eeprom::readBlock(unsigned int address, uint8_t *buffer, int length)
{
	_ReadBlock(address, buffer, length);
}

////////////////////////////////////////////////////////////////////
//
// PRIVATE
//

// LENGTH <=32;
void I2C_eeprom::_WriteBlock(unsigned int address, uint8_t* buffer, uint8_t length)
{
	Wire.beginTransmission(_Device);
	Wire.send((int)(address >> 8)); 
	Wire.send((int)(address & 0xFF));  
	for (uint8_t c = 0; c < length; c++)
		Wire.send(buffer[c]);
	Wire.endTransmission();
}


void I2C_eeprom::_ReadBlock(unsigned int address, uint8_t* buffer, uint8_t length)
{
	Wire.beginTransmission(_Device);
	Wire.send((int)(address >> 8));
	Wire.send((int)(address & 0xFF));
	Wire.endTransmission();
	Wire.requestFrom(_Device, length);
	for (int c = 0; c < length; c++ )
	  if (Wire.available()) buffer[c] = Wire.receive();
}
//
// END OF FILE
//