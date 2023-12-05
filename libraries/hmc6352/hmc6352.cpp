//
//    FILE: hmc6352.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.4.0
// PURPOSE: Arduino library for HMC6352 digital compass sensor


#include "hmc6352.h"


#define HMC_GET_DATA        0x41
#define HMC_WAKE            0x57
#define HMC_SLEEP           0x53
#define HMC_SAVE_OP_MODE    0x4C
#define HMC_CALLIBRATE_ON   0x43
#define HMC_CALLIBRATE_OFF  0x45
#define HMC_UPDATE_OFFSETS  0x4F
#define HMC_WRITE_RAM       0x47
#define HMC_READ_RAM        0x67
#define HMC_WRITE_EEPROM    0x77
#define HMC_READ_EEPROM     0x72


//  ERROR CODES ALL FUNCTIONS
//
//  * twi_writeTo codes (== endTransmission  commands)
//    HMC6532_I2C_OK                      0 .. OK
//    HMC6532_I2C_ERROR_BUFFEROVERFLOW   -1 .. length to long for buffer
//    HMC6532_I2C_ERROR_ADDR_NACK        -2 .. address send, NACK received
//    HMC6532_I2C_ERROR_DATA_NACK        -3 .. data send, NACK received
//    HMC6532_I2C_ERROR_OTHER            -4 ..
//                other twi error (lost bus arbitration, bus error, ..)
//
//  * requestFrom
//    HMC6352_I2C_ERROR_REQ_FROM        -10 .. not enough values returned
//
//  * function calls
//    HMC6532_OK                    0
//    HMC6352_ERROR_PARAM1        -20
//    HMC6352_ERROR_PARAM2        -21
//


hmc6352::hmc6352(uint8_t address, TwoWire *wire)
{
  _address = address;
  _wire    = wire;
}


bool hmc6352::begin()
{
  if (! isConnected())
  {
    return false;
  }
  return true;
}


bool hmc6352::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
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
  if (rv != 0) return -rv;   //  problem with handshake
  yield();
  delay(6);                  //  see datasheet, p8
  return rv;
}


//  read the last value from the sensor
int hmc6352::readHeading()
{
  int rv = _wire->requestFrom(_address, (uint8_t)2);  //  remove ambiguity
  if (rv != 2) return HMC6352_I2C_ERROR_REQ_FROM;
  rv = _wire->read() * 256;  //  MSB
  rv += _wire->read();       //  LSB
  return rv;
}


//  wake up from energy saving modus
int hmc6352::wakeUp()
{
  int rv =  cmd(HMC_WAKE);
  yield();
  delayMicroseconds(100);
  return rv;
}


//  go into energy saving modus
int hmc6352::sleep()
{
  int rv = cmd(HMC_SLEEP);
  yield();
  delayMicroseconds(10);
  return rv;
}


//  values obtained from dump
int hmc6352::factoryReset()
{
  writeRAM(0x74, 0x50);  //  is needed !!
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
  yield();
  delayMicroseconds(125);
  return HMC6532_OK;
}


//  HANDLE WITH CARE - RESTART NECESSARY
//    mode          = 0, 1, 2
//    frequency     = 1, 5, 10, 20 Hz.
//    periodicReset = true/false
//  Returns Operational Mode Control Byte
int hmc6352::setOperationalModus(hmcMode mode, uint8_t frequency, bool periodicReset)
{
  //  Operational Mode Control Byte
  //  bit 2,3,7 are always 0
  byte omcb = 0;
  switch(frequency)
  {
    case 1:  break;
    case 5:  omcb |= 0x20; break;
    case 10: omcb |= 0x40; break;
    case 20: omcb |= 0x60; break;
    default: return HMC6352_ERROR_PARAM2;
  }

  if (periodicReset) omcb |= 0x10;

  switch(mode)
  {
    case STANDBY: omcb |= 0x00; break;
    case QUERY:   omcb |= 0x01; break;
    case CONT:    omcb |= 0x02; break;
    default: return HMC6352_ERROR_PARAM1;
  }

  saveOpMode(omcb);
  return omcb;
}


//  read the Operational Modus as byte from EEPROM
//  TODO: split into 3 items
//
int hmc6352::getOperationalModus()
{
  //  datasheet state that at startup the OM is copied from EEPROM
  //  and that after writing to RAM a reboot is needed to enable new settings
  //  my interpretation ==> EEPROM is leading

  int operationalMode = readCmd(HMC_READ_RAM, 0x74);
  //  int operationalMode = readCmd(HMC_READ_EEPROM, 0x08);
  return operationalMode;
}


//  Switch between normal heading and raw modes
//  default = 0 ==> normal headings
//  Note: after a reboot the output modus will be 0 again.
//        as it is only stored in RAM
//        0 = HEADING
int hmc6352::setOutputModus(uint8_t outputModus)
{
  if (outputModus > 4)    //  4 = MAGY
  {
    return HMC6352_ERROR_PARAM1;
  }
  return writeCmd(HMC_WRITE_RAM, 0x4E, outputModus);
}


//  Read the output modus from RAM
int hmc6352::getOutputModus()
{
  return readCmd(HMC_READ_RAM, 0x4E);
}


//  NOT TESTED
int hmc6352::callibrationOn()
{
  int rv = cmd(HMC_CALLIBRATE_ON);
  yield();
  delayMicroseconds(10);
  return rv;
}


//  NOT TESTED
int hmc6352::callibrationOff()
{
  int rv = cmd(HMC_CALLIBRATE_OFF);
  yield();
  delay(15);
  return rv;
}


//  NOT TESTED
int hmc6352::setI2CAddress(uint8_t address)
{
  if ((address < 0x10) || (address > 0xF6) )
  {
    return HMC6352_ERROR_PARAM1;
  }
  return writeCmd(HMC_WRITE_EEPROM, 0, address);
}


//  returns I2C address from EEPROM
int hmc6352::getI2CAddress()
{
  return readCmd(HMC_READ_EEPROM, 0);
}


//  NOT TESTED
int hmc6352::setTimeDelay(uint8_t milliSeconds)
{
  return writeCmd(HMC_WRITE_EEPROM, 5, milliSeconds);
}


int hmc6352::getTimeDelay()
{
  return readCmd(HMC_READ_EEPROM, 5);
}


//  NOT TESTED
//  nosm = NumberOfSummedMeasurements
int hmc6352::setMeasurementSumming(uint8_t nosm)
{
  uint8_t _nosm = nosm;
  if (_nosm < 1) _nosm = 1;
  else if (_nosm > 16 ) _nosm = 16;
  return writeCmd(HMC_WRITE_EEPROM, 6, _nosm);
}


int hmc6352::getMeasurementSumming()
{
  return readCmd(HMC_READ_EEPROM, 6);
}


//  NOT TESTED
int hmc6352::getSWVersionNumber()
{
  return readCmd(HMC_READ_EEPROM, 7);
}


//  used by setOperationalModus()
int hmc6352::saveOpMode(byte OpMode)
{
  writeCmd(HMC_WRITE_RAM, 0x74, OpMode);
  int rv = cmd(HMC_SAVE_OP_MODE);
  yield();
  delayMicroseconds(125);
  return rv;
}


//  NOT TESTED
//  meaning UpdateOffsets unknown
//  therefore removed from lib for now
int hmc6352::updateOffsets()
{
  int rv = cmd(HMC_UPDATE_OFFSETS);
  yield();
  delay(6);
  return rv;
}


//  idem
//  use at own risk ...
int hmc6352::writeEEPROM(uint8_t address, uint8_t data)
{
  return writeCmd(HMC_WRITE_EEPROM, address, data);
}


//  idem
int hmc6352::readEEPROM(uint8_t address)
{
  return readCmd(HMC_READ_EEPROM, address);
}


//  idem
//  Most RAM locations have an unknown meaning
//  use at own risk ...
int hmc6352::writeRAM(uint8_t address, uint8_t data)
{
  return writeCmd(HMC_WRITE_RAM, address, data);
}


//  idem
int hmc6352::readRAM(uint8_t address)
{
  return readCmd(HMC_READ_RAM, address);
}


///////////////////////////////////////////////////////////
//
//  PRIVATE FUNCTIONS
//
int hmc6352::cmd(uint8_t c)
{
  _wire->beginTransmission(_address);
  _wire->write(c);
  int rv = _wire->endTransmission();
  yield();
  delay(10);
  return rv;
}


int hmc6352::readCmd(uint8_t c, uint8_t address)
{
  _wire->beginTransmission(_address);
  _wire->write(c);
  _wire->write(address);
  int rv = _wire->endTransmission();
  if (rv != 0) return -rv;
  yield();
  delayMicroseconds(70);

  rv = _wire->requestFrom(_address, (uint8_t)1);
  if (rv != 1) return HMC6352_I2C_ERROR_REQ_FROM;
  rv = _wire->read();
  return rv;
}


int hmc6352::writeCmd(uint8_t c, uint8_t address, uint8_t data)
{
  _wire->beginTransmission(_address);
  _wire->write(c);
  _wire->write(address);
  _wire->write(data);
  int rv = _wire->endTransmission();
  yield();
  delayMicroseconds(70);
  return rv;
}


//  -- END OF FILE --

