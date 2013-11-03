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
// 1.0.01 - 2013-11-01 fixed writeBlock bug, refactor 
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
	Wire.begin(); 		// initialise the connection
    // TWBR = 12;          // 12 = 400Khz  72 = 100    FCPU/16+(2*TWBR)
}

void I2C_eeprom::writeByte(uint16_t address, uint8_t data )
{
	_WriteBlock(address, &data, 1);
}

void I2C_eeprom::setBlock(uint16_t address, uint8_t data, int length)
{
	uint8_t buffer[I2C_EEPROM_PAGESIZE];
	for (uint8_t i =0; i< I2C_EEPROM_PAGESIZE; i++) buffer[i] = data;
	
    _pageBlock(address, buffer, length, false);
}

void I2C_eeprom::writeBlock(uint16_t address, uint8_t* buffer, int length)
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
void I2C_eeprom::readBlock(uint16_t address, uint8_t* buffer, int length)
{
    int cnt = min(length, I2C_EEPROM_PAGESIZE);
	while (cnt > 0)
	{
		_ReadBlock(address, buffer, cnt);  // todo check return value..
		address += cnt;
		buffer += cnt;
		length -= cnt;
        cnt = min(length, I2C_EEPROM_PAGESIZE);
	}
}

////////////////////////////////////////////////////////////////////
//
// PRIVATE
//


// detemines length until first multiple of 16 of an address
// so writing allways occurs up to 16 byte boundaries
// this is automatically 64 byte boundaries
int I2C_eeprom::endOfPage(uint16_t address)
{
	uint16_t eopAddr = ((address + I2C_EEPROM_PAGESIZE - 1) / I2C_EEPROM_PAGESIZE) * I2C_EEPROM_PAGESIZE;  // "end of page" address
	return eopAddr - address;  // length until end of page
}


// _doBlock aligns buffer to page boundaries
void I2C_eeprom::_pageBlock(uint16_t address, uint8_t* buffer, int length, bool incrBuffer)
{
	// determine length until end of page
	int le = endOfPage(address);
    int cnt = 0;
    if (le > 0) cnt = min(length, le);  // first block till end of page
    else cnt = min(length, I2C_EEPROM_PAGESIZE);
	while (cnt > 0)
	{
         _WriteBlock(address, buffer, cnt); // todo check return value..
        address += cnt;
        if (incrBuffer) buffer += cnt;
        length -= cnt;
        cnt = min(length, I2C_EEPROM_PAGESIZE);  // rest with BLOCKSIZE or the remaining last bytes
	}
}


// pre: length <= I2C_EEPROM_PAGESIZE;
void I2C_eeprom::_WriteBlock(uint16_t address, uint8_t* buffer, uint8_t length)
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
	Wire.endTransmission();
    delay(5);
}

// pre: buffer is large enough to hold length bytes (not tested)
int I2C_eeprom::_ReadBlock(uint16_t address, uint8_t* buffer, uint8_t length)
{
#if defined(ARDUINO) && ARDUINO >= 100
	Wire.beginTransmission(_deviceAddress);
	Wire.write((int)(address >> 8));
	Wire.write((int)(address & 0xFF));
	Wire.endTransmission();
	Wire.requestFrom(_deviceAddress, length);
    
	int cnt = 0;
	unsigned long before = millis();
	while ((cnt < length) && ((millis() - before) < I2C_EEPROM_TIMEOUT))
	{
    	if (Wire.available()) buffer[cnt++] = Wire.read();
	}
	return cnt;    
#else
	Wire.beginTransmission(_deviceAddress);
	Wire.send((int)(address >> 8));
	Wire.send((int)(address & 0xFF));
	Wire.endTransmission();
	Wire.requestFrom(_deviceAddress, length);
	
	int cnt = 0;
	unsigned long before = millis();
	while ((cnt < length) && ((millis() - before) < I2C_EEPROM_TIMEOUT))
	{
    	if (Wire.available()) buffer[cnt++] = Wire.receive();
	}
	return cnt;
#endif
}

//
// END OF FILE
//