#pragma once
//
//    FILE: Cozir.h
//  AUTHOR: DirtGambit & Rob Tillaart
// VERSION: 0.3.0
// PURPOSE: library for COZIR range of sensors for Arduino
//          Polling Mode
//     URL: https://github.com/RobTillaart/Cozir
//          http://forum.arduino.cc/index.php?topic=91467.0
//
// READ DATASHEET BEFORE USE OF THIS LIB !
//


#include "Arduino.h"


#define COZIR_LIB_VERSION           (F("0.3.0"))


// OUTPUTFIELDS
// See datasheet for details.
// These defines can be OR-ed for the SetOutputFields command
#define CZR_LIGHT                   0x2000
#define CZR_HUMIDITY                0x1000
#define CZR_FILTLED                 0x0800
#define CZR_RAWLED                  0x0400
#define CZR_MAXLED                  0x0200
#define CZR_ZEROPOINT               0x0100
#define CZR_RAWTEMP                 0x0080
#define CZR_FILTTEMP                0x0040
#define CZR_FILTLEDSIGNAL           0x0020
#define CZR_RAWLEDSIGNAL            0x0010
#define CZR_SENSTEMP                0x0008
#define CZR_FILTCO2                 0x0004
#define CZR_RAWCO2                  0x0002

#define CZR_NONE                    0x0001


// easy default setting for streaming
#define CZR_HTC                     (CZR_HUMIDITY | CZR_RAWTEMP | CZR_RAWCO2)
// not in datasheet for debug only
#define CZR_ALL                     0x3FFE


// OPERATING MODES
#define CZR_COMMAND                 0x00
#define CZR_STREAMING               0x01
#define CZR_POLLING                 0x02


class COZIR
{
public:
  COZIR(Stream * str);
  void     init();      // sets operatingMode to CZR_POLLING
  bool     isInitialized();

  // warning: CZR_STREAMING is experimental, minimal tested.
  void     setOperatingMode(uint8_t mode);
  uint8_t  getOperatingMode() { return _operatingMode; };


  float    celsius();
  float    fahrenheit() { return (celsius() * 1.8) + 32; };
  float    kelvin()     { return celsius() + 273.15; };
  float    humidity();
  float    light();
  uint32_t CO2();
  uint16_t getPPMFactor();   // P14 . command  return 1, 10 or 100


  // Calibration function, read datasheet before use
  uint16_t fineTuneZeroPoint(uint16_t v1, uint16_t v2);
  uint16_t calibrateFreshAir();
  uint16_t calibrateNitrogen();
  uint16_t calibrateKnownGas(uint16_t value);


  // WARNING: following 3 functions are NOT RECOMMENDED,
  //          read datasheet before use
  // uint16_t calibrateManual(uint16_t value);
  // uint16_t setSpanCalibrate(uint16_t value);
  // uint16_t getSpanCalibrate();


  // DIGIFILTER, use with care, read datasheet before use
  //     32 = default value = 32,
  //      1 = fast (noisy)
  //    255 = slow (smoothed)
  //      0 = special. details see datasheet
  void     setDigiFilter(uint8_t value);
  uint8_t  getDigiFilter();


  // STREAMING MODE - needs testing...
  void     setOutputFields(uint16_t fields);
  uint16_t getOutputFields() { return _outputFields; };
  bool     inOutputFields(uint16_t field);
  void     clearOutputFields() { setOutputFields(CZR_NONE); };
  // WARNING:
  // After a call to GetRecentFields() you must read the serial port yourself as
  // the internal buffer of this Class cannot handle the possible large output.
  // Answers can be over 100 bytes long!
  void     getRecentFields();


  // EEPROM
  void     setAutoCalibrationPreload(uint16_t value);
  uint16_t getAutoCalibrationPreload();

  void     setAutoCalibrationInterval(uint16_t value);
  uint16_t getAutoCalibrationInterval();

  void     setAutoCalibrationOn();
  void     setAutoCalibrationOff();
  bool     getAutoCalibration();

  void     setAutoCalibrationBackgroundConcentration(uint16_t value);
  uint16_t getAutoCalibrationBackgroundConcentration();

  void     setAmbientConcentration(uint16_t value);
  uint16_t getAmbientConcentration();

  void     setBufferClearTime(uint16_t value);
  uint16_t getBufferClearTime();

  // TODO test EEPROM function first.
  // void setEEPROMFactoryReset();

  // META INFORMATION
  void     getVersionSerial();
  void     getConfiguration();


  ///////////////////////////////////////////////
  //
  // SEMI PRIVATE FOR UNIT TESTING THEM
  //
  void     _setEEPROM(uint8_t address, uint8_t value);
  uint8_t  _getEEPROM(uint8_t address);
  void     _setEEPROM2(uint8_t address, uint16_t value);
  uint16_t _getEEPROM2(uint8_t address);


private:
  Stream * _ser;
  char     _buffer[20];

  uint32_t _initTimeStamp = 0;
  uint16_t _ppmFactor     = 1;

  uint8_t  _operatingMode = CZR_STREAMING;
  uint16_t _outputFields  = CZR_NONE;

  void     _command(const char* str);
  uint32_t _request(const char* str);
};


// -- END OF FILE --
