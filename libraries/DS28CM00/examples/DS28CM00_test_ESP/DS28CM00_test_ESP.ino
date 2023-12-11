//
//    FILE: DS28CM00_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test DS28CM00 lib
//    DATE: 2020-04-10
//     URL: https://github.com/RobTillaart/DS28CM00


#include "Wire.h"
#include "DS28CM00.h"

#include <rom/crc.h>  //  ESP32 specific


uint8_t uid[8];

DS28CM00 DS28(&Wire1);


void setup()
{
  Serial.begin(115200);

  Serial.println(__FILE__);
  Serial.print(F("DS28CM00 library: "));
  Serial.println(DS28CM00_LIB_VERSION);

  Wire.begin(10, 12);
  DS28.begin();

  Serial.println();
}


void loop()
{
  test();
  delay(1000);
}


void test()
{
  bool b = DS28.getUID(uid);

  if (b == false)
  {
    Serial.println(F("Error communicating with DS28CM00."));
  }
  else
  {
    //  PRINT UID
    Serial.print(F("UID:\t"));
    for (uint8_t i = 0; i < 8; i++)
    {
      if (uid[i] < 0x10) Serial.print('0');
      Serial.print(uid[i], HEX);
      Serial.print(' ');
    }
    Serial.println();

    //  GET MODE
    uint8_t mode = 0;
    DS28.getMode(mode);
    Serial.print(F("MODE:\t"));
    Serial.println(mode);

    //  TOGGLE MODE
    if (mode == DS28CM00_I2C_MODE)
    {
      DS28.setSMBusMode();
    }
    else
    {
      DS28.setI2CMode();
    }

    //  CRC GENERATION
    //  TODO VERIFY WHICH CRC  
    //  uint8_t crc8_le(uint8_t crc, uint8_t const *buf, uint32_t len);
    //  uint8_t crc8_be(uint8_t crc, uint8_t const *buf, uint32_t len);

    uint8_t crc = crc8_le(0, uid, 7);
    if (crc == uid[7])
    {
      Serial.println(F("CRC:\tOK"));
    }
    else
    {
      Serial.println(F("CRC:\tFAIL"));
    }

    Serial.println();
  }
}


//  -- END OF FILE --


