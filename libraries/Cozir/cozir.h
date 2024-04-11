#pragma once
//
//    FILE: Cozir.h
// VERSION: 0.3.8
// PURPOSE: library for COZIR range of sensors for Arduino
//          Polling Mode + stream parser
//     URL: https://github.com/RobTillaart/Cozir
//          http://forum.arduino.cc/index.php?topic=91467.0
//
//     READ DATASHEET BEFORE USE OF THIS LIB !
//


#include "Arduino.h"


#define COZIR_LIB_VERSION           (F("0.3.8"))


//  OUTPUT FIELDS
//  See datasheet for details.
//  These defines can be OR-ed for the SetOutputFields command
//
#define CZR_UNKNOWN_2               0x8000     // returns  P 00128  ?
#define CZR_UNKNOWN_1               0x4000     // returns  E 00016  ?
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


//  factory default
#define CZR_DEFAULT                 (CZR_FILTCO2 | CZR_RAWCO2)
//  easy default setting for streaming
#define CZR_HTC                     (CZR_HUMIDITY | CZR_RAWTEMP | CZR_RAWCO2)
//  not in datasheet for debug only
#define CZR_ALL                     0x3FFE


//  OPERATING MODES
#define CZR_COMMAND                 0x00
#define CZR_STREAMING               0x01
#define CZR_POLLING                 0x02


class COZIR
{
public:
  COZIR(Stream * str);
  void     init();      //  sets operatingMode to CZR_POLLING
  bool     isInitialized();

  //  warning: CZR_STREAMING is experimental, minimal tested.
  bool     setOperatingMode(uint8_t mode);
  uint8_t  getOperatingMode() { return _operatingMode; };


  //  POLLING MODE
  float    celsius();
  float    fahrenheit() { return (celsius() * 1.8) + 32; };
  float    kelvin()     { return celsius() + 273.15; };
  float    humidity();
  float    light();
  uint32_t CO2();
  uint16_t getPPMFactor();   //  P14 . command  return 1, 10 or 100


  //  CALIBRATION
  //  read datasheet before use
  uint16_t fineTuneZeroPoint(uint16_t v1, uint16_t v2);
  uint16_t calibrateFreshAir();
  uint16_t calibrateNitrogen();
  uint16_t calibrateKnownGas(uint16_t value);

  //  WARNING: following 3 functions are NOT RECOMMENDED,
  //           read datasheet before use
  //  uint16_t calibrateManual(uint16_t value);
  //  uint16_t setSpanCalibrate(uint16_t value);
  //  uint16_t getSpanCalibrate();


  //  DIGIFILTER, use with care, read datasheet before use
  //     32 = good default value,
  //      1 = fast (noisy and responsive to fast changes)
  //    255 = slow (smoothed to the max)
  //      0 = special. details see datasheet
  void     setDigiFilter(uint8_t value);
  uint8_t  getDigiFilter();


  //  STREAMING MODE
  void     setOutputFields(uint16_t fields);
  uint16_t getOutputFields() { return _outputFields; };
  bool     inOutputFields(uint16_t field);
  void     clearOutputFields() { setOutputFields(CZR_NONE); };
  //  WARNING:
  //  After a call to GetRecentFields() you must read the serial port yourself as
  //  the internal buffer of this Class cannot handle the possible large output.
  //  Answers can be over 100 bytes long!
  void     getRecentFields();


  //  EEPROM
  //  not all sensors support these.
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

  //  TODO test EEPROM function first.
  //  void setEEPROMFactoryReset();


  //  META INFORMATION
  //  library does not parse the output (yet)
  void     getVersionSerial();
  void     getConfiguration();


  ///////////////////////////////////////////////
  //
  //  SEMI PRIVATE FOR UNIT TESTING THEM
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



////////////////////////////////////////////////////////////////////////////////
//
//  C0ZIRParser
//
//  used to parse the stream from a COZIR CO2 sensor.
//  Note: one can comment fields / code not used to minimize footprint.
//
class C0ZIRParser
{
public:
  C0ZIRParser();

  //  init resets all internal values
  void init();
  //  resetParser only resets current FIELD (last values are kept).
  void resetParser() { _field = 0; };


  //  returns field char if a field is completed, 0 otherwise.
  uint8_t nextChar(char c);

  //  FETCH LAST READ VALUES
  float    celsius();
  float    fahrenheit()    { return (celsius() * 1.8) + 32; };
  float    kelvin()        { return celsius() + 273.15; };
  float    humidity()      { return 0.1 * _humidity; };

  uint16_t light()         { return _light; };
  uint16_t ledFilt()       { return _LED_FILT; };
  uint16_t ledRaw()        { return _LED_RAW; };
  uint16_t ledMax()        { return _LED_MAX; };
  uint16_t ledSignalFilt() { return _LED_signal_FILT; };
  uint16_t ledSignalRaw()  { return _LED_signal_RAW; };

  uint16_t zeroPoint()     { return _zeroPoint; };
  uint16_t tempFilt()      { return _temperature_FILT; };
  uint16_t tempRaw()       { return _temperature_RAW; };
  uint16_t tempSensor()    { return _temperature_Sensor; };

  uint16_t CO2()           { return _CO2_FILT; };
  uint16_t CO2Raw()        { return _CO2_RAW; };

  uint16_t samples()       { return _samples; };
  uint16_t getPPMFactor()  { return _PPM; }


private:
  //       FIELD                    ID character
  uint16_t _light;              //  L
  uint16_t _humidity;           //  H
  uint16_t _LED_FILT;           //  D
  uint16_t _LED_RAW;            //  d
  uint16_t _LED_MAX;            //  l    // el not one
  uint16_t _zeroPoint;          //  h
  uint16_t _temperature_RAW;    //  V
  uint16_t _temperature_FILT;   //  T
  uint16_t _LED_signal_FILT;    //  o    // oo not zero
  uint16_t _LED_signal_RAW;     //  O    // oo not zero
  uint16_t _temperature_Sensor; //  v
  uint16_t _CO2_FILT;           //  Z
  uint16_t _CO2_RAW;            //  z

  //  not output fields sec but useful.
  uint16_t _samples;            //  a
  uint16_t _PPM;                //  .    // point


  //  parsing helpers
  uint32_t _value;    //  to build up the numeric value
  uint8_t  _field;    //  last read FIELD

  //  returns FIELD char if a FIELD is completed, 0 otherwise.
  uint8_t store();
};


//  -- END OF FILE --

