// 
//    FILE: hmc6352.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.03
// PURPOSE: HMC6352 library for Arduino
//
// HISTORY: 
// 0.1.00 - 2011-04-07 initial version
// 0.1.01 - 2011-04-09 quite a complete redo 
// 0.1.02 - 2011-04-12 added timing, fixed a bug
// 0.1.03 - 2011-04-13 fixed small things; added getHeading()
// 
// Released to the public domain
//

#include <hmc6352.h>
#include <Wire.h>
#include "WProgram.h"

/* ERROR CODES ALL FUNCTIONS
//
// * twi_writeTo codes (== endTransmission  commands)
//   0 .. OK
//  -1 .. length to long for buffer
//  -2 .. address send, NACK received
//  -3 .. data send, NACK received
//  -4 .. other twi error (lost bus arbitration, bus error, ..)
//
// * requestFrom 
// -10 .. not enough values returned
//
// * function calls
//   0 .. OK
// -20 .. error param1
// -21 .. error param2
// -22 .. error param3
//
// 
*/

hmc6352::hmc6352(uint8_t device)
{
	Wire.begin();
	_device = constrain(device, 0x10, 0xF6);
}

int hmc6352::getHeading()
{
	int rv = askHeading();
	if (rv != 0) return rv; 
	return readHeading();
}

// Ask the device to make a new reading
int hmc6352::askHeading()
{
	int rv = cmd(HMC_GET_DATA);
	if (rv != 0) return -rv;   // problem with handshake
	delay(6); // see datasheet, p8
	return rv;
}

// read the last value from the
int hmc6352::readHeading()
{
	int rv = Wire.requestFrom(_device, (uint8_t)2);  // remove ambiguity
	if (rv != 2) return -10;
	rv = Wire.receive() * 256;  // MSB
	rv += Wire.receive();       // LSB
	return rv;
}

// wake up from energy saving modus
int hmc6352::wakeUp()
{
	int rv =  cmd(HMC_WAKE);
	delayMicroseconds(100);
	return rv;
}

// go into energy saving modus
int hmc6352::sleep()
{
	int rv = cmd(HMC_SLEEP);
	delayMicroseconds(10);
	return rv;
}

// values obtained from dump
int hmc6352::factoryReset()
{
	writeRAM(0x74, 0x50); // is needed !!
	writeCmd(HMC_WRITE_EEPROM, 0, 66);
	writeCmd(HMC_WRITE_EEPROM, 1, 0);
	writeCmd(HMC_WRITE_EEPROM, 2, 0);
	writeCmd(HMC_WRITE_EEPROM, 3, 0);
	writeCmd(HMC_WRITE_EEPROM, 4, 0);
	writeCmd(HMC_WRITE_EEPROM, 5, 1);
	writeCmd(HMC_WRITE_EEPROM, 6, 4);
	writeCmd(HMC_WRITE_EEPROM, 7, 6);
	writeCmd(HMC_WRITE_EEPROM, 8, 0x50);
	cmd(HMC_SAVE_OP_MODE);
	delayMicroseconds(125);
	return 0;
}

// HANDLE WITH CARE - RESTART NECESSARY
// Returns Operational Mode Config Byte
int hmc6352::setOperationalModus(hmcMode m, uint8_t freq, bool periodicReset)
{
	byte omcb = 0;  // Operational Mode Control Byte
	switch(freq)
	{
	case 1: break;
	case 5: omcb |= 0x20; break;
	case 10: omcb |= 0x40; break;
	case 20: omcb |= 0x60; break;
	default: return -21;
	}

	if (periodicReset) omcb |= 0x10;

	switch(m)
	{
	case STANDBY: break;  // omcb |= 0x00;
	case QUERY: omcb |= 0x01; break;
	case CONT: omcb |= 0x02; break;
	default: return -20;
	}

	writeCmd(HMC_WRITE_RAM, 0x74, omcb);
	cmd(HMC_SAVE_OP_MODE);
	delayMicroseconds(125);
	return omcb;
} 

// read the Operational Modus as byte from EEPROM
// TODO: split into 3 items
//
int hmc6352::getOperationalModus()
{
	// datasheet state that at startup the OM is copied from EEPROM
	// and that after writing to RAM a reboot is needed to enable new settings
	// my interpretation ==> EEPROM is leading
	return readCmd(HMC_READ_RAM, 0x74);
	//return readCmd(HMC_READ_EEPROM, 0x08);
}

// Switch between normal heading and raw modes
// default = 0 ==> normal headings
// Note: after a reboot the output modus will be 0 again.
int hmc6352::setOutputModus(uint8_t om)
{
	if (om > 4) return -20;
	return writeCmd(HMC_WRITE_RAM, 0x4E, om);
}

// Read the output modus from RAM
int hmc6352::getOutputModus()
{
	return readCmd(HMC_READ_RAM, 0x4E);
}

// NOT TESTED
int hmc6352::callibrationOn()
{
	int rv = cmd(HMC_CALLIBRATE_ON);
	delayMicroseconds(10);
	return rv;
}

// NOT TESTED
int hmc6352::callibrationOff()
{
	int rv = cmd(HMC_CALLIBRATE_OFF);
	delay(15);
	return rv;
}

// NOT TESTED
int hmc6352::setI2CAddress(uint8_t address)
{
	if (address < 0x10 || address > 0xF6 ) return -20;
	return writeCmd(HMC_WRITE_EEPROM, 0, address);
}

// returns current I2C address
int hmc6352::getI2CAddress()
{
	return readCmd(HMC_READ_EEPROM, 0);
}

// NOT TESTED
// meaning time delay unknown
// therefore removed from lib for now
int hmc6352::setTimeDelay(uint8_t msec)
{
	return writeCmd(HMC_WRITE_EEPROM, 5, msec);
}

int hmc6352::getTimeDelay()
{
	return readCmd(HMC_READ_EEPROM, 5);
}

// NOT TESTED
// meaning measurement summing unknown
// therefore removed from lib for now
int hmc6352::setMeasurementSumming(uint8_t ms)
{
	if (ms > 16 ) ms = 16;
	return writeCmd(HMC_WRITE_EEPROM, 6, ms);
}

int hmc6352::getMeasurementSumming()
{
	return readCmd(HMC_READ_EEPROM, 6);
}

// Makes only sense in setOperationalModus()
// therefore removed from lib for now
int hmc6352::saveOpMode()
{
	int rv = cmd(HMC_SAVE_OP_MODE);
	delayMicroseconds(125);
	return rv;
}


// NOT TESTED
// meaning UpdateOffsets unknown
// therefore removed from lib for now
int hmc6352::updateOffsets()
{
	int rv = cmd(HMC_UPDATE_OFFSETS);
	delay(6);
	return rv;
}

// idem
// use at own risk ...
int hmc6352::writeEEPROM(uint8_t address, uint8_t data)
{
	return writeCmd(HMC_WRITE_EEPROM, address, data);
}

// idem
int hmc6352::readEEPROM(uint8_t address)
{
	return readCmd(HMC_READ_EEPROM, address);
}


// idem
// Most RAM locations have an unknown meaning
// use at own risk ...
int hmc6352::writeRAM(uint8_t address, uint8_t data)
{
	return writeCmd(HMC_WRITE_RAM, address, data);
}
// idem
int hmc6352::readRAM(uint8_t address)
{
	return readCmd(HMC_READ_RAM, address);
}

/* PRIVATE FUNCTIONS
   mostly to remove redundancy in functions above
*/
int hmc6352::cmd(uint8_t c)
{
	Wire.beginTransmission(_device);
	Wire.send(c);
	int rv = Wire.endTransmission();
	delay(10);
	return rv;
}

int hmc6352::readCmd(uint8_t c, uint8_t address)
{
	Wire.beginTransmission(_device);
	Wire.send(c);
	Wire.send(address);
	int rv = Wire.endTransmission();
	if (rv != 0) return -rv;
	
	delayMicroseconds(70);
	
	rv = Wire.requestFrom(_device, (uint8_t)1);
	if (rv != 1) return -10; 
	rv = Wire.receive();
	return rv;
}

int hmc6352::writeCmd(uint8_t c, uint8_t address, uint8_t data)
{
	Wire.beginTransmission(_device);
	Wire.send(c); 
	Wire.send(address); 
	Wire.send(data); 
	int rv = Wire.endTransmission();
	delayMicroseconds(70);
	return rv;
}
