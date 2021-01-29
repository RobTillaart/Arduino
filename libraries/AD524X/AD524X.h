#pragma once
//
//    FILE: AD524X.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.1
// PURPOSE: I2C digital PotentioMeter AD5241 AD5242
//    DATE: 2013-10-12
//     URL: https://github.com/RobTillaart/AD524X
//

#include "Arduino.h"
#include "Wire.h"


#define AD524X_VERSION        (F("0.3.1"))


#define AS524X_OK             0
#define AS524X_ERROR          100


class AD524X
{
public:
  explicit AD524X(const uint8_t address, TwoWire *wire = &Wire);

#if defined (ESP8266) || defined(ESP32)
  bool    begin(uint8_t sda, uint8_t scl);
#endif
  bool    begin();
  bool    isConnected();
  
  uint8_t reset();    // reset both channels to 127 and O1/O2 to LOW
  uint8_t zeroAll();  //   set both channels to 0   and O1/O2 to LOW

  uint8_t read(const uint8_t rdac);
  uint8_t write(const uint8_t rdac, const uint8_t value);
  uint8_t write(const uint8_t rdac, const uint8_t value, const uint8_t O1, const uint8_t O2);

  uint8_t setO1(const uint8_t value = HIGH);  // HIGH (default) / LOW
  uint8_t setO2(const uint8_t value = HIGH);  // HIGH (default) / LOW
  uint8_t getO1();
  uint8_t getO2();

  uint8_t midScaleReset(const uint8_t rdac);
  uint8_t pmCount() { return _pmCount; };

  // debugging
  uint8_t readBackRegister();  // returns the last value written in register.

  // experimental - to be tested - use at own risk
  uint8_t shutDown();          // datasheet P15

protected:
  uint8_t _pmCount = 0;

private:
  uint8_t send(const uint8_t, const uint8_t);     // cmd value

  uint8_t _address;
  uint8_t _lastValue[2];
  uint8_t _O1;
  uint8_t _O2;

  TwoWire*  _wire;
};

//////////////////////////////////////////////////////////////

class AD5241 : public AD524X
{
public:
  AD5241(const uint8_t address, TwoWire *wire = &Wire);
};

class AD5242 : public AD524X
{
public:
  AD5242(const uint8_t address, TwoWire *wire = &Wire);
};


// -- END OF FILE --
