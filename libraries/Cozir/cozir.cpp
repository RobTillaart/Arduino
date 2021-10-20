//
//    FILE: Cozir.cpp
//  AUTHOR: DirtGambit & Rob Tillaart
// VERSION: 0.3.1
// PURPOSE: library for COZIR range of sensors for Arduino
//          Polling Mode
//     URL: https://github.com/RobTillaart/Cozir
//          http://forum.arduino.cc/index.php?topic=91467.0
//
// HISTORY:
//  0.3.1   2021-10-20  update Arduino-CI, badges in readme.md
//  0.3.0   2021-08-08  Major update - breaks interface (names mainly)
//                      add isInitialized(),   add getOperatingMode(), 
//                      add getOutputFields(), add inOutputFields(), 
//                      add kelvin(),          add EEPROM functions
//                      class methods camelCase
//                      extend unit tests
//  0.2.6   2021-01-31  fix #4 use Mode0 for versions and configuration
//  0.2.5   2020-12-26  fix software Serial + version number (oops)
//  0.2.2   2020-12-17  add Arduino-CI + unit tests
//  0.2.1   2020-06-05  fix library.json
//  0.2.0   2020-03-30  some refactor and own repo
//  0.1.06  added support for HardwareSerial for MEGA (Rob T)
//          removed support for NewSoftSerial ==> stop pre 1.0 support)
//  0.1.05  fixed bug: uint16_t request() to uint32_t request() in .h file (Rob T)
//  0.1.04  changed CO2 to support larger values (Rob T)
//  0.1.03  added setOperatingMode
//  0.1.02  added support Arduino 1.x
//  0.1.01  initial version
//
// READ DATASHEET BEFORE USE OF THIS LIB !
//


#include "cozir.h"


#define CZR_INIT_DELAY              1200
#define CZR_REQUEST_TIMEOUT         200


// EEPROM ADRESSES
// P 11-12 manual
//      Name          Address         Default value/ notes
#define CZR_AHHI        0x00            // reserved
#define CZR_ANLO        0x01            // reserved
#define CZR_ANSOURCE    0x02            // reserved
#define CZR_ACINITHI    0x03            // 87
#define CZR_ACINITLO    0x04            // 192
#define CZR_ACHI        0x05            // 94
#define CZR_ACLO        0x06            // 128
#define CZR_ACONOFF     0x07            // 0
#define CZR_ACPPMHI     0x08            // 1
#define CZR_ACPPMLO     0x09            // 194
#define CZR_AMBHI       0x0A            // 1
#define CZR_AMBLO       0x0B            // 194
#define CZR_BCHI        0x0C            // 0
#define CZR_BCLO        0x0D            // 8



COZIR::COZIR(Stream * str)
{
  _ser = str;
  _buffer[0] = '\0';
}


void COZIR::init()
{
  // override default streaming (takes too much performance)
  setOperatingMode(CZR_POLLING);
  _initTimeStamp = millis();
  // delay for initialization is kept until next major release.
  //    timestamp + isInitialized() is prepared.
  //    users can comment next line.
  delay(CZR_INIT_DELAY);
}


bool COZIR::isInitialized()
{
  return (millis() - _initTimeStamp) > CZR_INIT_DELAY;
}


////////////////////////////////////////////////////////////
//
// OPERATING MODE
//
// note: use CZR_COMMAND to minimize power consumption
// CZR_POLLING and CZR_STREAMING use an equally amount
// of power as both sample continuously...
//
void COZIR::setOperatingMode(uint8_t mode)
{
  _operatingMode = mode;
  sprintf(_buffer, "K %u", mode);
  _command(_buffer);
}


////////////////////////////////////////////////////////////
//
// POLLING MODE
//
// you need to set the polling mode explicitly before
// using these functions. SetOperatingMode(CZR_POLLING);
// this is the default behaviour of this Class but
// not of the sensor!!
//
float COZIR::celsius()
{
  uint16_t rv = _request("T");
  return 0.1 * (rv - 1000.0);     // P17 negative values
}


float COZIR::humidity()
{
  return 0.1 * _request("H");
}


// UNITS UNKNOWN lux??
float COZIR::light()
{
  return 1.0 * _request("L");
}


uint32_t COZIR::CO2()
{
  return _request("Z");
}


uint16_t COZIR::getPPMFactor()
{
  _ppmFactor = _request(".");
  return _ppmFactor;
}

// CALLIBRATION - USE THESE WITH CARE
// use these only in polling mode (on the Arduino)

// FineTuneZeroPoint()
// a reading of v1 will be reported as v2
// sort of mapping
// check datasheet for detailed description
uint16_t COZIR::fineTuneZeroPoint(uint16_t v1, uint16_t v2)
{
  sprintf(_buffer, "F %u %u", v1, v2);
  return _request(_buffer);
}


// mostly the default calibrator
uint16_t COZIR::calibrateFreshAir()
{
  return _request("G");
}


uint16_t COZIR::calibrateNitrogen()
{
  return _request("U");
}


uint16_t COZIR::calibrateKnownGas(uint16_t value)
{
  sprintf(_buffer, "X %u", value);
  return _request(_buffer);
}


//uint16_t COZIR::calibrateManual(uint16_t value)
//{
  //sprintf(_buffer, "u %u", value);
  //return _request(_buffer);
//}

//uint16_t COZIR::setSpanCalibrate(uint16_t value)
//{
  //sprintf(_buffer, "S %u", value);
  //return _request(_buffer);
//}

//uint16_t COZIR::getSpanCalibrate()
//{
//  return _request("s");
//}


void COZIR::setDigiFilter(uint8_t value)
{
  sprintf(_buffer, "A %u", value);
  _command(_buffer);
}


uint8_t COZIR::getDigiFilter()
{
  return _request("a");
}


////////////////////////////////////////////////////////////
//
// STREAMING MODE
//
// output fields should be OR-ed
// e.g. SetOutputFields(CZR_HUMIDITY | CZR_RAWTEMP | CZR_RAWCO2);
//
// you need to set the STREAMING mode explicitly
// SetOperatingMode(CZR_STREAMING);
//
// in STREAMING mode you must parse the output of serial yourself
//
void COZIR::setOutputFields(uint16_t fields)
{
  _outputFields = fields;
  sprintf(_buffer, "M %u", fields);
  _command(_buffer);
}


bool COZIR::inOutputFields(uint16_t field)
{
  return (_outputFields & field) == field;
}


// WARNING:
// After a call to GetRecentFields() you must read the serial port yourself as
// the internal buffer of this Class cannot handle the possible large output.
// It can be over 100 bytes long lines!
void COZIR::getRecentFields()
{
  _command("Q");
}

////////////////////////////////////////////////////////////
//
// EEPROM CALLS - USE WITH CARE
//
void COZIR::setAutoCalibrationPreload(uint16_t value)
{
  _setEEPROM2(CZR_ACINITHI, value);
}

uint16_t COZIR::getAutoCalibrationPreload()
{
  return _getEEPROM2(CZR_ACINITHI);
}

void COZIR::setAutoCalibrationInterval(uint16_t value)
{
  _setEEPROM2(CZR_ACHI, value);
}

uint16_t COZIR::getAutoCalibrationInterval()
{
  return _getEEPROM2(CZR_ACHI);
}

void COZIR::setAutoCalibrationOn()
{
  _setEEPROM(CZR_ACONOFF, 1);
}

void COZIR::setAutoCalibrationOff()
{
  _setEEPROM(CZR_ACONOFF, 0);
}

bool COZIR::getAutoCalibration()
{
  return _getEEPROM(CZR_ACONOFF);
}

void COZIR::setAutoCalibrationBackgroundConcentration(uint16_t value)
{
  _setEEPROM2(CZR_ACPPMHI, value);
}

uint16_t COZIR::getAutoCalibrationBackgroundConcentration()
{
  return _getEEPROM2(CZR_ACPPMHI);
}

void COZIR::setAmbientConcentration(uint16_t value)
{
  _setEEPROM2(CZR_AMBHI, value);
}

uint16_t COZIR::getAmbientConcentration()
{
  return _getEEPROM2(CZR_AMBHI);
}

void COZIR::setBufferClearTime(uint16_t value)
{
  _setEEPROM2(CZR_BCHI, value);
}

uint16_t COZIR::getBufferClearTime()
{
  return _getEEPROM2(CZR_BCHI);
}


/*
// TODO first verify if single functions work.

void COZIR::setEEPROMFactoryReset()
{
  setAutoCalibrationPreload(0x57C0);
  setAutoCalibrationInterval(0x8E80);
  setAutoCalibrationOff();
  setAutoCalibrationBackgroundConcentration(0x01C2);
  setAmbientConcentration(0x01C2);
  setBufferClearTime(0x0008);
}
*/



////////////////////////////////////////////////////////////
//
// COMMAND MODE
//
// read serial yourself -
//
// TODO Page 5:  Mode 0 Command Mode
// This is primarily intended for use when extracting larger chunks
// of information from the sensor (for example using the Y and * commands).
// In this mode, the sensor is stopped waiting for commands.
//
void COZIR::getVersionSerial()
{
  // override modes to prevent interference in output
  setOperatingMode(CZR_COMMAND);
  _command("Y");
}


void COZIR::getConfiguration()
{
  // override modes to prevent interference in output
  setOperatingMode(CZR_COMMAND);
  _command("*");
}


/////////////////////////////////////////////////////////
//
// PRIVATE
//
void COZIR::_command(const char* str)
{
  _ser->print(str);
  _ser->print("\r\n");
}


uint32_t COZIR::_request(const char* str)
{
  _command(str);

  // read the answer from serial.
  // TODO: PROPER TIMEOUT CODE.
  // - might be a big delay
  // - what is longest answer possible?
  uint8_t idx = 0;
  uint32_t start = millis();
  // while (millis() - start < CZR_REQUEST_TIMEOUT)
  delay(CZR_REQUEST_TIMEOUT);
  while (true)
  {
    // delay(1);
    if (_ser->available())
    {
      char c = _ser->read();
      _buffer[idx++] = c;
      _buffer[idx] = '\0';
      if (c == '\n') break;
    }
  }
  uint32_t rv = atol(&_buffer[2]);
  if (idx > 2) return rv;
  return 0;
}


void COZIR::_setEEPROM(uint8_t address, uint8_t value)
{
  if (address > CZR_BCLO) return;
  sprintf(_buffer, "P %u %u", address, value);
  _command(_buffer);
}


uint8_t COZIR::_getEEPROM(uint8_t address)
{
  sprintf(_buffer, "p %u", address);
  return _request(_buffer);
}


void COZIR::_setEEPROM2(uint8_t address, uint16_t value)
{
  if (address > CZR_BCLO) return;
  sprintf(_buffer, "P %u %u", address, value >> 8);
  _command(_buffer);
  sprintf(_buffer, "P %u %u", address + 1, value & 0xFF);
  _command(_buffer);
}


uint16_t COZIR::_getEEPROM2(uint8_t address)
{
  sprintf(_buffer, "p %u", address);
  uint16_t val = _request(_buffer) << 8;
  sprintf(_buffer, "p %u", address + 1);
  return val + _request(_buffer);
}



// -- END OF FILE --
