//
//    FILE: Cozir.cpp
//  AUTHOR: DirtGambit & Rob Tillaart
// VERSION: 0.3.8
// PURPOSE: library for COZIR range of sensors for Arduino
//          Polling Mode + stream parser
//     URL: https://github.com/RobTillaart/Cozir
//          http://forum.arduino.cc/index.php?topic=91467.0
//
//     READ DATASHEET BEFORE USE OF THIS LIB !
//


#include "cozir.h"


#define CZR_INIT_DELAY              1200
#define CZR_REQUEST_TIMEOUT         200


//  EEPROM ADRESSES
//  P 11-12 manual     WHICH
//
//      Name          Address         Default value/ notes
#define CZR_AHHI        0x00            //  reserved
#define CZR_ANLO        0x01            //  reserved
#define CZR_ANSOURCE    0x02            //  reserved
#define CZR_ACINITHI    0x03            //  87
#define CZR_ACINITLO    0x04            //  192
#define CZR_ACHI        0x05            //  94
#define CZR_ACLO        0x06            //  128
#define CZR_ACONOFF     0x07            //  0
#define CZR_ACPPMHI     0x08            //  1
#define CZR_ACPPMLO     0x09            //  194
#define CZR_AMBHI       0x0A            //  1
#define CZR_AMBLO       0x0B            //  194
#define CZR_BCHI        0x0C            //  0
#define CZR_BCLO        0x0D            //  8



COZIR::COZIR(Stream * str)
{
  _ser = str;
  _buffer[0] = '\0';
}


void COZIR::init()
{
  //  override default streaming (takes too much performance)
  setOperatingMode(CZR_POLLING);
  _initTimeStamp = millis();
  //  delay for initialization is kept until next major release.
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
//  OPERATING MODE
//
//  note: use CZR_COMMAND to minimize power consumption
//  CZR_POLLING and CZR_STREAMING use an equally amount
//  of power as both sample continuously...
//
bool COZIR::setOperatingMode(uint8_t mode)
{
  if (mode > CZR_POLLING) return false;
  _operatingMode = mode;
  sprintf(_buffer, "K %u", mode);
  _command(_buffer);
  return true;
}


////////////////////////////////////////////////////////////
//
//  POLLING MODE
//
//  you need to set the polling mode explicitly before
//  using these functions. SetOperatingMode(CZR_POLLING);
//  this is the default behaviour of this Class but
//  not of the sensor!!
//
float COZIR::celsius()
{
  uint16_t rv = _request("T");
  return 0.1 * (rv - 1000.0);
}


float COZIR::humidity()
{
  return 0.1 * _request("H");
}


//  UNITS UNKNOWN lux??
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

//  CALLIBRATION - USE THESE WITH CARE
//  use these only in polling mode (on the Arduino)

//  FineTuneZeroPoint()
//  a reading of v1 will be reported as v2
//  sort of mapping / offset
//  check datasheet for detailed description
uint16_t COZIR::fineTuneZeroPoint(uint16_t v1, uint16_t v2)
{
  sprintf(_buffer, "F %u %u", v1, v2);
  return _request(_buffer);
}


// f mostly the default calibrator
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
//  STREAMING MODE
//
//  output fields should be OR-ed
// e.g. SetOutputFields(CZR_HUMIDITY | CZR_RAWTEMP | CZR_RAWCO2);
//
//  you need to set the STREAMING mode explicitly
//  SetOperatingMode(CZR_STREAMING);
//
//  in STREAMING mode you must parse the output of serial yourself.
//  stream looks like [space field space value]*  \n
//
//  - find separator ('\n')
//  - read until next separator ('\n') in a buffer,
//  - parse buffer [field space value]
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


//  WARNING:
//  After a call to GetRecentFields() you must read the serial port yourself as
//  the internal buffer of this Class cannot handle the possible large output.
//  It can be over 100 bytes long lines!
void COZIR::getRecentFields()
{
  _command("Q");
}

////////////////////////////////////////////////////////////
//
//  EEPROM CALLS - USE WITH CARE
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
//  TODO first verify if single functions work.

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
//  COMMAND MODE
//
//  read serial yourself -
//
//  TODO Page 5:  Mode 0 Command Mode
//  This is primarily intended for use when extracting larger chunks
//  of information from the sensor (for example using the Y and * commands).
//  In this mode, the sensor is stopped waiting for commands.
//
void COZIR::getVersionSerial()
{
  //  override modes to prevent interference in output
  setOperatingMode(CZR_COMMAND);
  _command("Y");
}


void COZIR::getConfiguration()
{
  //  override modes to prevent interference in output
  setOperatingMode(CZR_COMMAND);
  _command("*");
}


/////////////////////////////////////////////////////////
//
//  PRIVATE
//
void COZIR::_command(const char* str)
{
  _ser->print(str);
  _ser->print("\r\n");
}


uint32_t COZIR::_request(const char* str)
{
  _command(str);

  //  read the answer from serial.
  //  TODO: PROPER TIMEOUT CODE.
  //  - might be a big delay
  //  - what is longest answer possible? CZR_REQUEST_TIMEOUT?
  uint8_t idx = 0;
  uint32_t start = millis();
  while (millis() - start < CZR_REQUEST_TIMEOUT)
  {
    if (_ser->available())
    {
      char c = _ser->read();
      if (c == '\n') break;
      _buffer[idx++] = c;
      _buffer[idx] = '\0';
    }
  }
  //  Serial.print("buffer: ");
  //  Serial.println(_buffer);
  uint32_t rv = 0;
  //  default for PPM is different.
  if (str[0] == '.') rv = 1;
  //  do we got the requested field?
  if (strchr(_buffer, str[0]) && (idx > 2))
  {
    rv = atol(&_buffer[2]);
  }
  return rv;
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



////////////////////////////////////////////////////////////////////////////////
//
//  C0ZIRParser
//
C0ZIRParser::C0ZIRParser()
{
  init();
}


void C0ZIRParser::init()
{
  _light              = 0;
  _humidity           = 0;
  _LED_FILT           = 0;
  _LED_RAW            = 0;
  _LED_MAX            = 0;
  _zeroPoint          = 0;
  _temperature_RAW    = 0;
  _temperature_FILT   = 0;
  _LED_signal_FILT    = 0;
  _LED_signal_RAW     = 0;
  _temperature_Sensor = 0;
  _CO2_FILT           = 0;
  _CO2_RAW            = 0;
  _samples            = 0;
  _PPM                = 1;  //  Note default one
  _value              = 0;
  _field              = 0;
}


uint8_t C0ZIRParser::nextChar(char c)
{
  static bool skipLine = false;
  uint8_t rv = 0;

  //  SKIP * and Y until next return.
  //  as output of these two commands not handled by this parser
  if ((c == '*') || (c == 'Y') || (c == '@')) skipLine = true;
  if (c == '\n') skipLine = false;
  if (skipLine) return 0;

  //  TODO investigate
  //  if the last char is more than 2..5 ms ago (9600 baud ~ 1 char/ms)
  //  it probably needs to sync with the stream again.
  //  but it depends on how calling process behaves.
  //  - need for uint32_t _lastChar time stamp?

  switch(c)
  {
    case '0' ... '9':
      _value *= 10;
      _value += (c - '0');
      break;
    //  major responses to catch
    case 'z':
    case 'Z':
    case 'L':
    case 'T':
    case 'H':
    //  all other known responses, starting a new field
    case 'X':
    case '.':
    case '@':     //  skipped
    case 'Y':     //  skipped
    case '*':     //  skipped
    case 'Q':
    case 'F':
    case 'G':
    case 'M':
    case 'K':    //  mode
    case 'A':
    case 'a':
    case 'P':
    case 'p':
    case 'S':
    case 's':
    case 'U':
    case 'u':
    //  new line triggers store() to have results available faster.
    //  saves ~500 millis() for the last FIELD
    case '\n':
      rv = store();
      _field = c;
      _value = 0;
      break;

    //  drop fields of Y, and * command.
    //  reset parsing on separators of Y and * commands
    case ':':
    case ',':
      _field = 0;
      _value = 0;
      break;

    case ' ':    //  known separator
    case '\r':   //  known return
      break;
    default:     //  catch all unknown characters, including glitches.
      break;
  }
  return rv;
}


float C0ZIRParser::celsius()
{
  return  0.1 * (_temperature_FILT - 1000.0);
}


//////////////////////////////////
//
//  PRIVATE
//
uint8_t C0ZIRParser::store()
{
  switch(_field)
  {
    //  LIGHT related
    case 'L':
      _light = _value;
      return _field;
    case 'D':
      _LED_FILT = _value;
      return _field;
    case 'd':
      _LED_RAW = _value;
      return _field;
    case 'l':
      _LED_MAX = _value;
      return _field;
    case 'o':
      _LED_signal_FILT = _value;
      return _field;
    case 'O':
      _LED_signal_RAW = _value;
      return _field;

    //  TEMPERATURE & HUMIDITY
    case 'V':
      _temperature_RAW = _value;
      return _field;
    case 'v':
      _temperature_Sensor = _value;
      return _field;
    case 'T':
      _temperature_FILT = _value;
      return _field;
    case 'H':
      _humidity = _value;
      return _field;

    //  CO2 related
    case 'z':
      _CO2_RAW = _value;
      return _field;
    case 'Z':
      _CO2_FILT = _value;
      return _field;

    //  OTHER
    case 'h':
      _zeroPoint = _value;
      return _field;
    case 'a':
      _samples = _value;
      return _field;
    case '.':
      _PPM = _value;
      return _field;
  }
  return 0;
}


//  -- END OF FILE --

