//
//    FILE: DAC8551.h
//  AUTHOR: Rob Tillaart
// PURPOSE: DAC8550 DAC8551 library for Arduino
// VERSION: 0.1.1
// HISTORY: See DAC8551.cpp
//     URL: https://github.com/RobTillaart/Arduino/tree/master/libraries/DAC8551
//
// Released to the public domain
//

#include <SPI.h>

#define DAC8551_POWERDOWN_NORMAL   0
#define DAC8551_POWERDOWN_1K       1
#define DAC8551_POWERDOWN_100K     2
#define DAC8551_POWERDOWN_HIGH_IMP 3

#define DAC8551_LIB_VERSION (F("0.1.1 experimental"))

class DAC8551
{
public:
  // type = 0,1,2,4  8550, 8551, 8552, 8554
  DAC8551(); 
  DAC8551(uint8_t spiData, uint8_t spiClock, uint8_t slaveSelect); 

  void begin();

  void setValue(uint16_t value);
  uint16_t getValue();

  void setPowerDown(uint8_t powerDownMode);
  uint8_t getPowerDownMode();

private:
  uint8_t _spiData;
  uint8_t _spiClock;
  uint8_t _slaveSelect;
  bool    _hwSPI;
  uint8_t _value;
  uint8_t _register;

  void updateDevice();
  void swSPI_transfer(uint8_t value);
};

// END OF FILE