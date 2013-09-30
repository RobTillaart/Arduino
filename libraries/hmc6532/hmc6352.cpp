// 
//    FILE: hmc6352.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: HMC6352 library for Arduino
//
// HISTORY: 
// 0.1.00 - 2011-04-07 initial version
// 
// Released to the public domain
//

#include <hmc6352.h>
#include <Wire.h>
#include "WProgram.h"


/* ERROR CODES ALL FUNCTIONS

// * twi_writeTo codes
//   0 .. OK
//  -1 .. length to long for buffer
//  -2 .. address send, NACK received
//  -3 .. data send, NACK received
//  -4 .. other twi error (lost bus arbitration, bus error, ..)
// * requestFrom 
// -10 : not enough values returned
*/

// >=0 == direction 
// < 0 error code
hmc6352::hmc6352(uint8_t device)
{
	Wire.begin();
	_device = constrain(device, 0x10, 0xF6);
}

/* RETURN VALUES
// >=0 == direction 
// < 0 error code
*/
int hmc6352::direction()
{
	int rv = cmd(HMC_GET_DATA);
	if (rv != 0) return -rv;   // problem with handshake
	delay(6); // see datasheet, p8

	// no need for wire.available()...
	rv = Wire.requestFrom(_device, (uint8_t)2);  // remove ambiguity
	if (rv != 2) return -10; 
	rv = Wire.receive() * 256;
	rv += Wire.receive();
	return rv;
}

int hmc6352::qry()
{
	// no need for wire.available()...
	int rv = Wire.requestFrom(_device, (uint8_t)2);  // remove ambiguity
	if (rv != 2) return -10; 
	rv = Wire.receive() * 256;
	rv += Wire.receive();
	return rv;
}

int hmc6352::wakeUp()
{
	return cmd(HMC_WAKE); 
}

int hmc6352::sleep()
{
	return cmd(HMC_SLEEP); 
}

// values obtained from dump
int hmc6352::factoryReset()
{
    writeRAM(0x74, 0x50);

	writeCmd(HMC_WRITE_EEPROM, 0, 66);
	writeCmd(HMC_WRITE_EEPROM, 1, 0);
	writeCmd(HMC_WRITE_EEPROM, 2, 0);
	writeCmd(HMC_WRITE_EEPROM, 3, 0);
	writeCmd(HMC_WRITE_EEPROM, 4, 0);
	writeCmd(HMC_WRITE_EEPROM, 5, 1);
	writeCmd(HMC_WRITE_EEPROM, 6, 4);
	writeCmd(HMC_WRITE_EEPROM, 7, 6);
	writeCmd(HMC_WRITE_EEPROM, 8, 80);
	cmd(HMC_SLEEP); 
	delay(1000);
	cmd(HMC_WAKE); 
	return 0;
}

// HANDLE WITH CARE - RESTART NECESSARY
/* RETURN VALUES
     0 = OK
   -20 = illegal param1
   -21 = illegal param1
   -22 = illegal param2
*/
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
	return 0;
} 

int hmc6352::SaveOpMode()
{
	return cmd(HMC_SAVE_OP_MODE);
}

int hmc6352::getOperationalModus()
{
	// readCmd(HMC_READ_RAM, 0x74);
	return readCmd(HMC_READ_EEPROM, 0x08);
}

// WARNING DANGEROUS
//
/* RETURN VALUES
//   0 = OK
// -20 = illegal param1
*/
int hmc6352::setOutputModus(uint8_t om)
{
	if (om > 4) return -20;
	return writeCmd(HMC_WRITE_RAM, 0x4E, om);
}

int hmc6352::getOutputModus()
{
	return readCmd(HMC_READ_RAM, 0x4E);
}

/* RETURN VALUES
//   0 = OK
// -20 = illegal param1
*/
int hmc6352::setI2Caddress(uint8_t address)
{
	if (address < 0x10 || address > 0xF6 ) return -20;
	return writeCmd(HMC_WRITE_EEPROM, 0, address);
}

int hmc6352::getI2Caddress()
{
	return readCmd(HMC_READ_EEPROM, 0);
}

/* RETURN VALUES
//   0 = OK
// -20 = illegal param1
*/
int hmc6352::setTimeDelay(uint8_t msec)
{
	return writeCmd(HMC_WRITE_EEPROM, 5, msec);
}

int hmc6352::getTimeDelay()
{
	return readCmd(HMC_READ_EEPROM, 5);
}

int hmc6352::setMeasurementSumming(uint8_t ms)
{
	if (ms > 16 ) ms = 16;
	return writeCmd(HMC_WRITE_EEPROM, 6, ms);
}

int hmc6352::getMeasurementSumming()
{
	return readCmd(HMC_READ_EEPROM, 6);
}


int hmc6352::UserCallibrationOn()
{
	return cmd(HMC_CALLIBRATE_ON);
}

int hmc6352::UserCallibrationOff()
{
	return cmd(HMC_CALLIBRATE_OFF);
}

int hmc6352::UpdateOffsets()
{
	return cmd(HMC_UPDATE_OFFSETS);
}

int hmc6352::writeEEPROM(uint8_t address, uint8_t data)
{
	return writeCmd(HMC_WRITE_EEPROM, address, data);
}

int hmc6352::readEEPROM(uint8_t address)
{
	return readCmd(HMC_READ_EEPROM, address);
}

int hmc6352::writeRAM(uint8_t address, uint8_t data)
{
	return writeCmd(HMC_WRITE_RAM, address, data);
}

int hmc6352::readRAM(uint8_t address)
{
	return readCmd(HMC_READ_RAM, address);
}

/* PRIVATE FUNCTIONS
*/
int hmc6352::cmd(uint8_t c)
{
	Wire.beginTransmission(_device);
	Wire.send(c);
	return Wire.endTransmission();
}

int hmc6352::readCmd(uint8_t c, uint8_t address)
{
	Wire.beginTransmission(_device);
	Wire.send(c);
	Wire.send(address);
	int rv = Wire.endTransmission();
	if (rv != 0) return -rv;

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
	return Wire.endTransmission();
}
