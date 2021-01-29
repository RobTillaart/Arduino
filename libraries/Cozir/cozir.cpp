//
//    FILE: Cozir.cpp
//  AUTHOR: DirtGambit & Rob Tillaart
// VERSION: 0.2.5
// PURPOSE: library for COZIR range of sensors for Arduino
//          Polling Mode
//     URL: https://github.com/RobTillaart/Cozir
//          http://forum.arduino.cc/index.php?topic=91467.0
//
// HISTORY:
// 0.2.5    2020-12-26  fix software Serial + version number (oops)
// 0.2.2    2020-12-17  add arduino-ci + unit tests
// 0.2.1    2020-06-05  fix library.json
// 0.2.0    2020-03-30  some refactor and own repo 
// 0.1.06   added support for HardwareSerial for MEGA (Rob T)
//          removed support for NewSoftSerial ==> stop pre 1.0 support)
// 0.1.05   fixed bug: uint16_t request() to uint32_t request() in .h file (Rob T)
// 0.1.04   changed CO2 to support larger values (Rob T)
// 0.1.03   added setOperatingMode
// 0.1.02   added support Arduino 1.x
// 0.1.01   initial version
//
// READ DATASHEET BEFORE USE OF THIS LIB !
//


#include "cozir.h"


COZIR::COZIR(Stream * str)
{
    ser = str;
    buffer[0] = '\0';
}


void COZIR::init()
{
    // overide default streaming (takes too much performance)
    SetOperatingMode(CZR_POLLING);
    // delay for initialization  TODO should be timestamp based
    //                           with an isInitialized function. Non blocking.
    delay(1200);
}


////////////////////////////////////////////////////////////
//
// OPERATING MODE
//
// note: use CZR_COMMAND to minimize power consumption
// CZR_POLLING and CZR_STREAMING use an equally amount
// of power as both sample continuously...
//
void COZIR::SetOperatingMode(uint8_t mode)
{
    sprintf(buffer, "K %u", mode);
    Command(buffer);
}


////////////////////////////////////////////////////////////
//
// POLLING MODE
//
// you need to set the polling mode explicitely before
// using these functions. SetOperatingMode(CZR_POLLING);
// this is the default behaviour of this Class but
// not of the sensor!!
//
float COZIR::Celsius()
{
    uint16_t rv = Request("T");
    return 0.1 * (rv - 1000.0);     // P17 negative values
}


float COZIR::Humidity()
{
    return 0.1 * Request("H");
}


// TODO UNITS UNKNOWN lux??
float COZIR::Light()
{
    return 1.0 * Request("L");
}


uint32_t COZIR::CO2()
{
    return Request("Z");
}

uint16_t COZIR::getPPMFactor()
{
  _ppmFactor = Request(".");
  return _ppmFactor;
}

// CALLIBRATION - USE THESE WITH CARE
// use these only in pollingmode (on the Arduino)

// FineTuneZeroPoint()
// a reading of v1 will be reported as v2
// sort of mapping
// check datasheet for detailed description
uint16_t COZIR::FineTuneZeroPoint(uint16_t v1, uint16_t v2)
{
    sprintf(buffer, "F %u %u", v1, v2);
    return Request(buffer);
}


// mostly the default calibrator
uint16_t COZIR::CalibrateFreshAir()
{
    return Request("G");
}


uint16_t COZIR::CalibrateNitrogen()
{
    return Request("U");
}


uint16_t COZIR::CalibrateKnownGas(uint16_t value)
{
    sprintf(buffer, "X %u", value);
    return Request(buffer);
}


//uint16_t COZIR::CalibrateManual(uint16_t value)
//{
    //sprintf(buffer, "u %u", value);
    //return Request(buffer);
//}

//uint16_t COZIR::SetSpanCalibrate(uint16_t value)
//{
    //sprintf(buffer, "S %u", value);
    //return Request(buffer);
//}

//uint16_t COZIR::GetSpanCalibrate()
//{
//    return Request("s");
//}


void COZIR::SetDigiFilter(uint8_t value)
{
    sprintf(buffer, "A %u", value);
    Command(buffer);
}


uint8_t COZIR::GetDigiFilter()
{
    return Request("a");
}


////////////////////////////////////////////////////////////
//
// STREAMING MODE
//
// outputfields should be OR-ed
// e.g. SetOutputFields(CZR_HUMIDITY | CZR_RAWTEMP | CZR_RAWCO2);
//
// you need to set the STREAMING mode explicitely
// SetOperatingMode(CZR_STREAMING);
//
// in STREAMING mode you must parse the output of serial yourself
//
void COZIR::SetOutputFields(uint16_t fields)
{
    sprintf(buffer, "M %u", fields);
    Command(buffer);
}


// WARNING:
// After a call to GetRecentFields() you must read the serial port yourself as
// the internal buffer of this Class cannot handle the possible large output.
// It can be over 100 bytes long lines!
void COZIR::GetRecentFields()
{
    Command("Q");
}

////////////////////////////////////////////////////////////
//
// EEPROM - USE WITH CARE
//
// SEE DATASHEET 7.2 EEPROM FOR DETAILS
//
void COZIR::SetEEPROM(uint8_t address, uint8_t value)
{
    if (address > BCLO) return;
    sprintf(buffer, "P %u %u", address, value);
    Command(buffer);
}


uint8_t COZIR::GetEEPROM(uint8_t address)
{
    sprintf(buffer, "p %u", address);
    return Request(buffer);
}

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
void COZIR::GetVersionSerial()
{
    Command("Y");
}


void COZIR::GetConfiguration()
{
    Command("*");
}


/////////////////////////////////////////////////////////
//
// PRIVATE
//
void COZIR::Command(const char* str)
{
    ser->print(str);
    ser->print("\r\n");
}


uint32_t COZIR::Request(const char* str)
{
    Command(str);

    // read answer; there may be a 100ms delay!
    // TODO: PROPER TIMEOUT CODE. - what is longest answer possible?
    // yield()?
    // output always stops with /r/n.
    
    delay(200);

    // start with empty buffer
    uint8_t idx = 0;
    while(ser->available())
    {
        buffer[idx++] = ser->read();
    }
    buffer[idx] = '\0';

    uint32_t rv = atol(&buffer[2]);
    return rv;
}


// -- END OF FILE --
