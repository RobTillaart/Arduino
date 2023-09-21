//
//    FILE: DS28CM00_getUID.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test DS28CM00 lib
//     URL: https://github.com/RobTillaart/DS28CM00


#include "Wire.h"
#include "DS28CM00.h"

DS28CM00 DS28(&Wire);

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

  //  read different sizes.
  for (uint8_t size = 1; size < 9; size++)
  {
    DS28.getUID(uid, size);
    Serial.print(size);
    Serial.print("\tUID:\t");
    for (uint8_t i = 0; i < size; i++)
    {
      if (uid[i] < 0x10) Serial.print('0');
      Serial.print(uid[i], HEX);
      Serial.print(' ');
    }
    Serial.println();
  }
  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
