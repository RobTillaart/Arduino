//
//    FILE: BH1750FVI.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: library for BH1750FVI lux sensor Arduino
//     URL: https://github.com/RobTillaart/Arduino/tree/master/libraries
//
// Released to the public domain
//
// 0.1.0	2020-02-02 - initial version

#include "BH1750FVI.h"

#if defined(ESP8266) || defined(ESP32)
BH1750FVI::BH1750FVI(const uint8_t address, const uint8_t dataPin, const uint8_t clockPin)
{
	_address = address;
	_data = 0;
	_error = BH1750FVI_OK;
	_factor = 69;
	_wire = &Wire;

	if ((dataPin < 255) && (clockPin < 255))
	{
		_wire->begin(dataPin, clockPin);
	} else {
		_wire->begin();
	}
}
#endif

BH1750FVI::BH1750FVI(const uint8_t address, TwoWire *wire)
{
	_address = address;
	_data = 0;
	_error = BH1750FVI_OK;
	_factor = 69;
	_wire = wire;
	_wire->begin();
}

float BH1750FVI::getLux(void)
{
	return readData() / 1.2;
}

int BH1750FVI::getError()
{
	int e = _error;
	_error = BH1750FVI_OK;
	return e;
}

void BH1750FVI::changeTiming(uint8_t val)
{
	_factor = val;
	uint8_t Hbits = 0x40 | (val >> 5);
	uint8_t Lbits = 0x60 | (val & 0x1F);
	command(Hbits);
	command(Lbits);
}

void BH1750FVI::setCorrectionFactor(float f)
{
	uint8_t timingValue = round(69 * constrain(f, 0.01, 3.68));
	changeTiming(timingValue);
}


///////////////////////////////////////////////////////////
//
// PRIVATE
//

uint16_t BH1750FVI::readData()
{
	if (_wire->requestFrom(_address, (uint8_t) 2) != 2)
	{
		_error = BH1750FVI_ERROR_WIRE_REQUEST;
		return _data; // last value
	}
	_data = _wire->read();
	_data <<= 8;
	_data += _wire->read();
	return _data;
}

void BH1750FVI::command(uint8_t value)
{
	_wire->beginTransmission(_address);
	_wire->write(value);
	_error = _wire->endTransmission();
}

// --- END OF FILE ---
