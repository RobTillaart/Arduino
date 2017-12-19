//
//    FILE: DAC8552.h 
//  AUTHOR: Rob Tillaart
// PURPOSE: DAC8552 library for Arduino
// VERSION: 0.1.1
// HISTORY: See DAC8552.cpp
//     URL: https://github.com/RobTillaart/Arduino/tree/master/libraries/DAC8552
//
// Released to the public domain
//

#include <SPI.h>

#define DAC8552_POWERDOWN_NORMAL   0
#define DAC8552_POWERDOWN_1K       1
#define DAC8552_POWERDOWN_100K     2
#define DAC8552_POWERDOWN_HIGH_IMP 3

#define DAC8552_LIB_VERSION (F("0.1.1 experimental"))

class DAC8552
{
public:
  DAC8552();
  DAC8552(uint8_t spiData, uint8_t spiClock, uint8_t slaveSelect);

  void begin();

  void bufferValue(uint8_t DAC, uint16_t value);
  void setValue(uint8_t DAC, uint16_t value);
  uint16_t getValue(uint8_t DAC);

  void bufferPowerDown(uint8_t DAC, uint8_t powerDownMode);
  void setPowerDown(uint8_t DAC, uint8_t powerDownMode);
  uint8_t getPowerDownMode(uint8_t DAC);


private:
  uint8_t _spiData;
  uint8_t _spiClock;
  uint8_t _slaveSelect;
  bool    _hwSPI;
  uint8_t _register[2];
  uint16_t _value[2];

  void updateDevice(uint8_t DAC, bool directWrite);
  void swSPI_transfer(uint8_t value);
};

// END OF FILE