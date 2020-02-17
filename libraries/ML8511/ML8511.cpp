//
//    FILE: ML8511.cpp
//  AUTHOR: Rob.Tillaart@gmail.com
// VERSION: 0.1.1
// PURPOSE: ML8511 - UV sensor - library for Arduino
//
// HISTORY:
// 0.1.0  2020-02-03 - initial version
// 0.1.1  2020-02-17 - added _voltPerStep() to support more boards
//

#include "ML8511.h"

/////////////////////////////////////////////////////
//
// PUBLIC
//
ML8511::ML8511(uint8_t analogPin, uint8_t enablePin)
{
	_analogPin = analogPin;
	_voltsPerStep = 5.0/1023;
	
	if (enablePin >= 0)
	{
		_enablePin = enablePin;
		pinMode(_enablePin, OUTPUT);
		_enabled = false;
		enable();
	}
	else 
	{
		_enabled = true;
	}
};

float ML8511::getUV(uint8_t energyMode)
{
	if (!_enabled)
	{
		enable();
		// datasheet page 5 states wait for max 1 millisecond
		uint32_t start = micros();
		while (micros() - start < 1000)
		{
			yield();
		}
	}

	float voltage = analogRead(_analogPin) * _voltsPerStep;
	if (energyMode == LOW)
	{
		disable();
	}

	// see datasheet - page 4
	// mW/cm2 @ 365 nm
	// @ 25 Celcius
	// formula estimated on graph
    if (voltage <= 1.0) 
	{
		return 0.0;
	}
	voltage -= 1.0;		// subtract for zero point.
	float mW = voltage * (15.0 / 1.8);
	return mW;
}

void  ML8511::setVoltsPerStep(float voltage, uint32_t steps)
{
	if (voltage > 0.0) _voltsPerStep = voltage / steps;
}

void ML8511::enable()
{
	digitalWrite(_enablePin, HIGH);
	_enabled = true;
};

void ML8511::disable()
{
	digitalWrite(_enablePin, LOW);
	_enabled = false;
};

// END OF FILE
