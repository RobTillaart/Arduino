//
//    FILE: AGS02MA_UGM3.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: test application
//    DATE: 2021-08-12
//     URL: https://github.com/RobTillaart/AGS02MA
//

#include "AGS02MA.h"


AGS02MA AGS(26);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Wire.begin();
  Wire.setClock(30400);
#if defined(__AVR__)
  Serial.print("TWBR:\t");
  Serial.println(TWBR);
#endif

  Serial.print("AGS02MA_LIB_VERSION: ");
  Serial.println(AGS02MA_LIB_VERSION);
  Serial.println();


  bool b = AGS.begin();
  Serial.print("BEGIN:\t");
  Serial.println(b);

  b = AGS.setUGM3Mode();
  uint8_t m = AGS.getMode();
  Serial.print("MODE:\t");
  Serial.print(b);
  Serial.print("\t");
  Serial.println(m);

  uint8_t version = AGS.getSensorVersion();
  Serial.print("VERS:\t");
  Serial.println(version);

}


void loop()
{
  delay(2000);
  uint32_t value = AGS.readUGM3();
  Serial.print("UGM3:\t");
  Serial.print(value);
  Serial.print("\t");
  Serial.print(AGS.lastStatus(), HEX);
  Serial.print("\t");
  Serial.print(AGS.lastError(), HEX);
  Serial.println();
}


// -- END OF FILE --
