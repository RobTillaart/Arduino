//
//    FILE: DS28CM00_test.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: test DS28CM00 lib
//    DATE: 2017-07-15
//     URL:
//
// Released to the public domain
//

#include <Wire.h>
#include <DS28CM00.h>
#include <util/crc16.h>


uint8_t uid[8];

DS28CM00 DS28;

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

    uint8_t mode = 0;
    DS28.getMode(mode);

    Serial.print(F("MODE:\t"));
    Serial.println(mode);
    if (mode == DS28CM00_I2C_MODE)
    {
      DS28.setSMBusMode();
    }
    else
    {
      DS28.setI2CMode();
    }

    uint8_t crc = 0;
    for (uint8_t i = 0; i < 7; i++)
    {
      crc = _crc_ibutton_update(crc, uid[i]);
    }
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

// END OF FILE