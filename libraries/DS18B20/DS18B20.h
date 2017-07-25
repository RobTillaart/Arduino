//
//    FILE: DS18B20.h
//  AUTHOR: Rob.Tillaart@gmail.com
// VERSION: 0.1.0
//    DATE: 2017-07-25
//
// PUPROSE: library for DS18B20 temperature sensor with minimal footprint
//
// This library supports one single DS18B20 per pin only and no parasite mode.
// It is a minimalistic version of the Dallas Temperature Control Library of
// Miles Burton (kudo's to Miles for that great lib).
//
// As the DTC library is quite big to learn I rewrote it to this minimalistic
// version that allows the user to learn faster to do the most essential things.
// Effort has been taken to keep the code, variables and function names
// compatible with aforementioned library. This way people can step over to
// the DTC lib with relative few problems.
//
// This library only supports the asynch way of working in which one has to
// actively check for completion. This way people will learn how to work in
// a non-blocking way from the beginning.
//

#ifndef DS18B20_H
#define DS18B20_H

#define DS18B20_LIB_VERSION "0.1.0"

#include <OneWire.h>

// Error Code
#define DEVICE_DISCONNECTED -127

typedef uint8_t DeviceAddress[8];
typedef uint8_t ScratchPad[9];

class DS18B20
{
public:
  explicit  DS18B20(OneWire *);
  bool      begin(void);
  void      setResolution(uint8_t);
  void      requestTemperatures(void);
  float     getTempC(void);
  bool      isConversionComplete(void);

private:
  void          readScratchPad(uint8_t *, uint8_t);
  DeviceAddress deviceAddress;
  OneWire*      _wire;
};

#endif

//  END OF FILE