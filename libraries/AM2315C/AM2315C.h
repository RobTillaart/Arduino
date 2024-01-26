#pragma once
//
//    FILE: AM2315C.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for AM2315C I2C temperature and humidity sensor.
// VERSION: 0.2.1
//     URL: https://github.com/RobTillaart/AM2315C
//
//
//  Always check datasheet
//
//                    +-----------------+
//    RED    -------- | VDD             |
//    YELLOW -------- | SDA    AM2315C  |
//    BLACK  -------- | GND             |
//    WHITE  -------- | SCL             |
//                    +-----------------+



#include "Arduino.h"
#include "Wire.h"

#define AM2315C_LIB_VERSION                    (F("0.2.1"))

#define AM2315C_OK                             0
#define AM2315C_ERROR_CHECKSUM                -10
#define AM2315C_ERROR_CONNECT                 -11
#define AM2315C_MISSING_BYTES                 -12
#define AM2315C_ERROR_BYTES_ALL_ZERO          -13
#define AM2315C_ERROR_READ_TIMEOUT            -14
#define AM2315C_ERROR_LASTREAD                -15


class AM2315C
{
public:
  //  CONSTRUCTOR
  //  fixed address 0x38
  AM2315C(TwoWire *wire = &Wire);

  //  start the I2C
  bool     begin();
  bool     isConnected();
  uint8_t  getAddress();


  //  ASYNCHRONUOUS CALL
  //  trigger acquisition.
  int      requestData();
  //  read the raw data.
  int      readData();
  //  converts raw data bits to temperature and humidity.
  int      convert();


  //  SYNCHRONOUS CALL
  //  blocking read call to read + convert data
  int      read();
  //  access the converted temperature & humidity
  float    getHumidity();
  float    getTemperature();


  //  OFFSET  1st order adjustments
  void     setHumOffset(float offset = 0);
  void     setTempOffset(float offset = 0);
  float    getHumOffset();
  float    getTempOffset();


  //  READ STATUS
  uint8_t  readStatus();
  //  3 wrapper functions around readStatus()
  bool     isCalibrated();
  bool     isMeasuring();
  bool     isIdle();
  //  status from last read()
  int      internalStatus();


  //  TIMING
  uint32_t lastRead();
  uint32_t lastRequest();


  //  RESET  (new since 0.1.4)
  //  use with care
  //  returns number of registers reset => must be 3
  //  3     = OK
  //  0,1,2 = error.
  //  255   = no reset needed.
  //  See datasheet 7.4 Sensor Reading Process, point 1
  //  use with care
  uint8_t  resetSensor();


private:
  float    _humidity;
  float    _temperature;
  float    _humOffset;
  float    _tempOffset;

  uint8_t  _status;
  uint32_t _lastRequest;
  uint32_t _lastRead;
  uint8_t  _bits[7];

  uint8_t  _crc8(uint8_t *ptr, uint8_t len);

  //  use with care
  bool     _resetRegister(uint8_t reg);

  TwoWire* _wire;
};


//  -- END OF FILE --

