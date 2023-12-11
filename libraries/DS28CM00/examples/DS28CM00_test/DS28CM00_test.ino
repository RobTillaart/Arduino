//
//    FILE: DS28CM00_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test DS28CM00 lib
//    DATE: 2017-07-15
//     URL: https://github.com/RobTillaart/DS28CM00


#include "Wire.h"
#include "DS28CM00.h"

#if defined(ESP32) || defined(ESP8266)
#include "rom/crc.h"        //  ESP32 specific
DS28CM00 DS28(10, 12);      //  ESP32 I2C pins (choice)
#else
#include "util/crc16.h"
DS28CM00 DS28(&Wire);
#endif

uint8_t uid[8];


void setup()
{
  Serial.begin(115200);

  Serial.println(__FILE__);
  Serial.print(F("DS28CM00 library: "));
  Serial.println(DS28CM00_LIB_VERSION);

  Wire.begin();
  Wire.setClock(100000);
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
    // PRINT UID
    Serial.print(F("UID:\t"));
    for (uint8_t i = 0; i < 8; i++)
    {
      if (uid[i] < 0x10) Serial.print('0');
      Serial.print(uid[i], HEX);
      Serial.print(' ');
    }
    Serial.println();

    // GET MODE
    uint8_t mode = 0;
    DS28.getMode(mode);
    Serial.print(F("MODE:\t"));
    Serial.println(mode);

    // TOGGLE MODE
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

#if defined(ESP32) || defined(ESP8266)
    // uint8_t crc8_le(uint8_t crc, uint8_t const *buf, uint32_t len);
    // uint8_t crc8_be(uint8_t crc, uint8_t const *buf, uint32_t len);

    uint8_t crc = crc8_le(0, uid, 7);
#else
    uint8_t crc = 0;
    for (uint8_t i = 0; i < 7; i++)
    {
      crc = _crc_ibutton_update(crc, uid[i]);
    }
#endif
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

