#ifndef I2C_EEPROM_H
#define I2C_EEPROM_H
// 
//    FILE: I2C_eeprom.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Simple I2C_eeprom library for Arduino with EEPROM 24LC256 et al.
// VERSION: 1.0.01
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


#define I2C_EEPROM_VERSION "1.0.01"

// I2C_EEPROM_PAGESIZE must be 16 for the Arduino 
// as the WIre lib buffer is too small
#define I2C_EEPROM_PAGESIZE 16

#define I2C_EEPROM_TIMEOUT  1000

// interface
class I2C_eeprom 
{
	public:
	// (I2C address)
	I2C_eeprom(uint8_t);
    
	// (mem_address, value)
	void writeByte(uint16_t, uint8_t );
	// (mem_address, buffer, length)
	void writeBlock(uint16_t, uint8_t*, int );
    
	// (mem_address, value, count)
	void setBlock(uint16_t, uint8_t, int );
    
	// (mem_address)
	uint8_t readByte(uint16_t);
	// (mem_address, buffer, length)
	void readBlock(uint16_t, uint8_t*, int );

	private:
	uint8_t _deviceAddress;
    uint8_t _pagesize;
    
	// (address)
	int endOfPage(uint16_t);
	// (mem_address, buffer, length, incrBuffer)
    void _pageBlock(uint16_t, uint8_t*, int length, bool);
    
	// (mem_address, buffer, length)
	void _WriteBlock(uint16_t, uint8_t*, uint8_t );
	int _ReadBlock(uint16_t, uint8_t*, uint8_t );
};

#endif
// END OF FILE