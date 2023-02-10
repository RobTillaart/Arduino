#pragma once
//
//    FILE: DHT20.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for DHT20 I2C temperature and humidity sensor.
// VERSION: 0.2.2
//     URL: https://github.com/RobTillaart/DHT20
//

//  Always check datasheet - front view
//
//          +--------------+
//  VDD ----| 1            |
//  SDA ----| 2    DHT20   |
//  GND ----| 3            |
//  SCL ----| 4            |
//          +--------------+


#include "Arduino.h"
#include "Wire.h"

#define DHT20_LIB_VERSION                    (F("0.2.2"))

#define DHT20_OK                             0
#define DHT20_ERROR_CHECKSUM                -10
#define DHT20_ERROR_CONNECT                 -11
#define DHT20_MISSING_BYTES                 -12
#define DHT20_ERROR_BYTES_ALL_ZERO          -13
#define DHT20_ERROR_READ_TIMEOUT            -14
#define DHT20_ERROR_LASTREAD                -15


class DHT20
{
public:
  //  CONSTRUCTOR
  //  fixed address 0x38
  DHT20(TwoWire *wire = &Wire);

  //  start the I2C
#if defined(ESP8266) || defined(ESP32)
  bool     begin(const uint8_t dataPin, const uint8_t clockPin);
#endif
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

