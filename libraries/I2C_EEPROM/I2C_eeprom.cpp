// 
//    FILE: I2C_eeprom.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 1.0.00
// PURPOSE: Simple I2C_eeprom library for Arduino with EEPROM 24LC256 et al.
//
// HISTORY: 
// 0.1.00 - 2011-01-21 initial version
// 0.1.01 - 2011-02-07 added setBlock function
// 0.2.00 - 2011-02-11 fixed 64 bit boundary bug
// 0.2.01 - 2011-08-13 _readBlock made more robust + return value 
// 1.0.00 - 2013-06-09 support for Arduino 1.0.x
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
	_Device = device;
	Wire.begin(); 		// initialise the connection
}

void I2C_eeprom::writeByte(unsigned int address, uint8_t data )
{
	_WriteBlock(address, &data, 1);
}

void I2C_eeprom::writeBlock(unsigned int address, uint8_t* buffer, int length)
{
	// determine length until end of page
	int le = endOfPage(address);
	if (le > 0)
	{
		_WriteBlock(address, buffer, le); // todo check return value..
		address += le;
		buffer += le;
		length -= le;
	}
	
	// write the rest at BLOCKSIZE (16) byte boundaries ///
	while (length > 0)
	{
		_WriteBlock(address, buffer, min(length, BLOCKSIZE));  // todo check return value..
		address += BLOCKSIZE;
		buffer += BLOCKSIZE;
		length -= BLOCKSIZE;
	}
}

void I2C_eeprom::setBlock(unsigned int address, uint8_t data, int length)
{
	uint8_t buffer[BLOCKSIZE];
	for (uint8_t i =0; i< BLOCKSIZE; i++) buffer[i] = data;
	
	// determine length until end of page
	int le = endOfPage(address);
	if (le > 0)
	{
		_WriteBlock(address, buffer, le);
		address += le;
		length -= le;
	}
	
	while (length > 0)
	{
		_WriteBlock(address, buffer, min(length, BLOCKSIZE)); // // todo check return value..
		address += BLOCKSIZE;
		length -= BLOCKSIZE;
	}
}


uint8_t I2C_eeprom::readByte(unsigned int address)
{
	uint8_t rdata;
	_ReadBlock(address, &rdata, 1);  // todo check return value..
	return rdata;
}

// maybe let's not read more than 30 or 32 uint8_ts at a time!
void I2C_eeprom::readBlock(unsigned int address, uint8_t* buffer, int length)
{
	while (length > 0)
	{
		_ReadBlock(address, buffer, min(length, BLOCKSIZE));  // todo check return value..
		address += BLOCKSIZE;
		buffer += BLOCKSIZE;
		length -= BLOCKSIZE;
	}
}

////////////////////////////////////////////////////////////////////
//
// PRIVATE
//


// detemines length until first multiple of 16 of an address
// so writing allways occurs up to 16 byte boundaries
// this is automatically 64 byte boundaries
int I2C_eeprom::endOfPage(unsigned int address)
{
	const int m = BLOCKSIZE;
	unsigned int eopAddr = ((address + m - 1) / m) * m;  // "end of page" address
	return eopAddr - address;  // length until end of page
}

// pre: length < 32;
void I2C_eeprom::_WriteBlock(unsigned int address, uint8_t* buffer, uint8_t length)
{
	Wire.beginTransmission(_Device);
    
#if defined(ARDUINO) && ARDUINO >= 100
	Wire.write((int)(address >> 8)); 
	Wire.write((int)(address & 0xFF));  
	for (uint8_t c = 0; c < length; c++)
        Wire.write(buffer[c]);
#else
	Wire.send((int)(address >> 8)); 
	Wire.send((int)(address & 0xFF));  
	for (uint8_t c = 0; c < length; c++)
		Wire.send(buffer[c]);
#endif

	Wire.endTransmission();
	delay(5);
}

// pre: buffer is large enough to hold length bytes
int I2C_eeprom::_ReadBlock(unsigned int address, uint8_t* buffer, uint8_t length)
{
    
#if defined(ARDUINO) && ARDUINO >= 100
	Wire.beginTransmission(_Device);
	Wire.write((int)(address >> 8));
	Wire.write((int)(address & 0xFF));
	Wire.endTransmission();
	Wire.requestFrom(_Device, length);
    
	int c = 0;
	unsigned long before = millis();
	while ((c < length) && ((millis() - before) < 1000))
	{
    	if (Wire.available()) buffer[c++] = Wire.read();
	}
	return c;    
#else
	Wire.beginTransmission(_Device);
	Wire.send((int)(address >> 8));
	Wire.send((int)(address & 0xFF));
	Wire.endTransmission();
	Wire.requestFrom(_Device, length);
	
	int c = 0;
	unsigned long before = millis();
	while ((c < length) && ((millis() - before) < 1000))
	{
    	if (Wire.available()) buffer[c++] = Wire.receive();
	}
	return c;
#endif
}

//
// END OF FILE
//