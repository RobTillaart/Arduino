#ifndef BH1750FVI_H
#define BH1750FVI_H
																																												//
//    FILE: BH1750FVI_H.h
//  AUTHOR: Rob dot Tillaart at gmail dot com
// VERSION: 0.1.0
// PURPOSE: library for BH1750FVI lux sensor Arduino
// HISTORY: See BH1750FVI.cpp
//
// Released to the public domain
//

//  breakout BH1750FVI / GY-30
//
//      +-----------------------+
//  GND |o                      |
//  ADD |o                      |
//  SDA |o                      |
//  SCL |o                      |
//  VCC |o                      |
//      +-----------------------+
//
// ADDRESS:
// 0 = 0x23
// 1 = 0x5C
//

#include "Wire.h"
#include "Arduino.h"

#define BH1750FVI_LIB_VERSION       "0.1.0"
#define BH1750FVI_DEFAULT_ADDRESS   0x23
#define BH1750FVI_ALT_ADDRESS		0x5C

// COMMANDS
#define BH1750FVI_POWER_ON   		0x00
#define BH1750FVI_POWER_OFF   		0x01
#define BH1750FVI_RESET		   		0x07
#define BH1750FVI_CONT_HIGH			0x10
#define BH1750FVI_CONT_HIGH2		0x11
#define BH1750FVI_CONT_LOW		   	0x13
#define BH1750FVI_ONCE_HIGH		  	0x20
#define BH1750FVI_ONCE_HIGH2		0x21
#define BH1750FVI_ONCE_LOW		 	0x23


// ERROR CODES
#define BH1750FVI_OK		                 0
#define BH1750FVI_ERROR_WIRE_REQUEST		 -10


class BH1750FVI
{
public:

#if defined(ESP8266) || defined(ESP32)
	// dataPin and clockPin can be used for ESP8266
	BH1750FVI(const uint8_t address, const uint8_t dataPin, const uint8_t clockPin);
#endif

	BH1750FVI(const uint8_t address, TwoWire *wire = &Wire);

	float   getLux();
	int     getError();

	void 	powerOn() 	{ command(BH1750FVI_POWER_ON); };
	void 	powerOff()	{ command(BH1750FVI_POWER_OFF); };
	void 	reset()		{ command(BH1750FVI_RESET); };

	// MODE		TIME		RESOLUTION
	// High		120 ms		0.5 lux		// recommended
	// High2	120 ms		1 lux
	// Low		16 ms		4 lux
	void	setContHighRes()	{ command(BH1750FVI_CONT_HIGH); };
	void	setContHigh2Res()	{ command(BH1750FVI_CONT_HIGH2); };
	void	setContLowRes()		{ command(BH1750FVI_CONT_LOW); };
	void	setOnceHighRes()	{ command(BH1750FVI_ONCE_HIGH); };
	void	setOnceHigh2Res()	{ command(BH1750FVI_ONCE_HIGH2); };
	void	setOnceLowRes()		{ command(BH1750FVI_ONCE_LOW); };

	// read datasheet about details of the correction factor
	// to be used for very high and very low brightness
	// or to correct for e.g. transparancy
	void	changeTiming(uint8_t val);			// 69 is default
	void    setCorrectionFactor(float f);		// 0.01 .. 3.68
	float   getCorrectionFactor() { return _factor / 69.0; };

private:
	uint16_t 	readData();
	void    	command(uint8_t value);

	uint8_t 	_address;
	uint16_t 	_data;
	int     	_error;
	uint8_t     _factor;

	TwoWire* _wire;
};
#endif

// END OF FILE
